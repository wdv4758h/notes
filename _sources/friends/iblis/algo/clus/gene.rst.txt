Genetic Algorithm
===============================================================================

String (chromosome) 的選用

Paper
    1996, PRL, Vol 17 P825-832

    "In Search of Optimal Clustering using GA"

把 n 點分成 k 群之結果用長度為 n 之 string 表示

e.g. 3000 points 分 3 群, 則
(x_1, x_2, ,,,           x_3000) =
(A,   A,   C, B, C, ..., C)

缺點
    i.找最佳分群結果(最佳字串)太花時間.

    \because solution space 是 3^3000

    ii.

    string1: ABB CBA
    string2: ACC BBA

    做 Cross over, 取 string1 前半 以及 string2 後半,
    得到 ABB BBA, 則 Cluster C 不見了, 群數變少,
    是無效的 cross over


2002 Info Science
    "An Evolutionary Technique based on k-means for Optimal Clustering"

    其 Optimal 是企圖降低 1 次方 error,
    而不是 TSSE 的 2 次方 error

    此法改用 k 個群中心當作字串
    e.g. 若資料是 d 維度 data

    則 string:
    :math:`(\vec{c_1}, \vec{c_2}, \dots, \vec{c_k})`
    :math:`= (c_{11}, c{12}, \dots, c{1d}, c{21}, c{22}, \dots, c{2d}, \dots)`
    其長度為 :math:`k \times d` 之 string


Algorithm
----------------------------------------------------------------------

假設 Population Pool 的 size = 50

#.
    隨便產生至多 50 組 k-means 分群結果, 記為
    :math:`(\vec{c_1}, \dots, \vec{c_k})`

#.
    做 Selection Crossover, Mutation

    作用到 這 50 組 :math:`(\vec{c_1}, \dots, \vec{c_k})`

#.
    改分配 :math:`{\vec{x_1}, \dots, \vec{x_n}}` 到最近的 centroid,
    後 update centroid, :math:`(\vec{c_1}, \dots, \vec{c_k})`

    算
    TSE = \Mu = \sum_1^k \sum_{\vec{x} \in Cluster_j} \| \vec{x} - \vec{c_j} \|

#.
    扔掉 Population Pool 裡面最差的 string,
    補進上一輪的最佳 string

#.
    重複 step 2~4, 做到指定之 generation (iteration),
    此時才 output 產生最小 TSE 的那組 centroid 以及分群結果



Selection
    Pool 裡的 TSE 比較小之 string 複製數份(以增加被使用次數)

    TSE 越小者, copy 約多份

Crossover
    依機率 P_{crossover} 執行 crossover

    本法用 *單點* 之 crossover, 即在 {1, 2, ..., kd - 1}
    中挑個位置

    取兩個 string 在此點以右之部分, 互換這兩個 part
    得兩新字串


