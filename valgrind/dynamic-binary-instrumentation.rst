===========================================================================
[2007] Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation
===========================================================================

名詞解釋
========================================

* Instrumentation

    在資訊領域中，instrumentation 代表著追蹤程式執行、診斷錯誤、衡量效能的能力

* Dynamic Binary Instrumentation (DBI)

    接續前面說的 instrumentation，DBI 是其中一個子項目，針對的是 binary，而偵測時期在執行期間

* Dynamic Binary Analysis (DBA)

    DBA，如字面上的意思，是針對 binary 在執行期間的分析


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


Reference
========================================

* `[2007] Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation <http://valgrind.org/docs/valgrind2007.pdf>`_
