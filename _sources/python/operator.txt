========================================
Operator
========================================

`operator — Standard operators as functions <https://docs.python.org/3/library/operator.html>`_


Getter & Caller
========================================

.. code-block:: python

    import operator

    # lambda s: (s[1], s[5], s[9])
    get = operator.itemgetter(1, 5, 9)
    print(get(range(20, 40)))   # (21, 25, 29)


.. code-block:: python

    import operator

    # lambda s: (s.start, s.stop, s.step)
    get = operator.attrgetter('start', 'stop', 'step')
    print(get(range(20, 40)))   # (20, 40, 1)


.. code-block:: python

    import operator

    # lambda s: s.values()
    call = operator.methodcaller('values')
    data = { i: i**2 for i in range(10) }
    print(call(data))   # dict_values([0, 1, 4, 9, 16, 25, 36, 49, 64, 81])



Inplace Operators
========================================

.. code-block:: python

    import operator

    a = '123'
    operator.iadd(a, 'test')
    # a : '123'

    b = [1, 2, 3]
    operator.iadd(a, [4, 5, 6])
    # a : [1, 2, 3, 4, 5, 6]
