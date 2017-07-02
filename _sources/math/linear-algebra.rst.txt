========================================
線性代數 （Linear Algebra）
========================================


當初在學線性代數的時候沒學好，
希望未來有機會可以理解它 ... QQ


.. contents:: 目錄


核心問題
========================================

* 線性系統
* 最小平方法
* 特徵值與特徵向量
* 奇異值分解


線性系統
------------------------------

:核心問題: 線性系統
:重要觀念:
    * 線性方程式（Linear Equation）
    * 矩陣代數
    * 向量空間（Vector Space）
:應用:
    * 解 N 元一次方程式
:NumPy: numpy.linalg.solve
:SymPy: Matrix.solve


給定一 ``m x n 階的矩陣 A`` 與 ``m 維的常數向量 b`` ，
求 ``n 維的向量 x`` ，
使得 ``A x = b`` 。


m 個點，每個點維度為 n，
解方程式
（最少需要 n 個點）。


NumPy 使用範例－linalg.solve
++++++++++++++++++++++++++++

.. code-block:: python

    >>> import numpy as np
    >>> A = np.matrix('1 2 3; 1 3 8; 3 5 7')
    >>> b = np.array([14, 31, 34])
    >>> x = np.linalg.solve(A, b)
    >>> x
    array([ 1.,  2.,  3.])


SymPy 使用範例－Matrix.solve
++++++++++++++++++++++++++++++++++++++++++

.. code-block:: python

    >>> import sympy
    >>> sympy.init_printing(use_unicode=True)
    >>> A = sympy.Matrix([[1, 2, 3], [1, 3, 8], [3, 5, 7]])
    >>> b = sympy.Matrix([14, 31, 34])
    >>> A
    ⎡1  2  3⎤
    ⎢       ⎥
    ⎢1  3  8⎥
    ⎢       ⎥
    ⎣3  5  7⎦
    >>> b
    ⎡14⎤
    ⎢  ⎥
    ⎢31⎥
    ⎢  ⎥
    ⎣34⎦
    >>> A.solve(b)
    ⎡1⎤
    ⎢ ⎥
    ⎢2⎥
    ⎢ ⎥
    ⎣3⎦



最小平方法
------------------------------

:核心問題: 最小平方法
:重要觀念:
    * 線性變換
    * 內積空間
:應用:
    * 線性回歸
:NumPy: numpy.linalg.lstsq
:SymPy: Matrix.solve_least_squares


給定一 ``m x n 階的矩陣 A`` 與 ``m 維的常數向量 b`` ，
求 ``n 維的向量 x-hat`` ，
使得 ``∥ b - A x-hat ∥²`` 有最小值。

m 個點，每個點維度為 n，
解線性回歸。


NumPy 使用範例－linalg.lstsq
++++++++++++++++++++++++++++

.. code-block:: python

    >>> import numpy as np
    >>> A = np.matrix('1 2 3; 4 5 6; 7 8 9')
    >>> b = np.array([1, 2, 3])
    >>> np.linalg.solve(A, b)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "/home/user/venv/lib/python3.5/site-packages/numpy/linalg/linalg.py", line 384, in solve
        r = gufunc(a, b, signature=signature, extobj=extobj)
      File "/home/user/venv/lib/python3.5/site-packages/numpy/linalg/linalg.py", line 90, in _raise_linalgerror_singular
        raise LinAlgError("Singular matrix")
    numpy.linalg.linalg.LinAlgError: Singular matrix
    >>> x = np.linalg.lstsq(A, b)
    >>> x
    (array([-0.05555556,  0.11111111,  0.27777778]),
     array([], dtype=float64),
     2,
     array([  1.68481034e+01,   1.06836951e+00,   4.41842475e-16]))


SymPy 使用範例－Matrix.solve_least_squares
++++++++++++++++++++++++++++++++++++++++++

