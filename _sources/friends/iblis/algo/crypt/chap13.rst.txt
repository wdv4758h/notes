Digital Signature
===============================================================================

Bob 的 message 會先過 hash function 然後 用 private key sign 這個 hash value，
然後 append 在 message 後面


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


SlGamal Digital Signature
----------------------------------------------------------------------

require: q, a (primitive root of q)


#. Each user generate their own key

   #. each private key: 1< x_A < q - 1

   #. public key y_A = a^{x_A} mod q

#. Choose k, k 跟 q-1 互質, then compute

   #. S_1 = a^k mode q

   #. S_2 = k^{-1}(m - x_A S_1)


#. Signature pair (S_1, S_2)


Schnorr Digital Signature
----------------------------------------------------------------------

...

(ref to text book)



NIST standard
----------------------------------------------------------------------

#. DSA -- based on RSA,
   有 random number k, 對每個 signature。
   每次對同一個 message 用不同的 k。

#. 用 ECC


ECDSA
----------------------------------------------------------------------



RSA-PSS
----------------------------------------------------------------------

#. as secure as RSA, 可被證明的。


Mask Generation Function (MGF)

    基本上是個 hash function。

    但這個 function output 可以被設計，重新定義，根據需求。

    `salt`
