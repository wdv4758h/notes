Cluster number
===============================================================================

Fuzzy K-Means
----------------------------------------------------------------------

FKM =
    min \sum_{j=1}^K \sum_{i=1}^n u_{ij}^2 \| x_i - c_j \|^2

1995 iEEE-T-FuzzySystem 提到數種指標包括

PC
    PC = \frac{\sum_{1}^K \sum_{1}^n u_{ij}^2}{n points}

    \frac{1}{k} <= PC <= 1

PC 大時, 像 Hard clustering

\therefore 其 k 可能較有意義 ( \Mu_{ij} ~= 0 or 100%)


PE
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Partition Entropy

= \frac{-1}{n} \sum_{1}^K \sum_{1}^K (u_{ij} log(u_{ij}))

0 <= PE <= log K

PE 小則像 Hard clustering,
此時 K 可能較有意義

2001 Fuzzy Sets & System

Pages 239 - 247
有 PC 的實驗

Iris 亦分兩群
其餘實驗大致 ok

