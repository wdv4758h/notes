========================================
Network Security
========================================

Ch00 - Introduction
========================================

* 3 exams (roughly 25%, 25%, 25%)
    - 11/3 (Tue), 12/8, 1/12, (1/5 ETH professor’s talk)
    - 4 quizzes (drop the lowest grade): 5%
* Others combined: 20%
    - 1 homework/2 weeks
    - 1 big project (consists of smaller projects)

Ch01 (Pages: 32)
========================================

* CIA Triad
    - Confidentiality
    - Integrity
    - Availability

* Security Services
    - X.800
        + A service provided by a protocol layer of communicating open systems and that ensures adequate security of the systems or of data transfers
    - RFC 4949
        + A processing or communication service provided by a system to give a specific kind of protection to system resources


* X.800
    - Authentication
    - Access control
    - Data confidentiality
    - Data integrity
    - Nonrepudiation

* Security Attacks
    - Passive Attacks
        + 只從系統取得資訊，對系統資源不影響
        + 重點在資訊取得 (經由傳送的資料或是流量分析)
    - Active Attacks
        + Masquerade (冒充)
        + Replay
        + Modification of messages
        + Denial of service
        + (會更動到系統資源或影響操作，更動資料或偽造資料)


* Standards
    - NIST (National Institute of Standards and Technology) (國家標準技術研究所)
        + FIPS (Federal Information Processing Standards)
        + SP (Special Publications)
    - ISOC (Internet Society)
        + RFCs
        + Internet Engineering Task Force (IETF)
        + Internet Architecture Board (IAB)

* The OSI security architecture


Ch02 (Pages: 38)
========================================

* 功用
    - 加解密
    - 認證、簽章

* Encryption
    - Symmetric Encryption (對稱加密)
        + 加解密用同一把 key
    - Asymmetric Encryption (非對稱加密)
        + 加解密用不同把 key


* Symmetric Encryption
    - 需要強力的加密方式
    - 發送端和接收端需要取得同把 secret key
    - 安全性會在 key 身上而不是演算法本身

* Cryptography
    - plaintext to ciphertext
        + Substitution (取代)
        + Transposition (換位)
        + Product systems (Substitution 和 Transposition 組合)

* Cryptanalysis

* `Attack Model <https://en.wikipedia.org/wiki/Attack_model>`_
    - Ciphertext-only attack (COA)
    - Known-plaintext attack (KPA)
    - Chosen-plaintext attack (CPA)
    - Chosen-ciphertext attack (CCA)
    - Open key model attacks
    - Side-channel attack

* Feistel Cipher
    - symmetric structure
    - block ciphers
    - https://en.wikipedia.org/wiki/Block_cipher
    - block size 為 64-bit，後 32-bit 會成為新的前 32-bit，另外後 32-bit 還會拿來跟 key 做加密 (交給任意的加密演算法)，結果再跟前原本的 32-bit 做 XOR，形成新的後 32-bit，以此循環多個回合
    - 最後一回合結束後再前後交換，打亂順序


* Block Cipher
    - 固定長度的明文加密成固定長度的密文 (DES, AES, ...)
    - 把明文切成許多 block 下去做加密
    - 如果長度不是 block 的整數倍，則加上 padding 形成完整的 block
    - 為最常用的對稱式加密演算法
    - Block Mode (depend on block cipher encryption)
        + ECB
        + CBC
        + GCM
    - 三個常見的 Symmetric Block Cipher
        + `Data Encryption Standard (DES) <https://en.wikipedia.org/wiki/Data_Encryption_Standard>`_
            * Feistel Cipher 的加強版
            * Block : 64 bits
            * Key : 56 bits (以現在來說已經過短了)
            * 16 rounds
        + Triple DES (3DES)
        + Advanced Encryption Standard (AES)
            * 2001 年，AES 取代 DES 成為標準
            * Block : 128 bits

+------------+-----+---------------+--------------+
|            | DES | AES           | 3DES         |
+============+=====+===============+==============+
| Block Size | 64  | 128           | 64           |
+------------+-----+---------------+--------------+
| Key Size   | 56  | 128, 192, 256 | 56, 112, 168 |
+------------+-----+---------------+--------------+
| Rounds     | 16  | 10, 12, 14    | 48           |
+------------+-----+---------------+--------------+
| Strength   | 1   | 3             | 2            |
+------------+-----+---------------+--------------+


* `Cipher block modes of operation <https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation>`_
    - ECB (Electronic Codebook Mode)
        + 各個 block 獨立處理，可同時進行，任意存取
        + M -> f(M, key) -> N
        + codebook
        + 可能會有 relpay attack
    - CBC (Cipher Block Chaining Mode)
        + 前一個 block 的 ciphertext 會加入下一個 block 的加密 (XOR)
    - CFB (s-bit Cipher Feedback Mode)
        + 和 CBC 相似，操作都相同，但是位置跟順序不一樣
        + self-synchronizing stream cipher
    - CTR (Counter Mode)
        + 輸入 Nonce (an arbitrary number that may only be used once) 和 counter (block counter) 加密，加密後和原文取 XOR
        + (硬體) 可以平行化計算各個 blocks
        + (硬體) Throughput 只受平行化量限制
        + (軟體) 跑在支援平行化的 CPU 會很有效率
        + 加密演算法不會受到輸入的 plaintext 或 ciphertext 影響，只有一系列的 XORs 計算
        + 可以隨機存取第 i 個 block 的 plaintext 或 ciphertext
        + 更前面提到的 mode 一樣安全
        + 只需要實作加密演算法 (不用做解密)

