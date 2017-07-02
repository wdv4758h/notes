===========
``tcpdump``
===========
* 指定 interface 並只聽取 ICMP 封包 ::

    # tcpdump -i <interface> icmp

* dump 出可被 wireshark 開啟的格式 ::

    # tcpdump -i <interface> -s 65535 -w <output-file>