.. code-block:: python

    >>> import sympy
    >>> sympy.init_printing(use_unicode=True)
    >>> A = sympy.Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    >>> b = sympy.Matrix([1, 2, 3])
    >>> A
    ⎡1  2  3⎤
    ⎢       ⎥
    ⎢4  5  6⎥
    ⎢       ⎥
    ⎣7  8  9⎦
    >>> b
    ⎡1⎤
    ⎢ ⎥
    ⎢2⎥
    ⎢ ⎥
    ⎣3⎦
    >>> A.solve_least_squares(b)
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
      File "/home/user/venv/lib/python3.5/site-packages/sympy/matrices/matrices.py", line 991, in solve_least_squares
        return self.cholesky_solve(rhs)
      File "/home/user/venv/lib/python3.5/site-packages/sympy/matrices/matrices.py", line 861, in cholesky_solve
        Y = L._lower_triangular_solve(rhs)
      File "/home/user/venv/lib/python3.5/site-packages/sympy/matrices/dense.py", line 420, in _lower_triangular_solve
        raise TypeError("Matrix must be non-singular.")
    TypeError: Matrix must be non-singular.

    # TODO !




特徵值與特徵向量（Eigenvalues & Eigenvectors）
---------------------------------------------

:核心問題: 特徵值與特徵向量
:重要觀念:
    * 行列式
    * 特徵分析
    * 典型形式
:應用:
:NumPy: numpy.linalg.eig
:SymPy: Matrix.eigenvals, Matrix.eigenvects


Markov Matrices
++++++++++++++++++++


NumPy 使用範例－linalg.eig
++++++++++++++++++++++++++

