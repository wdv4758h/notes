========================================
Concurrency & Rust
========================================


.. contents:: 目錄


Crossbeam - concurrent library
=================================================

:Repo: https://github.com/crossbeam-rs/crossbeam


Rust 目前最廣泛使用的 concurrent 套件，
效能比 ``std::mpsc`` 好非常多。
``crossbeam-channel`` 跟其他實做的 `效能比較 <https://github.com/crossbeam-rs/crossbeam/blob/master/crossbeam-channel/benchmarks/README.md>`_ 。


* bounded channel
* unbounded channel
* bounded MPMC queue
* unbounded MPMC queue
* epoch-based GC



Rayon - data-parallelism library
========================================

:Repo: https://github.com/rayon-rs/rayon


Rayon 的一大特色在於資料平行化，
在一些情況下只要把原本操作 Iterator 的程式碼從 ``.iter()`` 改成 ``.par_iter()`` 即可，
接著就可以看到效能在多核心機器下的提升。


* parallel sort
    - `#379 - parallel sort <https://github.com/rayon-rs/rayon/pull/379>`_
    - `rayon - par_sort() <https://docs.rs/rayon/1.0.3/rayon/slice/trait.ParallelSliceMut.html#method.par_sort>`_



使用案例
========================================

* Servo
    - `std::mpsc 換成 crossbeam-channel <https://github.com/servo/servo/pull/21325>`_



參考
========================================

* `Lock-free Rust: Crossbeam in 2019 <https://stjepang.github.io/2019/01/29/lock-free-rust-crossbeam-in-2019.html>`_
* [2018] `Writing "Hands-On Concurrency with Rust" <https://blog.troutwine.us/2018/06/07/hands-on-concurrency-with-rust/>`_
* `Crossbeam Wiki - Learning Resources <https://github.com/crossbeam-rs/rfcs/wiki>`_
    - 蒐集了許多 Concurrency 相關學習資源
* `Crossbeam RFC - crossbeam-channel - 2017-11-09-channel <https://github.com/crossbeam-rs/rfcs/blob/master/text/2017-11-09-channel.md>`_
* 溝通種類
    - SPSC
    - SPMC
    - MPSC
    - MPMC
