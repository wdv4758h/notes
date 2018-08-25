Key Managment and Distribution
===============================================================================

Symmetric key 要 share 而且用一段時間後要換。
所以安全性跟 `key distribution technique` 息息相關。

目前安全性的依賴 key 的保存。
How to keeping private key secure?


Key Distribution
----------------------------------------------------------------------

Symmetric key
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

對稱式加密需要 shared key，那麼這個 key 怎麼傳過去給對方？
大家都看得到你的封包。

假設有 A B 兩方，你可以

#. 實體上交給對方

#. 找個第三方同時在實體上交給 A B

#. 假設 A B 直接有已經用過的 old key，那麼 A 可以產生一個 new key 然後
    用 old key 加密後給 B。然後下次 A B 都用 new key。

#. A B 都用加密連線連到 third party C， C 就用這個加密連線同時傳給 A B。

Option 1, 2 is manual delivery, but no scalable. 在這種 end-to-end 的 case
就不 scalable。

Option 3 在 attacker 拿到其中一次的 key 之後，後面就通通爆炸。

"Communication between end systems is encrypted using a temporary key,
often referred to as a `session key`"

`session key` 從 key distribution center 來的。

Key Hierarchy
    figure 14.2: 2 level of keys

    `master key` and `session key` layer.

    Third party (key center) 跟每個人都 keep `master key`
    拿來傳 session key。 option 4

    如果有 N 跟 host，那麼 key center 只有 physically deliver
    N 跟 key 即可，算是可行的。

    Session key 拿來加密 data，這個 key 是拋棄式的。
    暫時的 key。

    14.3


Key Distribution Scenario
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Key Distribution Center (KDC)

如果 A 要連 B，需要一次性的 session key。
A, B 對 KDC 都有 master key :math:`K_A, K_B` 。

#. A 跟 KDC 要了一個 session key。這個 request 會有 transaction id，用
   nonce 表示。nonce 可以是 timestamp, counter, random number ...etc。

#. KDC 就用一個加密連線送資料給 A，裡面包含：

    - one-time session key :math:`K_s`

    - original message, 像是裡面的 nonce，做確認用。

    - 一包可以直接送給 B 的資料包，KDC 直接用 :math:`K_B` 加密好了：

        - 裡面有 session key :math:`K_s`

        - A 的相關資訊，一些有的沒的。

#. 接下來就做點 Ack 就好了，B 就用這個 session key 隨便送個值給 A

#. A 就做點事情丟回去. E.g. 對這個值 + 1。確定 session key 的使用上沒問題
   就可以開始傳資料。


Hierarchical Key Control
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

對超大的網路，單一的 KDC 會不夠，KDCs 可以有 hierarchy。


Session Key Lifetime
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Key exchange 越頻繁，安全性就越好，
讓 attacker 只能拿到比較少的 ciphertext 來攻擊。

但是另一面是 session key 產生，exchange 會有 overhead。
就要 trade-off。

Connection-oriented protocol
    session key per connection，
    single connection 但如果時間很長，還是要定期換。
    (figure 14.4)

Connectionless (I guess is streaming) protocol:
    沒明確開始/結束時間的 protocol。

    Security depend on key exchange frequency.


Transparent Key Control Scheme
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

把 security 的 function 塞在某個 layer，讓 user application 覺得 transparent。
這個 layer/service 就自己跑去跟 KDC 處理完 session key distribution。


Decentralized Key Control
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

原本的方法，基本上要有被信任的 KDC，但如果 key distribution 是 fully
decentralized 就不需要這個要求。
就 end-to-end 之間都要有 master key。


Control Key Usage
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

在這裡去區分 session key 的用途：

- Data-encryption key: general communication

- PIN-encryption key: personal identification number (PIN)

- File-encryption key

對於 control usage，KDC 用 hash 跟加密去 couple control vector。
來傳遞 control vector 避免被改掉。

.. math::

    E((K_{master} \oplus H(CV)), K_{session})

Where :math:`CV` is the control vector.


Symmetric Key Distribution Using Asymmetric Encryption
----------------------------------------------------------------------

Public key encryption 慢，很少直接拿來傳資料；或是只用在小的資料。
所以 public key encryption 的用途變成是拿來傳遞 shared secret key。

Simple Secret Key Distribution

    #. A 給 B，A 的 public key

    #. B 選好 session key 用 A 的 public key 加密送給 A。

    #. A 拿到 session key

    #. 雙方丟掉所有的 public-private key

    會遇到 man-in-the-middle attack，
    在 A 丟出 public key 的時候就被 middle 攔截然後換掉。

Secret Key Distribution with Confidentiality

    A, B 之間要先交換好 public key，用 Option 1 - 4。e.g. 實體交換。

Hybrid Scheme

    用 public key method 去跟 KDC 交換 master key?


Distribution of Public Key
----------------------------------------------------------------------

- Public announcement

- Publicly available dir
  找可信任的第三方 maintain 這個資料。

- Public-key authority

- Public-key certificates

Pub/private key pair

    * Who is the owner of private key?

    *


X.509
----------------------------------------------------------------------



Public Key Infrastructure
----------------------------------------------------------------------

PKI
