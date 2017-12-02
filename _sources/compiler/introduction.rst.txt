========================================
編譯器
========================================


.. contents:: 目錄


環境設定
========================================

.. code-block:: sh

    export CC="clang"
    export CXX="clang++"
    export AS="llvm-as"
    export LD="lld"
    export NM="llvm-nm"
    export AR="llvm-ar"
    export RANLIB="llvm-ar"
    export CLFAGS="-fuse-ld=$LD"
    export CXXLFAGS="-fuse-ld=$LD"



C Compiler - clang
========================================



Assembler - llvm-as
========================================



Archive - llvm-ar
========================================



Ranlib - llvm-ranlib
========================================

**ranlib** 是負責建立 archive 的 index 來幫助 static linking，
建好的 index 可以用 ``nm -s`` 或 ``nm --print-armap`` 列出來，
等同於 ``ar -s`` ，
但基於歷史因素仍然留存。



Linker - lld
========================================

nm
========================================

C runtime - crt#.o
========================================

為 LLVM 實做 Compiler Frontend
========================================

為 LLVM 實做 Optimization Pass
========================================

為 LLVM 實做 Assembler
========================================

為 LLVM 實做 Linker
========================================

為 LLVM 實做 JIT backend
========================================

參考
========================================

* `Bitcode Demystified - Low Level Bits <https://lowlevelbits.org/bitcode-demystified/>`_
* `The Architecture of Open Source Applications: LLVM <http://www.aosabook.org/en/llvm.html>`_
* `Adrian Sampson: LLVM for Grad Students <https://www.cs.cornell.edu/~asampson/blog/llvm.html>`_
* `Creating a C Library - OSDev Wiki <http://wiki.osdev.org/Creating_a_C_Library>`_
* `Calling Global Constructors - OSDev Wiki <http://wiki.osdev.org/Calling_Global_Constructors>`_
* `Object Files - OSDev Wiki <http://wiki.osdev.org/Object_Files>`_
* `How kernel, compiler, and C library work together - OSDev Wiki <http://wiki.osdev.org/How_kernel,_compiler,_and_C_library_work_together>`_
* `Mini FAQ about the misc libc/gcc crt files <https://dev.gentoo.org/~vapier/crt.txt>`_
