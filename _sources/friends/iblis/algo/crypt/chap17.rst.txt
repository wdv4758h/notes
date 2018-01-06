Transport-Level Security
===============================================================================

網路這麼多層，就選一層做 security module，embedding 進去就好了。


Transport Layer Security

    SSL/TLS
    SSL 是一開始的 spec，TLS 是後繼者(?)

    對 application layer 來說是 transparent 的。

    Rely on TCP。

    e.g. HTTPs: combine SSL/TLS and HTTP into one package

TLS Architecture

    * TLS connection

    * TLS session: created by handshake protocol


    Session state
        - identifier

        - cipher spec

        - master secret

        - etc...


Handshake


