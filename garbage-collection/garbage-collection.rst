========================================
Garbage Collection
========================================


.. contents:: 目錄


歷史
========================================

Garbage Collection 的技術誕生於 1960 年代，
John McCarthy 在開發 Lisp 程式語言時，
發明了 Garbage Collection 來實做程式語言，
當時提出了使用 Mark & Sweep 演算法搭配 DFS （depth-first search）來辨別仍然可以被存取到的變數。
其中 John McCarthy 一開始堅持 Lisp 的 S-expression 結構必須是「不可變動的（immutable）」，
允許利用 reference sharing 作為 copying 的內部實做，
這樣的優化技巧以及後來放鬆限制允許「可變動」的結構，
是為發想出 Garbage Collection 的動機。

在開始開發 Lisp 的 1958 年的 40 年後，
1998 年的 10 月，
展開了第一場 「International Symposium on Memory Management （簡稱 ISMM）」。



常見 Garbage Collection 技術
========================================

GC 的實做都基於四種基本的演算法改造而成，
分別為：

* Mark-Sweep GC
* Mark-Compact GC
* Copying GC
* Reference Counting


而 GC 要做的事情可以分成三件：

* 分配新空間
* 分辨 Live Objects 與 Garbages
* 回收 Garbages


Mark-Sweep GC
------------------------------

為最早出現，
簡單且非常常見的 GC 演算法，
會先標記所有可以追蹤到的物件（也就是 Live Objects），
剩餘的則是 Garbages，
接著進行回收，
此過程會造成程式暫停執行其他工作，
此現象稱為「Stop The World」。


Tricolor
++++++++++++++++++++

Bitmap
++++++++++++++++++++

Lazy Sweeping
++++++++++++++++++++


Mark-Compact GC
------------------------------

在程式一開始，我們會有連續的可用記憶體可以分配，
但隨著執行時間變長，
在反覆地記憶體分配與重新分配中，
很容易出現記憶體破碎化的狀況（Memory Fragmentation），
這會造成至少兩個問題：

1. 雖然我們還有許多破碎的小空間，但是我們無法找到足夠大的連續空間分配給接下來的使用，造成要不到記憶體。在沒有使用 GC 的程式中，這通常會造成程式終止。在有 GC 的程式中，會過於頻繁地觸發 GC 運作，來嘗試清出空間。

2. 就算記憶體足夠，記憶體破碎化還是可能造成程式使用更多的 Address Space、Pages、Cache Lines，因此造成效能變差。

要完全避免記憶體破碎化是不太可能的，
一來是不能預測未來一連串的記憶體分配請求，
二來是就算知道接下來一連串的記憶體分配請求，
要最佳地分配好也是 NP-hard 的問題（[robs80]_）。

我們雖然不完全避免記憶體破碎化，
但是我們可以管理，
在「記憶體分配速度」和「記憶體破碎化」之間取一個平衡點。
而管理的方式就是利用「Compaction」或「Copying」技術，
說白了就是整理記憶體內使用的區塊，
把使用的部份集中起來。

在使用 Compaction 整理的時候會依照特定的整理原則，
常見的整理原則有三種：

* Arbitary：不管原本記憶體位址的順序，也不管是否有指到其他人
* Linearising：物件會被分配到和自己比較相關的物件的附近（例如資料結構內為 siblings）
* Sliding：物件會直接被擠到 Heap 的某一邊，保持原本的順序，並把 Garbage 擠去另外一邊

大部分的實做會選擇 Arbitary 或 Sliding。
Arbitary 實做容易且執行快速，
尤其是各節點都是同樣大小時，
但是不會保留原本的相對順序，
會對 mutator 造成 Spatial Locality 的問題（Pages、Cache Lines）
（已經有論文和實驗證實更改物件原本的順序會造成 Throughput 大幅下降 [abua04]_）。
現代的 Compaction 大多使用 Sliding，
不會改變相對的順序，
相比 Arbitary 所會遇到的 Spatial Locality 問題較小。

另外 Copying 則是可以更進一步地改善 Spatial Locality 的問題，
因為 siblings 都會放在比較靠近的位置。

參考：

* `Compacting Garbage Collection in SpiderMonkey <https://hacks.mozilla.org/2015/07/compacting-garbage-collection-in-spidermonkey/>`_


Two-Finger Compaction
+++++++++++++++++++++

Lisp 2 Algorithm
++++++++++++++++++++

Threaded Compaction
++++++++++++++++++++

One-pass Compaction
++++++++++++++++++++


Copying GC
---------------------------------


Generational Mark & Sweep GC
---------------------------------

Generational garbage collection 的核心觀念就是「大多數的物件的生命都很短」，
所以就修改原本的 GC 設計，依照不同的存在時間有不同的處理方式，
對於 Tracing 的 GC 會需要去掃過物件來檢查是否有物件已經成為 Garbage，
當程式會製造出大量的物件時，檢查的時間就會上升，這時如果用已經存在的時間來區分，
而做不同的處理方式時，多數的短期物件就可以更快的被回收，也不必頻繁檢查會長期存在的物件。

* SpiderMonkey 利用了這種方式來讓 temporary objects 的 penalty 下降
* [1984] `Garbage collection in a large Lisp system <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.122.4295>`_


Nursery & Tenured
++++++++++++++++++++

