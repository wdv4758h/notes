-   察看 routing table ::

      $ route

-   一次設定 IP ::

      $ sudo ifconfig eth4 xxx.xxx.xxx.xxx netmask xxx.xxx.xxx.xxx

-   新增 default route ::

      $ sudo ip route add default via <gateway IP>
      $ sudo route add default gw <gateway IP>

-   永久設定 IP ::

      #/etc/network/interfaces
      #auto lo
      #iface lo inet loopback

      auto eth4

      #iface eth0 inet static
      iface eth4 inet static
      #address xxx.xxx.xxx.xxx
      address xxx.xxx.xxx.xxx
      netmask xxx.xxx.xxx.xxx
      gateway xxx.xxx.xxx.xxx

-   重啟網路 ::

      $ sudo /etc/init.d/networking restart

