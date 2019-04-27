========================================
VPN
========================================


.. contents:: 目錄


介紹
========================================



WireGuard
========================================

:Site: https://www.wireguard.com/

WireGuard 是新的 VPN 協定，
設計在 Layer 3 上，
採用了現今安全快速的加密演算法，
目標是比現有的 OpenVPN、IPsec 還要簡單、安全、快速。
原先是釋出給 Linux kernel，
但是現在已經可以在各平台上使用。

使用 WireGuard 時會利用自己的 private key 和對方的 public key 建立網路界面，
所有要使用這個 VPN 的封包會透過這個網路界面送出，
WireGuard 會用 UDP 傳送包裝過的 IP 封包，
也可以和 firewall hole punching 一同運作。
而金鑰和設定檔的分享都在 WireGuard 的規範之外，
這樣的模型比起既有 VPN 反而跟 SSH/Mosh 比較像，
除了最簡單的複製貼上外，
你也可以跟 LDAP 整合、在使用佈署工具時一同推送或是接上服務來分享設定。


WireGuard 採用了叫做 Cryptokey Routing 的概念，
也就是把 public key 跟 tunnel IP 配對起來，
針對過來的 IP 去檢查是否是用對應到的金鑰。
server 設定範例：

.. code-block:: dosini

    [Interface]
    PrivateKey = yAnz5TF+lXXJte14tji3zlMNq+hd2rYUIgJBgB3fBmk=
    ListenPort = 51820

    [Peer]
    PublicKey = xTIBA5rboUvnH4htodjb6e697QjLERt1NAB4mZqp8Dg=
    AllowedIPs = 10.192.122.3/32, 10.192.124.1/24

    [Peer]
    PublicKey = TrMvSoP4jYQlY6RIzBgbssQqY3vxI2Pi+y71lOWWXX0=
    AllowedIPs = 10.192.122.4/32, 192.168.0.0/16

    [Peer]
    PublicKey = gN65BkIKy1eCE9pP1wdc8ROUtkHLF2PfAqYdyYBz6EA=
    AllowedIPs = 10.10.10.230/32

client 設定範例:

.. code-block:: dosini

    [Interface]
    PrivateKey = gI6EdUSYvn8ugXOt8QQD6Yc+JyiZxIhp3GInSWRfWGE=
    ListenPort = 21841

    [Peer]
    PublicKey = HIgo9xNzJMWLKASShiTqIybxZ0U3wGLiUeJ1PKf8ykw=
    Endpoint = 192.95.5.69:51820
    AllowedIPs = 0.0.0.0/0


WireGuard 還支援 roaming，
所以不會在切換網路後就整個斷開無法使用（像是 Mosh 一樣可以自動恢復連線）。

WireGuard 也對於 Container 很友善，
只要把建立的網路界面開給 Container 使用，
如此一來 Container 馬上就可以用 WireGuard VPN 了。


* `LPC2018 - WireGuard: Next-Generation Secure Kernel Network Tunnel <https://www.youtube.com/watch?v=CejbCQ5wS7Q>`_
    - `Slide - LPC2018 - WireGuard: Next-Generation Secure Kernel Network Tunnel <https://www.wireguard.com/talks/lpc2018-wireguard-slides.pdf>`_
    - Layer 3 secure network tunnel for IPv4 and IPv6
    - designed for Linux kernel
    - UDP based, firewall hole punching
    - modern cryptographic
    - simple
    - SSH like authentication model
    - replacement for OpenVPN and IPsec
    - Timers: a stateless interface for a stateful protocol
        + no "connecting" "connected"
    - endpoints roam like mosh
    - static fixed length header -> no parsing needed !!! (more secure)
    - static allocations and guarded state
        + all state is allocated during config
        + no dynamic allocation during responsing the packets
    - you can't scan the internet for WireGuard, it doesn't response to unauthenticated packets
    - Noise Protocol Framework



參考
========================================

* `Wikipedia - VPN <https://en.wikipedia.org/wiki/Virtual_private_network>`_
* `Wikipedia - IKE (Internet Key Exchange) <https://en.wikipedia.org/wiki/Internet_Key_Exchange>`_
* OpenVPN
* `Algo - personal IPSec VPN in the cloud <https://github.com/trailofbits/algo>`_
