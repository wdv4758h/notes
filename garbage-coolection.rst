========================================
Garbage Collection
========================================

Background
========================================

Reference Counting
========================================

* 問題在 reference cycle，會需要一個 cycle detect algorithm 來爬過所有 objects，但這就會產生 ondeterministic GC pause

Tracing
========================================

mark-and-sweep
------------------------------

Generational
========================================

Generational garbage collection 的核心觀念就是 "大多數的物件的生命都很短"，
所以就修改原本的 GC 設計，依照不同的存在時間有不同的處理方式，
對於 Tracing 的 GC 會需要去掃過物件來檢查是否有物件已經成為 Garbage，
當程式會製造出大量的物件時，檢查的時間就會上升，這時如果用已經存在的時間來區分，
而做不同的處理方式時，多數的短期物件就可以更快的被回收，也不必頻繁檢查會長期存在的物件。

* SpiderMonkey 利用了這種方式來讓 temporary objects 的 penalty 下降

Nursery & Tenured
------------------------------

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
========================================

拆散整個 GC 過程，把每次暫停的時間縮短
