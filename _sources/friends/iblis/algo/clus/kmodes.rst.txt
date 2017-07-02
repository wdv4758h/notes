K-Modes
===============================================================================

分 Category Data (Non-numerical 非數值)

1998, K-Modes

Mode 約等於 群中心，但不是平均而得，而是發生頻率最多次。

e.g. n = 5 , 點 {\vec{x_1} ... \vec{x_5}} 分 k = 2 群
given x_1 = (\alpha, big) = x_4
      x_3 = x_5 (\beta, mid)
      x_2 = (\beta, small)

Init
    猜 z_A = x_1 = (\alpha, big)
       z_B = x_2 = (\beta, small)

Iteration 1
    i. 分配 x_3 to B cluster (\because z_A 有兩個不同， z_B 只有一個不同)
       x_4 to A; x_5 to B
    ii. update centroid
        z_A = Mode { x_1 = (\alpha, big) = x_4 } = (\alpha, big)
        z_B = Mode { (\beta, small), (\beta, mid), (\meta, mid)} = (\beta, mid)

Iteration 2
    i. 改分配後
        A = {x_1, x_4},
        B = {x_2, x_3, x_5}
    ii. update centroid
        z_A = (\alpha, big)
        z_B = (\beta, small)
        Stop!


ps. 用發生率取代幾何平均

問題
    若
    A = {
        x_1 = (1, 1, 天)
        x_2 = (1, 1, 地)
        x_3 = (1, 1, 玄)
    }
    B = {
        x_4 = (1, 1, 黃)
        x_5 = (2, 1, 玄)
        x_6 = (1, 2, 天)
    }

    Mode z_A (1, 1, 天), Mode z_B = (1, 1, 黃)

    則 x_7 = (1, 1, 宇) 應分到哪裡？

2007, IEEE-T-PAMI
"On the impact of Dissimilarity Measure"

e.g. 統計圖 for A

| \dots | dim 1 | dim 2 | dim 3   |
| 1     | 3 次  | 3     | 1 次 天 |
|       |       |       | 1 次 地 |
|       |       |       | 1 次 玄 |
|       |       |       | 0 次 黃 |
|       |       |       | 0 次 宇 |
+-------+-------+-------+---------+
| 2     | 0     | 0     |         |

for B

| 1     | 2 次  | 2     |
| 2     | 1     | 1     |

diff measurement for (x_7, z_A) = (1 - (3 次) / 3) + (1- 3/3) + 1 = 1 維不同

(x_7, z_A) = (1- 2/3) + (1 - 2/3) + 1 = 1.6666 維不同

\therefore x_7 分到 A


Example
----------------------------------------------------------------------

47 點的 soybean data ( 大豆疾病 )
35-dim 裡的 21-dim 有用 ( 其餘 14-dim 只有同一種讀數 )

4 種疾病
- D_1: 10 point
- D_2: 10
- D_3: 10
- D_4: 17

各跑 100 種 initials 取平均
則

|               | k-mods     | 2007 改良距離 |
| Accurarcy     | 82.6%      | 91.32%        |
| Precision     | 88.1%      | 95.0%         |

ps. 名詞解釋
e.g 若 A class 原有 130 點: 110 點 分對， 20 點分錯

       B class      150     120           30

       則 Accurarcy = \frac{110 + 120}{130 + 150}

       而 Precision_A = 被分到 A 者,有多少來自 A
                      = \frac{110}{110 + 30}
                      (意義是: 分到 A 的可信度)
          Precision_B = \frac{120}{120 + 20}

    Recall Rate_A = \frac{110}{130}


Better Initials for K-mods
----------------------------------------------------------------------

Pattern Reconition Leter, vol 23 2002

符號: n point 分 k clusters

let J = \frac{n}{k} * 0.1 ~ 0.5

然後從 data 做 random sub-sample
以挑出 J 個 subset of data

abbr. CM = Cluster Modes
abbr. FM = Finer Modes (Better Modes)

Input: k, J, data
Output: k 個還不錯的 Modes

Step 1:
    sub-sampling. Initially set CMU = 空集合
    Then, for i = 1...j do (A) and (B)

    A. for subset S_i of Data, randomly 從 S_i 選 modes,
       以開始跑 k-modes

       Let CM_i 為跑完之 k 個 modes

    B. CMU 為所有 CM_i 之 Union

Step 2: Refinement
    For i = 1 ... J do
    用 CM_i 將 CMU 分成 k clusters,
    得 FM_i

Step 3: Selection
    看哪一組的 FM_i 是最佳代表 CMU
    i.e (Total Distortion 最小化)

    Then, output best FM_i


Experiment
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

| Accurarcy | Better initail method | Random initial |
| 98%       | 14 次                 |  5 次          |
| 94%       |                       |  2             |
| 89%       |                       |  2             |
| 77%       |                       |  3             |
| 70%       | 5                     |  0             |

| 68%       | 0  可能 sampling 不好 |  5             |
| 66%       | 1                     |  3             |


ROCK Method
----------------------------------------------------------------------


