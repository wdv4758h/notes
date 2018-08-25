========================================
CPython
========================================


編譯 - 編譯和執行平台相同
========================================

Debug 模式：

.. code-block:: sh

    # CPython source code 已經從自己 Hosting 轉移到 GitHub 上了
    $ git clone https://github.com/python/cpython
    $ cd cpython
    $ ./configure --with-pydebug
    $ make -j8
    $ ./python -m test -j8



編譯 - 編譯和執行平台不同 - Android
========================================

.. code-block:: sh

    # 下載 Android NDK
    mkdir ndk
    cd ndk
    wget https://dl.google.com/android/repository/android-ndk-r15c-linux-x86_64.zip
    unzip android-ndk-r15c-linux-x86_64.zip
    cd ../

    # 下載 CPython 程式碼
    git clone https://github.com/python/cpython
    cd cpython
    mkdir mybuild

    # 編譯 host CPython
    # 在 Cross Compile 時需要同版本的 CPython
    ./configure
    make -j BUILDPYTHON=hostpython hostpython PGEN=Parser/hostpgen Parser/hostpgen
    mv Parser/hostpgen hostpgen


    # 設定 NDK 環境
    # ==> 變動區域，自行根據需求更換
    export ANDROID_NDK_ROOT="$HOME/ndk/android-ndk-r15c"
    export ANDROID_NDK_VERSION="15"
    export ANDROID_API="24"
    export ANDROID_ARCH="arm"
    export GCC_VERSION="4.9"
    # 要執行編譯結果的機器
    export ANDROID_HOST="arm-linux-androideabi"
    # 負責編譯的機器
    export ANDROID_BUILD="x86_64-pc-linux-gnu"
    export TARGET_ABI="armeabi-v7a"
    export TARGET="arm-none-linux-android"
    export KERNEL=linux
    export MACHINE=x86_64
    # ==> 固定區域
    export SYSROOT="$ANDROID_NDK_ROOT/platforms/android-$ANDROID_API/arch-$ANDROID_ARCH"
    export LLVM_TOOLCHAIN="$ANDROID_NDK_ROOT/toolchains/llvm/prebuilt/$KERNEL-$MACHINE"
    # NDK 編譯器現在是 Clang，但是底下仍然需要一些 GCC 的工具
    export GCC_TOOLCHAIN_NAME=$ANDROID_HOST-$GCC_VERSION
    export GCC_TOOLCHAIN="$ANDROID_NDK_ROOT/toolchains/$GCC_TOOLCHAIN_NAME/prebuilt/$KERNEL-$MACHINE"
    export CC="$LLVM_TOOLCHAIN/bin/clang -target $TARGET -gcc-toolchain $GCC_TOOLCHAIN"
    export CXX="$LLVM_TOOLCHAIN/bin/clang++ -target $TARGET -gcc-toolchain $GCC_TOOLCHAIN"
    export GCC="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-gcc"
    export AR="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-ar"
    export LD="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-ld"
    export RANLIB="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-ranlib"
    export READELF="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-readelf"
    export STRIP="$GCC_TOOLCHAIN/bin/$ANDROID_HOST-strip --strip-debug --strip-unneeded"
    export NDK_FLAGS="--sysroot=$SYSROOT -D__ANDROID_API__=$ANDROID_API -isystem $ANDROID_NDK_ROOT/sysroot/usr/include/$ANDROID_HOST -I$ANDROID_NDK_ROOT/sources/cxx-stl/llvm-libc++/include -L$ANDROID_NDK_ROOT/sources/cxx-stl/llvm-libc++/libs/$TARGET_ABI"
    export CPPFLAGS="$CPPFLAGS $NDK_FLAGS"
    export CFLAGS="$CFLAGS $NDK_FLAGS -Wno-unused-value -Wno-empty-body -Qunused-arguments -Wno-nullability-completeness"
    export LDFLAGS="$LDFLAGS --sysroot=$SYSROOT"

    # configure 時也要寫參數
    ./configure CC="$CC" \
                AR="$AR" \
                LD="$LD" \
                RANLIB="$RANLIB" \
                READELF="$READELF" \
                CPPFLAGS="$CPPFLAGS" \
                LDFLAGS="$LDFLAGS" \
                CFLAGS="$CFLAGS" \
                --host=$ANDROID_HOST \
                --build=$ANDROID_BUILD \
                --enable-shared \
                --enable-ipv6 \
                --without-ensurepip \
                ac_cv_file__dev_ptmx=yes \
                ac_cv_file__dev_ptc=no \
                ac_cv_little_endian_double=yes \
                --prefix=$PWD/mybuild

    # Cross Compile，並指定 host CPython
    $ make -j CROSS_COMPILE_TARGET=yes HOSTPYTHON=./hostpython HOSTPGEN=./hostpgen
    # 安裝到指定資料夾
    $ make -j install CROSS_COMPILE_TARGET=yes HOSTPYTHON=./hostpython HOSTPGEN=./hostpgen



