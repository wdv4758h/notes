====================================================================
Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation
====================================================================

這邊的資訊主要來自於 2007 年發的 papaer "Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation"
以及現在 Valgrind 的 source code 和 documentation。


名詞解釋
========================================

* Instrumentation

    在資訊領域中，instrumentation 代表著追蹤程式執行、診斷錯誤、衡量效能的能力

* Dynamic Binary Instrumentation (DBI)

    接續前面說的 instrumentation，DBI 是其中一個子項目，針對的是 binary，而偵測時期在執行期間

* Dynamic Binary Analysis (DBA)

    DBA，如字面上的意思，是針對 binary 在執行期間的分析

* Intermediate Representation (IR)


Introduction
========================================

DBA 常用 DBI 來實作，在執行時把分析的程式碼加到要分析的程式，
這對使用者很方便 (不用重新 compile 或 link)。
然而大部分的 DBI frameworks 都把重點放在 performance 而不是能力，
但是是能力讓這類工具有用的
所以 Valgrind 的開發者認為 DBI 的能耐還沒完全展現出來。

Valgrind 把重點放在 **shadow values** 這概念上，
shadow values 是很強大但相關的研究較少、較難實作的 DBA 技術，
在這概念下需要對所有的 register 和 memory 做 shadow (自己維護一份)，
也因為這 feature 讓 Valgrind 做出來的 lightweight 工具跑的相對慢，
但是 Valgrind 可以做出更多更有趣、更重量級的工具，
這是其他 frameworks 很難做到的 (例如 Pin 或 DynamoRIO)。

shadow value tools 會維護一份程式的狀態，
把原本的程式狀態稱為 S，
那就會存一份 S' 裡面包含 S 的所有值 (例如 register 和 user-mode address)，
而 shadow values 有九種需求要滿足，
九種需求可以依照特性分成四類 (Shadow State、讀寫操作、Allocation/Deallocation、增加輔助資訊)：

* Shadow State
    1. 提供 shadow registers (例如 integer、FP、SIMD)
    2. 提供 shadow memory
        + 並且需要在 multithread 下可以安全地存取 shadow memory
* 讀寫操作
    3. instrument read/write instructions
        + 需要知道每個 instruction 存取了哪些 memory 和 registers
        + 最好能做到跨平台 (跨 ISA)
    4. instrument read/write system calls
        + 所有的 system call 都會去存取 register 或 memory，還可能從 register 或 stack 讀參數，最後寫回 register 或 memory，而且還要注意許多 system call 會存取 user-mode 的 memory (pointer)
* Allocation and deallocation operations
    5. instrument start-up allocations
        + 在程式開始執行時，所有 register 都會被 "allocated"，因為是 statically allocated memory locations，所以 shadow value tool 必須也這些做好 (create suitable shadow values)
        + 對於此時還沒 allocated 的也要處理，可能在 allocated 之前發生不當的存取
    6. instrument system call (de)allocations
        + 一些 system call 會 allocate memory (e.g. brk, mmap)，一些會 deallocate memory (e.g. munmap)，
        + mremap 會讓 memory 被 copy，shadow memory 也要 copy 好
    7. instrument stack (de)allocations
        + 更新 stack pointer
        + 這部份會比較耗時，因為 stack pointer 時常變動，而且有些程式會在多個 stack 之間切換，shadow value tool 會需要把這些 stack allocations 或 deallocations 區分出來，這對於 binary level 來說不容易
    8. instrument heap (de)allocations
        + 大部分的程式會利用來自 library 的 heap allocator，heap allocator 會把用 system call (brk、mmap) 取得的 large chuncks 中的一塊 heap blocks 傳回去給 client，每段 heap block 都有 book-keeping data (例如 block size)，這些是 client program 不應該存取的 (讀可能還安全，寫的話可能會 crash allocator)，所以有 kernel-level addressability 之上蓋了一層 library-level addressability 的概念
        + 忽略 large chuncks 的 kernel-level allocations
        + 直到 allocator 把 allocated 的 bytes 轉交給 client 之前都不把 memory 當作 active
        + realloc 也要像 mremap 一樣被處理
* Transparent execution, but with extra output
    9. extra output
        + 不影響執行，產生有幫助的 output
        + 另外開個地方來 output，例如沒在用的 stderr 或 file


