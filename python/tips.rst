========================================
Python Tips
========================================

紀錄一些 Python 上的小技巧，
善用後可以很方便，
不過有些已經用的很習慣了，
之後有想到任何新接觸 Python 的人會需要的再補上 :P

Python 的 bool 可以拿來做運算
========================================

.. code-block:: python

    >>> +True
    1
    >>> +False
    0
    >>> True + 1
    2


善用 any 和 all
========================================

* any 是只要傳入的 iterable 中間有任何的 bool 是 True 就回傳 True
* all 是傳入的 iterable 中間全部的 bool 必須是 True 才回傳 True


分 group
========================================

.. code-block:: python

    >>> x = range(9)
    >>> list(zip(*[iter(x)]*3))
    [(0, 1, 2), (3, 4, 5), (6, 7, 8)]



Others
========================================

* `Python name mangling: When in doubt, do what? <http://stackoverflow.com/questions/7456807/python-name-mangling-when-in-doubt-do-what>`_
