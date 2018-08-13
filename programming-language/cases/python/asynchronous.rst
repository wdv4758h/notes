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


asyncio 搭配 ThreadPoolExecutor
--------------------------------


.. code-block:: python

    import asyncio
    import concurrent.futures


    def test(name):
       import os
       import time
       time.sleep(5)
       pid = os.getpid()
       print(f"{name}: {pid}")

    def run_in_thread(func, *args, loop=None, executor=None, **kwrags):
        """
        We are talking about Python thread here.

        With this function we can offload some sync task to other thread,
        so it won't block the event loop thread.

        The OS thread underneath will still be 1 due to CPython implementation.
        """

        if loop is None:
            loop = asyncio.get_event_loop()
        if executor is None:
            executor = concurrent.futures.ThreadPoolExecutor(max_workers=1)
        return loop.run_in_executor(executor, func, *args, **kwrags)

    async def task_maker(loop=None):
        for i in range(100):
            await asyncio.sleep(0.1)
            run_in_thread(test, f"c{i}")

    async def event_loop_report():
        import threading
        loop = asyncio.get_event_loop()
        while True:
            task_count = len(asyncio.Task.all_tasks(loop))
            thread_count = threading.active_count()
            # task count 2, thread count "1 ~ 5x"
            print(f"task count {task_count}, thread count {thread_count}")
            await asyncio.sleep(1)

    def run():
        loop = asyncio.get_event_loop()
        futures = asyncio.gather(task_maker(), event_loop_report())
        try:
            loop.run_until_complete(futures)
        finally:
            loop.run_until_complete(loop.shutdown_asyncgens())
            loop.close()

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

* `PEP 492 -- Coroutines with async and await syntax <https://www.python.org/dev/peps/pep-0492/>`_
    - 假定 Asynchronous 的工作都會被 Event Loop 排程、掌控
    - 只跟「使用 yield 來作為給排程器的訊號表示要等到 event 結束」的 coroutine 有關
    - 區隔 native coroutine 和 generator
    - 先前問題
        + 既有的 coroutine via generator 容易讓人搞混
        + 因為共用語法所以容易讓人搞混一般的 generator 和 coroutine
        + 函式是否是 coroutine 取決於裡面是否有使用 yield 和 yield from，這容易造成誤會或是在重構時發生意外
        + 支援 Asynchronous 呼叫時受限於 yield 的語法，無法和 with 或 for 搭配使用
    - 這個 PEP 讓 coroutine 成為 Python 的原生語言特色，並且跟 generator 區隔
    - 用語
        + native coroutine：使用新語法的函式
        + generator-based coroutine：使用 generator 語法的 coroutine
        + coroutine：以上兩種
    - ``async def`` 表示這函式永遠都是 coroutine
        + 在裡面使用 ``yield`` 或 ``yield from`` 是 SyntaxError
        + CPython code object 新增
            * ``CO_COROUTINE`` 表示 native coroutine
            * ``CO_ITERABLE_COROUTINE`` 表示 generator-based coroutine
        + StopIteration 不會傳到 coroutine 外，出去會變成 RuntimeError
        + 當 native coroutine 被 GC 時，如果沒有被 ``await`` 過會噴 RuntimeWarning
    - ``@types.coroutine`` 可以用於銜接現有的 generator-based coroutines 和 native coroutine
    - ``await`` 會用來取得 coroutine 的結果，取代先前 generator-based coroutine 中的 ``yield from``
    - 在 ``async def`` 外使用 ``await`` 是 SyntaxError
    - ``async with`` 作為 asynchronous context managers
    - ``async for`` 搭配 asynchronous iterable
    - asynchronous iterable 最後會 raise ``StopAsyncIteration`` ，因為其他 exception 會被轉成 RuntimeError
    - ``PYTHONASYNCIODEBUG``
* asyncio.Future
* `Python Documentation - asyncio — Asynchronous I/O, event loop, coroutines and tasks <https://docs.python.org/3/library/asyncio.html>`_
* `Python Documentation - Develop with asyncio <https://docs.python.org/3/library/asyncio-dev.html>`_
* `Python Documentation - Base Event Loop <https://docs.python.org/3/library/asyncio-eventloop.html>`_
* `uvloop - Blazing fast Python networking — magicstack <https://magic.io/blog/uvloop-blazing-fast-python-networking/>`_
