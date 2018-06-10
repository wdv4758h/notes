========================================
DNS
========================================


.. contents:: 目錄


運作流程
========================================

推薦閱讀 `How DNS works <https://howdns.works/>`_ 網站，
裡面用漫畫的方式來呈現，
以可愛的圖像來說明 DNS 的運作。



實做
========================================

* `Knot DNS <https://github.com/CZ-NIC/knot>`_
* `NSD <https://github.com/NLnetLabs/nsd>`_
    - C based DNS server
* `BIND 9 <https://github.com/isc-projects/bind9>`_
* `PowerDNS <https://github.com/PowerDNS/pdns>`_
    - C++ based DNS server
* `Erl-DNS <https://github.com/aetrion/erl-dns/>`_
    - Erlang based DNS server
* `Unbound <https://github.com/NLnetLabs/unbound>`_
    - C based DNS server
* `Trust-DNS <https://github.com/bluejekyll/trust-dns>`_
    - Rust based DNS client and server



效能測試
========================================

* `Benchmark – Knot DNS <https://www.knot-dns.cz/benchmark/>`_



mDNS (Multicast DNS)
========================================

mDNS 是在 RFC 6762 中定義的協議，
藉由 multicast UDP 來在 local network 裡尋找對應的服務，
此作法不需要 DNS server，
也不需要額外的設定。
（經由 mDNS 可以達成 Service Discovery 的效果）

由於是使用 UDP，
所以在網路中沒有對應的服務時並不會 block，
若有人收到並回應的話才進行後續處理。
mDNS 預設只處理 ``.local`` TLD 的網域。


相關實做：

* `Avahi <https://github.com/lathiat/avahi>`_
* Apple Bonjour
* Rust
    - `Trust-DNS <https://github.com/bluejekyll/trust-dns>`_
    - `mdns <https://github.com/dylanmckay/mdns>`_


相關使用：

* AirPlay
* AirPrint
* Google Cast
* Cloud Print


相關連結：

* `Wikipedia - Multicast DNS <https://en.wikipedia.org/wiki/Multicast_DNS>`_
* `Wikipedia - Zero-configuration networking <https://en.wikipedia.org/wiki/Zero-configuration_networking>`_
* `Google Cloud Print Connector <https://github.com/google/cloud-print-connector/>`_



文章
========================================

* `PowerDNS - A warm welcome to DNS <https://powerdns.org/hello-dns/>`_
* `The Top DNS Servers And What They Offer - DNSimple Blog <https://blog.dnsimple.com/2015/02/top-dns-servers/>`_