核心概念就是 registers 和 memory 中的東西都要自己做一份，
而且要把自己那份跟原本的區分開來，
並且確保可以安全地在各個情況下使用 (例如 multithread)。
接著是執行的操作都要紀錄到，
掌控所有的使用 (讀寫)。

shadow value tool 為 heavyweight 的 DBA tools 可以滿足這九種需求，
然而大部份的 DBA tools 都只做到了九種需求的 subset (通常都包含最後增加輔助資訊的需求)。


Valgrind 運作方式
========================================

基本架構
------------------------------

Valgrind 會利用 dynamic binary re-compilation，
先把 client 程式讀到和 Valgrind 同個 process，
接著把 client machine code 分成一小塊一小塊，
依 execution-driven 的方式用 just-in-time 得技術把 machine code block 轉成 VEX IR (RISC-like)。
VEX IR 是 Valgrind 開發者設計來給 DBI 使用的 IR，
目前這部份已經從 Valgrind 分離出去成 libVEX 了，
libVEX 負責動態地把 machine code 轉換成 VEX IR，
並且去 call 要做 IR instrumentation 的工具的 hooks，
而轉換的結果會存在 code cache，再需要時會重新 run 過。

Valgrind 的核心花費大部分的時間在製造、尋找、執行 machine code 和 VEX IR 的轉換，
而 client program 原本的 machine code 都不會跑到。

到這邊可以看到 Valgrind 的複雜來自於要把 client 和 tool 壓在同一個 process，
需要用分享的資源 (例如 registers 和 memory)，
而且 Valgrind 要小心地確保在 system call、signals、threads 參與的狀況下不會對 client 失去掌控。


Valgrind 可以正常處理的程式有：

* normal executable code
* dynamically linked libraries
* shared libraries
* dynamically generated code

只有 self-modifying code 會有問題，
而執行過程中只有 system calls 裡面的狀況是 Valgrind 不能掌控的，
但是 system call 的 side-effects 還是可以間接觀察到。

::

    　                                    +--------------------+     +-------------------------+
                  +--------------+        |      libVEX        |     | IR instrumentation tool |
                  |              |        |                    |     |                         |
                  +--------------+        |                    |     |                         |
                  |              | -----+ |                    |     |                         |
                  +--------------+      | |                    |     |                         |
                  |              |      | |      +--------+    |     |                         |
    x86/Linux     +--------------+      +------> |        | -------->|                         |
    AMD64/Linux   | machine code | ------------> | VEX IR |    |     |                         |
    ARM/Linux     +--------------+      +------> |   --------------- |                         |
    x86/MacOSX    |              |      | |      +---|----+    |     |                         |
    AMD64/MacOSX  +--------------+      | |          |         |     |                         |
    ....          |              | -----+ |          |         |     |                         |
                  +--------------+        |          |         |     |                         |
                  |              |        +----------|---------+     +-------------------------+
                  +--------------+                   |
                                                     v
                                             +--------------+
                                             | machine code |
                                             +--------------+

Starting Up
------------------------------

start up 這部份的目的是要把 Valgrind 的 core、tool、clent program 都 load 到同一個 process，
共用 address space。
Valgrind tool 都是包含 core code 的 statically-linked executable，
每個 tool 都包含一份 core code 有一點點浪費空間 (2007 年的時候 core 大約 2.5 MB)，
但是可以讓事情簡單一些。

client 程式 (執行檔) 會被 load 到一個通常是可用的 non-standard address，
在 x86/Linux 中這個位址是 0x38000000 (各平台的位址可以看 Valgrind 的 configure.ac)，
0x38000000 在 1GB 之下 (1024 * 1024 * 1024 bytes => 0x40000000)，
所以就算有個用 1:3 來切割 user:kernel address space 的 kernel 也可以 work，
精確地位址是不固定的，重點是要避開一般預設的程式 load address，
同時確保 loader 可以在 1GB 以下被 load。
如果 Valgrind 要用的 address 不是可用的 (極少數特殊情況)，
Valgrind 可以重新 compile 來使用不同的 address。

