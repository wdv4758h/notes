Clustering Aggregation by Probability Accumenulation
===============================================================================


Wang, Yang, Zhou
P.R. 2009 Vol 42 page. 668-675

:math:`{\vec{x_1} \dots \vec{x_n}}` for each is m-dimension

~
c^(1) ... c^(9) 是 9 種分群結果

Step 1:
    算 Component Matrix [A]^(P), P = 1 ... 9

    A^(P)_{ii} = 1, \forall i = 1 ... n

                  /- 0, if x_i 與 x_j 不同群 in C(P)
    A^(P)_{ij} = {
                  \-    \frac{1}{1 + (含 x_i, x_j 那群之元素個數)^(1/m)}

Step 2
    \bar{A} = P association
            = \frac{1}{9} \sum^9_{P=1} [A]^(P)

Step 3
    Then, transform \bar{A} into distance matrix

    d(x_i, x_j) = 1 - \bar{A}(x_i, x_j)
                = 1 - \bar{A_{ij}}

Step 4
    Hierar Merge(用 D_{min})

    停在 big jump of distance 之前


Exp
----------------------------------------------------------------------

{x_1 ... x_9 } 1-dim
做兩次分群 (e.g. k-means, k=3, 做兩次)

exp 1:
    - A cluster {x_1, x_2}
    - B cluster {x_3, x_4}
    - C cluster {x_5, x_6, x_7}

exp 2:
    - A cluster {x_1, x_3}
    - B cluster {x_2, x_4, x_5}
    - C cluster {x_6, x_7}

則 7,7 的 association matrix \bar{A} 是


.. math::

    2 \bar{A} = (兩個 exp 加總)


|     |  x_1  x_2      |  x_3    x_4  |  x_5    x_6     x_7     |
| x_1 |       1/(1+2)  |  1/(1+2)
| x_2 |                |  (exp2)

| x_3 |                |       1/3  |
| x_4 |                |

| x_5 |                |            |         1/(1+3)  1/(1+3)
| x_6 |
| x_7 |


取 1 - \bar{A} 當距離

.. math::

    1 - \bar{A} = ...


Step 4:
    Hierar Merge
    e.g. {x_1, x_3, x_4} vs {x_5} vs{x_6, x_7}



|  兩個 half rings  |  400 + 100 point         | 2D

| Iris              | 50 + 50 + 50 point       | 4
| 手寫字            | 100 point (10 clusters)  | 64-dim
| 乳癌              | 683 (2 clusters)         | 9-dim

| Wine              | 178 (3 cluster)          | 13-dim
| Glass             | 214 (6)                  | 9


Pre-processing
    Normalize Data 使 mean = 0, var = 1
    在資料所在的空間畫等大小之方格，每格若出現 3 點，則只計一次

exp: run 10 times or 50 times exps, \forall Data set 用 k-means,
k 介於 10~30間，任意
e.g. 100~638 point , avg 349 point, squrt(349) = 19)

比較
    IEEE-T-PAMI 2005
    "Evidence Accumulation" (EA)

另一篇
    2002 CE 法

Error Rate
    無 pre-processing

|                | EA    |  CE    |   PA   |

| 2 half rings   | 0     | 25.42  |  0     |
| 3 rings        | 0.8%  | 49     |  0     |
| 雪茄           | 5.7%  | 24     | 8.6    |
| Iris           | 33    | 33     | 33     |

| 手寫字         | 65    |
| 乳癌           | 30    |

| average        | 34    |


Conclusion
----------------------------------------------------------------------

有 Pre-Processing 的 data:

P.A 約可改良 10% 的 error rate

PA(2009) 比 EA(2005)
    - 都不用 pre-proc, 改良 3%
    - 都     pre-proc, 改良 2%

PA 比起 CE(2002)
    - 都不用 pre-proc, 改良 12%
    - 都     pre-proc, 改良 19%
