========================================
tcpdump
========================================


.. contents:: 目錄


arp
========================================

.. code-block:: sh

    # tcpdump
    $ sudo tcpdump arp
    $ sudo tcpdump arp -vv

.. code-block:: sh

    # Wireshark
    $ tshark -O arp -w log.pcap

.. code-block:: sh

    # show
    $ arp -n
    $ ip -s -s neigh

    # clear
    $ sudo arp -d $IP
    $ arp -n | awk '/^[1-9]/ {print "arp -d "$1}' | sudo sh
    $ sudo ip -s -s neigh flush all

    # request
    $ sudo arping -I $INTERFACE -b $IP
    $ ping $IP


用 tcpdump 攔截封包
========================================

所有
------------------------------

.. code-block:: sh

  $ tcpdump

.. code-block:: sh

  $ tcpdump -tttt -qn -vvv


UDP
------------------------------

.. code-block:: sh

  tcpdump -tttt -qn -vvv udp

.. code-block:: sh

  tcpdump -tttt -qn -vvv host 54.191.179.231 and udp

.. code-block:: sh

  tcpdump -n udp dst portrange 40000-60000


寫成 pcap 檔
------------------------------

.. code-block:: sh

  tcpdump -tttt -qn -vvv -w webrtc.pcap
