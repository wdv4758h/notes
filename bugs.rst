========================================
踩 Bug 紀錄 (從 2015-10-26 開始)
========================================

2015-10-26
========================================

Clang 3.7 - Sanitizer on Ubuntu
-------------------------------

原本想把 Neovim 的 ``.travis.yml`` 改成使用 Clang 3.7 (當時是使用 Clang 3.6)，
在自己的 Arch Linux 上編譯測試會動，
發現有 ``-fno-sanitize-recover`` 的 warning，
改成 ``-fno-sanitize-recover=all`` 可以修掉，
接著把更動 push 到自己的 GitHub 上跑 Travis CI 做測試，
發現會 build failed，
問題發生在 link time，
原因是在 Ubuntu (Travis CI 提供的服務跑在 Ubuntu 上) 找不到 Sanitizer 該有的 library：

::

    /usr/bin/ld: cannot find /usr/lib/llvm-3.7/bin/../lib/clang/3.7.0/lib/linux/libclang_rt.asan-x86_64.a: No such file or directory

後來發現似乎是跟 compiler-rt 目前只能用 ``cmake`` 編出來有關，
接著找到了一些 LLVM 的 bug report：

* `Bug 15732 - [META] CMake build equivalent to the autotools build <https://llvm.org/bugs/show_bug.cgi?id=15732>`_
* `Bug 24919 - [autoconf -> cmake] libclang.a is not packaged in the Ubuntu x86_64 pre-built <https://llvm.org/bugs/show_bug.cgi?id=24919>`_

實際測試在 Ubuntu 上安裝 Clang 3.7，
發現只能找到 ``libclang_rt.builtins-x86_64.a`` 和 ``libclang_rt.profile-x86_64.a`` ，
其他的就沒有了 ...



2015-10-31
========================================

Neovim - jump to last position on reopen doesn't work
-----------------------------------------------------

``viminfo`` 的新名字為 ``shada``

* `jump to last position on reopen doesn't work anymore <https://github.com/neovim/neovim/issues/3472>`_
* `[RDY] Fix local marks saving/restoring with ShaDa <https://github.com/neovim/neovim/pull/3490/files>`_


Neovim - Latest neovim not using .nvimrc
-----------------------------------------------------

新路徑： ``$HOME/.config/nvim/``

* `Latest neovim not using .nvimrc <https://github.com/neovim/neovim/issues/3530>`_


2015-11-24
========================================

gcc - ICE (internal compiler error)
-----------------------------------

.. code-block:: sh

    $ gcc -v
    Using built-in specs.
    COLLECT_GCC=gcc
    COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-unknown-linux-gnu/5.2.0/lto-wrapper
    Target: x86_64-unknown-linux-gnu
    Configured with: /build/gcc-multilib/src/gcc-5.2.0/configure --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++ --enable-shared --enable-threads=posix --enable-libmpx --with-system-zlib --with-isl --enable-__cxa_atexit --disable-libunwind-exceptions --enable-clocale=gnu --disable-libstdcxx-pch --disable-libssp --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-plugin --enable-install-libiberty --with-linker-hash-style=gnu --enable-gnu-indirect-function --enable-multilib --disable-werror --enable-checking=release --with-default-libstdcxx-abi=gcc4-compatible
    Thread model: posix
    gcc version 5.2.0 (GCC)



``test1.c`` :

.. code-block:: c

    int a[100];

    int main()
    {
        #pragma omp simd collapse(2)
        for (int i = 0; i < 10; i++) {
            for (int k = a[i]; k < 0; k++) {
                a[i] = a[i] - 1;
            }
        }

        return 0;
    }



``test2.c`` :

.. code-block:: c

    int a[100];

    int main()
    {
        #pragma omp for simd collapse(2)
        for (int i = 0; i < 10; i++) {
            for (int k = a[i]; k < 0; k++) {
                a[i] = a[i] - 1;
            }
        }

        return 0;
    }


.. code-block:: sh

    $ gcc -O3 -fopenmp test1.c
    test1.c: In function ‘main’:
    test1.c:7:23: warning: ‘i’ is used uninitialized in this function [-Wuninitialized]
            for (int k = a[i]; k < 0; k++) {
                        ^
    test1.c:3:5: internal compiler error: in expand_one_var, at cfgexpand.c:1339
    int main()
        ^
    Please submit a full bug report,
    with preprocessed source if appropriate.
    See <https://bugs.archlinux.org/> for instructions.

    $ gcc -O3 -fopenmp test2.c
    test2.c: In function ‘main’:
    test2.c:7:23: internal compiler error: in gimplify_var_or_parm_decl, at gimplify.c:1801
            for (int k = a[i]; k < 0; k++) {
                        ^
    Please submit a full bug report,
    with preprocessed source if appropriate.
    See <https://bugs.archlinux.org/> for instructions.
