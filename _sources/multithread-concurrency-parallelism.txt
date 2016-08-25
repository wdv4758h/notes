========================================
名詞釐清
========================================

記一下目前的理解

::

    +-------------------------+
    |              +----------|-----------------------------+
    |              | +--------|-------+                     |
    |              | |        |       |                     |
    |              | |        |       |                     |
    |  Parallelism | | Multithread    |    Concurrency      |
    |              | |        |       |                     |
    |              | |        |       |                     |
    |              | +--------|-------+                     |
    |              +----------|-----------------------------+
    +-------------------------+


* Multithread 包含於 Concurrency
* 存在某情況屬於 Multithread 但不屬於 Parallelism
* 也存在某情況屬於 Multithread 也屬於 Parallelism
* 存在某情況屬於 Concurrency 和 Parallelism 但不屬於 Multithread
* 存在某情況不屬於 Concurrency 但屬於 Parallelism


Concurrency
========================================

* 重點 1 : "**多個處理同時存在**"
    - 同時存在即可，不一定要同時執行
    - Multithread on single-core CPU 就是同時存在但輪流執行
* 重點 2 : "**結果可以是 non-deterministic**"
    - 運算結果可以跟沒有 Concurrency 時不同
    - Multithread on multi-core CPU 沒加上 Data Synchronization 就是 non-deterministic
    - 例如輸出的順序不同即是 non-deterministic

Concurrency 的確抽象層次比 Multithread 高，
允許同時有好幾隻 process 但每隻只有一個 thread (user & kernel)，
也允許執行在多個不同的作業系統上。
反正東西有在處理就好，管你在哪裡、怎麼分配，很多人幫我跑就對了。
Concurrency 底下可以用 Multithread 來支援這樣的行為。


* `Wikipedia - Concurrency (computer science) <https://en.wikipedia.org/wiki/Concurrency_%28computer_science%29>`_

Multithread
========================================

重點 : "**多個 thread**"

Multithread 則是層級比 Concurrency 低的，
為單一作業系統上的狀況，
一隻 process 有多個 thread 共用資源在跑。


* `Wikipedia - Thread (computing) <https://en.wikipedia.org/wiki/Thread_%28computing%29#Multithreading>`_
* `Wikipedia - Multithreading (computer architecture) <https://en.wikipedia.org/wiki/Multithreading_%28computer_architecture%29>`_



Parallelism
========================================

* 重點 1 : "**多個處理同時進行**"
    - 是真的同時，而不是輪流做
    - Multithread on single-core CPU 就不符合這點
* 重點 2 : "**結果是 deterministic**"
    - 運算結果跟沒有 Parallelism 的情況要一模一樣
    - Multithread on multi-core CPU 要加上 Data Synchronization 才符合這點

Parallel 雖然和 Concurrency 非常相關，
但是兩個是不同的概念，
Parallel 的重點是事情真的 "同時" 在處理，
可以分成 bit-level、instruction level、data、task parallelism。

* parallelism without concurrency
    - bit-level parallelism
* concurrency without parallelism
    - multitasking by time-sharing on a single-core CPU

* `Wikipedia - Parallel computing <https://en.wikipedia.org/wiki/Parallel_computing>`_
* `Wikipedia - Very long instruction word <Very long instruction word>`_
* `Wikipedia - Parallel processing <https://en.wikipedia.org/wiki/Parallel_processing>`_
* `Parallelism Is Not Concurrency | Existential Type <https://existentialtype.wordpress.com/2011/03/17/parallelism-is-not-concurrency/>`_
