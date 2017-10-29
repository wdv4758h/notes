ethernet
--------
::

  - ifconfig eth0 <IP> netmask <netmask>
  - route add default gw <gateway>
  - edit /etc/resolv.conf 
  
    - nameserver <DNS>

variable example::

  - <IP> = 192.168.1.10
  - <netmask> = 255.255.255.128
  - <gateway> = 192.168.1.126
  - <DNS> = 8.8.8.8

wireless
--------

command intro
~~~~~~~~~~~~~
::

  - ifconfig       # network config
  - iwlist         # scan wireless
  - iwconfig       # wireless network config
  - dhclient       # dhcp
  - wpa_passphrase # generate wpa.conf file, with wireless SSID and WPA Shared Key(password)
  - wpa_supplicant # connect to WPA wireless network

usage
~~~~~
::

  - ifconfig # find your NIC's interface, ex. wlan0
  - ifconfig <interface> up
  - iwlist <interface> scan
  
  example: <interface> = wlan0

non wpa wireless
""""""""""""""""
- ``iwconfig <interface> essid <SSID> key s:<wireless_key>``

    - s: for ascii key, default HEX key

- ``dhclient -v <interface>``

wpa wireless
""""""""""""
- ``wpa_passphrase <SSID> >> /etc/wpa_supplicant.conf``

    - input SSID's WPA Pre-Shared Key(password)

- ``wpa_supplicant -B -D wext -i <interface> -c /etc/wpa_supplicant.conf``

    - ``-i <interface>``
    - ``-c <conf_file>``
    - ``-D <driver>``: specify wireless driver, wext is the generic driver.
    - ``-B``: run in background 

reference
---------
- http://www.ghacks.net/2009/04/14/connect-to-a-wireless-network-via-command-line/
- WPA/WPA2: http://linuxcommando.blogspot.tw/2013/10/how-to-connect-to-wpawpa2-wifi-network.html 