+---------------------------+-----+-----+-----+-----+
|                           | ECB | CBC | CFB | CTR |
+===========================+=====+=====+=====+=====+
| Encryption parallelizable | Yes | No  | NO  | Yes |
+---------------------------+-----+-----+-----+-----+
| Decryption parallelizable | Yes | Yes | Yes | Yes |
+---------------------------+-----+-----+-----+-----+
| Random read access        | Yes | Yes | Yes | Yes |
+---------------------------+-----+-----+-----+-----+

* RSA
    - 非對稱 (asymmetric)

* Random Number Generator
    - TRNG (True Random Number Generator) : 把真的 random 資料轉成 bit stream
    - PRNG (Pseudorandom Number Generator) : 輸入 seed 產生 Pseudorandom bit stream
        + Symmetric Block Ciphers
        + Asymmetric Ciphers
        + Hash functions and message authentication codes
    - PRF (Pseudorandom Function) : 輸入 seed 和 context-specific values 產生 Pseudorandom value

* RC4 Algorithm
    - Wired Equivalent Privacy (WEP) protocol
    - WiFi Protected Access (WPA) protocol
    - IEEE 802.11 wireless LAN standard
    - Stream Ciphers
    - RC4 會把加密用的 key (還有 key 的長度) 經過處理後拿去跟原文 XOR 產生 ciphertext


* Kerberos


Ch03 (Pages: 33)
========================================

* Encryption
    - Conventional Encryption
        + 加解密都是用同一把 key
    - Public-Key Encryption
        + Public Key & Private Key
    - Secret Value

* Message Authentication
    - Using a Message Authentication Code (MAC)
    - Using a One-Way Hash Function

* (Crypto) Hash
    - 任意長度的輸入轉成固定長度的結果
    - MD5, SHA1, SHA2, ...

* One-Way Hash Function
    - 接收各種 size 的資訊 (``M``)，產生固定 size 的結果 (``H(M)``)
    - 不需要把 secret key 當作輸入
    - 把資訊 (``M``) 的摘要也一起送出，作為驗證
    - Secure Hash Function 性質
        + 很難從 ``H(M)`` 找到 ``M`` (One-Way)
        + 很難找到 ``N`` 使得 ``H(M)`` 等同於 ``H(N)`` (Pre-Image Resistance)
        + 很難找到不同的 ``M`` 和 ``N`` 使得 ``H(M) = H(N)`` (Collision Free)

* SHA
    - NIST 1993
    - 基於 MD4
    - 160-bit hash value


+---------------------+--------+---------+---------+---------+---------+
|                     | SHA-1  | SHA-224 | SHA-256 | SHA-384 | SHA-512 |
+=====================+========+=========+=========+=========+=========+
| Message Digest Size | 160    | 224     | 256     | 384     | 512     |
+---------------------+--------+---------+---------+---------+---------+
| Message Size        | < 2^64 | < 2^64  | < 2^64  | < 2^128 | < 2^128 |
+---------------------+--------+---------+---------+---------+---------+
| Block Size          | 512    | 512     | 512     | 1024    | 1024    |
+---------------------+--------+---------+---------+---------+---------+
| Word Size           | 32     | 32      | 32      | 64      | 64      |
+---------------------+--------+---------+---------+---------+---------+
| Number of Steps     | 80     | 64      | 64      | 80      | 80      |
+---------------------+--------+---------+---------+---------+---------+


* HMAC

* Counter with Cipher Block Chaining-Message Authentication Code (CCM)
    - CTR
    - CMAC
    - AES



+----------------+-----------------------+-------------------+--------------+
| Algorithm      | Encryption/Decryption | Digital Signature | Key Exchange |
+================+=======================+===================+==============+
| RSA            | Yes                   | Yes               | Yes          |
+----------------+-----------------------+-------------------+--------------+
| Diffie-Hellman | No                    | No                | Yes          |
+----------------+-----------------------+-------------------+--------------+
| DSS            | No                    | Yes               | No           |
+----------------+-----------------------+-------------------+--------------+
| Elliptic Curve | Yes                   | Yes               | Yes          |
+----------------+-----------------------+-------------------+--------------+


* `Diffie-Hellman <https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange>`_
    - 第一個公開的 public-key 演算法
    - 在不安全的環境下建立互相信任的 private key
    - 流程
        1. [公開] Alice & Bob 溝通好選擇兩個數字 ``p`` 和 ``g``
        2. [非公開] Alice & Bob 各自選一個數字作為 secret number (``a`` 和 ``b``)
        3. [公開] Alice : ``A = g ^ a mod p``
        4. [公開] Bob : ``B = g ^ b mod p``
        5. [非公開] Alice : ``s = B ^ a mod p``
        6. [非公開] Bob : ``s = A ^ b mod p``

.. image:: /images/crypto/Diffie-Hellman-Key-Exchange.png



* RSA decryption

* Digital Signature Standard (DSS)
    - 利用 SHA-1 做出新的 Digital Signature Algorithm (DSA)
    - Unlike RSA, it cannot be used for encryption or key exchange

* Elliptic-curve cryptology (ECC)
    - offer equal security for a far smaller bit size (compare to RSA)


Ch04 (Pages: 37)
========================================

* Kerberos
    - https://www.microsoft.com/taiwan/technet/columns/profwin/kerberos101.mspx
    - 必須使用 ``對稱加密``
    - 不使用 public-key 加密
    - version 4
        + Authentication Server (AS) (認證服務)
            * 提供可信任的認證 (ticket granting ticket TGT)
            * 核發 TGT 與 Session Key
        + Ticket Granting Server (TGS) (取票服務)
            * 使用者在拿到 TGT 之後可以存取到 TGS 的服務
            * 核發 Server 的 Ticket 與 Session Key
        + Complex protocol using DES
    - version 5


* X.509

* PKIX
