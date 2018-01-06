Chapter 2: Symmetric Cipher
===============================================================================

A.k.a

    - conventional encryption

    - single key encryption


我們有 `plaintext` ，把這個 plaintext 轉成 `ciphertext` 的過程稱為
`encryption` 。
反向的操作是 `decryption` 。

cryptanalysis
    對於不知道 encryption 過程/細節，但是我們想要進行 decryption。
    Area of "breaking the code".

cryptology
    cryptography + cryptanalysis


Symmetric Cipher Model
----------------------------------------------------------------------

#. Plaintext

#. Encryption Algorithm

#. Secret key: 作為 encryption algorithm 的其中一個 input 參數

#. Ciphertext: algo 的 output

#. Decryption Algorithm

額外的兩個條件：

#. Encryption algorithm 的強度要做到，
   即使中間人拿到了一個或多個 ciphertext，
   還是無法在有限時間做 decryption（拿到 secret key）。
   更好的狀況是，中間人即使拿到了成對的 plaintext 跟 ciphertext，
   還是找不出 secret key。

#. Sender 跟 receiver 之間 share 的 secret key，不能被拿到。

我們這些假設，讓我們只需要保護 secret key，而不需要保護 algorithm，
algorithm 可以公開。


Cryptography
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. Operations：基本上是 substitution，是因為需要 reversible，
   轉換後資料不能有損。
   一連串的 substitution 就是 product systems。

#. Key 的數量：
   一個 shared key，是 symmetric。
   sender / receiver 兩個不同的 key 是 asymmetric。

#. Plaintext 的處理方式：

    - `block cipher`

    - `stream cipher`


Cryptanalysis attack
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- Ciphertext only

- Known plaintext
    - 有 plaintext-ciphertext pair(s)

- Chosen plaintext

- Chosen ciphertext

- Chose Text


強度

    - unconditional secure

        - 理想

    - computational secure
        - cost 超越解出 plaintext 的價值

        - computation 時間

            - DES: 56 bits

            - triple DES: 168 bits

            - AES: 128 bits


Substitution Techniques
----------------------------------------------------------------------

Substitution and transposition


Caesar Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

凱撒

.. math::

    E(k, p) = (p + k) \mod 26

    D(k, c) = (p - c) \mod 26

Key space 只有 25


Monoalphabetic Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

對前面 Caesar Cipher 做 permutation，所以 key space 會有 26!

而 cryptanalysis 的做法會是用額外的知識規則，
e.g. ciphertext 是英文，那麼就建立 frequency table，
對 ciphertext 做統計後去猜，但比較統計需要資料量夠。


Playfair Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Multiletter cipher

兩個字母一組。


Hill Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Multiletter cipher

.. math::

    \vec{c} = \vec{p} K mod 26
    \vec{p} = \vec{c} K^{-1} mod 26


Vigenere Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Let :math:`k_i` 是 key 為 :math:`j` (shift j) 的 Caesar Cipher。

.. math::

    c_i = (p_i + k_{i mod m}) mod 26
    p_i = (c_i - k_{i mod m}) mod 26

實作上 key 就 repeat 到跟 plaintext 一樣長即可

E.g.::

    key = hellohellohe
    msg = magic number
    c   = ...

    julia> caesar(k, p) = Char((Int(p) - Int('a') + Int(k) - Int('a')) % 26 + Int('a'))
    caesar (generic function with 1 method)

    julia> map(x->caesar(x...), zip(key, msg))
    12-element Array{Char,1}:
     't'
     'e'
     'r'
     't'
     'q'
     '['
     'r'
     'f'
     'x'
     'p'
     'l'
     'v'


Vernam Cipher
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

對 binary data，然後 cryptanalysis 沒 frequency table 可以用。

.. math::

    c_i = p_i ⊻ k_i
    p_i = c_i ⊻ k_i

(xor)


One-Time Pad
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Improve Vernam Cipher.

用 Random key，長度跟 plaintext 同，不做 repeat。

每個 key 對一個 message 只用一次就丟掉。
這樣 cryptanalysis 上，沒統計的關係，不可解。

*perfect secrecy*


Transposition Techniques
----------------------------------------------------------------------

透過些 permutation


Rail Fence
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

msg: meet me after the party

::

    m e m a t r h p r y
     e t e f e t e a t

這種簡單的 transposition cipher 的 frequency 就是 plaintext frequency。
Digram/Trigram table 可解。


Rotor Machine
----------------------------------------------------------------------
