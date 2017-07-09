===============================================================================
DNSSEC
===============================================================================
在 DNS 出現的時候，民風還很純樸，沒有人想得到現在網路上會有那麼多壞人（？

總之，DNSSEC 出現了，企圖要讓 DNS 變得安全，無論對 server 還是對 client。

在繼續讀這篇以前，請先了解 DNS 的概念。


Resource Record (RR)
-------------------------------------------------------------------------------
向下相容是很重要的，DNSSEC 基本上是在現有的 DNS 加上認證的機制。

所以原本 DNS 的 SOA / A / AAAA / NS / MX / ...，在 DNSSEC 也都有。

此外，DNSSEC 再加上了一些 RR：

* RRSIG (RR signature)

  - 就是把 RR 拿去做數位簽章（digital signature）

* DNSKEY

  - Server 的 public key

* DS (delegation signer)

  - Server 把自己的 public key 做 digital signature 以後，放到 parent zone 裡面做為 DS record。

* NSEC (next secure record)

  - 下一個存在的 record，用來證明「你查的這東西真的不存在」

* NSEC3 (next secure record version 3)

  - 下一個存在的 record 的 hash

* NSEC3PARAM (next secure record version 3 parameters)

  - （不知道）


範例
-------------------------------------------------------------------------------
Bob 是一台 DNSSEC server，負責的 domain 是 bob.example.com

Alice 想要向 DNSSEC server Bob 查詢 banana.bob.example.com（假設它真的存在）

1.  Alice 向 Bob 查詢 banana.bob.example.com 的 A record
2.  Bob 回應 banana.bob.example.com 的 A record

RRSIG 可以證明這個 A record 真的是 Bob 發出來的。

如果 Alice 想要確認 Bob 是一台有認證過的 DNSSEC server，可以透過以下方式證明：

* 向 example.com 查詢 bob.idv.tw 的 DS record
* 向 bob.example.com 查詢 DNSKEY record

--------

Alice 想要向 Bob 查詢一個存在的 domain name，例如 hahaha.bob.example.com

1.  Alice 向 Bob 查詢 hahaha.bob.example.com 的 A record
2.  Bob 沒有這個 record，所以回應一個 NSEC3 record

Alice 可以把 hahaah.bob.example.com 做一次 hash，再和拿到的 NSEC3 做比對。

如果不一樣的話，表示 Bob 說「我這裡真的沒有這個 record。」

NSEC3 record 也有對應的 RRSIG record，所以 Alice 不用擔心這個 response 是假的。
