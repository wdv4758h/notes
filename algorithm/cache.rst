========================================
Cache
========================================


.. contents:: 目錄


介紹
========================================

* LRU (Least Recently Used)
* LFU (Least Frequently Used)
* LRFU (LRU + LFU)
* ARC (Adaptive Replacement Cache)
* LIRS (Low Inter-reference Recency Set)
* W-TinyLFU (Window TinyLFU)
* Bélády's optimal
    - 演算法假設能知道未來再也不會用到某值，故無法實作，可以當成 Cache 演算法的 Upper Bound



Example
========================================

O* nuances

+-------------+-----------+---------------------------+
|             | Traversal | Cache Misses in Traversal |
+-------------+-----------+---------------------------+
| Array       | O(N)      | O(0)                      |
+-------------+-----------+---------------------------+
| Linked List | O(N)      | O(N)                      |
+-------------+-----------+---------------------------+



參考
========================================

* `Wikipedia - Cache replacement policies <https://en.wikipedia.org/wiki/Cache_replacement_policies>`_
* `Wikipedia - Page replacement algorithm <https://en.wikipedia.org/wiki/Page_replacement_algorithm>`_
* `Why Intel Added Cache Allocation Technology in Broadwell <http://danluu.com/intel-cat/>`_
* `Cache is the new RAM <http://carlos.bueno.org/2014/11/cache.html>`_
* `Cache Efficiency <https://github.com/ben-manes/caffeine/wiki/Efficiency>`_
* `Wikipedia - Cache algorithms <https://en.wikipedia.org/wiki/Cache_algorithms>`_
* [2015] `TinyLFU: A Highly Efficient Cache Admission Policy <https://arxiv.org/abs/1512.00727>`_
