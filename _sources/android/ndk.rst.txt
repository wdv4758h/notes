========================================
Android NDK
========================================

.. contents:: Table of Contents


Introduction
========================================

Android NDK 裡面會附上 Cross Compile 用的程式，
例如 ``toolchains/`` 資料夾裡面就包含不同平台的 GCC Cross Compiler 的執行檔，
另外則含有 Clang 的 Makefile 設定。
(GCC 的 Cross Compile 需要先編成不同的 GCC Binary，Clang 則是有更好的支援，使用 ``-target`` 參數選擇即可)


Build Standalone Clang Cross Compile Toolchain
==============================================

.. code-block:: sh

    $ android-ndk-r10e/build/tools/make-standalone-toolchain.sh \
        --toolchain=arm-linux-androideabi-clang3.6 \
        --llvm-version=3.6 \
        --arch=arm \
        --abis=armeabi-v7a-hard \
        --platform=android-21 \
        --package-dir=/tmp
    Auto-config: --toolchain=arm-linux-androideabi-4.8, --llvm-version=3.6
    Copying prebuilt binaries...
    Copying sysroot headers and libraries...
    Copying c++ runtime headers and libraries...
    Creating package file: /tmp/arm-linux-androideabi-4.8.tar.bz2
    Cleaning up...
    Done.
    $ file /tmp/arm-linux-androideabi-4.8.tar.bz2
    /tmp/arm-linux-androideabi-4.8.tar.bz2: bzip2 compressed data, block size = 900k


compiler-rt
========================================

.. code-block:: sh

    $ ls -al arm-linux-androideabi-4.8/lib/clang/3.6/lib/linux/
    total 7332
    -rw-r----- 1 dv dv 2323826 Apr  1 06:26 libclang_rt.asan-arm-android.a
    -rw-r----- 1 dv dv   36437 Apr  1 06:27 libclang_rt.asan-arm-android.a.syms
    -rwxr-x--- 1 dv dv 1599248 Apr  1 06:27 libclang_rt.asan-arm-android.so*
    -rw-r----- 1 dv dv   16596 Apr  1 06:26 libclang_rt.asan_cxx-arm-android.a
    -rw-r----- 1 dv dv      73 Apr  1 06:26 libclang_rt.asan_cxx-arm-android.a.syms
    -rw-r----- 1 dv dv   14064 Apr  1 06:34 libclang_rt.asan_cxx-i686-android.a
    -rw-r----- 1 dv dv 1986448 Apr  1 06:34 libclang_rt.asan-i686-android.a
    -rwxr-x--- 1 dv dv 1504988 Apr  1 06:35 libclang_rt.asan-i686-android.so*
    -rw-r----- 1 dv dv    2100 Apr  1 06:26 libclang_rt.asan-preinit-arm-android.a
    -rw-r----- 1 dv dv    1844 Apr  1 06:34 libclang_rt.asan-preinit-i686-android.a
    $ file android-ndk-r10e/toolchains/llvm-3.6/prebuilt/linux-x86_64/lib/clang/3.6/lib/linux/libclang_rt.asan-arm-android.so
    android-ndk-r10e/toolchains/llvm-3.6/prebuilt/linux-x86_64/lib/clang/3.6/lib/linux/libclang_rt.asan-arm-android.so: ELF 32-bit LSB shared object, ARM, EABI5 version 1 (SYSV), dynamically linked, interpreter /system/bin/linker, BuildID[sha1]=414a26fe76bb09de2d0d101e3ed6200da5d1cadc, not stripped


Build LLVM From Source For Android
========================================


"cpufeatures" Library
========================================

* `The cpufeatures Library <https://developer.android.com/ndk/guides/cpu-features.html>`_


Build Your NDK
========================================


Reference
========================================

* `Android NDK ABIs <https://developer.android.com/ndk/guides/abis.html>`_
* `Google Code Review - NDK <https://android-review.googlesource.com/#/q/project:platform/ndk>`_
* `AOSP - NDK <https://android.googlesource.com/platform/ndk>`_
* `AOSP - Prebuilts NDK <https://android.googlesource.com/platform/prebuilts/ndk>`_
* `NDK - Release Notes <https://developer.android.com/ndk/downloads/index.html#rel>`_

* `AOSP - LLVM <https://android.googlesource.com/platform/external/llvm/>`_
* `AOSP - compiler-rt <https://android.googlesource.com/platform/external/compiler-rt/>`_
* `AOSP - Clang <https://android.googlesource.com/platform/external/clang/>`_
