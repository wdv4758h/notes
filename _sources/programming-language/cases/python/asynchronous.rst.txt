========================================
Asynchronous
========================================


.. contents:: 目錄


asyncio
========================================

:Docs: https://docs.python.org/3/library/asyncio.html

asyncio 的 event loop 實做是可以自己替換的。



uvloop
========================================

:Repo: https://github.com/MagicStack/uvloop


利用 Cython 寫的，底下接 ``libuv`` ，
目的是直接取代 Standard Library 內的 ``asyncio`` ，
需要 Python 3.5 以上。



aiohttp - Async HTTP client/server framework
============================================

:Repo: https://github.com/aio-libs/aiohttp


底下的 Worker 目前有：

* GunicornWebWorker
* GunicornUVLoopWebWorker
* GunicornTokioWebWorker


``GunicornTokioWebWorker`` 是基於 Rust 的 `Tokio 的 Python 包裝 <https://github.com/PyO3/tokio>`_ ，
這個 Worker 目前還在實驗、開發中，
其他 Worker 則是穩定發行了。



參考
========================================

* `asyncio — Asynchronous I/O, event loop, coroutines and tasks <https://docs.python.org/3/library/asyncio.html>`_
* `uvloop - Blazing fast Python networking — magicstack <https://magic.io/blog/uvloop-blazing-fast-python-networking/>`_
