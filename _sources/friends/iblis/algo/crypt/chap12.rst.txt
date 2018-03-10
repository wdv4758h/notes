Message Authentication Code
===============================================================================

Message Authentication Functions
----------------------------------------------------------------------

- Lower level function: 本章

- Higher level function


Lower level function: authenticator

    - Hash function

    - Message encryption

    - Message Authentication Code (MAC)

Message encryption
    用對稱式加密不好做，如果 ciphertext 被中間改過，那麼你怎麼自動判斷
    現在解出來的 plaintext 是對的？e.g. 還是要用人去看，語義到底是不是英文。


FCS: Frame check sequence, aka checksum
    為了做 error-detection，要做在 encryption 之前。讓我們可以直接判斷
    到底有沒有被改過。

兩種做法, figer 12.2：

    - internal error control，message concate checksum 之後整個加密。
      這樣整個加密，只要 ciphertext 被改， M 跟 checksum 都會被改到，
      然後就會對不起來。

      .. math::

          E(K, (M || F(M)))

    - external error control, 先加密 M，然後 FCS append 在 ciphertext 後面。

      .. math::

          E(K, M) || F(E(K, M))


Public-Key encryption
    慢，作為最後手段。但不需要 FCS。

    因為 A 拿 B 的 public key 得到 ciphertext 後送給 B。
    B 可以解就沒問題，但不保證 A 的身份，大家都有 B 的 public key。

    如果換成 A 用 A 的 private 加密後寄出去，那麼網路上所有人都可以解密。

    要有 authentication + confidentiality，
    在 A 用 A 的 private key 做 signature ，然後用 B 的 public key 加密
    message + signature 後寄出即可。


Message Authentication Code

    用 secret key 生出一個 fixed-size block，即為 `cryptographic checksum` or
    MAC，然後 append 到 M。

    A, B shared secret key :math:`K` ，A 送資料給 B。

    .. math::

        MAC \leftarrow C(K, M)

    where C is the MAC function.

    然後 append MAC 到 M。
    這樣對 M 是沒 confidentiality。

    MAC function 的選擇上，不需要可逆，可以是 one-way。

    confidentiality 有兩種方法

        - :math:`E(K_2, C(K_1, M))`

        - :math:`E(K_2, M) || C(K_1, M)`


Requirement of MAC
----------------------------------------------------------------------

假設我們現在是 k bits key，:math:`2^k` 個 possible keys，
MAC function 的 output 是 :math:`n` 所以有 :math:`2^n` 種 code。

且

.. math::

    2^n < 2^k


有很多 key 會得出一樣的 MAC。
所以 attacker 還要確定一下哪個 key 是對的。
要拿下一組 MAC 跟 M 的 pair 來縮小範圍。


Brute-Force Attack
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- 需要已知的 M, MAC pair。

- key space

- MAC 的長度加長


HMAC: MAC based on Hash functions
----------------------------------------------------------------------

A MAC example based on symmetric block cypher.

近年來 MAC based on cryptographic hash function 開始發展，
因為 (e.g. MD5, SHA) 的效率比 DES 好。


Y 從 msg 切 block

Hash((pad(K) XOR opad),
     Hash(IV, (pad(K) XOR ipad) concate Y))


還有 precomute 版本？為了效率


Security

    取決於 hash function 的強度。


MAC based on Block Cipher: DAA and CMAC
----------------------------------------------------------------------

Data Authentication Algothrim (DAA)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Out-of-date

Based on CBC mode 的 DES。

對資料 M 切 blocks :math:`D_1, \dots D_N`

.. math::

    O_1 & \leftarrow E(K, D_1) \\
    O_i & \leftarrow E(K, (D_i \oplus O_{i-1}))


Ciper-Based Message Authentication Code (CMAC)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

DAA 的加強版

.. math::

    C_1 & \leftarrow E(K, M_1) \\
    C_i & \leftarrow E(K, (M_i \oplus C_{i-1}))


Counter with Ciper Block Chaining Message Authentication Code(CCM)
----------------------------------------------------------------------

HtE
    Hash-then-encrypt :math:`E(K, M || h)`

MtE
    MAC-then-encrypt. 兩個 keys 一個 MAC 的，一個 encryption algo 的。
    :math:`E(K_2, (M || MAC(K_1, M)))`

    SSL/TLS 在用

EtM
    Encrypt-then-MAC. Two keys.
    Pair :math:`(E(K_2, M), MAC(K_1, E(K_2, M)))`

    IPsec

E&M
    Encrypt-and-MAC. Two keys.
    Pair :math:`(E(K_2, M), MAC(K_1, M))`

    SSH


Counter with Cipher Block Chaining-Message Authentication Code (CCM)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

用 AES, CTR operation mode, CMAC

Single key for both encryption and MAC

Authentication

    Input: Nonce + Associate Data (e.g. protocol header) + Message (plaintext)

    對整個 input 切 blocks。然後丟到 CMAC (with key K)。

Encryption

    ?

CGM



Key Wra 12.8
