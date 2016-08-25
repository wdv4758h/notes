========================================
JIT
========================================

.. contents:: 目錄


Case Study
========================================

McCarthy's LISP
------------------------------

Thompson's regex
------------------------------

LuaJIT
------------------------------

Smalltalk
------------------------------


Regular Expression History
========================================

以下的內容翻譯、修改自
`Regular Expressions – a brief history <http://blog.staffannoteberg.com/2013/01/30/regular-expressions-a-brief-history/>`_


Regular Expression 的概念最早發展自神經科學家和邏輯學家合作，
嘗試了解人類大腦如何用簡單的細胞來產生出複雜的模式。

在 1943 年時，Warren McCulloch (神經科學家) 和 Walter Pitts (邏輯學家)
在 Bulletin of Mathematical Biophysics  5:115-133 發布了
「A logical calculus of the ideas immanent in nervous activity」，
這篇論文對於後來的資訊領域有很大的影響 (雖然這不是這論文本來的目標)。

在 1956 年時，Stephen Kleene (數學家) 改進這個模型，
在「Representation of events in nerve nets and finite automata」中
他用簡單的代數學作為表示 (只有兩個 operations 和一個 function)，
此時「Regular Sets」和「Regular Expressions」這兩個詞就誕生了。

在 1968 年時，
Ken Thompson 在 Communications of the ACM (CACM) Volume 11
發表了「Regular Expression Search Algorithm」，
其中描述了一個可以把 Regular Expression 轉成 IBM 7094 object code 的編譯器。
而在那之後 Ken Thompson 還把 Kleene 的標記法實作在 ``QED`` 這個編輯器中，
如此一來使用者可以對文件做複雜的 pattern matching，
這個功能後來也被實作在 ``ed`` 編輯器中。

在 ``ed`` 中，
如果想要搜尋 Regular Expression 要寫成 ``g/<regular expression>/p`` ，
其中 ``g`` 代表全域搜尋、 ``p`` 代表輸出結果。
這指令 ``g/re/p`` 也就成為後來 ``grep`` 指令的來源，
``grep`` 最早釋出於 1973 年的 Unix v4 (但已經使用許久)，
但是當時並沒有實作完整的 Regular Expression。
直到 1979 年釋出的 Unix v6 中
Alfred Aho 的 ``egrep`` (extended grep) 才有更完整的支援，
``egrep`` 會把所有收到的 Regular Expression 轉成對應的 DFA 來執行。

1987 年，Larry Wall 發明 Perl 程式語言，
其中 Regular Expression 的整合讓 Regular Expressions 更加廣為使用。
後來更多的功能加進了 Regular Expressions，
Perl 也增加了抽象化跟語法糖，
其中有些功能甚至不能用 Finite Automata 完成，
這樣的發展產生了一個問題，
「現代的 Regular Expressions」還能叫作「Regular Expressions」嗎？
「現代的 Regular Expressions」 不只包含 Kleene 的代數表示，
還包含後續各程式語言實作上加入的功能 (例如 Perl)。

