Chapter 8: More about Number Theory
===============================================================================

Fermat's and Euler's Theorems
----------------------------------------------------------------------

Fermat's Theorem
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`p` 是質數
找另一不被 :math:`p` 整除只正整數 :math:`a`

則 :math:`a^{p-1} \mod p = 1` (餘數是 1

或 :math:`a^p \mod p = a \mod p`


Euler's Totient Function
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. math::

    \phi(n)

小於 n 的正整數中 跟 n 互質的數量

:math:`\phi(8) = 4`

:math:`\phi(37) = 36`

如果有兩相異質數 :math:`p, q`

.. math::

    \phi(pq) = \phi(p) \times \phi(q) = (p - 1)(q - 1)

所以

.. math::

    \phi(21) = \phi(3 \times 7) = \phi(3) \times \phi(7) = (3 - 1)(7 - 1) = 12


Euler's Theorem
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`a, n` 互質

.. math::

    a^{\phi(n)} \equiv 1 (\mod n)

意思就是

.. math::

    a^{\phi(n)} \mod n = 1


alternative form

.. math::

    a^{\phi(n) + 1} \equiv a (\mod n)


Testing for Primality
----------------------------------------------------------------------

Miller-Rabin Algorithm
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

property of prime

First property:
:math:`p` is a prime, :math:`n < p, n \in \mathbb{N}`

.. math::

    (a \mod p) \times (a \mod p) = (a^2 \mod p)


Given

.. math::

    a \mod p & = 1 & (\text{or})\\
    a \mod p & = -1

iff

.. math::

    a^2 \mod p = 1


Discrete Logarithm
----------------------------------------------------------------------

Primitive Root
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:math:`a, p` 互質

如果 :math:`a` 只有 :math:`a^{\phi(p) = p - 1} \equiv 1 (\mod p)`
其他的次方都不是 1。

意味著 :math:`a^1, a^2, \dots, a^{p - 1}` mod 的 output 都完全不同。

對非 primitive root 的 餘數是 就會呈現 規律狀。

那麼 :math:`a` 就是 :math:`p` 的 primitive root

不一定每個 integer 都有 primitive root


Logarithm for Modular Arithmetic
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

首先我們有 :math:`p` 的 primitive root :math:`a`

對任意整數 :math:`b`

.. math::

    b \equiv a^i (\mod p)

因為 :math:`a` 是 primitive root ，所以 :math:`a^i` 形成的集合就是
:math:`\{ 1, \dot, p - 1\}`
