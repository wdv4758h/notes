Hierarchical Methods
===============================================================================

- Divisive 分裂式
- Agglomerative 聚合式

Def
    Hierarchical Clustering 的相反詞是 Partitional Clustering

    e.g.

    - K-Means: 一層
    - Peak-climbing: 一層
    - Graph


Divisive
----------------------------------------------------------------------

At first, there is only one group.

We will pick up a group and divide it in following step.

e.g.

.. math::

    \text{init} \{1, 3, 5, 6 ,78, 79, 96, 97, 98\}

    \text{step1} \{1, 3, 5, 6, | ,78, 79, 96, 97, 98\}

    \text{step2} \{1, 3, | , 5, 6\} \text{&} \{78, 79, | , 97, 98\}

    \text{step3 ... etc}


Agglomerative
----------------------------------------------------------------------

At first, each point form a cluster.

:math:`\therefore` *n* point :math:`\geq` *n* clusters.

Then, we will merge the most similar two clusters via following step.

:math:`\therefore \text{clusters} - 1`


Distance between Two Clusters
----------------------------------------------------------------------

Assume we have two clusters -- :math:`\text{cluster}_A \text{cluster}_B`.


Definition 1: Centroid
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D(A, B) = \| \overline{a} - \overline{b} \|

.. math::

    \text{where }
    \overline{a} = \frac{\sum_{\vec{x} \in A} \vec{x}}{ | a | }

    \overline{b} = \frac{\sum_{\vec{x} \in B} \vec{x}}{ | b | }


Definition 2: Min Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D_{min}(A, B) = min(\| \vec{a} - \vec{b} \|)

.. math::

    \text{where }
    \vec{a} \in A,
    \vec{b} \in B

    Complexity: \Omega(n^2)

Note that only :math:`D_{min}` has Chaining Effect.


Definition 3: Max Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D_{max}(A, B) = max(\| \vec{a} - \vec{b} \|)

    \text{where }
    \vec{a} \in A,
    \vec{b} \in B

    Complexity: \Omega(n^2)


Definition 4: Average Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D_{average}(A, B) =
    \frac{\sum_{
        \substack{
            \vec{a} \in A \\
            \vec{b} \in B}}
        \| \vec{a} - \vec{b} \|}
    { | A | \times | B | }


Definition 5: Ward's Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D_{Ward}(A, B) =
    \sqrt{\frac{2 | A | | B | }{ | A | + | B | }} \times
    | \overline{a} - \overline{b} |

When we merge two cluster into one, the *TSSE* will rise.
Ward suggests that picking up the merging of mini *TSSE* rise.

Wishart turned Ward's theorem into formula.

We can consider this formula as:

.. math::

    \text{(a coefficient related to size of clusters)} \times
    \text{(centroid distance)}


Distance Matrix
----------------------------------------------------------------------

距離矩陣

Assume there is a n-by-n matrix :math:`A_{n \times n}`.

.. math::

    \begin{matrix}
        ~      & x_1    & x_2    & \dots  & x_n    \\
        x_1    & 0      & d_{12} & \dots  & d_{1n} \\
        x_2    & d_{21} & 0      & \dots  & d_{2n} \\
        \vdots & \vdots & \vdots & \ddots & \vdots \\
        x_n    & d_{n1} & d_{n2} & \dots  & 0      \\
    \end{matrix}


It's a symmetric matrix.

:math:`\because d_{12} = d_{21} = | \vec{x_2} - \vec{x_1} |`

:math:`\therefore \Omega(n^2)` 計算跟儲存量


Update Formula of Agglomerative Method
----------------------------------------------------------------------

在合併的過程， A, B merge 為 R (:math:`R = A \cup B`).

Calculate :math:`D(R, Q), \forall Q \neq A \text{ and } Q \neq B`

For reducing cpu time, we have update formula.

.. math::

    \text{Assume } |A| = 70, |B| = 30

    \therefore |R| = 100

    \overline{r} =
    \frac{70}{70 + 30} \overline{a} + \frac{30}{70 + 30} \overline{b}

    \text{where } \overline{r}, \overline{a}, \overline{b} \text{ is the centroid.}


Min Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    \text{Let } D = D_{min}

    \text{Then, }
    D_{min}(R ,Q) = min(D_{min}(A, Q), D_{min}(B, Q))


Max Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`D_{max}` will same as :math:`D_{min}`:

.. math::

    D_{max}(R, Q) = max(D_{max}(A, Q), D_{max}(B, Q))


Average Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    D_{average}(R, Q)
        & = \displaystyle\sum_{\substack{\vec{r} \in R \\
                                            \vec{q} \in Q}}
            \frac{\| \overline{r} - \overline{q} \|}{|R| \times |Q|},
            \text{ where } \overline{r}, \overline{q} \text{ is centroid}
            & \text{By def}
            \\
        & = \frac{1}{|R| \times |Q|}
            (
            \sum_{\substack{\vec{a} \in A \\
                            \vec{q} \in Q}}
                \|\vec{a} - \vec{q}\|
            +
            \sum_{\substack{\vec{b} \in B \\
                            \vec{q} \in Q}}
                \|\vec{b} - \vec{q}\|
            ) \\
        & = \frac{|A|}{|R|}
            \Big(
                \frac{1}{|Q| \times |A|}
                \sum_{\substack{\vec{a} \in A \\
                                \vec{q} \in Q}}
                \|\vec{a} - \vec{q}\|
            \Big)
            +
            \frac{|B|}{|R|}
            \Big(
                \frac{1}{|Q| \times |B|}
                \sum_{\substack{\vec{b} \in B \\
                                \vec{q} \in Q}}
                \|\vec{b} - \vec{q}\|
            \Big) \\
        & = \frac{|A|}{|R|}
            D_{average}(A, Q) + \frac{|B|}{|R|} D_{average}(B, Q)


