Frequentist Inference
===============================================================================


Confidence Intervals
----------------------------------------------------------------------

假設我們的一次實驗，是丟一硬幣 100 次。
某次實驗得到 44 head, 56 tail。
試問本次實驗的 95% Confidence Interval 為何？

我們的 single outcome 是 Bernoulli distribution

.. math::

    x_i \sim Bern(p)

只是我們的 :math:`p` 是 unknown，
而且在 frequentist 的假設下 :math:`p` 是固定的值。

回想中央極限定理

.. math::

    \sum_n x_i \sim N(np, np(1 - p))

而 :math:`n` 越大就會越像 normal distribution，
我們的 :math:`n = 100`

95% 的 confidence interval 為

.. math::

    [44 - 1.96 \sigma, 44 + 1.96 \sigma]

這個算出來， :math:`50` 有在這個 interval 中，
我們有 95 % 的信心說這個硬幣是公正的。

對 95% confidence interval 的討論：

#. 在 frequentist 的想法中，每個 100 次丟擲的實驗都有一個特定的 C.I.，
   而比例上，有 95% 的 C.I. 裡面有 true :math:`p`

   - 對單一特定的 C.I. 我們也想討論裡面有沒有 true :math:`p` ，
     對 frequentist 而言，就是有或是沒有。

#. 但對 Baysian 的分析來說，一個 C.I. 裡面有沒有 true :math:`p` ，
   是用機率來討論。
