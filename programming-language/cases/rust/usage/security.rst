========================================
Security
========================================


.. contents:: 目錄


概覽
========================================

::

    +-------------+------------------------------+
    | rustls      | quinn                        |
    |    +-------------+     +---------+---------+
    |    | webpki      |     |         | tokio   |
    +----+-------------+-----+         +---------+
    |         ring           | futures           |
    +------------------------+-------------------+



Cryptographic
========================================

ring - Cryptographic Operations
-------------------------------

:Repo: https://github.com/briansmith/ring


ring 是密碼學相關操作的 library，
由 Rust、C、assembly 寫成，
大部分的 C、assembly 是從 BoringSSL 來的，
而 BoringSSL 則是從 OpenSSL 來的，
ring 有定期從 BoringSSL 上游拉回更動。


Dalek - Fast, safe, pure-rust elliptic curve cryptography
---------------------------------------------------------

:Site: https://dalek.rs/
:Repo: https://github.com/dalek-cryptography/


* Curve25519
* Ed25519
* x25519 Elliptic Curve Diffie-Hellman key exchange
* Ristretto
* Bulletproofs


Sodium Oxide (binding of libsodium)
-----------------------------------

:Repo: https://github.com/sodiumoxide/sodiumoxide


RustCrypto hashes
-------------------------------

:Repo: https://github.com/RustCrypto/hashes



TLS
========================================

Rustls
------------------------------

:Repo: https://github.com/ctz/rustls


基於 ring 和 libwebpki 去實做 TLS library，
專案程式碼都是 Rust code。


參考：

* `TLS performance: rustls versus OpenSSL <https://jbp.io/2019/07/01/rustls-vs-openssl-performance.html>`_


rust-native-tls - 系統 TLS library 抽象化
-----------------------------------------

:Repo: https://github.com/sfackler/rust-native-tls


對系統 TLS library 做包裝，
根據編譯的平台做選擇。

支援：

* OSX: Secure Transport
* Windows: SChannel
* Other: OpenSSL


MesaLink - memory-safe and OpenSSL-compatible TLS library
---------------------------------------------------------

:site: https://mesalink.io/
:repo: https://github.com/mesalock-linux/mesalink


基於 ring 和 rustls



Web PKI X.509
========================================

webpki
------------------------------

:Repo: https://github.com/briansmith/webpki


基於 ring 去實做 WebPKI X.509 Certificate Validation，
專案程式碼都是 Rust code。



QUIC
========================================

Quinn
------------------------------

:Repo: https://github.com/djc/quinn

Quinn 是基於 Rust futures 和 tokio 的 QUIC 實做。


futures + tokio + ring + webpki


* `Quinn 合併了先前 Quicr 的一些實做 <https://github.com/Ralith/quicr>`_
* `Ninn - QUIC + Noise = nQUIC <https://github.com/rot256/ninn>`_
    - `Noise Protocol Framework - crypto protocols that are simple, fast, and secure <http://www.noiseprotocol.org/>`_


Quiche (by CloudFlare)
------------------------------

:Repo: https://github.com/cloudflare/quiche


參考：

* `Enjoy a slice of QUIC, and Rust! <https://blog.cloudflare.com/enjoy-a-slice-of-quic-and-rust/>`_


Nego (by Mozilla)
------------------------------

:Repo: https://github.com/mozilla/neqo



Digital Signature (數位簽章)
=========================================

Signatory
------------------------------

Signatory 提供了數位簽章的 API，
並且支援多種 backend 支援，
可以依照偏好選擇實做版本。

支援：

* ECDSA
* Ed25519



2FA (Two Factor Authentication)
========================================

LibreAuth - HOTP/TOTP/...
------------------------------

:repo: https://github.com/breard-r/libreauth



參考
========================================

* `Rust Crypto <https://github.com/RustCrypto>`_
    - block cipher algorithms
    - stream cipher algorithms
    - digital signature algorithms
    - cryptographic hash functions
