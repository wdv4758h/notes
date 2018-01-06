Hash Functions
===============================================================================

Hash function :math:`H` 吃任意長度的 input data :math:`M` ，
然後輸出固定長度的 output。

.. math::

    h = H(M)

主要的目的是拿來做 data integrity 的檢查，checksum。


Cryptography Hash Functions
----------------------------------------------------------------------

這類的演算法，有這些特性：

- One-way property: 單向的效果，
  computational infeasible to find the data object, given a certain hash.
  給你一個 hash，找 hash 麻煩。

- Collision-free property: 對於兩個不同的 input data，找不到一個 pair 是算出
  相同的 hash value 的。

所以 hash functions 可以用在 data integrity，檢查資料有沒有被篡改。


Application of Cryptography Hash Functions
----------------------------------------------------------------------


Message Authentication
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Alice 要寄信給 Bob，在裡面的 data 加上了 Hash values
成為的 data'。
Bob 收到的時候只要把後面的 Hash values 拿起來看看，可以知道 data integrity，
有沒有傳壞掉。

但是這樣還是會遭到 man-in-the-middle-attack。

Darth 還是可以在中間加料後，append hash value 上去，讓 Bob 覺得東西好像沒
壞掉。

解法： Figure 11.3

#. 導入 data encryption 就好了。

#. 對 hash value 做簽章就好了。

#. 當資料很大時，我們就不會想要加密整個 data。
   在製作 hash value 的同時導入一個 shared 的 key 就好了。

#. double protection.


Message Authentication Code
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A.k.a `keyed hash function`

兩邊要 shared 一個 secret key 來做 authentication

Practices: SSL/TLS

.. math::

    E(K, H(M))


- MAC 沒辦法區分是兩者中誰送出的，因為是 shared secret key。

- Chap 12


Digital Signature
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. 假設 message 不 sensitive，就在 M 後面加上 digital signature
   就好了。證明是 Alice sign 的即可。


#. 如果 message 很重要，先 sign 一下 ，也可以整個兩個做對稱式加密。


Other Hash Functions Uses
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- Password saved in DataBases.
  (One-way password file)

- intrusion detection

- virus detection

- 實作 pseudorandom function (PRF) or a pseudorandom number generator (PRNG)


Two Simple Hash Functions
----------------------------------------------------------------------

input 長度不定，所以用 iteration。

這裡介紹簡單的，雖然 insecure。

#. 切 n 個 block，每個 block 直接 bit-by-bit XOR。

#. 每個 block + circular shift。
   第一個 block shift 1，第二個 shift 2 之類的。

上面這兩個 Hash functions 的弱點是，我們只要特製一下最後一個 block，
就能夠作出 collision。
因為這兩個 hash functions 就只是重複的做 XOR。


Requirements and Security
----------------------------------------------------------------------

Preimage

    :math:`x` is the preimage of :math:`h` for a hash values


Collision

    If :math:`x \neq y`, but :math:`H(x) = H(y)`

Requirements (table 11.1)

    - 不定長度 input

    - 固定長度 output

    - Efficiency: forward pass 簡單。

    - preimage resistant: one-way.

    - Second preimage resistant: weak collision resistant.
      Given :math:`x` 找不到 collision (computational infeasible)

    - Strong collision resistant: :math:`\forall (x, y)` pair, no collision.
      (computational infeasible)

    - Pseudorandomness: hash value 通過 pseudorandomness 的測試。


Attacks

    #. Brute-Force

    #. Cryptanalysis: attack the algorithm property.


Brute-Force Attacks
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

m-bit hash value,

給你 hash value :math:`h` ，然後找 preimage (input)
random 產出 input，每個 input 都有 hash value，有 :math:`2^m` 種可能。

期望值上至少也要 :math:`2^{m-1}` （一半）


那麼 second preimage?
給定 :math:`x` ，然後有 :math:`h` ，找到個 :math:`y, s.t. H(y) = H(x)`
:math:`2^m`

Collision Resistant: :math:`2^{m/2}` ?

MD4/MD5 -> 128 bit


Cryptanalysis
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

-


Hash Functions Based on Cipher Block Chaining
----------------------------------------------------------------------


11.8
MD4/MD5/SHA-family 的結構都長這樣。


SHA
----------------------------------------------------------------------

SHA-512
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Message 切 block ，不夠就 padding

用 chain 中最後一個的 result


SHA-3
----------------------------------------------------------------------

Sponge function



Sponge construction
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

message + padding 後切 blocks

- sponge function

    - :math:`f` internal function for handle input block

    - :math:`r` input block 的大小，單位是 bit

    - :math:`pad` padding algorithm

sponge function 的 input/output 都是 variable，所以可以作為

    - hash function: fixed-length output

    - pseudo-random number generator: fixed length input

input 大小為 :math:`n` 的 message，會被切成 k 個固定大小的 block，
:math:`r` bits for each block。
有需要的話，會加上 padding。


Iteration Function :math:`f`
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


.. math::

    R = i \circ \chi \circ \pi \circ \rho \circ \theta

Table 11.6


:math:`\theta` step

    Substitution


:math:`\rho` step

...
