========================================
Android With LLVM
========================================

* `[2014] Here be dragons: Using clang/LLVM to build Android <http://events.linuxfoundation.org/sites/events/files/slides/2014-ABS-LLVMLinux.pdf>`_
    - You can build a single project within Android by setting ``LOCAL_CLANG=true`` in ``Android.mk``
    - You can use clang globally by setting ``LOCAL_CLANG=true`` in ``build/core/clear_vars.mk``
