Key Managment and Distribution
===============================================================================

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

Option 1, 2 is manual delivery, but no scalable.

"Communication between end systems is encrypted using a temporary key,
often referred to as a `session key`"

Key Hierarchy
    figure 14.2: 2 level of keys

    `master key` and `session key` layer.

    Third party (key center) 跟每個人都 keep `master key`
    拿來傳 session key。 option 4

    session key 拿來加密 data，這個 key 是拋棄式的。

    14.3

Session key lifetime

    暫時的 key。

    Connection-oriented protocol: session key per connection
    (figure 14.4)

    Connectionless (I guess is streaming) protocol: security depend on
    key exchange frequency.


Hybrid Scheme

    ...


Pub/private key pair

    * How is the owner of private key?

    *

Remote user-auth principles

    * reply attack
        * 解法？ sender 跟 receiver 之間要有 seq number （流水號）


Kerberos

    AS

    Ticket

    TGS ticket-granting server