多數的 objects 都會 allocate 到一個叫做 Nursery 的 memory region，
當 Nursery 滿的時候，只檢查 Nursery 裡的 objects，此時多數的 short-lived temporary objects 就會被清掉，
而這樣的檢查相對於原本 (檢查全部的 objects) 也來的快

此時，依然存活的 objects 就會被放到 Tenured region

Tenured heap 仍然會回收 grabage，但是頻率會比 Nursery 來的低

最終然會需要原整的 GC，但是頻率也會比 Nursery GC 來的低

所以就分成下面這種情況

.. table::
    :class: table table-bordered

    +--------------------+------------+-----------+-------+
    | Garbage Collection | Scan Place | frequency | speed |
    +====================+============+===========+=======+
    | minor GCs          | Nursery    | high      | fast  |
    +--------------------+------------+-----------+-------+
    | major GCs          | full heap  | low       | slow  |
    +--------------------+------------+-----------+-------+

.. table::
    :class: table table-bordered

    +---------------+-------+
    | memory region | age   |
    +===============+=======+
    | Nursery       | young |
    +---------------+-------+
    | Tenured       | old   |
    +---------------+-------+



Reference Counting
------------------------------

* 問題在 reference cycle，會需要一個 cycle detect algorithm 來爬過所有 objects，但這就會產生 undeterministic GC pause


Incremental
------------------------------

拆散整個 GC 過程，把每次暫停的時間縮短


Parallel GC
---------------------------------


Concurrent GC
---------------------------------


Real-time GC
---------------------------------



案例研究
========================================

OpenJDK
------------------------------

參考：

* `JEP 189: Shenandoah: An Ultra-Low-Pause-Time Garbage Collector <http://openjdk.java.net/jeps/189>`_
* `JEP 248: Make G1 the Default Garbage Collector <http://openjdk.java.net/jeps/248>`_
* `JEP 291: Deprecate the Concurrent Mark Sweep (CMS) Garbage Collector <http://openjdk.java.net/jeps/291>`_
* [2014][YouTube] `"Shenandoah: An open source pauseless GC for OpenJDK." by Christine Flood <https://www.youtube.com/watch?v=QcwyKLlmXeY>`_
* [2016] `Shenandoah GC: Java Without The Garbage Collection Hiccups (Christine Flood) <http://www.slideshare.net/RedHatDevelopers/shenandoah-gc-java-without-the-garbage-collection-hiccups-christine-flood>`_


SerialGC
++++++++++++++++++++

特色：

* Small Footprint
* Minimal Overhead


ParallelGC
++++++++++++++++++++

特色：

* High Throughput


CMS (ParNew/Concurrent Mark Sweep)
++++++++++++++++++++++++++++++++++

特色：

* Minimal Pause Time
* 有 Concurrent Marking
* 在 pause time 進行 young generation copying
* 不會對 old generation 進行 Compaction


G1 (Garbage First)
++++++++++++++++++++

特色：

* Managed Pause Times
* 有部份 Parallel 和 Concurrent
* 有 Compaction
* 沒有 Concurrent Evacuation


Shenandoah
++++++++++++++++++++

目標：<10 ms GC pause times for 100GB+ Heaps

此 GC 的目標是要提供極低（ultra-low）的 pause time，
先前的 CMS 和 G1 都已經可以 Concurrent 地進行 live objects marking，
Shenandoah 則是讓 Compaction 也可以 Concurrent 地進行。


Azul
------------------------------

C4 (Continuously Concurrent Compacting Collector)
+++++++++++++++++++++++++++++++++++++++++++++++++

特色：

* Pauseless

參考：

* `Azul C4 Garbage Collector <https://www.azul.com/resources/azul-technology/azul-c4-garbage-collector/>`_
* `Understanding Java Garbage Collection <https://www.azul.com/files/Understanding_Java_Garbage_Collection_v41.pdf>`_
* [Paper] `C4: The Continuously Concurrent Compacting Collector <https://www.azul.com/files/c4_paper_acm1.pdf>`_
* `JVM performance optimization, Part 4: C4 garbage collection for low-latency Java applications <http://www.javaworld.com/article/2078661/java-concurrency/jvm-performance-optimization--part-4--c4-garbage-collection-for-low-latency-java-ap.html>`_


Go
------------------------------

PyPy
------------------------------

Boehm
------------------------------

LuaJIT
------------------------------


參考
========================================

* `Wikipedia - Mark-compact algorithm <https://en.wikipedia.org/wiki/Mark-compact_algorithm>`_
* `the Garbage Collection Bibliography <https://www.cs.kent.ac.uk/people/staff/rej/gcbib/>`_
* `Garbage collection thoughts <http://sebastiansylvan.com/post/garbage-collection-thoughts/>`_
* `Origins of Garbage Collection <https://www.seas.harvard.edu/courses/cs252/2016fa/16.pdf>`_
* `International Symposium on Memory Management (ISMM) <http://www.sigplan.org/Conferences/ISMM/>`_

.. [robs80] [1980] J. M. Robson. `Storage allocation is NP-hard <http://dx.doi.org/10.1016/0020-0190(80)90124-6>`_
.. [abua04] [2004] Diab Abuaiadh, Yoav Ossia, Erez Petrank, and Uri Silbershtein. `An efficient parallel heap compaction algorithm <https://www.research.ibm.com/haifa/projects/systems/rs/papers/ParCompac_OOPSLA04.pdf>`_
