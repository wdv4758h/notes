========================================
asmjit
========================================

.. contents:: 目錄


編譯 & 連結
========================================

.. code-block:: sh

    git clone https://github.com/kobalicek/asmjit/
    mkdir asmjit/build/
    cd asmjit/build
    cmake ../
    make -j

    edit myprogram.cpp
    clang++ myprogram.cpp -I ../asmjit/src -L . -l asmjit -o myprogram
    env LD_PRELOAD=./libasmjit.so ./myprogram




架構
========================================

支援：

* ASMJIT_BUILD_ARM
* ASMJIT_BUILD_ARM64
* ASMJIT_BUILD_X86
* ASMJIT_BUILD_X64
* ASMJIT_BUILD_HOST (預設只有 ASMJIT_BUILD_HOST)

使用：

.. code-block:: cpp

    #if defined(ASMJIT_BUILD_X64)
        ...
    #endif


Brainfuck
========================================
