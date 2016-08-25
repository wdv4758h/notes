========================================
LLVM
========================================

.. contents:: Table of Contents

(LLVM 用 reStructuredText 跟 Sphinx 在寫 Documentation)


Introduction
========================================

LLVM 是 **Chris Lattner** 於 2000 年在 UIUC 展開、發表於 2004 年的碩士論文專案，
原名為 「Low Level Virtual Machine」，
當中使用到的概念取自於 2003 年發表的論文
「 `LLVA: A Low-level Virtual Instruction Set Architecture <http://llvm.org/pubs/2003-10-01-LLVA.html>`_ 」，
於 2004 年發表 LLVM 論文
「 `LLVM: A Compilation Framework for Lifelong Program Analysis & Transformation <http://llvm.org/pubs/2004-01-30-CGO-LLVM.html>`_ 」，
後來由於發展不限於 Virtual Machine，
使用原名會造成誤解，
所以名稱改為 **LLVM** 。

LLVM 使用 ``University of Illinois/NCSA Open Source License`` 條款釋出，
使用 SVN 作為主要開發的版本工具，
每次新 release 即升一個小版號，
直到小版號超過九，
就升一次大版號。



Get Your LLVM
========================================

Release Prebuilt
------------------------------

LLVM Snapshot Builds
------------------------------

Autotools
------------------------------

CMake & Ninja
------------------------------

DragonEgg Plugin
========================================

* `DragonEgg - Using LLVM as a GCC backend <http://dragonegg.llvm.org/>`_

Polly
========================================

polyhedral optimizer

* `LLVM Framework for High-Level Loop and Data-Locality Optimizations <http://polly.llvm.org/changelog.html>`_
* `[GitHub] llvm-mirror/polly <https://github.com/llvm-mirror/polly>`_
* `Wikipedia - Polytope model <https://en.wikipedia.org/wiki/Polytope_model>`_
* `[2010] Polly - Polyhedral Transformations for LLVM <http://llvm.org/devmtg/2010-11/Grosser-Polly.pdf>`_


LLVM Linker
========================================

lld


Register Allocation
========================================

* `[2011] Register Allocation in LLVM 3.0 <http://llvm.org/devmtg/2011-11/Olesen_RegisterAllocation.pdf>`_
* `LLVM register allocation <https://cgcheng.hackpad.com/LLVM-register-allocation-quymvAj80nQ>`_


llc
========================================

.. code-block:: sh

    $ llc --version
    LLVM (http://llvm.org/):
    LLVM version 3.5.2
    Optimized build.
    Built Apr 23 2015 (08:23:12).
    Default target: x86_64-unknown-linux-gnu
    Host CPU: core-avx-i

    Registered Targets:
        aarch64    - AArch64 (little endian)
        aarch64_be - AArch64 (big endian)
        arm        - ARM
        arm64      - AArch64 (little endian)
        arm64_be   - AArch64 (big endian)
        armeb      - ARM (big endian)
        cpp        - C++ backend
        hexagon    - Hexagon
        mips       - Mips
        mips64     - Mips64 [experimental]
        mips64el   - Mips64el [experimental]
        mipsel     - Mipsel
        msp430     - MSP430 [experimental]
        nvptx      - NVIDIA PTX 32-bit
        nvptx64    - NVIDIA PTX 64-bit
        ppc32      - PowerPC 32
        ppc64      - PowerPC 64
        ppc64le    - PowerPC 64 LE
        r600       - AMD GPUs HD2XXX-HD6XXX
        sparc      - Sparc
        sparcv9    - Sparc V9
        systemz    - SystemZ
        thumb      - Thumb
        thumbeb    - Thumb (big endian)
        x86        - 32-bit X86: Pentium-Pro and above
        x86-64     - 64-bit X86: EM64T and AMD64
        xcore      - XCore


Garbage Collection
========================================

* `Garbage Collection with LLVM <http://llvm.org/docs/GarbageCollection.html>`_
* `[2013] On LLVM's GC Infrastructure <https://eschew.wordpress.com/2013/10/28/on-llvms-gc-infrastructure/>`_
* `[2014] Practical Fully Relocating Garbage Collection in LLVM <http://llvm.org/devmtg/2014-10/Slides/Reames-GarbageCollection.pdf>`_


LLVM Pass
========================================

* `Writing an LLVM Pass <http://llvm.org/docs/WritingAnLLVMPass.html>`_
* `[2014] Passes in LLVM <http://llvm.org/devmtg/2014-04/PDFs/Talks/Passes.pdf>`_
* `[2014] The LLVM Pass Manager Part 2 <http://llvm.org/devmtg/2014-10/Slides/Carruth-TheLLVMPassManagerPart2.pdf>`_


Misc
========================================

* `LLVMPin Instrumentation Framework <http://eces.colorado.edu/~blomsted/llvmpin/llvmpin.html>`_
* `C Concurrency: Still Tricky <http://llvm.org/devmtg/2015-04/slides/CConcurrency_EuroLLVM2015.pdf>`_


Idea
========================================

* LLVM For Writing Database
    - database framework ?
    - SQL with JIT support ?
    - `[2013] Building a Modern Database Using LLVM <http://llvm.org/devmtg/2013-11/slides/Wanderman-Milne-Cloudera.pdf>`_
    - `Impala - Real-time Query for Hadoop <https://github.com/cloudera/impala>`_
    - SQLite with LLVM JIT ?
    - http://sqlite.org/src/doc/trunk/README.md
    - mirror : http://repo.or.cz/sqlite.git

* LLVM for Concurrency
    - https://github.com/concurrencykit/ck

* LLVM for lock-free

* Code Gen
    - `Type-safe Runtime Code Generation: Accelerate to LLVM <https://speakerdeck.com/tmcdonell/type-safe-runtime-code-generation-accelerate-to-llvm>`_

* GCC
    - `編譯 GCC - 交叉編譯器 cross compiler <https://cgcheng.hackpad.com/-GCC-cross-compiler-iBJdwr3FQ75>`_
    - http://stackoverflow.com/questions/29453962/completely-standalone-clang-on-linux

* libunwind in compiler-rt
    - http://thread.gmane.org/gmane.comp.compilers.llvm.devel/78099
    - https://git.linaro.org/people/renato.golin/compiler-rt.git

* code suggestion

Reference
========================================

LLVM
------------------------------

* `Wikipedia - LLVM <https://en.wikipedia.org/wiki/LLVM>`_
* [Book] Getting Started with LLVM Core Libraries
* `AOSA - LLVM <http://www.aosabook.org/en/llvm.html>`_
* `LLVM: Implementing a Language <https://www.gitbook.com/book/landersbenjamin/llvm-implementing-a-language/details>`_
* [2014] `LLVM: A Compilation Framework for Lifelong Program Analysis & Transformation <http://llvm.org/pubs/2004-01-30-CGO-LLVM.pdf>`_

Ninja
------------------------------

* `[GitHub] martine/ninja <https://github.com/martine/ninja>`_
* `Ninja <http://martine.github.io/ninja/>`_
* `AOSA - Ninja <http://www.aosabook.org/en/posa/ninja.html>`_
* `Replacing Make with Ninja <http://jpospisil.com/2014/03/16/replacing-make-with-ninja.html>`_
* `Make vs Ninja Performance Comparison <http://hamelot.co.uk/programming/make-vs-ninja-performance-comparison/>`_