使用者用的 ``valgrind`` command 其實只是個 wrapper (wrapper 的 source code 為 repo 裡的 ``coregrind/launcher-linux.c``)，
這個 wrapper 會去爬 ``--tool`` 參數來決定要執行的 plugin，
每個 plugin 都是一個靜態連結的執行檔，
plugin 都放在 ``/usr/lib/valgrind/`` 裡面 (on Arch Linux)，
wrapper 會設定一些環境變數後用 ``execve`` 執行指定的 plugin。

Valgrind core 一開始會初始化一些 sub-systems (例如 address space manager、internal memory allocator)，
接著才 load 進來 cliet 程式 (text、data)，
client 程式可以是 ELF 執行檔或是 script (如果是 script 的話會讀入 interpreter)，
接下來建立 client 的 stack 和 data segment。

在這之後 Valgrind core 會要 tool 初始化自己，
core 和 tool 的 command-line 參數會在這時被處理。
core sub-system 初始化，
包含 translation table、signal-handling machinery、thread scheduler、debug information。

至此 Valgrind tool 已經取得所有的掌控權，
所有東西都已經就定位可以開始轉換並執行 client 程式了。

這個 Valgrind 架構和初始化方式其實是第三版了，
是目前最 reliable 的方式。
第一版為使用 dynamic linker 的 LD_PRELOAD 把 Valgrind core 和 tool (都是 shared object) inject 到 client，
但是這對 statically compiled executables 不管用，
也允許一部份的 client 程式在 Valgrind 掌控外先 native 地執行，
在加上這作法也不 portable。
第二版和現在的方式比較像，
但是需要一大塊空的 memory mappings 來讓 components 放到對的位置，
這作法比較 unreliable。
大部分的 DBI frameworks 都是使用第一種 injection 的方式，
而不是使用自己的 program loader。
為了避免前面兩種作法的缺點，
第三種作法有額外的兩種優點，
一是讓 Valgrind 可以掌控 memory layout，
二是讓避免對其他工具的依賴 (例如 dynamic linker)，
這是增加 Valgrind 強健性的好方式。


Guest and Host Registers
------------------------------

Valgrind 本身會直接跑在 host CPU，
而 client 程式則是概念性地跑在 Valgrind 弄出來的 guest CPU，
因為 dynamic binary recompilation 的關係 guest register 的值可能是在一個 host register 或是散佈在 memory 中，
而每個 guest register 都會有 shadow register。

Valgrind 會提供每個 client thread 一塊 memory (稱為 ThreadState)，
每個 ThreadState 包含給 thread 的 guest 和 shadow registers 的空間，
會在許多時間點維護這些值 (例如每個 code block 之間)。
這樣儲存 guest registers 的話就會需要不斷地把值在 host registers 和 memory 中移來移去，
效能顯然會在這邊降低，
但是作為一個 heavyweight 的工具，
這樣的作法卻是非常合理的。

Representation of code: D&R vs. C&A
-----------------------------------

DBI framework 有兩種基本的方式可以表示 code 和進行的 instrumentation：

* disassemble-and-resynthesise (D&R)
    - Valgrind 使用這種
    - 把 machine code 先轉成 IR
    - IR 會經由加入更多 IR 來被 instrument
    - IR 最後轉回 machine code 執行
    - 原本的 code 對 guest state 的所有影響都必須明確地轉成 IR，因為最後執行的是純粹由 IR 轉成的 machine code
* copy-and-annotate (C&A)
    - instructions 會逐字地複製 (除了一些 control flow 改變)
    - 每個 instruction 都加上註解描述影響 (annotate)，利用這些描述來幫助 instrumentation
        + 經由 data structures (DynamoRIO)
        + 經由 instruction-querying API (Pin)
    - 加入的分析 code 必須和原 code 錯開，不能影響原本的行為

基本上 DBI framework 可以分成這兩種，
但是混用是可以做到的，
早期的 Valgrind 對 interger instructions 使用 D&R，
而對 floating point insturctions 和 SIMD 使用 C&A (paper 上寫說並非設計想往這邊走，而是意外)。
另外，做一些變化也是可以的，例如 DynamoRIO 允許 instructions 在複製前 in-place 地修改，

各個設計都有優缺點，而 D&R 的方式需要更多的實作和設計，
而且最後從 IR 生出有效率地 machine code 也需要一些努力，
Valgrind JIT 就用了很多編譯器的技術。相對地，C&A 的作法就可以比 D&R 少費些心力。