現今 Linux 系統上常見的 grep 指令通常為 GNU grep，
是由 Mike Haerkal 撰寫，於 1988 年釋出第一版
(在 1987 年的「GNU's Bulletin」第二版就有提及)。


人物：

* `Warren McCulloch (神經科學家) <https://en.wikipedia.org/wiki/Warren_Sturgis_McCulloch>`_
* `Walter Pitts (邏輯學家) <https://en.wikipedia.org/wiki/Walter_Pitts>`_
* `Stephen Kleene (數學家) <https://en.wikipedia.org/wiki/Stephen_Cole_Kleene>`_
* `Ken Thompson <https://en.wikipedia.org/wiki/Ken_Thompson>`_
* `Alfred Aho <https://en.wikipedia.org/wiki/Alfred_Aho>`_
    - `Columbia - Alfred V. Aho <http://www.cs.columbia.edu/~aho/>`_
* `Larry Wall <https://en.wikipedia.org/wiki/Larry_Wall>`_
* Mike Haerkal

相關文章：

* `Regular Expressions – a brief history <http://blog.staffannoteberg.com/2013/01/30/regular-expressions-a-brief-history/>`_
* `“grep was a private command of mine for quite a while before i made it public.” -Ken Thompson <https://medium.com/@rualthanzauva/grep-was-a-private-command-of-mine-for-quite-a-while-before-i-made-it-public-ken-thompson-a40e24a5ef48#.4gu6lehr7>`_
* `Mike Haertel - why GNU grep is fast <http://lists.freebsd.org/pipermail/freebsd-current/2010-August/019310.html>`_


Implementation
========================================

* DynASM
    - http://luajit.org/dynasm.html
    - The Unofficial DynASM Documentation : https://corsix.github.io/dynasm-doc/
* `GCC - libgccjit <https://gcc.gnu.org/onlinedocs/jit/>`_
* `LLVM - MCJIT <http://llvm.org/docs/MCJITDesignAndImplementation.html>`_
* PyPy
* `AsmJit <https://github.com/kobalicek/asmjit>`_
* `LibJIT <https://www.gnu.org/software/libjit/>`_


Bindings
========================================

* `Python bindings for libgccjit <https://github.com/davidmalcolm/pygccjit>`_


FAQ
========================================

「什麼是 JIT ？ JIT 的目的是什麼？」

    JIT 指的是動態編譯的技術，也就是在程式執行期間去產生出新的程式碼來執行。
    而 JIT 的目的是要透過執行時期的資訊來編出優化品質更好的程式碼來提升效能。



「JIT 可以哪些額外的資訊？」

    JIT 可以透過執行時的 profiling 獲得的資訊包含：

    * 函數是否被大量使用
    * 函數的參數是否一直都是同一個值



「為什麼 JIT 可以提升效能？」

    這邊提升效能的重點是程式編譯出來的品質。

    對動態語言來說，
    JIT 可以針對型別做優化，例如原本 ``add(x, y)`` 可以接受各式的資料，
    每次執行時判斷 x 和 y 的型別來決定操作，
    假設現在執行過程中 x 和 y 都一直是整數，
    那這時 JIT 可以編成 ``add_int_int(x: int, y: int)`` 的形式，
    如此一來就可以達到效能的提升。



「JIT 常見的優點和缺點各是什麼？」

    優點

    * 實作良好的話可以大幅提升效能

    缺點

    * 複雜度比單純的直譯器高，還需要對不同的平台實作 JIT 後端，需要更多的人力 (財力) 投入



「JIT 和 AOT 的比較？」

    編譯器 (AOT)：

        準備： ::

            ＋－－－－－＋　　＋－－－－－＋　　＋－－－＋　　＋－－－＋
            ｜撰寫程式碼｜－＞｜輸入程式碼｜－＞｜編譯器｜－＞｜執行檔｜
            ＋－－－－－＋　　＋－－－－－＋　　＋－－－＋　　＋－－－＋

        使用： ::

            ＋－－－－－＋　　＋－－＋　　＋－－－－＋
            ｜輸入執行檔｜－＞｜執行｜－＞｜執行結果｜
            ＋－－－－－＋　　＋－－＋　　＋－－－－＋

    普通直譯器：

        準備： ::

            ＋－－－－－＋
            ｜撰寫程式碼｜
            ＋－－－－－＋

        使用： ::

            ＋－－－－－＋　　＋－－－－－－－－－－＋　　＋－－－－＋
            ｜輸入程式碼｜－＞｜直譯器（轉譯且執行）｜－＞｜執行結果｜
            ＋－－－－－＋　　＋－－－－－－－－－－＋　　＋－－－－＋

    有 JIT 的直譯器：

        準備： ::

            ＋－－－－－＋
            ｜撰寫程式碼｜
            ＋－－－－－＋

        使用： ::

            ＋－－－－－＋　　＋－－－－－－－－－－＋　　＋－－－－＋
            ｜輸入程式碼｜－＞｜直譯器（轉譯且執行）｜－＞｜執行結果｜
            ＋－－－－－＋　　＋－－－－－－－－－－＋　　＋－－－－＋
            　　　　　　　　　　　　　｜　　　　　　　　　　　︿
            　　　　　　　　　　　　　ｖ　　　　　　　　　　　｜
            　　　　　　　　　　　＋－－－＋　　　　　　　　　｜
            　　　　　　　　　　　｜編譯器｜　　　　　　　　　｜
            　　　　　　　　　　　＋－－－＋　　　　　　　　　｜
            　　　　　　　　　　　　　｜　　　　　　　　　　　｜
            　　　　　　　　　　　　　ｖ　　　　　　　　　　　｜
            　　　　　　　　　　　＋－－－＋　　　　　　　　　｜
            　　　　　　　　　　　｜機械碼｜－－－－－－－－－＋
            　　　　　　　　　　　＋－－－＋



「為什麼 JIT 可以提升效能但是很多語言一開始卻不實作 JIT ？」

    相比 JIT，一般直譯器的實作比較容易，
    在時間跟金錢成本的衡量下可能會先選擇不實作 JIT。



「JIT 現今的實作種類有哪些？」

    1. Tracing-based JIT

        * [Lua] LuaJIT
        * [Python] PyPy
        * [Erlang] BEAMJIT
        * ...

    2. Method-based JIT

        * [JavaScript] V8
        * [JavaScript] SpiderMonkey
        * ...



「現今有哪些可以重複利用的 JIT Framework？」

    * Truffle/Graal
    * RPython Toolchain


「實作 JIT 會需要的功能？」

    取得記憶體空間 (mmap)

        .. code-block:: cpp

            #include <sys/mman.h>

            // $ man 2 mmap
            //
            // void *mmap(void *addr, size_t length,
            //            int prot, int flags,
            //            int fd, off_t offset);
            //
            // int munmap(void *addr, size_t length);
            //
            // If addr is not NULL, then the kernel takes it as a hint about where  to place the mapping

            ptr = mmap(addr,
                       len,
                       PROT_READ | PROT_WRITE,      // protection
                       MAP_PRIVATE | MAP_ANONYMOUS, // flags
                       -1,  // fd
                       0);  // offset

        * `POSIX - mmap <http://pubs.opengroup.org/onlinepubs/9699919799/functions/mmap.html>`_
        * `Linux 實作 - /mm/mmap.c <http://lxr.free-electrons.com/source/mm/mmap.c>`_
        * `FreeBSD 實作 - /contrib/netbsd-tests/lib/libc/sys/t_mmap.c <https://github.com/freebsd/freebsd/blob/master/contrib/netbsd-tests/lib/libc/sys/t_mmap.c>`_

    更改記憶體屬性 (mprotect)

        .. code-block:: cpp

            #include <sys/mman.h>

            // int mprotect(void *addr, size_t len, int prot);

            mprotect(addr, len, PROT_READ | PROT_EXEC);     // 可讀可執行
            mprotect(addr, len, PROT_READ | PROT_WRITE);    // 可讀可寫

        * `POSIX - mprotect <http://pubs.opengroup.org/onlinepubs/9699919799/functions/mprotect.html>`_
        * `Linux 實作 - /mm/mprotect.c <http://lxr.free-electrons.com/source/mm/mprotect.c>`_
        * `FreeBSD 實作 - /contrib/netbsd-tests/lib/libc/sys/t_mprotect.c <https://github.com/freebsd/freebsd/blob/master/contrib/netbsd-tests/lib/libc/sys/t_mprotect.c>`_


        * `Linux 實作 - /include/linux/mm_types.h <http://lxr.free-electrons.com/source/include/linux/mm_types.h>`_

            .. code-block:: c

                struct vm_area_struct {

                    ...

                    pgprot_t vm_page_prot;      /* Access permissions of this VMA. */
                    unsigned long vm_flags;     /* Flags, see mm.h. */

                    ...

                }



「為什麼使用 mmap 而不是用 malloc ?」

    malloc 提供的的確是 RW 的記憶體，
    我們也的確可以拿來使用於 JIT，
    不過記憶體的 protection bits 只能在 virtual memory page 的邊界設定，
    所以如果我們使用 malloc 的話，
    我們要自己手動確認分配到的記憶體有對齊到 page boundary，
    否則 mprotect 可能因為無法正確地更改記憶體屬性而產生不預期的行為，
    然而 mmap 保證只會分配到 page boundary (mmap 會拿整個 page)。



「有用到 JIT 技術的知名專案？」

    * [VEX IR] Valgrind
    * [Python] PyPy
    * [Lua] LuaJIT
    * [JavaScript] V8
    * [JavaScript] SpiderMonkey
    * [PCRE] sljit
    * [Octave] GNU Octave (JIT 基於 LLVM)

        https://www.gnu.org/software/octave/doc/v4.0.1/JIT-Compiler.html#JIT-Compiler

        JIT works by converting Octave's AST to the LLVM Internal Representation (IR)

    * [Julia] Julia (JIT 基於 LLVM)

    * Ravi
    * ...



「用於 PyPy 的 RPython Toolchain 實作了些什麼？」

    RPython Toolchain 是一個動態語言的直譯器 Framework，
    使用叫作 RPython (Restricted Python) 的語言 (Python 的子集合) 來實作直譯器，
    Toolchain 會在分析後幫忙產生 JIT 以及 GC，
    目前主要在使用的 backend 是 GenC，
    用於產生 C code 後再交給 GCC 或 Clang 編譯程執行檔。

    * `RPython's documentation <https://rpython.readthedocs.org/en/latest/index.html>`_



「RPython Toolchain 的優點和缺點？」

    優點：

    * 和使用 C 或 C++ 相比，用 RPython 開發寫起來比較輕鬆
    * 可以簡單地獲得 JIT 支援
    * 可以簡單地獲得 incremental generational mark-and-sweep GC 支援
    * 未來只要更新 RPython Toolchain 即可獲得新功能或效能提升
    * RPython Toolchain 有支援的 backend 就可以在其之上產生直譯器 (例如 JVM)

    缺點：

    * 要注意 RPython 的限制，雖然有文件，但還是可能碰到文件沒寫的問題
    * RPython Toolchain 在分析、產生 JIT 的過程過於緩慢、消耗資源
    * 支援平台受到 Toolchain 限制
    * Debug 方式會變得複雜一些



Brainfuck
========================================

DynASM
------------------------------

編譯 & 連結
++++++++++++++++++++

.. code-block:: sh

    # Write Your Code
    mkdir src
    wget https://github.com/corsix/dynasm-doc/raw/gh-pages/bf_dynasm.c -O src/myprogram.c

    # Get DynASM
    git clone http://luajit.org/git/luajit-2.0.git

    mkdir -p build
    cd build

    # Build minimal Lua interpreter
    clang -std=c11 -lm ../luajit-2.0/src/host/minilua.c -o minilua

    # run the DynASM preprocessor
    ./minilua ../luajit-2.0/dynasm/dynasm.lua -D X64 -o myprogram.posix64.c ../src/myprogram.c

	# use -D_DEFAULT_SOURCE for "MAP_ANONYMOUS"
    clang -std=c11 -D_DEFAULT_SOURCE -I ../ myprogram.posix64.c -o myprogram

    # Run !!!
	wget https://github.com/corsix/dynasm-doc/raw/gh-pages/mandelbrot.bf
    ./myprogram mandelbrot.bf



asmjit
------------------------------

編譯 & 連結
++++++++++++++++++++

.. code-block:: sh

    # Build asmjit
    git clone https://github.com/kobalicek/asmjit/
    mkdir -p asmjit/build/
    cd asmjit/build
    cmake ../
    make -j
    cd ../../
    mkdir -p build/lib
    cp asmjit/build/libasmjit.so build/lib/

    # Write Your Program
    mkdir -p src
    edit src/myprogram.cpp  # write your code here !

    # Build Your Program
    cd build
    clang++ -std=c++14 ../src/myprogram.cpp -I ../asmjit/src/ -L ./lib/ -l asmjit -o myprogram

    # Run !!!
    LD_PRELOAD=./lib/libasmjit.so ./myprogram


LLVM - MCJIT
------------------------------


LLVM - ORC (On Request Compilation) JIT
---------------------------------------


libgccjit
------------------------------


B3 JIT
------------------------------


libjit
------------------------------



Papers
========================================

* [2015] `A Tracing JIT Compiler for Erlang Using LLVM <https://lup.lub.lu.se/student-papers/search/publication/5470892>`_
* [2015] `The Impact of Meta-Tracing on VM Design and Implementation <http://tratt.net/laurie/research/pubs/papers/bolz_tratt__the_impact_of_metatracing_on_vm_design_and_implementation.pdf>`_
* [2015] `Pycket: A Tracing JIT For a Functional Language <http://homes.soic.indiana.edu/samth/pycket-draft.pdf>`_
* [2010] `High performance implementation of Python for CLI/.NET with JIT compiler generation for dynamic languages <http://buildbot.pypy.org/misc/antocuni-thesis.pdf>`_
* [2003] `A Brief History of Just-In-Time <http://dl.acm.org/citation.cfm?id=857077>`_


Blogs & Sites & Slides
========================================

Blogs

* `Carl Friedrich Bolz <http://cfbolz.de/>`_
* `Laurence Tratt <http://tratt.net/laurie/>`_
* `Cristian Esquivias - Writing a Language in Truffle <https://cesquivias.github.io/tags/truffle.html>`_
* `Hello, JIT World: The Joy of Simple JITs <http://blog.reverberate.org/2012/12/hello-jit-world-joy-of-simple-jits.html>`_


Sites

* `Software Developer Team <http://soft-dev.org/>`_


Slides

* `BEAMJIT: An LLVM based just-in-time compiler for Erlang <http://llvm.org/devmtg/2014-04/PDFs/Talks/drejhammar.pdf>`_


Reference
========================================

* `How to JIT - an introduction <http://eli.thegreenplace.net/2013/11/05/how-to-jit-an-introduction>`_
* `A Just-in-time Compiler In Rust <http://www.hydrocodedesign.com/2014/01/17/jit-just-in-time-compiler-rust/>`_
* [2003] A Brief History of Just-In-Time
* [1968] Ken Thompson - Programming Techniques: Regular expression search algorithm
* [1987] Rob Pike - Structural Regular Expressions


Mailing List
========================================

* `libgccjit - mailing list archives <https://gcc.gnu.org/ml/jit/>`_
* `LLVM - llvm-dev archives <http://lists.llvm.org/pipermail/llvm-dev/>`_
