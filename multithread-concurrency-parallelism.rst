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


Concurrency
========================================

重點 : "**多個處理同時存在**"

Concurrency 的確抽象層次比較高的，
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

重點 : "**多個處理同時進行**"

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
