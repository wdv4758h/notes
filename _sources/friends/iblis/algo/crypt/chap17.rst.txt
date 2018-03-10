Transport-Level Security
===============================================================================

網路這麼多層，就選一層做 security module，embedding 進去就好了。


Secure Scoket Layer
----------------------------------------------------------------------

SSL/TLS
SSL 是一開始的 spec，TLS 是後繼者(?)

對 application layer 來說是 transparent 的。

Rely on TCP。

e.g. HTTPs: combine SSL/TLS and HTTP into one package

實際上是兩層的設計

    - SSL Record Protocol

    - 在上層還有三個 protocol 被設計為 SSL 的一部分

        - SSL Handshake Protocol

        - SSL Change Cipher Spec Protocol

        - SSL Alert Protocol

    - HTTP 是與上面這三個同一層的東西。


    - Two concept

        - SSL session: created by Handshake Protocol.
          session 裡面會記錄加密的相關參數。很多 connection 可以 share
          同一組參數，因為交換參數很慢或耗費資源。

        - SSL connection: 每個 connection 會有一個跟它有關聯的 session。

    - state 參數很多

        - session state parameters: e.g. Cipher spec (MD5, SHA-1), session id,
          Master secret key.

        - connection state parameters: e.g. CBC initial vector ...


SSL Record Protocol
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Handshake Protocol
    會去交換兩個 key，第一個是 general 的 encryption shared secret key。

    第二個用在 MAC 的 secret key。

Data Processing

    #. Fragment: 切 block

    #. Compress

    #. Append MAC

    #. Encryption

    #. Prepend SSL Header


.. math::

    MAC = hash(K || pad_2 || hash(K || pad_1 || seq || SSL.type || SSL.len || SSL.fragment))

SSL.fragment 就是上面 compress 完的內容。


Change Cipher Spec
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

single byte value, 給 update pending state 用的.


Alert Protocol
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

two byte。

第一個 byte 是 level，fatal or warning。fatal 會讓整個 SSL connection
直接結束，其他還在同一個 session 上的 connection 就繼續，但是這個 session
不會再接受新的 connection。

第二個 byte 關於這個 level alert 的詳細 code。
e.g. unexpected_message, bad_record_mac, decompression_failure.... etc.


Handshake Protocol
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

3 fields

    - type (1 byte): e.g. hello_request, sever_hello, client_hello ... etc

    - length (3 byte)

    - content (>= 0 byte)


Transport Layer Security
----------------------------------------------------------------------


* TLS connection

* TLS session: created by handshake protocol

MAC
    TLS 用 HMAC

Handshake

    裡面有 pre-master secret，拿來算出 master secret


HTTPS
----------------------------------------------------------------------


SSH
----------------------------------------------------------------------


