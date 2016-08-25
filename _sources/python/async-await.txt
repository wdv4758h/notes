========================================
Python - async & await
========================================

History
========================================

* Python 2.5 - `PEP 342 -- Coroutines via Enhanced Generators <https://www.python.org/dev/peps/pep-0342/>`_
    - 實作更好的 coroutine-like 功能支援 (基於 extended generators)
    - 把 ``yield`` statement 變成 expression
    - 幫 generator 加上 ``send()`` 、 ``throw()`` 、 ``close()``
    - generator 被 GC 回收時，會去呼叫 ``close()``
* Python 3.3 - `PEP 0380 -- Syntax for Delegating to a Subgenerator <https://www.python.org/dev/peps/pep-0380/>`_
    - 加入 ``yield from`` expression，可以 delegate 給 sub-generator
* Python 3.4 - `PEP 3156 -- Asynchronous IO Support Rebooted: the "asyncio" Module <https://www.python.org/dev/peps/pep-3156/>`_
    - 加入 ``asyncio`` module (comprehensive asynchronous I/O framework)
* Python 3.5 - `PEP 0492 -- Coroutines with async and await syntax <https://www.python.org/dev/peps/pep-0492/>`_
    - 提供 ``async`` 和 ``await`` keywords 讓 coroutine 可以更方便地使用
    - 提供 ``@types.coroutine`` 來包裝原本使用 ``yield`` 和 ``yield from`` 撰寫的 function
    - asynchronous context managers (提供 ``__aenter__()`` 和 ``__aexit__()``)


Module
========================================

* ``asynchat`` module 現在還保留是為了 backwards compatibility，現在建議使用 ``asyncio``


Example
========================================

``async`` keyword 用來把 function 變成 coroutine，
在 coroutine 內可以使用 ``await`` 來暫停執行，
等待其他事情完成。

* ``async`` function 回傳的是 ``coroutine`` object
* ``await`` 只能用於 ``async`` function 內
* ``await with`` 後的 context manager 需要 ``__aenter__`` 和 ``__aexit__``
* ``await for`` 後的 iterable variable 需要 ``__aiter__`` 和 ``__anext__``


.. code-block:: python

    >>> async def f():
    ...     pass
    ...
    >>> x = f()
    >>> x
    <coroutine object f at 0x7f11f9c19ca8>

    >>> import asyncio
    >>> asyncio.iscoroutine(x)
    True
    >>> asyncio.iscoroutinefunction(f)
    True

    >>> class FakeCoro:     # asyncio.iscoroutine() uses collections.abc.Coroutine
    ...     def send(self, value): pass
    ...     def throw(self, typ, val=None, tb=None): pass
    ...     def close(self): pass
    ...     def __await__(self): yield
    ...
    >>> asyncio.iscoroutine(FakeCoro())
    True

    >>> class Awaitable:
    ...     def __await__(self):
    ...         return ('Hello ~', 'XD')
    ...
    >>> @asyncio.coroutine
    ... def g():
    ...     return Awaitable()
    ...
    >>> coro = g()
    >>> coro.send(None)
    'Hello ~'
    >>> coro.send(None)
    'XD'
    >>> coro.send(None)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    StopIteration
    >>> coro.close()
    >>> coro = g()
    >>> coro.close()
    >>> coro.send(None)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    StopIteration

    >>> async def bar():
    ...     return 'O w O'
    ...
    >>> async def foo():
    ...     return await bar()  # await 只能用在 async function 裡
    ...
    >>> loop = asyncio.get_event_loop()
    >>> loop.run_until_complete(foo())
    'O w O'
    >>> loop.close()



``async with`` :

(``async with`` 後面會在進 block 前先去 call ``__aenter__`` ，
接著在離開 block 時 call ``__aexit__`` 來做善後，
藉此可以在 method 中使用 ``await`` 來接其他 asynchronous function)