D&R 對於需要 low-level 資訊的狀況來說比較不適合，
例如每個 instruction 使用哪個 opcode 這樣的資訊可能會 lost，
但是 IR 註解可以幫忙處理這樣的事情，
例如 Valgrind 有 "marker" statement 可以標註原本 instruction 的 boundaries、addresses、length，
而且 C&R 如果 annotations 能力不夠的話也會有同樣的問題。

D&R 的威力會在需要加入複雜的 analysis code 的時候顯現，
首先 D&R 的 client 和 analysis code 都會使用一樣的 IR，
所以可以保證 analysis code 和 client code 有同樣的程度的能力，
再來把所有 side-effect 都明確地表示出來可以讓 instrumentation 變簡單。
接著是 JIT 可以讓 analysis code 和 client code 取得同樣好的優化，
並且原生地把兩個 code 交錯開來，
而 C&A 則需要提供個方式來描述 analysis code，
C&A 的 analysis code 要能有效率且安全地放進去反而需要額外的功夫 (framework 和 tool)，
例如 Pin 的 analysis code 是用 C 寫，
用外部的 C compiler 編譯，
Pin 則嘗試 inline 進去或是插入 function call。

最後，D&R 比較容易驗證，
任何 IR 轉換錯誤的行為都會很明顯，
而 C&A 的 annotations 有錯的話只會造成不正確地分析。
D&R 還允許 binary 從一個平台轉到另個平台 (雖然 Valgrind 沒有做)。

總結就是 D&R 需要比較多的力氣來實作，
支援 heavyweight instrumentation (需要 shadow value tools)，
但對於 ightweight instrumentation 來說算是 overkill。

Valgrind IR
------------------------------

在 Valgrind 3.0.0 之前 (2005 年 8 月)，
Valgrind 有針對 x86 的部份 D&R、部份 C&A，
以及像 assembly 的 IR (translation 單位為 basic block)。
在那之後，Valgrind 有了完整的 D&R 和 SSA (single-static-assignment) IR (像是 compiler 在用的 IR)。
IR blocks 也變成 superblocks (為 single-entry, multiple-exit)。


VEX IR
========================================

* https://github.com/svn2github/valgrind-vex/blob/master/pub/libvex_ir.h
* https://android.googlesource.com/platform/external/valgrind/+/master/VEX/pub/libvex_ir.h

Suppression
========================================

Valgrind 裝起來後預設會拿到一個 ``default.supp`` 在 ``/usr/lib/valgrind/default.supp`` ，
這類以 ``.supp`` 副檔名結尾的檔案稱為 "Suppression Files"，
目的是要把 Valgrind 的 False Positive 的判斷給壓下來，
讓輸出的結果更乾淨、好辨識問題。

* `Servo - Debugging <https://github.com/servo/servo/wiki/Debugging>`_


Reference
========================================

* `[2007] Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation <http://valgrind.org/docs/valgrind2007.pdf>`_
* `[2008] Optimizing Binary Code Produced by Valgrind <http://web.ist.utl.pt/nuno.lopes/pubs/valgrind08.pdf>`_
* svn://svn.valgrind.org/vex/trunk
* `libVEX - /pub/libvex_ir.h <https://github.com/svn2github/valgrind-vex/blob/master/pub/libvex_ir.h>`_
* `Valgrind - /configure.ac <https://github.com/svn2github/valgrind-master-mirror/blob/master/configure.ac>`_
    - valt_load_address_pri_norml
    - valt_load_address_pri_inner
* `How does valgrind work? <http://stackoverflow.com/a/27380829>`_
* `[2002] The design and implementation of Valgrind <http://courses.cs.washington.edu/courses/cse326/05wi/valgrind-doc/mc_techdocs.html>`_
* `Notes on Valgrind <http://publicclu2.blogspot.tw/2013/05/notes-on-valgrind.html>`_


Idea
========================================

* Ahead-of-time Valgrind
* LLVM IR to VEX IR
* LLVM JIT for VEX
* Multithread for Valgrind Tools
* Valgrind with STM
* https://archive.fosdem.org/2014/schedule/event/valgrind_bof/
