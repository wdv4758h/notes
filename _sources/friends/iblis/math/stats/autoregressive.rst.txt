Autoregressive Model
===============================================================================

.. highlight:: julia


Def
----------------------------------------------------------------------

AR(1)

.. math::

    y_t = \beta_0 + \beta_1 y_{t-1} + \epsilon_t

*order* of autoregression: 需要幾個前面的值

AR(k)

.. math::

    y_t = \beta_0 + \beta_1 y{t-1} + \dots + \beta_k y_{t-k} + \epsilon_t


Examples
----------------------------------------------------------------------

AR(1) plot 看看

::

    using Gadfly, MarketData
    plot(x=cl.values[1:end-1], y=cl.values[2:end])

linear model 看起來很有說服力。


Reference
----------------------------------------------------------------------

- https://onlinecourses.science.psu.edu/stat501/node/358
