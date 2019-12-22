========================================
libc
========================================


.. contents:: 目錄


rust-lang/libc
========================================

針對各平台 libc 的 binding。

（可以用來觀察不同平台間的差異，
撰寫新 libc 時也可以結合這個 binding 跟不同專案做測試）



japaric/libm
========================================

`musl libm <https://github.com/japaric/libm>`_ 移植



steed - Rust standard library without C dependencies
====================================================

:Repo: https://github.com/japaric/steed

目標是要達到讓 Rust 真正地易於 cross compile，
完全不需要 libc 的 libstd 實做是一部分，
另一部份是把 LLVM lld 加入 rustc。



參考
========================================

* man libc
* GNU libc
* musl libc
* μClibc
* Newlib libc
* Android Bionic
* BSD libc
* dietlibc
* `Comparison of C/POSIX standard library implementations for Linux <https://www.etalabs.net/compare_libcs.html>`_
* `rusl <https://github.com/anp/rusl>`_
