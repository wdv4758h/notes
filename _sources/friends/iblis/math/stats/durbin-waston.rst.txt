Durbin-Waston Test
===============================================================================

用來檢測 residual (prediction error) 的 :ref:`autocorrelation`


Def
----------------------------------------------------------------------

.. math::

    d = \frac{\sum_{t=2}^T (e_t - e_{t-1})^2}{\sum_{t=1}^T e_t^2}


:math:`T` 是 data 量。

:math:`d` 越大約好。通常來說 :math:`d>2` 代表 error 看起來差異夠大。


Reference
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Durbin%E2%80%93Watson_statistic
