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
