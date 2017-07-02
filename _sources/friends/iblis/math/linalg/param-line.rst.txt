Parametric Representations of Lines
===============================================================================

ref:
    https://www.khanacademy.org/math/linear-algebra/vectors-and-spaces/vectors/v/linear-algebra-parametric-representations-of-lines


假設所有 vector 的起點皆為原點。
我們可以以 vector 的機會表示某條通過原點的直線。

.. math::

    \text{Let } \vec{v} =
    \begin{bmatrix}
        2 \\
        1
    \end{bmatrix}

    \text{We define the line } L = \{ c \vec{t} | c \in \mathbb{R} \}

這個 :math:`L` 必通過原點。

而 *平移* 即可得到 :math:`\mathbb{R}^2` 上的任意直線

.. math::

    \text{Let } \vec{x} \ \text{is a vector on } \mathbb{R}^2

    L = \{ \vec{x} + c\vec{t} | c \in \mathbb{R} \}


Parametric Representations
----------------------------------------------------------------------

給定空間中任意兩點 :math:`\vec{a},\ \vec{b}`

通過這兩點所成的直線為

.. math::

    \begin{align}
        L & = \{ \vec{a} + c(\vec{a} - \vec{b}) | c \in \mathbb{R} \} \\
        & \text{or} \\
        L & = \{ \vec{b} + c(\vec{a} - \vec{b}) | c \in \mathbb{R} \}
    \end{align}