.. code-block:: python

    >>> import numpy as np
    >>> A = np.matrix('1 2 3; 4 5 6; 7 8 9')
    >>> (eigenvalues, eigenvectors) = np.linalg.eig(A)
    >>> eigenvalues
    array([  1.61168440e+01,  -1.11684397e+00,  -1.30367773e-15]
    >>> eigenvectors
    matrix([[-0.23197069, -0.78583024,  0.40824829],
            [-0.52532209, -0.08675134, -0.81649658],
            [-0.8186735 ,  0.61232756,  0.40824829]])


SymPy 使用範例－Matrix.eigenvals、Matrix.eigenvects
+++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: python

    >>> import sympy
    >>> sympy.init_printing(use_unicode=True)
    >>> A = sympy.Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    >>> A
    ⎡1  2  3⎤
    ⎢       ⎥
    ⎢4  5  6⎥
    ⎢       ⎥
    ⎣7  8  9⎦
    >>> eigenvalues = A.eigenvals()
    >>> eigenvalues
    ⎧      15   3⋅√33       3⋅√33   15   ⎫
    ⎨0: 1, ── + ─────: 1, - ───── + ──: 1⎬
    ⎩      2      2           2     2    ⎭
    >>> eigenvectors = A.eigenvects(simplify=True)
    >>> eigenvectors
    ⎡                ⎛               ⎡⎡      ⎛    4         ⎞                ⎤⎤⎞
    ⎢                ⎜               ⎢⎢   64⋅⎜────────── + 1⎟                ⎥⎥⎟
    ⎢                ⎜15   3⋅√33     ⎢⎢      ⎝13 + 3⋅√33    ⎠          6     ⎥⎥⎟
    ⎢⎛0, 1, ⎡⎡1 ⎤⎤⎞, ⎜── + ─────, 1, ⎢⎢───────────────────────── + ──────────⎥⎥⎟,
    ⎢⎜      ⎢⎢  ⎥⎥⎟  ⎜2      2       ⎢⎢(11 + 3⋅√33)⋅(13 + 3⋅√33)   13 + 3⋅√33⎥⎥⎟
    ⎢⎜      ⎢⎢-2⎥⎥⎟  ⎜               ⎢⎢                                      ⎥⎥⎟
    ⎢⎜      ⎢⎢  ⎥⎥⎟  ⎜               ⎢⎢            ⎛    4         ⎞          ⎥⎥⎟
    ⎢⎝      ⎣⎣1 ⎦⎦⎠  ⎜               ⎢⎢         16⋅⎜────────── + 1⎟          ⎥⎥⎟
    ⎢                ⎜               ⎢⎢            ⎝13 + 3⋅√33    ⎠          ⎥⎥⎟
    ⎢                ⎜               ⎢⎢         ───────────────────          ⎥⎥⎟
    ⎢                ⎜               ⎢⎢              11 + 3⋅√33              ⎥⎥⎟
    ⎢                ⎜               ⎢⎢                                      ⎥⎥⎟
    ⎣                ⎝               ⎣⎣                  1                   ⎦⎦⎠

    ⎛                 ⎡⎡                     ⎛     4         ⎞   ⎤⎤⎞⎤
    ⎜                 ⎢⎢                  64⋅⎜─────────── + 1⎟   ⎥⎥⎟⎥
    ⎜  3⋅√33   15     ⎢⎢     6               ⎝-3⋅√33 + 13    ⎠   ⎥⎥⎟⎥
    ⎜- ───── + ──, 1, ⎢⎢─────────── + ───────────────────────────⎥⎥⎟⎥
    ⎜    2     2      ⎢⎢-3⋅√33 + 13   (-3⋅√33 + 11)⋅(-3⋅√33 + 13)⎥⎥⎟⎥
    ⎜                 ⎢⎢                                         ⎥⎥⎟⎥
    ⎜                 ⎢⎢             ⎛     4         ⎞           ⎥⎥⎟⎥
    ⎜                 ⎢⎢          16⋅⎜─────────── + 1⎟           ⎥⎥⎟⎥
    ⎜                 ⎢⎢             ⎝-3⋅√33 + 13    ⎠           ⎥⎥⎟⎥
    ⎜                 ⎢⎢          ────────────────────           ⎥⎥⎟⎥
    ⎜                 ⎢⎢              -3⋅√33 + 11                ⎥⎥⎟⎥
    ⎜                 ⎢⎢                                         ⎥⎥⎟⎥
    ⎝                 ⎣⎣                    1                    ⎦⎦⎠⎦



奇異值分解
------------------------------

:核心問題: 奇異值分解
:重要觀念:
    * 二次型
:應用:
:NumPy: numpy.linalg.svd
:SymPy: Matrix.singular_values


NumPy 使用範例－linalg.svd
++++++++++++++++++++++++++

.. code-block:: python

    >>> import numpy as np
    >>> A = np.matrix('1 2 3; 4 5 6; 7 8 9')
    >>> (U, S, V) = np.linalg.svd(A)
    >>> U
    matrix([[-0.21483724,  0.88723069,  0.40824829],
            [-0.52058739,  0.24964395, -0.81649658],
            [-0.82633754, -0.38794278,  0.40824829]])
    >>> S
    array([  1.68481034e+01,   1.06836951e+00,   4.41842475e-16])
    >>> V
    matrix([[-0.47967118, -0.57236779, -0.66506441],
            [-0.77669099, -0.07568647,  0.62531805],
            [-0.40824829,  0.81649658, -0.40824829]])


SymPy 使用範例－Matrix.singular_values
++++++++++++++++++++++++++++++++++++++

.. code-block:: python

    >>> import sympy
    >>> sympy.init_printing(use_unicode=True)
    >>> A = sympy.Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
    >>> A
    ⎡1  2  3⎤
    ⎢       ⎥
    ⎢4  5  6⎥
    ⎢       ⎥
    ⎣7  8  9⎦
    >>> S = A.singular_values()
    >>> S
    ⎡    _______________      _________________   ⎤
    ⎢   ╱ 3⋅√8881   285      ╱   3⋅√8881   285    ⎥
    ⎢  ╱  ─────── + ─── ,   ╱  - ─────── + ─── , 0⎥
    ⎣╲╱      2       2    ╲╱        2       2     ⎦



參考
========================================

* `Linear Algebra – A Primer <https://jeremykun.com/2011/06/19/linear-algebra-a-primer/>`_


Visualization

* `Eigenvectors and Eigenvalues - Explained Visually <http://setosa.io/ev/eigenvectors-and-eigenvalues/>`_
* `Ordinary Least Squares Regression - Explained Visually <http://setosa.io/ev/ordinary-least-squares-regression/>`_
* `Principal Component Analysis - Explained Visually <http://setosa.io/ev/principal-component-analysis/>`_


Implementation

* `Linear algebra (numpy.linalg) <https://docs.scipy.org/doc/numpy/reference/routines.linalg.html>`_
* `Matrices — SymPy <http://docs.sympy.org/latest/tutorial/matrices.html>`_
