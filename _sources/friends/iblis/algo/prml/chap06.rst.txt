Kernel Method
===============================================================================

kernel function 用來量測 simularity or covariance(inner product) ... etc.

memory-based method

kernel 的值，非負


:homogeneous kernel: AKA. radial-basis function

.. math::

    k(\| vec{x} - vec{x'} \|)

Dual Representation
----------------------------------------------------------------------


Constructing Kernel
----------------------------------------------------------------------

類似 model selection

:Guassian Kernel: (6.23) 是 homogeneous kernel, 跟樣本的距離有關。

:Probabilistic generative kernel:

    .. math::

        k(x, x') = p(x) p(x')


有潛在模型 ``i``

    .. math::

        k(x, x') = \sum_x p(x | i ) p (x' | i) p(i)


Fisher Kernel
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

(6.33)


Radial Basis Fcuntion Network
----------------------------------------------------------------------


Guassian Process
----------------------------------------------------------------------

是個 Process ， 其他： drichlet process

Regerssion
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    t_n = y_n + error_n

假設 error 為 random variable ， 是 :math:`\mu = 0` 的 Guassian

.. math::

    p(t_n | y_n) = N(x_n | y_n, \beta^-1)


求

.. math::

    p(t_{n+1} | t_N)
