:title: [JCConf] OpenJDK vs. Dalvik/ART virtual machine
:slug: openjdk-vs-dalvik-and-art-vm
:date: 2014-12-01 02:38
:modified: 2014-12-01 02:38
:category: Misc
:tags: Java, OpenJDK, Dalvik, ART, VM
:author: wdv4758h
:summary: 觀看 JCConf 裡 OpenJDK vs. Dalvik/ART virtual machine 的紀錄

`JCConf 官網連結 (有 Video) <http://jcconf.tw/openjdk-vs-dalvik.html>`_

Preface
========================================

這裡不提

- JVM tuning
- JNI, GC, invokedynamic
- Production tweaking
- Android Programming

Content
========================================

::

                                                       +----------------+
                                                       | CLDC-HI (Java) |
                                                       +----------------+
                                                               ^
                                                               |
    +----------------+  +---------------------------+  +-------------------+
    | Self VM (Self) |->| Strongtalk VM (Smalltalk) |->| HotSpot VM (Java) |
    +----------------+  +---------------------------+  +-------------------+
            |                          |
            |                          |
            |                          |
            |                          |
            |                          |
            |                          |
            |                          |                 +-----------------+
            |                          --------------->  | V8 (Javascript) |
            ------------------------------------------>  +-----------------+




JIT
------------------------------

- Compiled when needed

Mixed-Mode
------------------------------

- Interpreted
    * Bytecode-walking
    * Artificial stack machine

- Compiled
    * Direct native operations
    * Native register machine

Profiling
------------------------------

- Gather data about code while interpreting
    * Invariants (types, constants, nulls)
    * Statistics (branches, calls)

Optimizations
------------------------------

- Method inlining
- Loop unrolling
- Lock coarsening/eliding
- Dead code elimination
- Duplicate code elimination
- `Escape analysis <http://en.wikipedia.org/wiki/Escape_analysis>`_

Hotspot
------------------------------

- client mode (C1) inlines, less aggressive
    * Fewer opportunities to optimize

- server mode (C2) inlines aggressively
    * Based on richer runtime profiling
    * Profile until 10k calls

- Tiered
    * Level 0 = Interpreter
    * Level 1~3 = C1
    * Level 4 = C2

from Interpreter to Compiler
------------------------------

- Bytecode interpreter
    * switch-threading
    * indirect-threading
    * token-threading
    * ...

Summary : OpenJDK
----------------------------------------

Introduction to Dalvik VM
----------------------------------------

- 因為硬體限制，不能像 HotSpot 一樣做那麼多優化
- Dalvik 是 Register-based 的 VM
- Dalvik Executable (DEX)
    * convert tool : dx

- Optimizing Dispatch
    * selective inlining
      + 打開 Java 程式執行的時候，CPU 就是不知道在忙什麼
      + 只是個印出 Hello World 的程式，發現 CPU 有點忙

- dexopt : Instruction Rewritten

libART (Android RunTime Library)
--------------------------------

- Use Ahead-Of-Time (AOT) scheme instead of JIT
    * Precompile Dalvik Bytecode into machine language during installation

Summary
========================================

- Hotspot 和 Dalvik 完全不同 codebase，但設計原理很像，Hotspot 實作比較完整，Dalvik 有很多先天限制
- Android L 啟動時間變更久 (重新 scan bytecode 來生成 machine code)
- 要兼顧效能和啟動時間
