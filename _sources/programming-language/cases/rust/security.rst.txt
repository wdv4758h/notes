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



ring - Cryptographic Operations
========================================

:Repo: https://github.com/briansmith/ring


ring 是密碼學相關操作的 library，
由 Rust、C、assembly 寫成，
大部分的 C、assembly 是從 BoringSSL 來的，
而 BoringSSL 則是從 OpenSSL 來的，
ring 有定期從 BoringSSL 上游拉回更動。



webpki - WebPKI X.509
========================================

:Repo: https://github.com/briansmith/webpki


基於 ring 去實做 WebPKI X.509 Certificate Validation，
專案程式碼都是 Rust code。



Rustls - TLS library
========================================

:Repo: https://github.com/ctz/rustls


基於 ring 和 libwebpki 去實做 TLS library，
專案程式碼都是 Rust code。



Quinn - QUIC library
========================================

:Repo: https://github.com/djc/quinn

Quinn 是基於 Rust futures 和 tokio 的 QUIC 實做。


futures + tokio + ring + webpki



rust-native-tls - 系統 TLS library 抽象化
=========================================

:Repo: https://github.com/sfackler/rust-native-tls


對系統 TLS library 做包裝，
根據編譯的平台做選擇。

支援：

* OSX: Secure Transport
* Windows: SChannel
* Other: OpenSSL



Signatory - 數位簽章演算法 library
=========================================

Signatory 提供了數位簽章的 API，
並且支援多種 backend 支援，
可以依照偏好選擇實做版本。

支援：

* ECDSA
* Ed25519
