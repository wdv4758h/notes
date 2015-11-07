========================================
Numpy
========================================

Numpy Slicing
========================================

.. code-block:: python

    >>> import numpy as np
    >>> data = np.mat('1 2 3; 4 5 6; 7 8 9')
    >>> data
    matrix([[1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]])
    >>> data[:, 0]   # row : all, col : 0
    matrix([[1],
            [4],
            [7]])
    >>> data[:, (0, 2)]         # row : all, col : (0, 2)
    matrix([[1, 3],
            [4, 6],
            [7, 9]])
    >>> data[(0, 2), (1, 1)]    # parameters : rows & cols, access (0, 1) & (2, 1)
    matrix([[2, 8]])
    >>> data[(0, 2),
    ...      (1, 1)]
    matrix([[2, 8]])
    >>> data[((0, 0), (1, 2)),
    ...      ((2, 1), (2, 1))]
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
