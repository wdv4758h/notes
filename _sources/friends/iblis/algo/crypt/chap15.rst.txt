User Authentication
===============================================================================



Remote user-auth principles

    * reply attack
        * 解法？ sender 跟 receiver 之間要有 seq number （流水號），
          但這個 overhead 是要一直追蹤東西有沒有到。
          ，事務上沒在用。

        * 加 Timestamp，但是大家都要做 clock sync。

        * Chanllenge/respone: 假設 A 是接受，一開始 B 先送一個 nonce
          (chanllenge)，然後下一個從 A 來的 message 都要有這個 nonce 的 respone (?)
          e.g. password authentication
Kerberos

    AS

    Ticket

    TGS ticket-granting server
