Digital Signature
===============================================================================

Bob 的 message 會先過 hash function 然後 用 private key sign 這個 hash value，
然後 append 在 message 後面。


Property
----------------------------------------------------------------------

#. 要能夠一起驗證 date and time

#. 其他人也要能驗證你簽出來的東西

#. 不可否認性質


Attacks
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

A is the signer
C is somebody on internet, the attacker.

#. Key-only attack: C 有 A 的 public key。C 的資訊量沒比較多，沒啥攻擊的好方法。

#. Known message attack: C 有 message + signature pairs。也是沒比較多。

#. Generic chosen message attack: C 選了一系列的 messages，然後拿到 這些特定的
   signatures

#. Directed chosen message attack: C 看著 A 的 public，然後才開始選
   系列 message。

#. Adaptive chosen message attack: C 想要 有 message-signature pair
   就隨時可以拿到


Forgery
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. Total break: C 拿到了 private key

#. Universal forgery: C 找到了不同的演算法，可以產出一樣的 signature，
   對任意的 input。

#. Selective forgery: only chosen text 有 signature。

#. Existential forgery: 就只是找到，但 message 內容可能是無意義的。


Digital Signature Requirements
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. signature 要 depends on message

#. signature 要用到 auther 的 unique information，來確認本人。

#. 承上，用到 sender 也可

#. easy to produce signature

#. easy to verify signature for receiver

#. computational infeasible to forge signature


Direct Digital Signature
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

指只有通訊的這些人，才會去 access signature。

然後如果需要機密性，就做 加密 整個 message + signature。

Security 的強度依賴於 sender 的 private key。
sender 說 private key 掉了，就嗨了了。


ElGamal Digital Signature
----------------------------------------------------------------------

Require: q, a (primitive root of q)


#. Each user generate their own key

   #. each private key: 1< x_A < q - 1

   #. public key y_A = a^{x_A} mod q

#. :math:`m = H(M)` 是 hash value

#. Choose k, k 跟 q-1 互質, then compute

   #. S_1 = a^k mode q

   #. S_2 = k^{-1}(m - x_A S_1)


#. Signature pair (S_1, S_2)

#. Verify

   #. :math:`V_1 \leftarrow \alpha^m mod q`

   #. :math:`V_2 \leftarrow (Y_A)^{S_1}(S_1)^{S_2}`

   #. Check :math:`V_1 = V_2`


Schnorr Digital Signature
----------------------------------------------------------------------

Based on discrete log.

希望 signature 的 generation 過程不 depend on message。
讓 CPU 可以先完成點事情。


(ref to text book)


NIST standard
----------------------------------------------------------------------

#. Digital Signature Standard (DSS)

#. 用 ECC

Digital Signagure Standard (DSS)
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

長得很像 RSA 的流程。

產生 sig 的 input:
    #. Hash value

    #. Private key

    #. Global public key (?)

    #. 一個 random number :math:`k`: 對每個 signature。
       每次對同一個 message 用不同的 k。

sig 的 out:

    #. :math:`s` part

    #. :math:`r` part

Verify input:

    #. :math:`s`

    #. :math:`r`

    #. Global public key

    #. User public key

Verify 的 output 跟 :math:`r` 比對即可。

其中 global public key 是個 tuple :math:`(p, q, g)`,
user private key 為 :math:`x`

Signing:

.. math::

    r & \leftarrow (g^k mod p) mod q \\
    s & \leftarrow (k^{-1} H(M) + xr) mod q

Where :math:`k` is a random number


Elliptic Curve Digital Signature Algorithm (ECDSA)
----------------------------------------------------------------------

Global Domain Parameters
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- :math:`q` a prime number

- :math:`a, b` coefficient in elliptic curve equation

- :math:`G = (x_g, y_g)` a base point on elliptic curve

- :math:`n` order of point :math:`G`
  即最小的整數，使得 :math:`nG = O`


Key Generation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#. Gen random integer :math:`d`, where :math:`1 < d < n`

#. :math:`Q = dG`

#. 得 public key :math:`Q`, private key :math:`d`


Signature Generation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

For message :math:`m`

#. Gen random number :math:`k`, where :math:`1 < k < n`

#. :math:`P = (x, y) = kG`, :math:`r = x mod n`
   如果 :math:`r = 0` 那麼重選 :math:`k`

#. :math:`t = k^-1 mod n`

#. :math:`e = H(m)`, where :math:`H` 是 SHA-1 function。

#. :math:`s = k^{-1}(e + dr) mod n`
   如果 :math:`s = O` 就重來。

Signature 即為 :math:`(r, s)`


RSA-PSS Digital Signature
----------------------------------------------------------------------

#. as secure as RSA, 可被證明的。


Mask Generation Function (MGF)

    基本上是個 hash function。

    但這個 function output 可以被設計，重新定義，根據需求。

    `salt`
