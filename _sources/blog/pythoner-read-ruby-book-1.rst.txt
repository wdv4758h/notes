:title: Pythoner 讀 「松本行弘的程式世界」 - part 1
:slug: pythoner-read-ruby-book-1
:date: 2014-10-10 16:20
:category: Misc
:tags: book
:author: wdv4758h
:summary: 讀書紀錄

這邊是讀了書上內容的節錄和獨後自己查的資料

目前心得 : 可以看到一些觀念，但是有些例子就 ... (尤其是少部份有提到 Python 的)

ch 14-1 - functional programming
========================================

是的沒錯，我第一個翻的章節是 chapter 14 ...

Fortran 設計者為 John Backus (John Backus 還發明了 BNF)，
其在 1997 年 Turing Award 上發表的語言 "FP" 被認為是 Functional Programming 的起點

Feature:

- Higher-order function
- pure function (no side effect)
    * Referential transparency

Lisp
------------------------------

Lisp 的基礎是 Alonzo Church 提的 lambda calculus，也支援 Higher-order function

Lisp 具有一些 functional 的特性，但不是純粹的 functional

Lisp 最大的特色是 S-expression

另一個特色是 list (LISP = LISt Processing)，Lisp 把節點稱為 cons cell，
cons 是從建立新 cell 的 function : cons (construct) 而來，
而一開始的 Lisp 環境把第一個資料放在 address register，第二個放在 data register，
所以 car = content of address register、cdr = content of data register，
構成 list 的資料成為 atom (symbol or number)

cons cell:

.. table::
    :class: table table-bordered

    +-----+-----+
    | car | cdr |
    +-----+-----+

Lisp 的 list 底下結構是 singly linked-list

Haskell
------------------------------

Haskell Curry 的 Combinatory logic 和 Alonzo Church 的 lambda calculus 幾乎相同的東西

Haskell feature:

- no side effect
- Higher-order function
- partial function application
- lazy evaluation
- type inference
- list comprehension
- block by indent

Haskell 有靜態多型的型別系統和 type inference，可以在接近 duck typing 的情況下，
在編譯時完成 type checking

OCaml
------------------------------

OCaml 歷史比 Haskell 早，誕生於法國

和 Haskell 相比有些不同:

- has side effect
- no lazy evaluation
- module system

OCaml 想要 lazy evaluation 時可以明確標示

Erlang
------------------------------

Erlang 是為了平行處理而設計的，設計受到 Prolog 影響

dynamic type, no lazy evaluation

以 actor 理論為基礎

Ruby
------------------------------

- Block
- Proc object
- lambda

- enumerator

- `What Is the Difference Between a Block, a Proc, and a Lambda in Ruby? <http://awaxman11.github.io/blog/2013/08/05/what-is-the-difference-between-a-block/>`_

.. code-block:: ruby

    [1,2,3].each { |x| puts x*2 }

    [1,2,3].each do |x|
        puts x*2         # block is everything between the do and end
    end

    lam = lambda { |x| puts x*2 }
    [1,2,3].each(&lam)

    p = Proc.new { |x| puts x*2 }
    [1,2,3].each(&p)     # The '&' tells ruby to turn the proc into a block

ch 14-2 Code Generation
------------------------------

nothing

ch 14-3 Memory Management
------------------------------

因為一些概念之前有看過了，所以這邊算是複習和加強 XD

Garbage Collection 的誕生是在 1960 年代，
起因於 Lisp 需要產生大量 cons cell object，不能明確管理各個 object

GC 衡量:

- GC 所佔的時間比例
- Pause Time
    * 平均 pause time
    * 最長的 pause time

no GC
++++++++++++++++++++

例如 C 或 C++，programmer 自己管理 memory，自己 malloc/free、new/delete

programmer 沒把程式寫好會造成:

- dangling pointer (因為把還在用的 free 掉了)
- memory leak (該 free 的沒 free 到)
- double free

要檢查這些問題可以使用 valgrind

GC algorithm
++++++++++++++++++++

.. table::
    :class: table table-bordered

    +--------------------+-------------------------------------------------------+----------------------------------+
    | Algorithm          | Description                                           | Problem                          |
    +====================+=======================================================+==================================+
    | reference counting | 用一數字紀錄被 reference 的次數，最容易實作           | - cycle reference                |
    |                    |                                                       | - 不適合平行處理                 |
    +--------------------+-------------------------------------------------------+----------------------------------+
    | mark & sweep       | 把 trace 的到的 objects 做標記，沒標到的清掉          | - objects 量上升時，速度容易下降 |
    +--------------------+-------------------------------------------------------+----------------------------------+
    | mark & compact     | 把 trace 的到的 objects 做標記，                      | - 比 mark & sweep 慢             |
    |                    | 接著把標過的集合起來，                                | - 不能使用保守 GC                |
    |                    | 如此一來 memory 操作就有了區域性，                    |                                  |
    |                    | 讓快取之類的機制效率提高                              |                                  |
    +--------------------+-------------------------------------------------------+----------------------------------+
    | copying            | 把還在用的複製一份到新的 memory 區域 (會分成新和舊)， |                                  |
    |                    | 接著把舊區域整個清掉                                  |                                  |
    +--------------------+-------------------------------------------------------+----------------------------------+

.. table::
    :class: table table-bordered

    +----------------+---------------------------------------------------------------------------------------------+
    | Algorithm      | Description                                                                                 |
    +================+=============================================================================================+
    | Generational   | 多數 objects 會在短時間內變成 garbage，所以可以用 age 做不同處理，                          |
    |                | 會分成 minor GC 和 major GC，                                                               |
    |                | 有 write barrier (紀錄 old object 裡用到 young object 的狀況，這紀錄稱為 remembered set)    |
    +----------------+---------------------------------------------------------------------------------------------+
    | Conservative   | 在 C 這種本來沒有 GC 的語言，compile 後就沒有區分 integer 和 pointer 的資訊，               |
    |                | 因為 CPU 不需要，這時可以使用 Conservative 實作，概念是 "碰到 address 相同時，              |
    |                | 代表可能被引用，視為存活"                                                                   |
    |                |                                                                                             |
    |                | (heap 會整個被掃過)                                                                         |
    +----------------+---------------------------------------------------------------------------------------------+
    | Incremental    | 把 GC 操作切割，以降低每次 GC 的最長時間，也用了 write barrier                              |
    +----------------+---------------------------------------------------------------------------------------------+
    | Concurrent     | 機制和 Incremental GC 類似，利用 write barrier 維持狀態資訊，實作時也可能有專用的 GC thread |
    +----------------+---------------------------------------------------------------------------------------------+
    | Bitmap Marking | Linux 這類 Unix-like 在 fork 時 memory addres 是 copy-on-write 的，                         |
    |                | 可以避免不必要的 page copy，但是和 GC 的搭配不太好，GC 在改動時就會大量複製，               |
    |                | Bitmap Marking 就是用來降低複製 page 的次數，不時直接對 object 做標記，                     |
    |                | 而是有另外的空間用於標記，所以複製的只有標記用的 Bitmap                                     |
    +----------------+---------------------------------------------------------------------------------------------+

ch 14-4 Ruby with C
========================================

介紹 Ruby 如何和 C 一起用

ch 14-5 Open Source
========================================

Open Source 發展簡史