.. code-block:: python

    >>> class Manager:
    ...     async def __aenter__(self):
    ...         print('__aenter__')
    ...         return self
    ...     async def __aexit__(self, *args):
    ...         print('__aexit__')
    ...         return True
    >>> async def foo():
    ...     async with Manager() as a:
    ...         print(42)
    >>> import asyncio
    >>> loop = asyncio.get_event_loop()
    >>> loop.run_until_complete(foo())
    __aenter__
    42
    __aexit__



``async for`` :

(``async for`` 後面會先去 call ``__aiter__`` 來拿 iterator，
接著用 ``__anext__`` 來取下一個值，
藉此可以在 method 中使用 ``await`` 來接其他 asynchronous function)

.. code-block:: python

    >>> class AsyncIter:
    ...     def __init__(self):
    ...         self.iteration = 0
    ...     async def __aiter__(self):
    ...         print('__aiter__')
    ...         return self
    ...     async def __anext__(self):
    ...         self.iteration += 1
    ...         if self.iteration > 10:
    ...             raise StopAsyncIteration
    ...         return 42
    >>> async def bar():
    ...     async for i in AsyncIter():
    ...         print(i)
    >>> loop.run_until_complete(bar())
    __aiter__
    42
    42
    42
    42
    42
    42
    42
    42
    42
    42



``asyncio.wait`` :

(``asyncio.wait`` 可以一次吃很多 coroutine 下去執行、等待)

.. code-block:: python

    >>> import asyncio
    >>> async def f(time, *args):
    ...     await asyncio.sleep(time)
    ...     print('O w O : {}'.format(args))
    >>> async def main():
    ...     result = await asyncio.wait([
    ...             f(0.5, 124124, 'asd'),
    ...             f(0.3, 423434343434343434343434343434343434343434343434, 'asd'),
    ...             f(0.1, 412124, 'das'),
    ...         ])
    ...     print(result)
    >>> loop = asyncio.get_event_loop()
    >>> loop.run_until_complete(main())
    O w O : (412124, 'das')
    O w O : (423434343434343434343434343434343434343434343434, 'asd')
    O w O : (124124, 'asd')
    ({<Task finished coro=<f() done, defined at <stdin>:1> result=None>, <Task finished coro=<f() done, defined at <stdin>:1> result=None>, <Task finished coro=<f() done, defined at <stdin>:1> result=None>}, set())



.. code-block:: python

    >>> import asyncio
    >>> tmp = asyncio.create_subprocess_shell('echo "yo"')
    >>> loop.run_until_complete(a)
    <Process 4037>
    yo



Reference
========================================

* `[LWN.net] Python coroutines with async and await <https://lwn.net/Articles/643786/>`_
* `Python - types module - types.coroutine <https://docs.python.org/3/library/types.html#types.coroutine>`_
    - transforms a generator function into a coroutine function which returns a generator-based coroutine
    - @types.coroutine
* `Python - Develop with asyncio <https://docs.python.org/3/library/asyncio-dev.html>`_
* `Python - Tasks and coroutines <https://docs.python.org/3/library/asyncio-task.html>`_
* `Python - Streams (high-level API) <https://docs.python.org/3/library/asyncio-stream.html>`_
* `Python - Asyncio Subprocess <https://docs.python.org/3/library/asyncio-subprocess.html>`_
* `PEP 3145 -- Asynchronous I/O For subprocess.Popen <https://www.python.org/dev/peps/pep-3145/>`_
* `Wikipedia - Coroutine <https://en.wikipedia.org/wiki/Coroutine>`_
* `CPython - Lib/test/test_asyncio/test_pep492.py <https://github.com/python/cpython/blob/master/Lib/test/test_asyncio/test_pep492.py>`_
* `CPython - Lib/asyncio/subprocess.py <https://github.com/python/cpython/blob/master/Lib/asyncio/subprocess.py>`_
* `CPython - Lib/test/test_asyncio/test_subprocess.py <https://github.com/python/cpython/blob/master/Lib/test/test_asyncio/test_subprocess.py>`_
* `Nick Coghlan's Python Notes - Some Thoughts on Asynchronous Programming <http://python-notes.curiousefficiency.org/en/latest/pep_ideas/async_programming.html>`_
* `Python Async IO Resources <http://asyncio.org/>`_
