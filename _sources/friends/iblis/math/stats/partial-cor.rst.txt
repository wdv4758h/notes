Partial Correlation
===============================================================================

.. highlight:: julia

在某些 random variable 給定/固定的狀況下，計算 correlation


Example
----------------------------------------------------------------------

觀察這個，底下的表格中
如果

- :math:`z = 0`, then :math:`x = 2y`

- :math:`z = 1`, then :math:`x = 5y`

::

    julia> df = DataFrame(x = [2, 6, 10, 20], y = [1, 3, 2, 4], z = [0, 0, 1, 1])
    4×3 DataFrames.DataFrame
    │ Row │ x  │ y │ z │
    ├─────┼────┼───┼───┤
    │ 1   │ 2  │ 1 │ 0 │
    │ 2   │ 6  │ 3 │ 0 │
    │ 3   │ 10 │ 2 │ 1 │
    │ 4   │ 20 │ 4 │ 1 │

想要知道 :math:`x,\ y` 之間的關係，無法不去 reference :math:`z`

如果直接算 :ref:`pearson correlation <pearson-cor>`::

    julia> cor(df[:x], df[:y])
    0.8356578380810945


算 partial correlation 得 ``0.904194430179465``:

.. literalinclude:: ./code/pcor.jl


Reference
----------------------------------------------------------------------

- https://en.wikipedia.org/wiki/Partial_correlation
