========================================
Asynchronous
========================================


.. contents:: 目錄


asyncio
========================================

:Docs: https://docs.python.org/3/library/asyncio.html

asyncio 的 event loop 實做是可以自己替換的。



範例
========================================

包裝 Sync 函式成 Async 函式
------------------------------

.. code-block:: python

    import asyncio
    from functools import wraps, partial


    def sync_to_async(func):
        """
        Example:

        >>> @sync_to_async
        ... def sync_func():
        ...     pass

        """

        @wraps(func)
        async def run(*args, loop=None, executor=None, **kwargs):
            if loop is None:
              loop = asyncio.get_event_loop()
            f = partial(func, *args, **kwargs)
            return await loop.run_in_executor(executor, f)
        return run


    @sync_to_async
    def test(name):
        import time
        time.sleep(5)
        return f"Hello {name}"

    def run():
        loop = asyncio.get_event_loop()
        future = asyncio.gather(test("c1"), test("c2"), test("c3"))
        # will show "['Hello c1', 'Hello c2', 'Hello c3']" in 5 seconds
        print(loop.run_until_complete(future))

    run()



包裝 Async 函式成 Sync 函式
------------------------------

.. code-block:: python

    import asyncio
    from functools import wraps, partial


    def async_to_sync(func):
        """
        Example:

        >>> @async_to_sync
        ... async def async_func():
        ...     pass

        """

        @wraps(func)
        def run(*args, loop=None, executor=None, **kwargs):
            if loop is None:
              loop = asyncio.get_event_loop()
            return loop.run_until_complete(func(*args, **kwargs))
        return run


    @async_to_sync
    async def test(name):
        await asyncio.sleep(5)
        return f"Hello {name}"

    def run():
        print(test("c1"))

    run()


asyncio 搭配 ProcessPoolExecutor
--------------------------------


.. code-block:: python

    import asyncio
    import concurrent.futures


    def test(name):
       import os
       import time
       time.sleep(1)
       pid = os.getpid()
       return f"{name}: {pid}"

    def run():
        executor = concurrent.futures.ProcessPoolExecutor(max_workers=3)
        loop = asyncio.get_event_loop()
        # need "pickle" support for function running in different processes
        futures = [loop.run_in_executor(executor, test, f"c{i}") for i in range(5)]
        # make a meta future for waiting
        future = asyncio.gather(*futures)
        # e.g. "['c0: 26902', 'c1: 26903', 'c2: 26904', 'c3: 26902', 'c4: 26903']"
        print(loop.run_until_complete(future))

    run()


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
