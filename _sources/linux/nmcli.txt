========================================
nmcli
========================================

.. code-block:: sh

    $ nmcli d
    DEVICE    TYPE      STATE        CONNECTION
    wlp3s0    wifi      connected    MYSSID1
    enp2s0f0  ethernet  unavailable  --
    lo        loopback  unmanaged    --

    $ nmcli dev wifi
    *  SSID            MODE   CHAN  RATE       SIGNAL  BARS  SECURITY
       MYSSID1         Infra  149   54 Mbit/s  100     ▂▄▆█  WPA2
       MYSSID2         Infra  1     54 Mbit/s  95      ▂▄▆█  WPA2
       MYSSID3         Infra  11    54 Mbit/s  42      ▂▄__  WPA2
       MYSSID4         Infra  157   54 Mbit/s  27      ▂___  WPA1
       MYSSID5         Infra  11    54 Mbit/s  45      ▂▄__  WPA2

    $ nmcli dev wifi con 'MYSSID1' password 'MYPASSWORD'
    $ nmcli con up id 'Wireless connection 1'
    # Note the "id" is NOT the SSID or BSSID
    # instead this is the "nickname" on your computer for this network.
    # /etc/NetworkManager/system-connections/MYSSID
