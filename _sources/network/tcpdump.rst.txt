========================================
tcpdump
========================================

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
