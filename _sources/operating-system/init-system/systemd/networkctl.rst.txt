========================================
networkctl
========================================

.. code-block:: sh

    $ networkctl
    IDX LINK             TYPE               OPERATIONAL SETUP
    1 lo               loopback           n/a         n/a
    2 enp2s0f0         ether              n/a         n/a
    3 wlp3s0           wlan               n/a         n/a

    3 links listed.
    $ networkctl status
    ●      State: n/a
        Address: 192.168.0.104 on wlp3s0
                fe80::c218:85ff:fef8:7583 on wlp3s0
        Gateway: 192.168.0.1 (D-Link International) on wlp3s0