Mutation
    本文依機率 P_{Mut} 從 Pool 抽出某 String 做突變

    令  TSE 未該抽出之 String 的 TSE

    Let TSE_{min} and TSE_{max} 未目前 Pool 裡的 50 個 String 之 min and max

    Let R = \frac{TSE - TSE_{min}}{TSE_{max} - TSE_{min}}
    \therefore 0 <= R <= 1 (0 is best; 1 is worest)

    然後, 在 -R <= \delta <= R 裡產生一個 \delta

    For each dimension = 1 ... d,
    一個群中心 \vec{C} 若要在該 dim 做突變, 則該 dim 新讀數為

    舊座標 + \delta(x^{dim}_{max} - 舊座標), if \delta > 0
    {
    ‘’     + \delta(舊座標 - x^{dim}_{min}), if \delta < 0

    其意義是往上/下調整 \delta 比例, 但不會超過極值


Experiment
----------------------------------------------------------------------

GA 每次跑 1000 個 generations
K-means 亦跑 1000 次

每組 data 跑 50 個實驗

e.g.1
    人造點: 2-dim, k=2 共 10 points

    k-means 之 TSE: 2.225 ~ 5.383 (average = 3.49)
    1996 GA : 都 2.225
    本文之 GA: 都 2.225

e.g.2
    人造點: 2-dim, k=2 共 76 points

    k-means TSE: 47.6 ~ 61.6 (50次)
    1996 GA: 60 ~ 72
    2002 GA: 都 47.6

e.g.3
    Indian 母音
    三男性發音, 共 871 點, 分六群

    k-means: 149373 ~ 151625
    1996 GA: 383484 ~ 149378
    2002 GA: 149356 ~ 149378

e.g.4
    Iris: 4-dim, 150 points, k=3

    k-means: 97~124
    1996 GA: 124~139
    2002 GA: 都 97.101


取得 min TSE 之平均 generation 數

+-------+---------+---------+
|       | 2002    | 1996    |
+-------+---------+---------+
| e.g.1 | 2~3     | 21      |
+-------+---------+---------+
| 2     | 3       | Never   |
+-------+---------+---------+
| 3     | 2115    | Never   |
+-------+---------+---------+
| 4     | 358     | 5868    |
+-------+---------+---------+


Topic: 不給定群數 之 GA
----------------------------------------------------------------------

Genetic Clustering for Unknow K (GCUK)

2002 P.R 作者同前

群數 k \in {2, 3, \dots, K_{max}}

機率
    - P_{crossover} = 0.8

    - P_{Mutation} = 0.001

Pool 之 Population size = 50

Init of Pool
    \forall i=1 ... 50

    randomly get K_i \in {2, ... 10}

    randomly get K_i points from {\vec{x_1}, ..., \vec{x_3000}}

    把 randomly K_i points 放入 10 個 slots

    e.g. 抽到 K_i = 4, 則 放 4 個資料點 {\vec{x_1}, x_3, x_99, x_2010}
    到 10 個 slots
    | # | x_99 | # | # | x_3 | # | x_2010 | # | x_1 | # |


DB-index (Davis & Bouldin)

群_i 的 Scatter 是 S_i = \frac{1}{群_i 點數}  \sum_{x \in 群_i} \|x - C_i \|

S_i 可以理解成勢力範圍

d_{ij} = \| C_i - C_j \|
R_i = max_{j != i}  \frac{S_i + S_j}{d_{ij}} = 第 i 群至其他群的最糟關係

DB 小比較好

DB = average({ R_i, ... })

G.A 之操作

Selection
    DB 小之字串 copy 幾組

Single-Point Corssover
    基於某機率 P_{cross}, 若抽出 Single-Point 是在 4&5 之間

    則                  vvv
    | #  | 73 | #  | 28 | #  | #  | 77 | #  | #  | #  |  (3 群)
    | 45 | 56 | #  | 79 | 63 | 98 | #  | 16 | 53 | #  |  (7 群)

    做完 crossover, 得新字串

    | #  | 73 | #  | 28 | 63 | 98 | #  | 16 | 53 | #  |  (6 群)
    | 45 | 56 | #  | 79 | #  | #  | 77 | #  | #  | #  |  (4 群)

Mutation
    依機率 P_{Mutation} 做突變
    挑某 String 做突變時
    該 String 的 非空slot
    依 Randon 挑出 \delta (0 <= \delta <= 1)
    調整

GCUL Algorithm
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Init
    50 組字串, 每組 # 數量不定

Step 1
    對每個 String_i, 抓出其有效群中心, 分解 再得 DB-ndex

Selection, Crossover, Mutation

Step 3
    若 generation 數量未滿,
    殺掉目前 pool 最差的 String, 用上一個 generation 最佳的代替

    Go to step 1

Experiment
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

e.g. Iris data

    三群分成兩群

    \therefore DB_{2群}  = 0.396 < DB_3 = 0.747

    但 Iris 太重疊, 許多 paper 的方法分成 2 群

.. note::

    DB-index 亦可換成其他指標
