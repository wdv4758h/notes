========================================
Clang Options
========================================


.. contents:: 目錄


更換 Linker
========================================

使用 ``-fuse-ld=...`` 更換（可以用 ``-Wl,--version`` 檢查）


.. code-block:: sh

    $ clang -Wl,--version
    GNU ld (GNU Binutils) 2.29.1
    Copyright (C) 2017 Free Software Foundation, Inc.
    This program is free software; you may redistribute it under the terms of
    the GNU General Public License version 3 or (at your option) a later version.
    This program has absolutely no warranty.

    $ clang -fuse-ld=gold -Wl,--version
    GNU gold (GNU Binutils 2.29.1) 1.14
    Copyright (C) 2017 Free Software Foundation, Inc.
    This program is free software; you may redistribute it under the terms of
    the GNU General Public License version 3 or (at your option) a later version.
    This program has absolutely no warranty.

    $ clang -fuse-ld=lld -Wl,--version
    LLD 5.0.0 (compatible with GNU linkers)

    $ clang -fuse-ld=/usr/bin/ld.lld -Wl,--version
    LLD 5.0.0 (compatible with GNU linkers)
