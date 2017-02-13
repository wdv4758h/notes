Eliminate Noise via Hierar. Agglom. Method
===============================================================================

用 Hierar Agglom D_centroid 去除影像之 Noise

Problem
    If a pixel whose Grey Level is :math:`x, 0<=x<=255`
    and the Grey Levle of 8 neighbor pixels is:

    +------+------+------+
    |  22  |  23  |  24  |
    +------+------+------+
    | 239  |   x  | 235  |
    +------+------+------+
    | 238  |  237 | 236  |
    +------+------+------+

I.
    8 neighbor 用 Hierar Agglom
    e.g. 分出
    A = {22, 23, 24}, \bar{A} = 23.0
    B = {235, 236, 237, 238}, \bar{B} = 237.0
    不給定群數，用個 threshold 來決定要不要 merge

II.
    Then, if :math:`\| x - \bar{A} \| = \| x - 23.0 \| < threshold_Noise`,
    則 x 像 A cluster \therefore 不改 x
    B cluster 同理

III.
    If \| x - \bar{A} \| > threshold_Noise *and*
    \| x - \bar{B} > threshold_Noise,
    則 x 是個四不像
    \therefore x is noise
    \therefore x 需換值

換值時，偏好大值，以及偏好 正上、正下、正左、正右 (人眼)

\therefore
Score 22 is \|A\| = 3
      23 is \|A\|+1 = 3 + 1 = 4
      24 is \|A\| = 3
Score 235 is \|B\| + 1 = 5 + 1
      236 is \|B\| = 5
      237 is \|B\| + 1 = 6
      238 is \|B\| = 5
      239 is \|B\| + 1 = 5 + 1
\therefore Score_A = 3 + 4 + 3 = 10
Score_B = 6 + 5 + 6 + 5 + 6 = 28
\therefore x \in B, i.e 237

實驗: 他用 T_Hierar = 25, T_Noise = 36

誤差定為 RMS = | Original - New |

本法 RMS = 11 < Mediam Filter 的 RMS = 19 < K-Means Filter 之 RMS = 21
