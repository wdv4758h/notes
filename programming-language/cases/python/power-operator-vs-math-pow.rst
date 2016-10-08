========================================
** operator v.s. math.pow
========================================

不知道有沒有注意過，
Python 裡面有 ``**`` operator 可以做指數運算，
而 ``math.pow`` 也可以做指數運算，
到底差在哪裡？
甚至有時候 ``**`` operator 會比較快，為什麼？

主要的差別在於 ``math.pow`` 會把傳入的兩個參數都先轉成 ``float`` ，
可以保證回傳的一定是 ``float`` ，
``**`` 則不一定 (甚至可以做虛數次方的運算)。
另外一個點是 ``**`` 的行為可以根據 ``__pow__`` 和 ``__rpow__`` 來改變，
而 ``math.pow`` 則不會，
如果不想使用到 ``__pow__`` 或 ``__rpow__`` 的東西的話，
可以指定使用 ``math.pow`` 。


寫一段小程式測試：

.. code-block:: python

    from dis import dis
    from timeit import timeit

    operations = ( ('2 ** 42', ''),
                ('pow(2, 42)', ''),
                ('math.pow(2, 42)', 'import math'),
                ('2 ** i', 'i = 42'),
                ('pow(2, i)', 'i = 42'),
                ('math.pow(2, i)', 'import math; i = 42'),
                ('i ** j', 'i, j = 2, 42'),
                ('pow(i, j)', 'i, j = 2, 42'),
                ('math.pow(i, j)', 'import math; i, j = 2, 42'), )

    result = []

    for operation in operations:
        expr, setup = operation
        time = timeit(expr, setup=setup)
        result.append('{:16}: {:<21} s'.format(expr, time))

    print('\n'.join(result))

    for operation in operations:
        expr, _ = operation
        print('\n{} :\n'.format(expr))
        dis(expr)


Python 3.4 : ::

    2 ** 42         : 0.02503299992531538   s
    pow(2, 42)      : 0.5010730230715126    s
    math.pow(2, 42) : 0.4331468460150063    s
    2 ** i          : 0.3975521819666028    s
    pow(2, i)       : 0.5939885310363024    s
    math.pow(2, i)  : 0.2997760840225965    s
    i ** j          : 0.48525534803047776   s
    pow(i, j)       : 0.5479897629702464    s
    math.pow(i, j)  : 0.2728949940064922    s

    2 ** 42 :

    1           0 LOAD_CONST               2 (4398046511104)
                3 RETURN_VALUE

    pow(2, 42) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_CONST               0 (2)
                6 LOAD_CONST               1 (42)
                9 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                12 RETURN_VALUE

    math.pow(2, 42) :

    1           0 LOAD_NAME                0 (math)
                3 LOAD_ATTR                1 (pow)
                6 LOAD_CONST               0 (2)
                9 LOAD_CONST               1 (42)
                12 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                15 RETURN_VALUE

    2 ** i :

    1           0 LOAD_CONST               0 (2)
                3 LOAD_NAME                0 (i)
                6 BINARY_POWER
                7 RETURN_VALUE

    pow(2, i) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_CONST               0 (2)
                6 LOAD_NAME                1 (i)
                9 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                12 RETURN_VALUE

    math.pow(2, i) :

    1           0 LOAD_NAME                0 (math)
                3 LOAD_ATTR                1 (pow)
                6 LOAD_CONST               0 (2)
                9 LOAD_NAME                2 (i)
                12 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                15 RETURN_VALUE

    i ** j :

    1           0 LOAD_NAME                0 (i)
                3 LOAD_NAME                1 (j)
                6 BINARY_POWER
                7 RETURN_VALUE

    pow(i, j) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_NAME                1 (i)
                6 LOAD_NAME                2 (j)
                9 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                12 RETURN_VALUE

    math.pow(i, j) :

    1           0 LOAD_NAME                0 (math)
                3 LOAD_ATTR                1 (pow)
                6 LOAD_NAME                2 (i)
                9 LOAD_NAME                3 (j)
                12 CALL_FUNCTION            2 (2 positional, 0 keyword pair)
                15 RETURN_VALUE


PyPy3 (PyPy 2.4.0, Python 3.2.5) ::

    2 ** 42         : 0.0019397735595703125 s
    pow(2, 42)      : 0.002593994140625     s
    math.pow(2, 42) : 0.07702302932739258   s
    2 ** i          : 0.03540802001953125   s
    pow(2, i)       : 0.03392314910888672   s
    math.pow(2, i)  : 0.07650113105773926   s
    i ** j          : 0.03323793411254883   s
    pow(i, j)       : 0.03371095657348633   s
    math.pow(i, j)  : 0.07712817192077637   s

    2 ** 42 :

    1           0 LOAD_CONST               0 (4398046511104)
                3 RETURN_VALUE

    pow(2, 42) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_CONST               0 (2)
                6 LOAD_CONST               1 (42)
                9 CALL_FUNCTION            2
                12 RETURN_VALUE

    math.pow(2, 42) :

    1           0 LOAD_NAME                0 (math)
                3 LOOKUP_METHOD            1 (pow)
                6 LOAD_CONST               0 (2)
                9 LOAD_CONST               1 (42)
                12 CALL_METHOD              2
                15 RETURN_VALUE

    2 ** i :

    1           0 LOAD_CONST               0 (2)
                3 LOAD_NAME                0 (i)
                6 BINARY_POWER
                7 RETURN_VALUE

    pow(2, i) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_CONST               0 (2)
                6 LOAD_NAME                1 (i)
                9 CALL_FUNCTION            2
                12 RETURN_VALUE

    math.pow(2, i) :

    1           0 LOAD_NAME                0 (math)
                3 LOOKUP_METHOD            1 (pow)
                6 LOAD_CONST               0 (2)
                9 LOAD_NAME                2 (i)
                12 CALL_METHOD              2
                15 RETURN_VALUE

    i ** j :

    1           0 LOAD_NAME                0 (i)
                3 LOAD_NAME                1 (j)
                6 BINARY_POWER
                7 RETURN_VALUE

    pow(i, j) :

    1           0 LOAD_NAME                0 (pow)
                3 LOAD_NAME                1 (i)
                6 LOAD_NAME                2 (j)
                9 CALL_FUNCTION            2
                12 RETURN_VALUE

    math.pow(i, j) :

    1           0 LOAD_NAME                0 (math)
                3 LOOKUP_METHOD            1 (pow)
                6 LOAD_NAME                2 (i)
                9 LOAD_NAME                3 (j)
                12 CALL_METHOD              2
                15 RETURN_VALUE


Reference
========================================

* `Exponentials in python x.**y vs math.pow(x, y) <http://stackoverflow.com/a/20970087>`_
* `Why is 2**100 so much faster than math.pow(2,100)? <http://stackoverflow.com/questions/28563187/why-is-2100-so-much-faster-than-math-pow2-100>`_
* `Python - math - Mathematical functions <https://docs.python.org/3/library/math.html>`_
    - This module is always available. It provides access to the mathematical functions defined by the C standard.
