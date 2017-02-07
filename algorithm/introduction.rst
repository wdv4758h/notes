========================================
演算法與資料結構
========================================


.. contents:: 目錄


介紹
========================================

演算法與資料結構是資訊領域中非常重要的一塊，
好的演算法可以節省時間和資源，
但是演算法何其多，
這邊只斷斷續續紀錄些許東西，
另外繁體中文資料中最齊全的網站應該屬「 `演算法筆記 <http://www.csie.ntnu.edu.tw/~u91029/>`_ 」莫屬，
可以多加利用。



Big O Notation
========================================


排序（Sort）
========================================


搜尋（Search）
========================================

Binary Search
------------------------------



圖像搜尋（Graph Search）
========================================

（先前修人工智慧時，有寫了一些相關的筆記，之後可以整理過來）


General
------------------------------

BFS
++++++++++++++++++++


Heuristic
------------------------------



Hash Table
========================================


Greedy
========================================



Dynamic Programming
========================================



Search Trees
========================================

Binary Search Tree
------------------------------

Red-Black Tree
------------------------------



Heaps
========================================

Binary Heap
------------------------------



Tries
========================================



Spatial Data Partitioning Trees
========================================

k-d tree
------------------------------



Other Trees
========================================



Probabilistic Data Structures
========================================

Probabilistic Data Structures 的特點在於告訴你「可能的」狀態，
不是確切的狀況，
適用於資料量大且計算不需要非常精確的狀況，
可以節省資源和時間。


參考：

* `PipelineDB - Probabilistic Data Structures & Algorithms <http://docs.pipelinedb.com/probabilistic.html>`_


Bloom Filter
------------------------------

Bloom Filter 的用途在測試一個值是否在一個集合內，
會有 False Positive（也就是不在集合內，卻回報有在集合內），
但是不會有 False Negaative（也就是是回報沒有在集合內，就真的不在集合內），
False Positive 的程度會受到使用的記憶體量和 Hash 方法影響，
使用越多的記憶體可以降低 False Positive。

Bloom Filter 為 m bits 的 array，
全部都初始化為 0，
另外搭配 k 個 Hash 函式（k 比 m 小很多）。

Bloom Filter 支援兩種操作：

* 新增數值：數值經過 k 個 Hash 函式處理後取得 array index，把值標為 1
* 檢驗數值：數值經過 k 個 Hash 函式處理後取得 array index，如果 array 內的值為 0，則該數值真的不在這個集合中，如果 array 內的值為 1，則該數值「可能」在這個集合中


Bloom Filter 的 False Positive Rate：

.. image:: /images/algorithm/bloom-filter-false-positive-rate.svg


特性：

* 少量的記憶體可以代表大量的數值，但是 False Positive 會上升
* 聯集和交集可以 Bitwise OR 和 Bitwise AND 實做


使用案例：

* 數個資料庫用於減少為了不存在的資料去存取硬碟（例如 Google BigTable、Apache HBase、Apache Cassandra、PostgreSQL）
* Akamai 發現該公司的 web server 有將近 3/4 的 request 是一次性的，所以利用 Bloom Filter 來檢驗，當 request 重複出現時才存到 cache，可以減少硬碟 loading 和增加 cache 的 hit rate
* Google Chrome 用於偵測可能有害的網站 URL
* Squid 用於 Cache
* Bitcon 用於加速同步
* Medium 用於避免推薦使用者已經讀過的文章


參考：

* `Bloom Filters by Example <https://llimllib.github.io/bloomfilter-tutorial/>`_
* `Wikipedia - Bloom Filter <https://en.wikipedia.org/wiki/Bloom_filter>`_


HyperLogLog
------------------------------

* `Wikipedia - HyperLogLog <https://en.wikipedia.org/wiki/HyperLogLog>`_


Count-Min Sketch
------------------------------


Locality-sensitive Hashing
========================================

MinHash
------------------------------

SimHash
------------------------------



Linear Programming
========================================



書籍
========================================

* [2016] `Grokking Algorithms: An illustrated guide for programmers and other curious people <https://www.manning.com/books/grokking-algorithms>`_
    - 入門級好書
