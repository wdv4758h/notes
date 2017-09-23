Autocorrelation
===============================================================================

物理意義上就是 serial correlation

Specific form:
- unit root processes
- trend stationary processes
- autoregressive processes
- moving average processes


Def
----------------------------------------------------------------------

一個 random process 的 autocorrelation 實際上就是用不同時間點做
:ref:`pearson-cor` 。

.. math::

    R(s, t) = \frac{E[(X_t - \mu_t)(X_s - \mu_s)]}{\sigma_t \sigma_s}


在 time series 中的兩個時間點的相關係數被稱為 *autocorrelation function*
(ACF)。

.. math::

    Corr(y_t, y_{t-k})

:math:`k` 是 lag。


Reference
----------------------------------------------------------------------

* http://juliastats.github.io/StatsBase.jl/stable/signalcorr.html#StatsBase.autocor

* https://en.wikipedia.org/wiki/Autocorrelation

* PACF: https://onlinecourses.science.psu.edu/stat510/node/62
