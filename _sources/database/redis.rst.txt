========================================
Redis
========================================


.. contents:: 目錄


介紹
========================================

:Site: https://redis.io/
:Repo: https://github.com/antirez/redis/


Redis 是 in-memory 的資料儲存軟體，
可以把他當資料庫或者是 message broker 使用。

另外 Redis 支援撰寫 extension，
所以有不少第三方模組可以使用。



基本指令
========================================

用 ``redis-cli`` 連到 Redis

.. code-block:: sh

    $ redis-cli
    # monitor 可以監控所有事件
    127.0.0.1:6379> monitor



參考
========================================

* `Redis - Pub/Sub <https://redis.io/topics/pubsub>`_
* `Redis Modules 列表 <https://redis.io/modules>`_
* `Redis Labs Modules <https://github.com/RedisLabsModules>`_
* `Redis Labs <https://github.com/RedisLabs>`_
* `Redis Cheat Sheet <https://lzone.de/cheat-sheet/Redis>`_
* `Redis Full Commands List <https://redis.io/commands>`_
* `Redis 設計與實現 <http://redisbook.com/>`_
