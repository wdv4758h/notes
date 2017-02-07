========================================
Parallel
========================================

.. contents:: Table of Contents


Introduction
========================================

為什麼需要平行化？
因為計算需求越來越大，
但是單顆 CPU 的效能已經遇到瓶頸，
原本可以藉由 CPU Clock Rate 的提升來獲得效能提升，
但是現在已經碰到一個上限，
CPU Clock Rate 再加下去會造成更多熱能產生，
能源使用效率也會下降，
然而單純的增加 CPU 數量並不會讓原本 Serial 的程式效能大幅提升，
另外 ILP (Instruction-Level Parallelism) 的效能提升在近幾年也逐漸趨緩，
因此軟體上的平行化變成了一個重要的 Topic。


平行化的程式通常由兩種方式來撰寫，
一個是使用明確地平行化的程式語言 (例如：High Performance Fortran)，
或是使用實作了平行化 Programming Model 的 Library，
這樣的例子有：

* Shared-memory library
    - Pthreads
    - OpenMP
* Distributed-memory library
    - MPI (Message Passing Interface)
* Heterogeneous-programming library
    - CUDA
    - OpenCL
* Cluster-based library
    - MapReduce


平行化程式撰寫步驟：

1. Decomposition (把計算分割成一個個 Task)
2. Assignment (把 Task 分派給 Process 或 Thread)
3. Orchestration (Data Access 或 Communication 等)
4. Mapping 到處理器上


Parallelism

* Task-Parallelism
    - 把問題的不同 Task 切割開，跟派給各個 Cores
* Data-Parallelism
    - 把問題的資料切割成數個相似的操作，分派給各個 Cores


Coordination

* Communication
    - 處理器間互相告知目前的部分結果
* Load Balancing
    - 盡量平均分配工作給每個處理器
* Synchronization
    - 有時候會需要每個處理器都處理到某個點的時候才繼續


Parallel Programming Models

* Control
* Data
* Synchronization
* Cost




Shared-Memory Systems
------------------------------

::

    +-----------+     +-----------+
    |           |     |           |
    | Processor |     | Processor |
    |       +---|-----|--+        |
    +-----------+     +-----------+
            |   Memory   |
    +-----------+     +-----------+
    |       +-- |-----|--+        |
    | Processor |     | Processor |
    |           |     |           |
    +-----------+     +-----------+



Distributed-Memory Systems
------------------------------

::

    +-----------+--------+      +-----------+--------+
    | Processor | Memory |      | Processor | Memory |
    +-----------+--------+      +-----------+--------+
                 |                           |
                 |       Network             |
    <------------+---------------------------+------->
                 |                           |
                 |                           |
    +-----------+--------+      +-----------+--------+
    | Processor | Memory |      | Processor | Memory |
    +-----------+--------+      +-----------+--------+



Hybrid Distributed-Memory Systems
---------------------------------

::

    +-----------+--------+      +-----------+--------+
    | Processor |        |      | Processor |        |
    +-----------+ Memory |      +-----------+ Memory |
    | Processor |        |      | Processor |        |
    +-----------+--------+      +-----------+--------+
                 |                           |
                 |       Network             |
    <------------+---------------------------+------->
                 |                           |
                 |                           |
    +-----------+--------+      +-----------+--------+
    | Processor |        |      | Processor |        |
    +-----------+ Memory |      +-----------+ Memory |
    | Processor |        |      | Processor |        |
    +-----------+--------+      +-----------+--------+
