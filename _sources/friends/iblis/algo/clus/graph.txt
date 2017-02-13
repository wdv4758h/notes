Graph-Theoretical Method
===============================================================================

Tree: 每個 vertix 都有 neighbor ，且沒有 loop


Definition Inconsistent Edge \overline{AB}
----------------------------------------------------------------------

\overline{AB} 是點 A 與 點 B 的連線，其長度遠大於其他任一 Edge 長

則 Inconsistent Edge 宜分群，形成 {A} {B} clusters。

若定 Neighborhood 是 2 行程內

Average_A = Neighborhood/ # of Neighborhood
V_A = A 的變異數

e.g AB - Average_A / Var_A ~= 22

若 Edge 長度為 normail distribution，不到 1% 的 Edge 會使 z >= 3

Inconsistent 決定於

- 是否要求 AB 兩端都要 Inconsistent

- Neighborhood 的大小

- 亦可使用 threshold
    + | AB - Average_A | >= threshold
    + | AB | / Average_A


Minimal Spanning Tree (MST)
----------------------------------------------------------------------

所有的 Tree 中 edge 總長最短的，答案不唯一

以 { \vec{x_1} .. \vec{x_n} } 建 MST

#. 任意用某點(e.g. A)起始，找出離 A 最近，連到 A，即得 Tree T_1

#. \forall k = 2, 3, 4... 建立 T_k from T_{k-1} by add (one of the) shortest
   edge from a node not in T_{k-1} such that T_k is still connected.

Complexity: \theata n^2

\therefore 慢

建完 MST 後，算每個 MST edge 之 inconsistency =
- | AB - Avg_A | / Var_A  > threshold
  | AB - Abg_B | / Var_B > threshold

然後用 inconsistency 排名，優先斷 inconsistency 大者

\therefore 將 connected graph 斷成 disconnected graph

1980 左右另有其他圖像被提出做分群
- Gabriel Graph
- Relative Neighborhood Graph
- D 三角 DT 圖

MST 對 touching 的 data 不太能分群


Definition of Gabriel Graph
----------------------------------------------------------------------

for {x_1, ... x_n}

x_i, x_j 兩點連線

Disk(x_1, x_j) 內不含資料點

以 \overline{x_i x_j} 為直徑，畫圓盤，盤內無其他資料點

| x_i - x_j | ^2 < | x_i - x_k | ^2 + | x_j - x_k | ^2, \forall k != i, j

ref: `https://en.wikipedia.org/wiki/Gabriel_graph`_


Definition of Relative Graph
----------------------------------------------------------------------

以 x_i 為圓心，以 x_j 為圓心， | \overline{x_i x_j} | 為半徑

畫出兩圓盤的交集區，稱為 Lune， Lune 內若無其他資料點 x_k,
就使 x_i x_j 連線

\overline{x_i x_j} \in Relative Graph <=>
| x_i - x_j | < Max{ | x_i - x_k | , | x_j - x_k | }, \forall k != i, j

- Lune 比蓋住 Disk
\therefore Lune 內無點， Disk 內必無點

\therefore 若 \overline{x_i x_j} 是 Relative Graph edge,
其也是 Gabriel Graph Edge

\therefore
Edge_{RNG} C Edge_{Gabriel}
           -


Delaunay Triamgles
----------------------------------------------------------------------

每個資料點佔出其勢力範圍

::

   \  x1 /
    \   /
     \ /
   x2 |  x3
      |
      |


Voronoi Diagram
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Delaunay 三角化

Def
    若兩資料點 x_i 與 x_j 的勢力範圍 (cell_i and cell_j) 有碰到
    (e.g. cell_i and cell_j 為 neighbor), 就 \overline{x_i, x_j} 連線

DT 的 edge 很多 >> Gabriel Graph # of edge >= RNG >= MST

註： Voronoi Diagram for data point { \vec{x_1} ... }
是用中垂線之觀念畫得（e.g. 將 \vec{x_1} \vec{x_2} 連線，畫此連線之中垂線）

Each data point 有其勢力範圍(cell_i)
\forall \vec{y} \in cell_i, | \vec{y} - \vec{x_i} | <= | \vec{y} - \vec{x_j} |
\forall j = 1 \dots n (j != i)


Clustering via Graph Method
----------------------------------------------------------------------

不管用何種圖(將 \vec{x_1} ... \vec{x_2} 連線)，
都在某種 inconsistency 的定義下，
可能拿掉 inconsistent 的 edge,
而斷成數群


e.g.

data point::

    (1, 1)
    (1, 2)
    (1, 3)
    (2, 1)
    (2, 2)
    (2, 3)
    (3, 1)
    (3, 2)
    (3, 3)

    (4, 4)
    (4, 6)
    (4, 8)
    (6, 4)
    (6, 6)
    (6, 8)
    (8, 4)
    (8, 6)
    (8, 8)

- MST 能分成兩群。 break \overline{(3, 3) (4, 4)}
