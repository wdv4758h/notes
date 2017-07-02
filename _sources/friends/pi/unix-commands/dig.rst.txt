=======
``dig``
=======
* 查詢 ``cs.nctu.edu.tw`` domain 的 ``mx`` record ::

    $ dig mx cs.nctu.edu.tw

  - ``mx``, ``A``, ``AAAA``, ``ns``, ``cname``, ``txt``, ``axfr``, ``soa`` 也都可以查詢

* 指定向 DNS server ``140.113.1.1`` 查詢 ::

    $ dig @140.113.1.1 bsd1.cs.nctu.edu.tw

* 指定向 DNS server ``140.113.1.1`` 查詢 ``mx`` record ::

    $ dig @140.113.1.1 mx cs.nctu.edu.tw

* 查反解 ::

    $ dig -x 140.113.1.1

* 在 FreeBSD 10 已被 ``drill`` 指令取代, 可到 ``dns/bind-tools`` ports 裡安裝
