Fast Methods to Find Nearest Cluster Centers
===============================================================================

e.g. k-means or VQ

Definition
    :math:`k` = # of clusters = codebook size
    :math:`\text{codebook } = \{ \vec{y_1}, \dots, \vec{y_n} \}`

Definition
    :math:`\vec{x} = (x_1, ... , x_16)` 是個 16 維的新資料點


Goal
.. math::
    min \| \vec{y_i} - \vec{x} \| ^2
    =
    min [ \sum_{j = 1}^{16} (y_{ij} - x_j)^2 ],
    i = 1, 2, .\dots, 128




假設到目前為止，已有某些 centroid 被檢查過。
e.g. 已查過 :math:`\vec{y_1} \vec{y_2}` 。
到目前為止最靠近 :math:`\vec{x}` 的平方誤差是

.. math::

    d^{2 (current)}_{min} = \| \vec{x} - \vec{y^{current}_{min}} \| ^2 =
    min \| \vec{x} - \vec{y_l} \| ^2,
    \vec{y_l} \in \{ 已檢查過 \}

問題：對下一個待檢查的 :math:`\vec{y_i}` ，應該老老實實的計算
:math:`\| \vec{y_i} - \vec{x} \| ^2` ?

Partial Distance Elimination
----------------------------------------------------------------------

1985 PDE Method

.. math::

    If (y_{i1} - x_1) ^ 2 + (y_{i2} - x_2) ^ 2 + (y_{i3} - x_3) ^ 2 >
    d^{2 (current)}_{min}

就不用繼續算下去


TIE Method
----------------------------------------------------------------------

三角不等式消除法

Pre-Processing: 先記錄 O(k^2) = 128x127/2 = C^n_2 組距離

Main: 只要

.. math::

    \| \vec{y_i} - \vec{y^{current}_{min}} \| >= 2 d^{current}_{min}

就保證 :math:`\vec{y_i}` 不可能更接近 :math:`\vec{x}`

Proof
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

三角形的兩邊合大於第三邊

::

    _
       \vec{x}
       /
      /
     /
    \vec{y^{current}_{min}}
     \
      \
       \ \vec{y_i}

.. math::

    \| \vec{y_i} - \vec{x} \| >=
    | \| \vec{y_i} - \vec{y^{current}_{min}} \| -
      \| \vec{y^{current}_{min}} - \vec{x}   \|
    |
    = | >= 2 d^{current}_{min} - d^{cur}_{min} |
    >= (2 - 1) d^{cur}_{min} =
    \| \vec{y^{cur}_{min}} - \vec{x} \|

IEEE-T-Com
----------------------------------------------------------------------

1994 Torres & Huguel

若每一維都 >= 0

.. math::

    If \| \vec{x} \| ^2 + \| \vec{y_i} \| ^2 -
    2 (\vec{y_i})_max ( \sum_1^{16} x_j ) >= d^{2 cur}_{min}

    or

    If \| \vec{x} \| ^2 + \| \vec{y_i} \| ^2 -
    2 (\vec{x})_max (\sum^16_{j=1} y_{ij}) >= "

    where X_max = max {x_1, x_2, \dotss, x_16} = \| \vec{x} \|_{infinit}

    where 先算好 3 x 128 個zhi


則 \vec{y_i} 不可能小於 \vec{y^{cur}_{min}}


Fast Kick-out by an Inequality
----------------------------------------------------------------------

IEEE-T-C.S.V.T 2000
K.S. Wu

.. math::

    \| \vec{x} - \vet{y_i} \| ^2 = (x - y_i) \dot (x - y_i)
        = \|x\|^2 + \|y_i\|^2 - 2 x \dot y_i

    let \telda d ^2 (x, y_i) = \| x - y_i \| - \| x \| ^2

在此新的定義之下，不影響結果

Now

.. math::

    d^2(x, y_i) = \| x - y_i \|^2 - \|x \|^2
        = (x - y_i)(x - y_i) - \|x\|^2
        = \|y_i\|^2 - 2 x \dot y_i
        >= \|y_i\|^2 - 2 \|x\| \|y\|
        = \|y_i\|(\|y_i\| - 2\|x\|)

    \therefore if \|y_i\|(\|y_i\| - 2 \|x\|) >= \telda d^{2 (current)}_{min}

    則 \telda d^2(x, y_i) >= \|y_i\|(\|y_i\| - 2 \|x\|)
       >= \telda d^{2 (current)}_{min}
       (define as \|x - y_i^{current}_{min}\|^2 - \|x\|^2)

    \therefore y_i 不會筆 y^{current}_{min} 跟近 x

Implementation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

先 sort \vec{y_1} ... \vec{y_128}

使 \|y_1\| <= \| y_2 \| <= ... <= \|y_128\|

Goal
    找 最靠近 x 的 y_i

Step 1
    算 2 \|x\|, 猜一個 y_{init} 當作 y^{current}_{min}

    let \telda d^2_{min} = \telda d^2(x, y_init)

    let remaining set R = {拿掉 y_init 的 centroid}

Step 2
    a. if R is empty set, the y^{current}_{min} is the answer;
       從 R 挑個 y_i
    b. 若 \|y_i\| (\|y_i\| - 2 \|x\|) >= \telda d^2_min,
       則
       case i.
            若 \|y_i\| >= \|x\| 則扔掉所有的  \{y_l | l>=i\}, goto step 2a
       case ii.
                       <=                              <=   , goto step 2a
    c. \telda d (x, y_i) 從 R 扔掉 y_i,
       若 \telda d^2 (x, y_i) >= \telda d^2_min, goto 2a
    d.
        Let d^2_min = \telda d^2(x, y_i)
        Let y^{current}_{min} = y_i
        goto step 2a


Step 2b case i and ii 是

.. math::


    \because \|y_l\|(\|y_l\| - 2\|x\|)
    >= \|y_i\|(\|y_i\| - 2 \|x\|)
    >= \deta d ^2_{min}

    \because f(t) = t(t - 2\|x\|)
                  = t^2 - 2\|x\| t
    是拋物線，且在 t = \|x\| 時最小


Conclusion
----------------------------------------------------------------------

| 方法 | 三角不等式  | 乙法 1994    | 投影法 1995            | Inequality  |
+------+-------------+--------------+------------------------+-------------+
| 儲存 | C^128_2     | 至少 3 x 128 | 128 + 128(\sqrt(16))   | 128         |
|      |             |              | 128(\sqrt{16})         |             |

* 512x512 切成 4-by-4 做 VQ 壓縮之時間

+---------------+-------------+---------+-----------+------------+
| Codebook Size | Full Search | 三角    | 乙        | Inequality |
+---------------+-------------+---------+-----------+------------+
| 128           | 30 s        | 4.5     | 5.3       | 1.89       |
+---------------+-------------+---------+-----------+------------+
| 256           | 73          | 8       | 14.37     | 4.15       |
+---------------+-------------+---------+-----------+------------+
| 512           | 146         | 13.7    | 27.24     | 7.23       |
+---------------+-------------+---------+-----------+------------+
