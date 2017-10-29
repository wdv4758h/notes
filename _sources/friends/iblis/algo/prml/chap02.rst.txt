Probability Distributions
===============================================================================

density estimation
    給定一個 random variable :math:`X`, random variable is a function,
    然後有 :math:`x_1, x_2, \dots, x_n` 已觀測的值。我們想要找到
    probability distribution :math:`p(X)`

Assumption
    常用 data points 之間為 i.i.d. (independent and identically distribution)

ill-posed problem
    *density estimation* problem 基本上是 ill-posed --
    無限多種 probability distribution 符合這有限的觀測值。
    所以需要注重 model selection

parametric distribution
    這些 distribution 是透過參數來控制形狀，不是 data；形狀早就決定了

non-parametric density estimation
    解決 parametric distribution 的限制， distribution 的形狀用 data set 決定；
    data set 也要夠大。



Bernoulli Distribution
----------------------------------------------------------------------

兩個 state

:math:`x \in {0, 1}`

.. math::

    \text{Let } & p(x = 1 | \mu) = \mu \\
    & p(x = 0 | \mu) = 1 - \mu

而 distribution 為

.. math::

    Bern(x | \mu) & = \mu^x (1 - \mu)^(1 - x) \\
    \therefore Bern(x = 1 | \mu) & = \mu^1 (1 - \mu)^0 \\
                                 & = \mu \\
    \therefore Bern(x = 0 | \mu) & = \mu^0 (1 - \mu)^1 \\
                                 & = (1 - \mu)

給定我們有 dataset :math:`\mathcal{D} = \{x_1, \dots, x_n\}`
而且之間為 iid。得 Likelihood function

.. math::

    p(\mathcal{D} | \mu) & = \prod_n^N p(x_n | \mu) \\
                         & = \prod_n^N \mu^x_n (1 - \mu)^(1 - x_n)

Then, log likelihood function

.. math::

    \ln p(\mathcal{D} | \mu)
        & = \sum_n^N \ln p(x_n | \mu) \\
        & = \sum_n^N \ln \Big( \mu^x_n (1 - \mu)^(1 - x_n) \Big)

而實際上去 maximum likelihood 時，

.. math::

    \mu_{ML} = \frac{1}{N} \sum_n^N x_n

就是看著 1 的數量，算 average


