Chapter 4: Number Theory
===============================================================================

Groups
----------------------------------------------------------------------

.. math::

    \{G, \cdot \}

一個 set 加上一個 binary operation 是一個 Group


Rings
----------------------------------------------------------------------

.. math::

    \{R, +, \times \}

一個 set 加上一個 addition operator，一個 multiplication operation


Fields
----------------------------------------------------------------------

.. math::

    \{F, +, \times \}

一個 set 加上一個 addition operator，一個 multiplication operation
滿足最多的 axioms。

.. note::

    integer 這個 set 不是 field，因為不滿足 multiplication inverse。

    3 跟 :math:`\frac{1}{3}`，但 :math:`\frac{1}{3}` 不在 integer 這個 set 裡面


E.g.

    - 實數

    - 有理數


Finite Fields
----------------------------------------------------------------------

在 cryptography，我們有興趣的是 finite field。
而這個 finite field 的 order（即 ``length(F)`` ）
一定是 :math:`p^n`, where :math:`p` is a prime, :math:`n \in \mathbb{N}`.

稱為 Galois Field

.. math::

    GF(p^n)


The set with modulo arithmetic operations denote as :math:`GF(p) = Z_n`
這個 n 一定要是 prime 才會構成裡面的每個 element 都有 multiplication inverse，
因為要裡面的 element 要跟 n 互質。所以寫作

.. math::

    Z_p

當 :math:`a, bb` 互質時，
求 multiplication inverse 時，用 extended Euclidean algorithm

.. math::

    ax + by & = 1 = gcd(a, b) \\
    [(ax \mod a) + (by \mod a)] \mod a & = 1 \mod a \\
    [0 + (by \mod a)] \mod a & = 1 \\
    by \mod a & = 1

:math:`\therefore y = b^{-1}` is multiplication inverse of :math:`b`.


Polynomial Arithmetic
----------------------------------------------------------------------


Ordinary Polynomial Arithmetic
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- 有加減乘。

- 除要是 Field。
  所以 :math:`\mathbb{N}` 沒有除法。


Finite Fields of :math:`GF(2^n)`
----------------------------------------------------------------------

假設我們要處理 8 bits data，8 bits 的範圍是 0~255
但是 :math:`GF(2^8)` 的 order 不是質數，最近的質數是 251
因此如果我們是以 8 bits 為單位的處理資料，有用到除法的話必須是 Field，
我們 251~255 這段是不能用的，造成浪費。


.. math::

    f(x) mod m(x) = m(x) - f(x)


Generator
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

用 generator 可以簡化乘法

次方用 (mod order-1)

:math:`G(2^n)` with irreducible polynomial :math:`f(x)`

然後 Let :math:`f(x) = 0` 就可以得到 generator :math:`g`
