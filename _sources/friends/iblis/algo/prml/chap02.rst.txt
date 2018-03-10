Probability Distributions
===============================================================================

Distribution
    狹義上是一個 function。

Density estimation
    給定一個 random variable :math:`X`, random variable is a function,
    然後有 :math:`x_1, x_2, \dots, x_n` 已觀測的值。我們想要找到
    probability distribution :math:`p(X)`

Assumption
    常用 data points 之間為 i.i.d. (independent and identically distribution)

Ill-posed problem
    *density estimation* problem 基本上是 ill-posed --
    無限多種 probability distribution 符合這有限的觀測值。
    所以需要注重 model selection

Parametric distribution
    這些 distribution 是透過參數來控制形狀，不是 data；形狀早就決定了

Non-parametric density estimation
    解決 parametric distribution 的限制， distribution 的形狀用 data set 決定；
    data set 也要夠大。


Bernoulli Distribution
----------------------------------------------------------------------

兩個 state

:math:`x \in {0, 1}`

.. math::

    \text{Let } & p(X = 1 | \mu) = \mu \\
    & p(X = 0 | \mu) = 1 - \mu

而 distribution 為

.. math::

    Bern(x | \mu) & = \mu^x (1 - \mu)^(1 - x) \\
    \therefore Bern(X = 1 | \mu) & = \mu^1 (1 - \mu)^0 \\
                                 & = \mu \\
    \therefore Bern(X = 0 | \mu) & = \mu^0 (1 - \mu)^1 \\
                                 & = (1 - \mu)


Expectation and Variance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

算一個 distribution 的 expectation value 就直接 sum 所有的狀況，
然後得出一個 value。

.. math::

    E(x) & = \sum_x x \times p(X = x) \\
         & = 1 \times \mu + 0 \times (1 - \mu) \\
         & = \mu


Variance: 回想一下標準差的中心思想，即到 expectation value 的平均距離，
只是用相減、平方後開根號最後乘上 :math:`\frac{1}{n}` 。
只是這邊改成用 :math:`p` 跟上面算出來的 :math:`E(x)`

.. math::

    var(x) & = \sum_x p(X = x) \times (x - E(x))^2 \\
           & = \sum_x p(X = x) \times (x - \mu)^2 \\
           & = p(X = 1) \times (1 - \mu)^2 + p(X = 0) \times (0 - \mu)^2 \\
           & = \mu \times (1- \mu)^2 + (1 - \mu) \times (-\mu)^2 \\
           & = \mu(1 - \mu)^2 + (1 - \mu)\mu^2 \\
           & = \mu(1 - \mu)(1 - \mu + \mu) \\
           & = \mu(1 - \mu)


Likelihood Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

給定我們有 dataset :math:`\mathcal{D} = \{x_1, \dots, x_n\}`
而且之間為 iid。得 Likelihood function

.. math::

    p(\mathcal{D} | \mu) & = \prod_n^N p(x_n | \mu) \\
                         & = \prod_n^N \mu^x_n (1 - \mu)^{1 - x_n}

Then, log likelihood function

.. math::

    \ln p(\mathcal{D} | \mu)
        & = \sum_n^N \ln p(x_n | \mu) \\
        & = \sum_n^N \ln \Big( \mu^x_n (1 - \mu)^{1 - x_n} \Big)

而實際上去 maximum likelihood 時，

.. math::

    \mu_{ML} = \frac{1}{N} \sum_n^N x_n

就是看著 1 的數量，算 average。


Binomial Distribution
----------------------------------------------------------------------

就是 Bernoulli random variable
（就是每個 random variable 裡面都長成 Bernoulli Distribution 的形狀）
的 sum，是 Bernoulli 的 general 版本，然後假設每個 sample 都是 i.i.d.。

換句話說，就是 n 跟 sample 一起看，
原本的 Bernoulli 是看著一個硬幣討論正反面的機率，
到了 Binomial 是討論一堆硬幣，觀測到其中的 :math:`x` 個都是正（反）面的機率。

因此，兩個參數。

.. math::

    X \sim Bin(n, \mu)


.. math::

    p(X = x | \mu) = \binom{n}{x} p^x (1 - p)^{n - x}

Where

.. math::

    \binom{n}{x} = \frac{n!}{x! (n-x)!}


Expectation and Variance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

期望值可以直接理解成，多個 Bernoulli sum 起來。

.. math::

    E(x) = \sum_{x = 0}^n x \times p(X = x | \mu) = n \mu

.. math::

    var(x) = \sum_{x = 0}^n (x - E(x))^2 p(X = x | \mu) = n \mu (1 - \mu)


Julia
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. code-block:: julia

    Bin(x, n, μ) = factorial(n) / (factorial(x) * factorial(n - x))  * μ^x * (1 - μ)^(n - x)

    julia> Bin(0, 10, .25)
    0.056313514709472656

    julia> Bin(1, 10, .25)
    0.1877117156982422

    julia> Bin(2, 10, .25)
    0.2815675735473633

    julia> Bin(3, 10, .25)
    0.25028228759765625

    julia> Bin(4, 10, .25)
    0.1459980010986328

    julia> Bin(5, 10, .25)
    0.058399200439453125
