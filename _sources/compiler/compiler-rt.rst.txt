========================================
LLVM - compiler-rt
========================================


.. contents:: 目錄


介紹
========================================

TL;DR:
將 LLVM IR 轉成對應的 CPU instruction 時，幫忙處理 CPU 沒實做的功能、歷史包袱或平台破碎化的 Library
（加上 Sanitizer）


compiler-rt 是 LLVM 中負責針對不同平台的 codegen 輔助 library，
rt 是 runtime 的縮寫。

LLVM backend 會負責把 LLVM IR 對應到特定平台的 CPU instruction，
在沒有 CPU instruction 可以直接對應時，
可以選擇直接換成一連串對應的 instruction 或是一個 function call 呼叫 compiler-rt 內的實做。


目前可以想像的使用情境有三種：

* CPU 沒實做的功能
* 歷史包袱
* 平台破碎化


CPU 沒實做的功能：
例如 64 bits 數字的處理要跑在 32 bits 平台上，
或是 128 bits 的數字在 64 bits 平台上。


歷史包袱：
例如同樣是 x86 平台，但是有小地方不相容（FPU instruction 之類的），
因此需要一層抽象化才可以跑在每個 x86 平台。


平台破碎化：
例如不同的 ARM 平台可能有自己擴充的 instruction，
要同時跑在兩個 ARM 平台就只能使用指令集交集的部份，
但是如此一來就不能善用額外的擴充 instruction，
因此抽象化一層出來，
在特定平台使用擴充的 instruction。


對應到 GCC 的專案內就是 ``libgcc`` 。


compiler-rt 除了上面提到的功能外，
還有另一部份是 Instrumentation 用的，
包含 AddressSanitizer、ThreadSanitizer、MemorySanitizer 等等。



Build From Source
========================================

.. code-block:: sh

    # http://clang.llvm.org/get_started.html

    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

    cd llvm/tools
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
    cd ../..

    cd llvm/projects
    svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
    cd ../..

    mkdir build
    cd build
    cmake -G "Unix Makefiles" ../llvm
    make -j8
    make install


如果系統已經有 ``llvm-config`` 的話可以使用以下方式只編 ``compiler-rt`` 的部份：

.. code-block:: sh

    # if you have llvm-config

    git clone https://github.com/llvm-mirror/compiler-rt/
    mkdir build
    cd build
    cmake ../compiler-rt -DLLVM_CONFIG_PATH=`which llvm-config`
    make



LLVM Weekly
========================================

* [2014-01-31][r200546_] Compiler-rt's CMake files will now compile the library for ARM. Give it a go and see what breaks. r200546.
* [2014-01-21][r199729_] In compiler-rt, support was added for intercepting and sanitizing arguments passed to printf functions in AddressSanitizer and ThreadSanitizer.
* [2014-01-16][r199377_] AddressSanitizer in compiler-rt gained the ability to start in 'deactivated' mode. It can later be activated when __asan_init is called in an instrumented library.


.. _r200546: http://reviews.llvm.org/rL200546
.. _r199729: http://reviews.llvm.org/rL199729
.. _r199377: http://reviews.llvm.org/rL199377



參考
========================================

* `compiler-rt 官網 <http://compiler-rt.llvm.org/>`_
* `LLVM - compiler-rt <http://llvm.org/svn/llvm-project/compiler-rt/trunk/>`_
* [GitHub] `llvm-mirror/compiler-rt <https://github.com/llvm-mirror/compiler-rt>`_
* `AOSP - compiler-rt <https://android.googlesource.com/platform/external/compiler-rt/>`_

Sanitizer:

* `CppCon 2014: Kostya Serebryany "Sanitize your C++ code" <https://isocpp.org/blog/2015/05/cppcon-2014-sanitize-your-cpp-code-kostya-serebryany>`_
* `CppCon 2015: Beyond Sanitizers <https://cppcon2015.sched.org/event/cab93ab408d0aacbc4c0894c44cfd9cf>`_
* `GCC Undefined Behavior Sanitizer – ubsan <http://developerblog.redhat.com/2014/10/16/gcc-undefined-behavior-sanitizer-ubsan/>`_
* `The Chromium Projects - AddressSanitizer (ASan) <https://www.chromium.org/developers/testing/addresssanitizer>`_
