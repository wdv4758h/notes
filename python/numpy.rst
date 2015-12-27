========================================
Numpy
========================================

.. contents:: Table of Contents


Numpy Slicing
========================================

.. code-block:: python

    >>> import numpy as np
    >>> data = np.mat('1 2 3; 4 5 6; 7 8 9')
    >>> data
    matrix([[1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]])


    >>> data[0, 1]      # data[0][1]
    2

    >>> data[:, 0]      # row : all, col : 0
    matrix([[1],
            [4],
            [7]])
    >>> data[1:, 1:]
    matrix([[5, 6],
            [8, 9]])
    >>> data[:, (0, 2)]         # row : all, col : (0, 2)
    matrix([[1, 3],
            [4, 6],
            [7, 9]])
    >>> data[1:-1, 1:-1]
    matrix([[5]])


    >>> data[(0, 2), (1, 1)]    # parameters : rows & cols, access (0, 1) & (2, 1)
    matrix([[2, 8]])
    >>> data[(0, 2),
    ...      (1, 1)]
    matrix([[2, 8]])


    >>> data[[1, 0]]
    matrix([[4, 5, 6],
            [1, 2, 3]])
    >>> data[[[1, 0]]]          # the same
    matrix([[4, 5, 6],
            [1, 2, 3]])
    >>> data[[[[1, 0]]]]
    matrix([[[4, 5, 6],
             [1, 2, 3]]])


    >>> data[((0, 0), (1, 2)),  # rows
    ...      ((2, 1), (2, 1))]  # cols
    matrix([[3, 2],
            [6, 8]])
    >>> data[(((0, 0), (1, 2)), ((0, 0), (1, 2))),
    ...      (((2, 1), (2, 1)), ((2, 1), (2, 1)))]
    matrix([[[3, 2],
            [6, 8]],

            [[3, 2],
            [6, 8]]])


    >>> data[ np.mat('0 0; 1 2') ]
    matrix([[[1, 2, 3],
            [1, 2, 3]],

            [[4, 5, 6],
            [7, 8, 9]]])


Numpy get n smallest data
========================================

``np.partition(a, k)`` 會把 a 的 k-th smallest element 放在 a[k]，
較小的值放在 a[:k]，較大的值放在 a[k+1:]，
index 從 0 開始 (所以第五小的值會在 index 4)

.. code-block:: python

    >>> import numpy as np
    >>> data = np.array([7, 8, 1, 2, 5, 9, 0])
    >>> data
    array([7, 8, 1, 2, 5, 9, 0])

    >>> np.argpartition(data, 0)    # indices
    array([6, 1, 2, 3, 4, 5, 0])
    >>> data[np.argpartition(data, 0)]      # guarantee the smallest value is at index 0
    array([0, 8, 1, 2, 5, 9, 7])
    >>> data[np.argpartition(data, 0)[0]]   # smallest
    0

    >>> np.argpartition(data, 3)    # indices
    array([2, 6, 3, 4, 0, 5, 1])
    >>> data[np.argpartition(data, 3)]      # guarantee the 4th smallest value is at index 3
    array([1, 0, 2, 5, 7, 9, 8])
    >>> data[np.argpartition(data, 3)[3]]   # 4th smallest
    5

    >>> np.partition(data, 3)       # new array, like ``data[np.argpartition(data, 3)]``
    array([1, 0, 2, 5, 7, 9, 8])
    >>> np.partition(data, 3)[3]    # 4th smallest
    5

    >>> data = np.mat('2 3 1; 5 6 4; 8 9 7')
    >>> data
    matrix([[2, 3, 1],
            [5, 6, 4],
            [8, 9, 7]])
    >>> np.partition(data, 0)
    matrix([[1, 3, 2],
            [4, 6, 5],
            [7, 9, 8]])
    >>> np.partition(data, 0)[:, 0]
    matrix([[1],
            [4],
            [7]])

    >>> data = np.array([[7, 8, 1, 2, 5, 9, 0], [7, 8, 1, 2, 5, 9, 0]])
    >>> data
    array([[7, 8, 1, 2, 5, 9, 0],
           [7, 8, 1, 2, 5, 9, 0]])
    >>> np.argpartition(data, 0)
    array([[6, 1, 2, 3, 4, 5, 0],
           [6, 1, 2, 3, 4, 5, 0]])
    >>> data.flat   # flat iterator
    <numpy.flatiter object at 0x13c04b0>
    >>> np.argpartition(data.flat, 0)
    array([ 6,  1,  2,  3,  4,  5,  0,  7,  8,  9, 10, 11, 12, 13])
    >>> data.flat[np.argpartition(data.flat, 0)[0]]
    0
    >>> np.argpartition(data.flat, 1)
    array([ 6, 13,  2,  3,  4,  5,  0,  7,  8,  9, 10, 11, 12,  1])
    >>> data.flat[np.argpartition(data.flat, 1)[1]]
    0


