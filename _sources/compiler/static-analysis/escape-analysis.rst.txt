========================================
Escape Analysis
========================================

Introduction
========================================

Escape Analysis 是 Static Analysis 裡的一個分支，
用來找出 pointer 可以被存取的 scope。

Escape Analysis 的結果可以用於 Compiler Optimizations，
例如：

* 把 Heap Allocations 換成 Stack Allocations：如果 object 是在一個 subroutine 被 allocated 的，而且只用於這個 subroutine

* 減少 Synchronization：如果 object 只會在一個 thread 裡被用到的話，就不需要做 Synchronization



現況
========================================

[2015-07-05]

* RPython Toolchain 有做 Escape Analysis 來減少 Heap Allocations，但是因為使用上效果沒有很顯著，所以目前是拿掉的
* Pyston 裡面也有接 LLVM 做 Escape Analysis
* Go 官方的 compiler 有支援 Escape Analysis，並且有好幾項測試
* llgo 也有做 Escape Analysis，裡面也是接 LLVM (llgo : Go frontend for LLVM)，根據 repo 上的說明，對於 libgo benchmark 大約會獲得 5.4% 的 performance 改進
* Nuitka 好像有要做？(不確定狀況) (Nuitka 為 Python to C++ compiler)
    - `An optimizing static Python compiler <https://ep2013.europython.eu/conference/talks/an-optimizing-static-python-compiler>`_
* Rust 好像有支援？(不確定狀況)
    - `Rust - Escape analysis <https://github.com/rust-lang/rust/issues/240>`_
* Java Hotspot 有支援 (從 Java SE 6u23 開始預設開啟)
* Julia 也有 Escape Analysis


Reference
========================================

* `Wikipedia - Escape Analysis <https://en.wikipedia.org/wiki/Escape_analysis>`_
* `The RPython Toolchain - Escape Analysis and Stack Allocation <https://rpython.readthedocs.org/en/latest/translation.html#escape-analysis-and-stack-allocation>`_
* `Escape Analysis in PyPy's JIT <http://morepypy.blogspot.tw/2010/09/escape-analysis-in-pypys-jit.html>`_
* `Using Escape Analysis Across Loop Boundaries for Specialization <http://morepypy.blogspot.tw/2010/09/using-escape-analysis-across-loop.html>`_
* `Pyston - Escape Analysis <https://github.com/dropbox/pyston/blob/master/src/codegen/opt/escape_analysis.cpp>`_
* `llgo - esc.go <https://github.com/go-llvm/llgo/blob/master/ssaopt/esc.go>`_
* `Java HotSpot - Escape Analysis <https://docs.oracle.com/javase/8/docs/technotes/guides/vm/performance-enhancements-7.html#escapeAnalysis>`_
* `Graal Partial Escape Analysis <https://wiki.openjdk.java.net/display/Graal/Graal+Partial+Escape+Analysis>`_
* `Escape Analysis in Go <https://scvalex.net/posts/29/>`_
* `Google Code - Go - esc.c <https://code.google.com/p/go/source/browse/src/cmd/gc/esc.c>`_
* `Go - esc.go <https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/esc.go>`_
* `Go - lex.go <https://github.com/golang/go/blob/master/src/cmd/compile/internal/gc/lex.go>`_
* `LuaJIT - Allocation Sinking Optimization <http://wiki.luajit.org/Allocation-Sinking-Optimization>`_
* `Using LLVM For Program Transformation <http://www.cs.umd.edu/~awruef/LLVM_Tutorial.pdf>`_
* `[LLVM][2014] Pyston: a Python JIT on LLVM <http://article.gmane.org/gmane.comp.compilers.llvm.devel/71870>`_
* `Runa - escapes.py <https://github.com/djc/runa/blob/master/runac/escapes.py>`_
* `Julia - codegen.cpp <https://github.com/JuliaLang/julia/blob/fd25bf9cf40bf6ecc97356cbe567c449059651c4/src/codegen.cpp#L1572>`_
* `Detecting Data Races using Dynamic Escape Analysis based on Read Barrier <https://www.usenix.org/legacy/publications/library/proceedings/vm04/tech/full_papers/nishiyama/nishiyama_html/index.html>`_
* `Patrick Lioi - Escape Analysis <http://patrick.lioi.net/2012/03/16/escape-analysis/>`_
* `V8 - hydrogen-escape-analysis.cc <https://code.google.com/p/v8/source/browse/branches/bleeding_edge/src/hydrogen-escape-analysis.cc>`_
