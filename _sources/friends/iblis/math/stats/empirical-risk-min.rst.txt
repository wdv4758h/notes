.. _empirical-risk-min:

Empirical Risk Minimization
===============================================================================

In context of supervised learning, 我們會有 loss function :math:`L(h(x), y)` ，
:math:`h(x)` 為我們的 approximator。

:risk: 定義成 expectation of loss function

.. math::

    R(h) = E(L(h(x), y)) = \int L(h(x), y) d p(x, y)

where :math:`p(x, y)` is the join probility distribution.

取得 optimal :math:`h^*` 即

.. math::

    h^* = \arg \min_{h \in H} R(h)

但是我們無法得知 `p(x, y)` ，所以我們只好近似

.. math::

    R_{emp}(h) = \frac{1}{m} \sum_i^m L(h(x_i), y_i)

就被稱為 Empirical Risk


Examples
----------------------------------------------------------------------

像是 MSE


Reference
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Empirical_risk_minimization
