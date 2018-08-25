.. _pearson-cor:

Pearson Correlation
===============================================================================

量測兩個 var :math:`X\ \text{and}\ Y` 的 linear correlation（線性相依）。

Def
----------------------------------------------------------------------

.. math::

    \rho_{X, Y} = \frac{cov(X, Y)}{\sigma_X \sigma_Y}
                = \frac{E[(X - \mu_X)(Y - \mu_Y)]}{\sigma_X \sigma_Y}

- :math:`X - \mu_X` 可以寫成 :math:`N \sigma_X`

- 同理， :math:`Y - \mu_Y` 可以寫成 :math:`M \sigma_Y`

- 所以整個 pearson correlation 就是在算 :math:`E[N \times M]`
    - FIXME: 但我無法證明 :math:`E[N \times M]` 的範圍是 1 ~ -1

- 所以沒單位， pearson correlation 是個係數，介於 1 到 -1


Reference
----------------------------------------------------------------------

* https://en.wikipedia.org/wiki/Pearson_correlation_coefficient
