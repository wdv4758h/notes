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



Example
========================================

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
    ...     return await bar()
    ...
    >>> loop = asyncio.get_event_loop()
    >>> loop.run_until_complete(foo())
    'O w O'
    >>> loop.close()




Reference
========================================

* `[LWN.net] Python coroutines with async and await <https://lwn.net/Articles/643786/>`_
* `Python - types module - types.coroutine <https://docs.python.org/3/library/types.html#types.coroutine>`_
    - transforms a generator function into a coroutine function which returns a generator-based coroutine
    - @types.coroutine
* `Wikipedia - Coroutine <https://en.wikipedia.org/wiki/Coroutine>`_
* `CPython - Lib/test/test_asyncio/test_pep492.py <https://github.com/python/cpython/blob/master/Lib/test/test_asyncio/test_pep492.py>`_
