========================================
Garbage Collection
========================================


.. contents:: 目錄


歷史
========================================



常見 Garbage Collection 技術
========================================

Reference Counting
------------------------------

* 問題在 reference cycle，會需要一個 cycle detect algorithm 來爬過所有 objects，但這就會產生 undeterministic GC pause


Stop-the-world Mark & Sweep
------------------------------

非常常見的 GC 演算法


Generational Mark & Sweep
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


Incremental
------------------------------

拆散整個 GC 過程，把每次暫停的時間縮短


Compacting
------------------------------

為了減少記憶體的破碎化

* `Compacting Garbage Collection in SpiderMonkey <https://hacks.mozilla.org/2015/07/compacting-garbage-collection-in-spidermonkey/>`_



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



參考
========================================

* `Garbage collection thoughts <http://sebastiansylvan.com/post/garbage-collection-thoughts/>`_
