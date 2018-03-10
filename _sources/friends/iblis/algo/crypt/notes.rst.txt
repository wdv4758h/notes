
Chap2 Number Theory
----------------------------------------------------------------------

9/20

Symmetric cypher: e.g. AES

Divisibility

    :math:`b | a`: b 整除 a

Division Algorithm

    :math:`a = qn + r`

GCD

Euclidean Algorithm

Mod: ``%``

Congruences

Extended Euclidean Algorithm

Euler's Totient Function :math:`\phi(n)`

    小於 n 的正整數中 跟 n 互質的數量

    e.g. :math:`\phi(8) = 4`

Fermat's Theorem

Miller-Rabin Algorithm

Chinese Remainder Theorem

Discrete Log

9/27

confusion and diffusion
https://zh.wikipedia.org/wiki/%E6%B7%B7%E6%B7%86%E8%88%87%E6%93%B4%E6%95%A3

Feistel Cipher Design Features

:math:`F` 越 non-linear 越好


DES (Data Encryption Standard)
https://en.wikipedia.org/wiki/Data_Encryption_Standard

Triple DES
https://en.wikipedia.org/wiki/Triple_DES

Chap5
----------------------------------------------------------------------

9/27

Groups, Rings, Fields


Chap10
----------------------------------------------------------------------

11/1

D H key exchange


Bob 跟 Alice
    #. share q 個 :math:`\alpha`

    #. 各自 generate 一個 private key

有 Man in the middle 問題
中間人就各自跟 Bob, Alice 做 key exchange
再把東西往兩邊複製。


ElGamal

Elliptic Curves