Assign with condition
========================================

.. code-block:: python

    >>> import numpy as np
    >>> data = np.array(range(10))
    >>> data
    array([0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
    >>> data > 5
    array([False, False, False, False, False, False,  True,  True,  True,  True], dtype=bool)
    >>> data[data > 5]
    array([6, 7, 8, 9])
    >>> data[data > 5] = -1
    >>> data
    array([ 0,  1,  2,  3,  4,  5, -1, -1, -1, -1])


Extend Numpy Array With Values
========================================

.. code-block:: python

    >>> import numpy as np
    >>> data = np.array([range(5)]*3)
    >>> print(data)
    array([[0, 1, 2, 3, 4],
           [0, 1, 2, 3, 4],
           [0, 1, 2, 3, 4]])
    >>> np.pad(data, ((0, 2), (2, 0)), 'constant', constant_values=9)
    array([[9, 9, 0, 1, 2, 3, 4],
           [9, 9, 0, 1, 2, 3, 4],
           [9, 9, 0, 1, 2, 3, 4],
           [9, 9, 9, 9, 9, 9, 9],
           [9, 9, 9, 9, 9, 9, 9]])


Print The Full Numpy Array
========================================

.. code-block:: python

    >>> import numpy
    >>> data = numpy.array(range(10000))
    >>> print(data)
    [   0    1    2 ..., 9997 9998 9999]
    >>> numpy.set_printoptions(threshold=numpy.inf)
    >>> print(data)     # print all the data


Generate An Array By Specific Function And Index
================================================

.. code-block:: python

    >>> import numpy
    >>> numpy.fromfunction(lambda x, y: x+y, (3, 3), dtype=int)
    array([[0, 1, 2],
           [1, 2, 3],
           [2, 3, 4]])
    >>> numpy.fromfunction(lambda x, y: (-1)**(x+y), (3, 3), dtype=int)
    array([[ 1, -1,  1],
           [-1,  1, -1],
           [ 1, -1,  1]])
    #
    # numpy.fromfunction
    #
    #     function accept coordinate
    #     shape of array you want


"Complex" Numpy Array To "Real" Numpy Array
===========================================

.. code-block:: python

    >>> data = np.array([i+i*2j for i in range(10)])
    >>> data
    array([ 0. +0.j,  1. +2.j,  2. +4.j,  3. +6.j,  4. +8.j,  5.+10.j,
            6.+12.j,  7.+14.j,  8.+16.j,  9.+18.j])
    >>> data.real
    array([ 0.,  1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9.])
    >>> data.imag
    array([  0.,   2.,   4.,   6.,   8.,  10.,  12.,  14.,  16.,  18.])


Insert Numpy Array
========================================

.. code-block:: python

    >>> data = np.array([range(5), range(5)])
    >>> data
    array([[0, 1, 2, 3, 4],
           [0, 1, 2, 3, 4]])
    >>> np.insert(data, slice(None, None), 42, axis=1)
    array([[42,  0, 42,  1, 42,  2, 42,  3, 42,  4],
           [42,  0, 42,  1, 42,  2, 42,  3, 42,  4]])


Reference
========================================

* `NumPy Reference <http://docs.scipy.org/doc/numpy-dev/reference/>`_
* `scipy array tip sheet <http://pages.physics.cornell.edu/~myers/teaching/ComputationalMethods/python/arrays.html>`_
* `Wikipedia - NumPy <https://en.wikipedia.org/wiki/NumPy>`_
