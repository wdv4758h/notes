========================================
Python's Concurrency
========================================


.. contents:: 目錄


concurrent.futures
========================================

:Docs: https://docs.python.org/3/library/concurrent.futures.html


基本使用
------------------------------

concurrent.futures 提供了高階的界面來操作，
在使用上更方便。


Thread:

.. code-block:: python

    from concurrent.futures import ThreadPoolExecutor

    with ThreadPoolExecutor(max_workers=1) as executor:
        future = executor.submit(pow, 323, 1235)
        print(future.result())


Process:

.. code-block:: python

    from concurrent.futures import ProcessPoolExecutor

    with ProcessPoolExecutor(max_workers=1) as executor:
        future = executor.submit(pow, 323, 1235)
        print(future.result())


timeout
------------------------------

.. code-block:: python

    from concurrent.futures import ProcessPoolExecutor, TimeoutError
    import time

    def stop_process_pool(executor):
        for pid, process in executor._processes.items():
            process.terminate()
        executor.shutdown()

    with ProcessPoolExecutor(max_workers=1) as executor:
        future = executor.submit(time.sleep, 10)
        try:
            print(future.result(timeout=1))
        except TimeoutError:
            print("this took too long...")
            stop_process_pool(executor)



Reference
========================================

* `Python - concurrent.futures — Launching parallel tasks <https://docs.python.org/3/library/concurrent.futures.html>`_
* `Python - paralellizing CPU-bound tasks with concurrent.futures <http://eli.thegreenplace.net/2013/01/16/python-paralellizing-cpu-bound-tasks-with-concurrent-futures>`_
* `Giuseppe Ciotta's Blog – ThreadPoolExecutor and ProcessPoolExecutor_ Modern Python idioms <https://giuseppeciotta.net/threadpoolexecutor-and-processpoolexecutor-modern-python-idioms.html>`_
