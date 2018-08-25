Monothetic Clustering
===============================================================================

v.s. Ploythetic Clusttering
大部分的 Clustering 是 poly, 同時考慮多變數來分群

e.g k-means, MST, Hierarchical

Monothetic 主要用作生物分類

e.g. 遇一生物，如何判別是否為新物種？
是非題
    Q1. 有脊椎嗎？
    Q2. 有冷血嗎？
    ...

物種既 binary string
2^50 ~= 10^15 = 14 兆


前處理
----------------------------------------------------------------------

恆 True 的問題，需排除
很 False 的問題，亦排除
e.g. 身高 <= 15000 m 嗎？
無辨識力

兩變數(e.g. 兩問題)
若 Ans 永遠相同，則排除1個
e.g. 問題內容相同，單位不同：cm / m

若 Ans 永遠相異，亦排除1個
e.g. 互補問題： < 100 cm & >= 100 cm

Topic:
誰該是 第一問題 for 分為兩群

用 Max Association Sum

Def
    Association Measure between variable x and y
    M(x, y) = | (出現 (1, 1) 的參數 \times 出現 (0, 0) 的次數) - ( .. (1, 0) - (0, 1) .. ) |

e.g. table on e3

M(x, y) = | 2 \times 2 - 2 \times 2 | = 0 , low association

M(r, s) = | 4 \times 2 - 2 \times 0 | = 8, high association

若兩變數之 Ans 幾乎都一樣則關聯亦高: e.g. | 6 \times 1 - 1 \times 1 | = 5
                                     e.g. | (n/2) \ times (n/2) - 0 \times 0 | = n^2 / 4


變數挑法:
1. 算 M_{ij} \forall i,j

2. Sum_x = \sum{\theta != x}{M_{x\theta}} = M_{xy} + M{xz} + ...
   Sum_y = \sum{M_{y\theta}}

3. 用 Max Association Sum 定出變數

e.g. 假設 y = v_2 , Sum_y 最大

則 8物 v_2 = 1 {甲丙戊庚}
       v_2 = 0 {乙丁己辛}

Then {甲丙戊庚} 根據 {v1, v3, v4, v5, v6} 做 table,
再算 Max Sum 挑變數(a new iteration)