Centroid Distance
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`D_{centroid}`

Fact 1: 1746, Steward proof that

.. math::

    \frac{n}{m + n} l^2 + \frac{m}{m + n} t^2 = s^2 + mn


Proof that :math:`\vec{T} = \vec{S} - \vec{N}`

.. image:: img/hier_triangle.png

.. math::

    \therefore
    t^2 & = \|\vec{S} - \vec{N}\| ^2 \\
        & = \| \vec{S} \|^2 + \| \vec{N} \|^2 -
            2 \| \vec{S} \| \| \vec{N} \| \\
        & = \| \vec{S} \| ^2 + \| \vec{N} \|^2 -
            2 \| \vec{S} \| \| \vec{N} \| \cos{\theta}
    \newline
    l^2 & = s^2 + m^2 - 2 s m \cos{(\pi - \theta)} \\
        & = s^2 + m^2 + 2 s m \cos{\theta}
    \newline
    \text{Also, } \because A \cup B & = R
    \newline
    \therefore
    \bar{r} & = \frac{|A|}{|R|} \bar{a} + \frac{|B|}{|R|} \bar{b}
            & \text{consider weighted average} \\
            & = \bar a + \frac{|B|}{|R|} (\bar b - \bar a)
    \newline
    \therefore (\bar r - \bar a) & = \frac{|B|}{|R|} (\bar b - \bar a)
        & (\bar{r} \in \overline{a b})
    \newline
            m       & = | \bar r - \bar a | \\
                    & = \frac{|B|}{|R|} (m + n) \\
    \frac{m}{m + n} & = \frac{|B|}{|R|} \\
    \frac{n}{m + n} & = \frac{1- m}{m + n} \\
                    & = \frac{|A|}{|R|}
    \newline
    \|S\|^2 & = \frac{n}{m + n} n^2 + \frac{m}{m + n} m ^ 2 - mn


Update Formula of Divisive
----------------------------------------------------------------------

一分為二的可能太多了

n 點 分 2 clusters 有
:math:`\frac{2^n  - 2}{2}` 種可能

遠大於 Agglomerative 的 merge

proof::

    x1 x2 x3 ... xn
    A  B  B ...  A

Consider we encode vector as a binary string.

且 :math:`2^n  - 2` (不能全為 A or B)

又 binary complement 視為 相同
e.g. AABAA v.s. BBABB 都是兩群

:math:`\therefore \frac{2^n - 2}{2}`


Divisive by Splinter Party
----------------------------------------------------------------------

政黨分裂法

一分為二:

Init, cal Distance Matrix

.. math::


    \begin{matrix}
      &  a & b & c & d  & e \\
    a &  0 & 2 & 6 & 10 & 9 \\
    b &  2 & 0 & 5 & 9  & 8 \\
    c &  6 & 5 & 0 & 4  & 5 \\
    d & 10 & 9 & 4 & 0  & 3 \\
    e &  9 & 8 & 5 & 3  & 0
    \end{matrix}

誰先脫黨？

- a 到其他人值平均距離  6.75

- b

- c

- d

- e

:math:`\therefore` a 最不滿

.. math::

    \{a\} \text{ vs } \{b, c, d, e \}

step 2, old cluster 問 「我恨舊黨 還是 新黨」

+---+--------------------+-----------------+----------------+
|   | distance to old    | distance to new | :math:`\delta` |
+===+====================+=================+================+
| b | (5, 9, 8) = 7.33   | 2               |  5.33          |
+---+--------------------+-----------------+----------------+
| c |                    | 6               |                |
+---+--------------------+-----------------+----------------+
| d |                    | 10              |                |
+---+--------------------+-----------------+----------------+
| e |                    | 9               |                |
+---+--------------------+-----------------+----------------+

.. math::

    \forall \delta > 0, \delta_{max} = b

    \therefore b \text{ leave}

.. math::

    \therefore

    \{a, b\} \text{ vs } \{c, d, e\}

step 3
    :math:`\{c, e, d\}` goto step2

.. math::

    \forall \delta < 0 \text{, then stop.}

    \text{reslut: }
    \{a, b\} \text{ vs } \{c, d, e\}


若要再分裂，應分裂何者？
有一種 rule 用 diameter

.. math::

    \begin{align}
    Dimt(\{a, b\}) & = max(\{2\}) & = 2 \\
    Dimt(\{c, d, e\}) & = max(\{4, 5, 3\}) & = 5  & -> \text{split } \{c, d, e\}
    \end{align}


若 群數未指定
則 可以用  diameter < args  => Stop
or  diameter change rate too high  => stop


Agglomerative 用 update formula

用 Distance Matrix

step1 {x1, x2} {x3 .. xn}

   x1 x2 x3 x4 x5
x1
x2


Divisive or Agglomerative 都從 Distance Matrix 開始: 已 :math:`\Omega{n^2}`


Experiment Suggestion
----------------------------------------------------------------------

Hierarchical Method will much slower, if n grows up.

- If # of clusters less, starts from Divisive
- If # of clusters large starts from Agglomerative
