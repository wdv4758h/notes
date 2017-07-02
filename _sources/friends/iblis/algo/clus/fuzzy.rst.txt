Fuzzy Clustering
===============================================================================

Fuzzy clustering 的相反詞是 hard clustering (crispy clustering)

e.g. k-means, hierarchical, peak-climbing... 皆是 hard clustering

Definition
----------------------------------------------------------------------

Fuzzy clustering 任一點都可屬於多群

e.g.

A point:

- 0.4 甲群
- 0.4 乙群
- 0.2 丙

B point:
- 0.3 甲
- ...

缺點：花時間

優點：有考慮到 data structure's detail
一點單獨看有比 hard clustering 多的 information


Fuzzy K-means
----------------------------------------------------------------------

AKA. Fuzzy C-means, F.C.M

1973 Bezdek 的 paper


{x_1, ..., x_n} 分 K 群

let {v_j | j=1...k} 為 k 個 cluster 的 centroid

q > 1 是控制參數

u_{ij} 是點 i 在 群_j 的可能性

\therefore u_i1 + ... + u_ik = 100%

min \sum{ (u_ij)^q | \vec{x_i} - \vec{v_j} | ^2 }, i=1...n, k=1...k

ps. tradictional K-means:

min \sum{ i=1...N }{ | \vec{x_i} \vec{v_j} | ^2 },
\vec{v_j} 是 \vec{x_i} 所屬的 cluster centroid

\therefore 傳統 K-means 是 F.K.M 的特例:
u_{ij} = 0 or 1


在 min 的要求下，有些數學式必須解( partial ... / partial ...  = 0)

Algo(F.K.M)

#. 隨便猜 k 個中心, { \vec{j} }, j=1...k

#. update membership coeffiecent u_{ij} =
{[ | \vec{x_i} - \vec{v_j} | ^-2 ] ^(1/{q-1})} / { \sum{l=1..k}{[ | \vec{x_i} - \vec{l} | ^-2] ^(1-/{q-1})}}

- 分母是為了 機率公設
- 1/(q-1) 是控制 fuzzy 的程度

#. update centroid
   \vec{v_{j}^{new}} = (\sum{i=1...n}(u_{ij})^q \times \vec{x_j}) / \sum{i=1..n}{(u_{ij})^q}

Max | u_{ij} - u_{ij}^{last run} | < threshold
=> stop


q > 1 will make F.K.M converge.
若 q 接近 1 會使 收斂慢 且 不 Fuzzy

e.g.
let q = 1 + 1/1000, \therefore 1/(q-1) = 1000

Assume
| x_i - v_1 | = 1/sqrt{50}
| x_i - v_2 | = 1/sqrt{49}
| x_i - v_3 | = 1/sqrt{48}

則
u_i1 = 50^1000 / (50^1000 + 49^1000 + 48^1000) = 99.99...%
u_i2 = 49^1000 / ''                            = 10^-9
u_i3 = 48^1000 / ''                            = 10^-18

\therefore 雖然 x_i 與 v_1 v_2 v_3 距離差不多
卻 winner takes all

1973 Bezdek 用 q = 2

.. note::
    Fuzzy K-means 仍會卡在 local min
