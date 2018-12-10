========================================
LTO - Link Time Optimization
========================================


.. contents:: 目錄


ThinLTO
========================================

:docs: https://clang.llvm.org/docs/ThinLTO.html


跟先前的 monolithic LTO 相比兼顧了編譯速度和結果。


* parallelism
* incremental



參考
========================================

* `Linktime optimization in GCC, part 1 - brief history <http://hubicka.blogspot.tw/2014/04/linktime-optimization-in-gcc-1-brief.html>`_
* `Linktime optimization in GCC, part 2 - Firefox <http://hubicka.blogspot.tw/2014/04/linktime-optimization-in-gcc-2-firefox.html>`_
* `Linktime optimization in GCC, part 3 - LibreOffice <http://hubicka.blogspot.tw/2014/09/linktime-optimization-in-gcc-part-3.html>`_

* `Building libreoffice with GCC 6 and LTO <http://hubicka.blogspot.tw/2016/03/building-libreoffice-with-gcc-6-and-lto.html>`_
* `GCC 8: link time and interprocedural optimization <https://hubicka.blogspot.com/2018/06/gcc-8-link-time-and-interprocedural.html>`_

* `Firefox is now built with clang LTO on all* platforms <https://glandium.org/blog/?p=3888>`_
    - `HN - Firefox is now built with clang LTO on all* platforms <https://news.ycombinator.com/item?id=17966967>`_


* cross-language LTO
    - `Rust - Implement cross-language ThinLTO <https://github.com/rust-lang/rust/issues/49879>`_