* `Clang - Cross Compilation <https://clang.llvm.org/docs/CrossCompilation.html>`_
* `OSDev wiki - LLVM Cross Compiler <http://wiki.osdev.org/LLVM_Cross-Compiler>`_
* `llvm::Triple Class Reference <http://llvm.org/doxygen/classllvm_1_1Triple.html>`_
* `Android NDK - Standalone Toolchains <https://developer.android.com/ndk/guides/standalone_toolchain.html>`_
* `Building Python Statically <https://wiki.python.org/moin/BuildStatically>`_



開關 CPython 內建 Extension
========================================

``Modules/Setup.dist``



資料結構
========================================

* [FOSDEM 2017] `Python Data Structures implementation - list, dict: how does CPython actually implement them? <https://archive.fosdem.org/2017/schedule/event/python_data_structures/>`_



decimal
========================================

在改 CPython 的 PKGBUILD 時，
才發現從 3.3 開始支援了一個 library 叫 ``libmpdec`` ，
用來提升 decimal module 的效能 (``libmpdec`` 是用 C 實作的 library)。

接到 CPython 上的 module 名稱叫作 ``_decimal`` ，
在 ``import decimal`` 時會先去嘗試尋找 ``_decimal`` (看系統有沒有 ``libmpdec``)
沒有的話會使用純 Python 實作的 ``_pydecimal``

* `Python 3.3 - integrate fast native decimal arithmetic. <https://docs.python.org/3/whatsnew/3.3.html#decimal>`_
* [CPython] `Issue 7652 - Merge C version of decimal into py3k. <https://bugs.python.org/issue7652>`_
* `mpdecimal - a package for correctly-rounded arbitrary precision decimal floating point arithmetic <http://www.bytereef.org/mpdecimal/index.html>`_
* `CPython - decimal.py <https://github.com/python/cpython/blob/master/Lib/decimal.py>`_
* `CPython - _decimal <https://github.com/python/cpython/tree/master/Modules/_decimal>`_
* `CPython - _pydecimal.py <https://github.com/python/cpython/blob/master/Lib/_pydecimal.py>`_


Articles
========================================

* [2010] `Python internals: Symbol tables, part 1 <http://eli.thegreenplace.net/2010/09/18/python-internals-symbol-tables-part-1/>`_
* [2010] `Python internals: Symbol tables, part 2 <http://eli.thegreenplace.net/2010/09/20/python-internals-symbol-tables-part-2>`_
* [2011] `Python list implementation <http://www.laurentluce.com/posts/python-list-implementation/>`_
* [2014] `CPython internals: A ten-hour codewalk through the Python interpreter source code <http://pgbovine.net/cpython-internals.htm>`_

* `CPython - Execution model <https://docs.python.org/3/reference/executionmodel.html>`_

* [GitHub] `Notes on making CPython faster <https://github.com/haypo/faster_cpython>`_



Talks
========================================

* [YouTube] `Architecture of CPython, the bricks! (Stéphane Wirtel) <https://www.youtube.com/watch?v=ZkAc6hzGun4>`_
* [YouTube] `From Source to Code: How CPython's Compiler Works - Brett Cannon <https://www.youtube.com/watch?v=R31NRWgoIWM>`_
* [YouTube] `Stepping Through CPython <https://www.youtube.com/watch?v=XGF3Qu4dUqk>`_
* [YouTube] `Hacking the CPython Interpreter | SciPy 2016 | James Powell <https://www.youtube.com/watch?v=1SqRRrmQHx0>`_



Other Python Implementations
========================================

* `Pyston <https://github.com/dropbox/pyston>`_
    - performance-oriented Python implementation built using LLVM and modern JIT techniques
* PyPy
    - Python implementation written in RPython framework with JIT and modern GC
* Jython
    - Python implementation written in Java to integrate with JVM
* IronPython
    - Python implementation written in C# to integrate with .NET framework



參考
========================================

* `Python Developer's Guide <https://docs.python.org/devguide/index.html>`_
* `BuildBot: Python - Waterfall <http://buildbot.python.org/all/waterfall>`_
* `Mercurial for git developers <https://docs.python.org/devguide/gitdevs.html>`_
* `CPython - Code Review <https://bugs.python.org/review/>`_
