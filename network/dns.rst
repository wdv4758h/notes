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



常見 DNS 設定
========================================

* Cloudflare: 1.1.1.1
* Google: 8.8.8.8



讓 NetworkManager 使用 systemd-resolved
========================================

開啟 ``systemd-resolved`` ：

.. code-block:: sh

    sudo systemctl enable systemd-resolved
    sudo systemctl start systemd-resolved
    systemd-resolve --status
    systemd-resolve --statistics
    systemd-resolve en.wikipedia.org


設定 NetworkManager 的 DNS 使用 ``systemd-resolved`` ：

``/etc/NetworkManager/conf.d/dns.conf`` ::

    [main]
    dns=systemd-resolved


.. code-block:: sh

    sudo systemctl restart NetworkManager



/etc/resolv.conf
========================================

1983 年，4.3BSD 釋出時包含了第一個通用的 Unix IP stack，
也成為現代 Unix-like 系統網路實做的基礎，
其中 ``resolv.conf`` 是其中一部分。

``/etc/resolv.conf`` 的處理是 libc 的一部分，
實做可以參考 musl：

* 對外的 API： `res_query <http://git.musl-libc.org/cgit/musl/tree/src/network/res_query.c>`_
* res_query 呼叫 `__res_send <http://git.musl-libc.org/cgit/musl/tree/src/network/res_send.c>`_
* __res_send 呼叫 `__res_msend <http://git.musl-libc.org/cgit/musl/tree/src/network/res_msend.c>`_
* __res_msend
    - `__get_resolv_conf 讀入 /etc/resolv.conf 設定檔 <http://git.musl-libc.org/cgit/musl/tree/src/network/resolvconf.c>`_
    - `__res_msend_rc <http://git.musl-libc.org/cgit/musl/tree/src/network/res_msend.c>`_



/etc/hosts
========================================



Trust-DNS
========================================

Trust-DNS 是用 Rust 實做的 DNS client/server。


Resolver
------------------------------

主要的型別為 ``Resolver`` ，
DNS 主機設定為 ``ResolverConfig`` ，
DNS query 調整為 ``ResolverOpts`` （例如 TTL、要不要使用 ``/ect/hosts`` ）。

``ResolverConfig`` 提供了一些預設的 DNS 設定，
例如 Google、Cloudflare、Quad9，
也可以選擇 DNS over TLS 或是 DNS over HTTPS。


範例：

.. code-block:: rust

    ////////////////////////////////////////
    // 1. 全部用預設
    ////////////////////////////////////////

    // Construct a new Resolver with default configuration options
    let resolver = Resolver::new(ResolverConfig::default(), ResolverOpts::default()).unwrap();
    // Lookup the IP addresses associated with a name.
    // The final dot forces this to be an FQDN, otherwise the search rules as specified
    // in `ResolverOpts` will take effect. FQDN's are generally cheaper queries.
    // Return type is `ResolveResult<LookupIp>`
    let response = resolver.lookup_ip("www.example.com.").unwrap();
    // There can be many addresses associated with the name,
    //  this can return IPv4 and/or IPv6 addresses
    let address = response.iter().next().expect("no addresses returned!");
    if address.is_ipv4() {
        assert_eq!(address, IpAddr::V4(Ipv4Addr::new(93, 184, 216, 34)));
    } else {
        assert_eq!(address, IpAddr::V6(Ipv6Addr::new(0x2606, 0x2800, 0x220, 0x1, 0x248, 0x1893, 0x25c8, 0x1946)));
    }

    ////////////////////////////////////////
    // 2. 使用 /etc/resolv.conf 的設定
    ////////////////////////////////////////

    // Use the host OS'es `/etc/resolv.conf`
    let resolver = Resolver::from_system_conf().unwrap();
    let response = resolver.lookup_ip("www.example.com.").unwrap();

    ////////////////////////////////////////
    // 3. 使用 Cloudflare
    ////////////////////////////////////////

    let resolver = Resolver::new(ResolverConfig::cloudflare(), ResolverOpts::default()).unwrap();
    let response = resolver.lookup_ip("www.example.com.").unwrap();

    ////////////////////////////////////////
    // 3. 使用 Cloudflare 的 DNS over HTTPS
    ////////////////////////////////////////

    let resolver = Resolver::new(ResolverConfig::cloudflare_https(), ResolverOpts::default()).unwrap();
    let response = resolver.lookup_ip("www.example.com.").unwrap();



參考
========================================

* `Arch Wiki - Domain Name Resolution <https://wiki.archlinux.org/index.php/Domain_name_resolution>`_
* `Arch Wiki - Category: Domain Name System <https://wiki.archlinux.org/index.php/Category:Domain_Name_System>`_
* `Wikipedia - resolv.conf <https://en.wikipedia.org/wiki/Resolv.conf>`_
