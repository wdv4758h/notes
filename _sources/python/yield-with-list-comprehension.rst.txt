========================================
yield with list comprehension
========================================

之前無意間發現可在 list comprehension 裡面使用 ``yield`` 和 ``yield from`` ，
這是一個 tricky 的用法 :P

Example
========================================

list :

.. code-block:: python

    >>> list((yield x) or x for x in [1, 2, 3])
    [1, 1, 2, 2, 3, 3]

    >>> list((yield from range(x)) for x in [1, 2, 3, 4])
    [0, None, 0, 1, None, 0, 1, 2, None, 0, 1, 2, 3, None]

    >>> list((yield x) or x if not x % 2 else x for x in [1, 2, 3])
    [1, 2, 2, 3]

    >>> def f(val):
    ...     return "Hi"
    >>> x = [1, 2, 3]
    >>> list(f((yield a)) for a in x)
    [1, 'Hi', 2, 'Hi', 3, 'Hi']

    >>> x = [1, 2, 3]
    >>> f = lambda x : x**2
    >>> list(f((yield a) or a) for a in x)
    [1, 1, 2, 4, 3, 9]

    >>> x = (lambda : ((yield 666),(yield 777),(yield 888)))()
    >>> next(x)
    666
    >>> next(x)
    777
    >>> next(x)
    888
    >>> next(x)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    StopIteration

    >>> (lambda x: 999)((yield 3))
      File "<stdin>", line 1
    SyntaxError: 'yield' outside function
    >>> list((lambda x: 999)((yield 3)) for i in [2])
    [3, 999]


dictionary :

.. code-block:: python

    # In Python 2
    >>> myset = set(['a', 'b', 'c', 'd'])
    >>> mydict = {item: (yield ''.join([item, 's'])) for item in myset}
    >>> mydict
    <generator object <dictcomp> at 0x7f479b246eb0>
    >>> dict(mydict)
    Traceback (most recent call last):
    File "<stdin>", line 1, in <module>
    ValueError: dictionary update sequence element #4 has length 4; 2 is required
    >>> mydict = {item: (yield ''.join([item, 's'])) for item in myset}
    >>> list(mydict)
    ['as', 'cs', 'bs', 'ds', {'a': None, 'c': None, 'b': None, 'd': None}]

    # In Python 3
    >>> myset = set(['a', 'b', 'c', 'd'])
    >>> mydict = {item: (yield ''.join([item, 's'])) for item in myset}
    >>> mydict
    <generator object <dictcomp> at 0x7f85655eb410>
    >>> dict(mydict)
    {'d': 's', 'a': 's', 'c': 's', 'b': 's'}
    >>> mydict = {item: (yield ''.join([item, 's'])) for item in myset}
    >>> list(mydict)
    ['cs', 'ds', 'bs', 'as']


flat_list
========================================

把傳入的巢狀 list 壓平

.. code-block:: python

    # assume there is no "None" in real data
    >>> flat_list = lambda l: list(filter(lambda x: x is not None, ((yield from flat_list(i)) if isinstance(i, list) else i for i in l)))
    >>> flat_list([1, 2, 3])
    [1, 2, 3]
    >>> flat_list([1, [2, 2, 2], 4])
    [1, 2, 2, 2, 4]
    >>> flat_list([[[2]], [4, [5, 6, [6], 6, 6, 6], 7]])
    [2, 4, 5, 6, 6, 6, 6, 6, 7]
    >>> flat_list([-1, [1, [-2], 1], -1])
    [-1, 1, -2, 1, -1]


Reference
========================================

* `[Python-ideas] Using yield inside a comprehension. <https://groups.google.com/forum/#!topic/python-ideas/JOFw5Al-kEM>`_
* `[2010] From List Comprehensions to Generator Expressions <http://python-history.blogspot.co.uk/2010/06/from-list-comprehensions-to-generator.html>`_
* `PEP 255 - Simple Generators <http://legacy.python.org/dev/peps/pep-0255/>`_
* `PEP 342 - Coroutines via Enhanced Generators <http://legacy.python.org/dev/peps/pep-0342/>`_
* `PEP 380 - Syntax for Delegating to a Subgenerator <http://legacy.python.org/dev/peps/pep-0380/>`_
* `How does this lambda/yield/generator comprehension work? <https://stackoverflow.com/questions/15955948/how-does-this-lambda-yield-generator-comprehension-work>`_
