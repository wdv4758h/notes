Hard Clustering Index
===============================================================================

Hard clustering 之指標 for 群數

DB Index
----------------------------------------------------------------------

min_{2 <= k <= k_max} DB_k

DB_k = \frac{1}{k} \sum^k_1 R_i = average R_i,
where R_i = Max_{j != i , 1 <= j <= k} R_{ij}
即群 i 至其他(重疊)群之最糟 relation

而 R_{ij} = \frac{S_i + S_j}{d_ij}, d_ij = \| \vec{c_i} - c_j \|,
S_i = \frac{\sum_{x \in Cluster_i} \| \vec{x} - C_i \|}{ | 群 i 點數 | }

註： 1997 年用圖學(e.g. MST or RNG)

DB^{RNG}_k = \frac{1}{k} \sum_1^k R^{MST}_i

而 R^{MST}_i = Max_{j != i} R^{MST}_{ij}

而 R^{MST}_{ij} = \frac{S^{MST}_i + S^{MST}_j}{d_ij}
                = \frac{ <same> }{ norm(C_i - C_j)  }

S^{MST}_i 是指群_i 之點畫 MST 後所有 egde 最長者


Dunn Index
----------------------------------------------------------------------

Def
    最大化 D_k

而

D_k = min_{1 <= i <= j <= k} \frac{D_{min}(群_i, 群_j)}
        {Max_{1 <= l <= k} Diameter(群_l)}

Diameter(C_l) = l 者群內相聚最遠的兩點之距離，代表群內緊密的程度


Noise
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

DUNN Index 受到雜訊影響

\therefore 改用 1997 之圖學法:

D^{MST}_k = min_{1 <= i <= j <= k} \frac{ norm(C_i, C_j)_D{mean}}
            {Max_{1 <= l <= k} S_l^{MST}}


Royal Statistics
----------------------------------------------------------------------

2001 "Estimating the # of clusters via the Gap Statistics"

Def
    一個群 (e.g. 群 A)

    D_A = \sum_{x_i \in A, x_j in A} \| x_i - x_j \|

    W_k = \sum^k_{A = 1} \frac{1}{2} \frac{D_A}{ len(A) }


Let Z is original data, 然後 包住 Z 產生一個長方體
(e.g. [min_x max_x] \times [min_y max_y] ...)

在長方體內，產生 (e.g 10 組)人造點

每組人造點都很像 uniform distribution

沿座標軸產生長方體，則 Simple，但效果差

若沿 Principal Axis of Data Z, 產生長方體,則效果好


答案是最小之 k in {2, 3, ... k_max}
滿足
 ~
 \sigma^{人造}_{k + 1} >= Gap(k + 1) - Gap(k)

Algo
    \forall k = 2, \dots, k_max
    #. Z 分 k 群, 算 log(W_k)

    #. 10 組人造點，各分 k clusters
       各算 log(W^{人造}_k),
       然後算 10 個 log 之 average 得 \bar{log(W^{人造}_k)}

    #. Gap(k) = \bar{log(W^{人造}_k)} - log(W_k)

    #. \sigma^{人造}_k 是這 10 組 log^{人造} 的 standard diviation

而
 ~
 \sigma^{人造}_{k} = sqrt( 1 + \frac{1}{10 組} ) \times \sigma^{人造}_k
