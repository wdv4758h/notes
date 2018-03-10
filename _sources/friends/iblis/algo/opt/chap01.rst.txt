Chapter 1: Introudction
===============================================================================

Local Minima
----------------------------------------------------------------------

Univariate
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. :math:`f'(x^*) = 0`: `first-order necessary condition` (FONC)

#. :math:`f''(x^*) \ge 0`: `second-order necessary condition` (SONC)

E.g.

.. math::

    f(x)   & = x^2 \\
    f'(x)  & = 2x \\
    f''(x) & = 2

且 :math:`x^* = 0`

Local minima 一定有這些性質，但不是有這個性質的就是 local minima。
e.g. :math:`f(x) = x^3` 就沒 local minima。

FONC 的證明可以用 :ref:`taylor-expansion` 得到。


Multivariate
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. :math:`\nabla f(\vec{x}) = 0`: `first-order necessary condition` (FONC)

#. :math:`\nabla^2 f(\vec{x})` is positive-semidefinite:
   `second-order necessary condition` (SONC)

如果一個點滿足的條件變成 positive-definite 那麼這個是 strong local minima。


RosonBrock Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A.k.a RosonBrock's banana function

這是個 non-convex function，常用來測試 optimization 的效能。

.. math::

    f(\vec{x}) = (a - x_1)^2 + b(x_2 - {x_1}^2)^2

其 global minima 就在 :math:`\vec{x} = (a, a^2)`

書中的參數是 :math:`a = 1, b = 5`


Contour Plot
----------------------------------------------------------------------

試試這個的等高線圖

.. math::

    f(x_1, x_2) = {x_1}^2 - {x_2}^2
