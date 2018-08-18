========================================
Cache
========================================


.. contents:: 目錄


介紹
========================================

* LRU cache (Least Recently Used)
* Adaptive Replacement Cache
* Low Inter-reference Recency Set
* Window TinyLfu
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



相關實做
========================================

Memcached
------------------------------

:Site: https://memcached.org/
:Repo: https://github.com/memcached/memcached
:Language: C


預設是 LRU cache


Redis
------------------------------

:Site: http://redis.io/
:Repo: https://github.com/antirez/redis/
:Language: C


可以想像為功能更複雜的 Memcached



參考
========================================

* `Why Intel Added Cache Allocation Technology in Broadwell <http://danluu.com/intel-cat/>`_
* `Cache is the new RAM <http://carlos.bueno.org/2014/11/cache.html>`_
* `Cache Efficiency <https://github.com/ben-manes/caffeine/wiki/Efficiency>`_
* `Wikipedia - Cache algorithms <https://en.wikipedia.org/wiki/Cache_algorithms>`_
* [2014] `TinyLFU: A Highly Efficient Cache Admission Policy <http://www.cs.technion.ac.il/~gilga/TinyLFU_PDP2014.pdf>`_
