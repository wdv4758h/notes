========================================
SymPy
========================================

Online
========================================

* `SymPy Gamma <http://www.sympygamma.com/>`_
* `SymPy Live <http://live.sympy.org/>`_
* `Try Jupyter! <http://try.jupyter.org/>`_ - ``import sympy``


Installation
========================================

.. code-block:: sh

    # 記得先切到 virtualenv 裡面
    $ pip install sympy

Example
========================================

Example 1
------------------------------

.. code-block:: python

    # var(names, **args)
    #     Create symbols and inject them into the global namespace.
    #
    #     This calls :func:`symbols` with the same arguments and puts the results
    #     into the *global* namespace. It's recommended not to use :func:`var` in
    #     library code, where :func:`symbols` has to be used::

    >>> from sympy import var
    >>> var('x y')
    (x, y)
    >>> z = x + y
    >>> z
    x + y

.. code-block:: python

    >>> from sympy import symbols
    >>> x, y = symbols('x y')
    >>> z = x + y
    >>> z
    x + y
    >>> z - x
    y
    >>> z + x
    2⋅x + y
    >>> z ** 2
           2
    (x + y)
    >>> (z ** 2).expand()
     2            2
    x  + 2⋅x⋅y + y
    # 把其他值代入原本的方程式
    >>> z
    x + y
    >>> z.subs(x, 3)
    y + 3
    >>> z.subs({x: 3, y: 4})
    7
    >>> z.subs([(x, 3), (y, 4)])
    7
    # symbol 名稱跟變數名稱可以不同
    >>> m, n = symbols('n m')
    >>> m
    n
    >>> n
    m
    >>> from sympy import init_printing
    >>> from sympy import Integral
    >>> init_printing()
    >>> a = Integral(z, x)
    >>> a
    ⌠
    ⎮ (x + y) dx
    ⌡
    >>> from sympy import pi
    >>> pi
    π
    # .evalf(100) : 計算 formula 實際的值，精準度指定為 100 位 (包含整數部份)
    >>> pi.evalf(100)
    3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068
    # .evalf(100, subs=...) : 計算 formula 實際的值 (代入其他值)，精準度為 100 位 (包含整數部份)
    >>> z.evalf(100, subs={x: pi, y: 1})
    4.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117068


Example 2 - solve
------------------------------

.. code-block:: python

    >>> from sympy import Symbol
    >>> from sympy.solvers import solve
    >>> x = Symbol('x')
    >>> y = x**2 - 1
    # 解出方程式 (x**2 - 1 = 0) 裡的 x
    >>> solve(y, x)
    [-1, 1]


Example 3 - plot (繪圖)
------------------------------

.. code-block:: python

    from sympy import var
    from sympy.plotting import plot

    fac = sympy.factorial
    sin = sympy.sin
    cos = sympy.cos

    var('x')

    error = abs(sin(x) - (x-x**3/fac(3)+x**5/fac(5)-x**7/fac(7)+x**9/fac(9)-x**11/fac(11)+x**13/fac(13)))

    plot(error, (x, 0, sympy.pi))

    error = abs(cos(x) - (1-x**2/fac(2)+x**4/fac(4)-x**6/fac(6)+x**8/fac(8)-x**10/fac(10)+x**12/fac(12)))
    plot(error, (x, 0, sympy.pi))


Example 4 - lambdify/ufuncify/... (轉成 lambda function)
--------------------------------------------------------

在 SymPy 的 `Numeric Computation <http://docs.sympy.org/dev/modules/numeric-computation.html>`_
裡有列出了許多計算實際值的方式，
目前有以下幾種作法：

+----------------+----------------------------+--------------+
| Tool           | Qualities                  | Dependencies |
+================+============================+==============+
| subs/evalf     | Simple                     | None         |
+----------------+----------------------------+--------------+
| lambdify       | Scalar functions           | math         |
+----------------+----------------------------+--------------+
| lambdify-numpy | Vector functions           | numpy        |
+----------------+----------------------------+--------------+
| ufuncify       | Complex vector expressions | f2py, Cython |
+----------------+----------------------------+--------------+
| Theano         | Many outputs, CSE, GPUs    | Theano       |
+----------------+----------------------------+--------------+


.. code-block:: python

    from sympy import var
    from sympy.utilities.lambdify import lambdify

    var('x')

    y = x**x
    f = lambdify(x, y)

    print(f(3))     # 27


.. code-block:: python

    # Generates a binary function that supports broadcasting on numpy arrays

    from sympy import var
    from sympy.utilities.autowrap import ufuncify

    var('x')

    y = x**x
    f = ufuncify(x, y)  # function 'f' can accept iterable parameter and return NumPy array

    print(f(3))             # 27.0
    print(f([1, 3, 5]))     # [  1.00000000e+00   2.70000000e+01   3.12500000e+03]


Other CAS
========================================

* `Maxima (software) <https://en.wikipedia.org/wiki/Maxima_%28software%29>`_
* `SageMath <http://www.sagemath.org/index.html>`_


Reference
========================================

* `SymPy <http://lidavidm.me/sympy/>`_
* `SymPy Live <http://live.sympy.org/>`_
* `[GitHub] sympy/sympy - A computer algebra system written in pure Python <https://github.com/sympy/sympy>`_
* `[GitHub] sympy/symengine - SymEngine is a fast symbolic manipulation library, written in C++ <https://github.com/sympy/symengine>`_
* `Wikipedia - SymPy <https://en.wikipedia.org/wiki/SymPy>`_
* `Wikipedia - Computer algebra system <https://en.wikipedia.org/wiki/Computer_algebra_system>`_
* `SageMathCloud <http://www.sagemath.com>`_
    - `SageMathCloud - FAQ <https://github.com/sagemathinc/smc/wiki/FAQ>`_
    - `SageMathCloud - Teaching <https://github.com/sagemathinc/smc/wiki/Teaching>`_
