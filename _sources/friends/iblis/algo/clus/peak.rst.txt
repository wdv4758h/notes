Peak-Climbing Method
===============================================================================

(Mode-Seeking Method)

User 不必給定群數，但須決定格子 (blocks) 數.
e.g.: 2-dimension -> Q x Q blocks

亦有 Valley-Seeking

e.g.:
We have data point with 2-dimension, and
:math:`Q \times Q = 6 x\times 6`.

Then, counting the data point located in each blocks.

Table for example:

+----+-----+-----+-----+-----+-----+
| 6  | 42  | 11  | 2   | 1   | 0   |
+----+-----+-----+-----+-----+-----+
| 37 | 250 | 58  | 10  | 24  | 9   |
+----+-----+-----+-----+-----+-----+
| 34 | 200 | 52  | 48  | 120 | 38  |
+----+-----+-----+-----+-----+-----+
| 3  | 25  | 19  | 125 | 230 | 97  |
+----+-----+-----+-----+-----+-----+
| 2  | 3   | 15  | 122 | 220 | 112 |
+----+-----+-----+-----+-----+-----+
| 0  | 5   | 7   | 52  | 190 | 46  |
+----+-----+-----+-----+-----+-----+

:math:`\forall` blocks, it has 8 neighbor.
Find the max of neighbor.

if max(neighbor) > self, then 畫出到 neighbor 的射線。

當 所以 neighbor 的射線都指向自己，即 local max (cluster center)

p.s. cluster 的範圍，由 Peak 反射線而行。

blocks number 不易決定，
太少 => 可能會只有 1 群，太多 => local max 太多

high-dimension 的資料不適用，
e.g.: 5-dimension 有 :math:`3^5 -1 = 243` 個 neighbor
