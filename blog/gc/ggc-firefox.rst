:title: Generational Garbage Collection for SpiderMonkey
:slug: ggc-spidermonkey
:date: 2014-09-26 12:27
:category: GC
:tags: gc
:author: wdv4758h
:summary: GGC has now been enabled in the SpiderMonkey in Firefox 32

原文章 : `Generational Garbage Collection in Firefox <https://hacks.mozilla.org/2014/09/generational-garbage-collection-in-firefox/>`_

今天看到上面那篇 SpiderMonkey 的 Generational Garbage Collection 的文章，
就讀一讀理解一下並做些紀錄

Generational garbage collection
========================================

Generational garbage collection 的核心觀念就是 "大多數的物件的生命都很短"，
所以就修改原本的 GC 設計，依照不同的存在時間有不同的處理方式，
對於 Tracing 的 GC 會需要去掃過物件來檢查是否有物件已經成為 Garbage，
當程式會製造出大量的物件時，檢查的時間就會上升，這時如果用已經存在的時間來區分，
而做不同的處理方式時，多數的短期物件就可以更快的被回收，也不必頻繁檢查會長期存在的物件。

原文章裡的 SpiderMonkey 利用了這種方式來讓 temporary objects 的 penalty 下降

Nursery & Tenured
========================================

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

Problem
========================================

Tenured object 裡面可能有指向 Nursery object 的資料
(Nursery objects 因為某些 Tenured objects 而持續 alive)

解法一
------------------------------

掃過整個 Tenured heap 來找出指到 Nursery objects 的 pointer，
但是這麼做的話就違背了 GGC 的設計本意，所以需要更 cheap 的解決方案

解法二
------------------------------

先注意到，在 heap graph 中 Tenured 指向 Nursery 的 edges 不會存在很久，
因為接下來 minor GC 就會把 Nursery 中的 survivors 移到 Tenured heap

所以我們在意的是從上次 minor/major GC 後，有更動過的 Tenured objects，
而這些 objects 的數量相對來說就會比較少

因此我們做的是在更動 Tenured objects 時，檢查是否有 Nursery pointers，
如果有的話就把這些 cross-generational edges 紀錄到 **store buffer** ，
這樣的事情稱為 write barrier

在 minor GC 時，我們就跑過一遍 store buffer 裡的資料並且把裡面的 Nursery objects 標記為存在

(edge 的來源都需要被使用，因為當 Nursery objects 被標記為存在之後，將會移往 Tenured area，
所以原本的 Tenured (裡面有指向 Nursery 的 pointer) 也需要被 update

minor GC 需要的執行時間決定於新 cross-generational edges 和 Nursery 裡的 objects 數量，
當然，追蹤 store buffer records 或是單純的檢查是否要新增 record 都會讓 normal heap access 有些許的效能損失，
所以某些 code 可能在 GGC 裡會變慢一些
