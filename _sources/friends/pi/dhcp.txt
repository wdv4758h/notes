====
DHCP
====
DHCP（Dynamic Host Configuration Protocol）讓 client（電腦/手機...等等）能自動取得 IP address。

* 基於 UDP
* 除了 IP address 以外，還可以設定 DNS、netmask、MTU 等等
* Server 使用 UDP port 67，client 使用 UDP port 68

流程： ::

  .--------------------------------------------------.
  |                                                  |
  |  Client                                  Server  |
  |    |                                       |     |
  |    | [DHCP discover]                       |     |
  |    |   src: 0.0.0.0:68                     |     |
  |    |   dst: 255.255.255.255:67             |     |
  |    |   我想要：                            |     |
  |    |     subnet mask                       |     |
  |    |     router                            |     |
  |    |     domain name                       |     |
  |    |     DNS server                        |     |
  |    |-------------------------------------->|     |
  |    |                                       |     |
  |    | [DHCP offer]                          |     |
  |    |   src: 192.168.1.1:67                 |     |
  |    |   dst: 255.255.255.255:68             |     |
  |    |   your ip addr: 192.168.1.100         |     |
  |    |   可能可以給你：                      |     |
  |    |     mask: 255.255.255.0               |     |
  |    |     router: 192.168.1.1               |     |
  |    |     期限: 1 天                        |     |
  |    |     DNS servers: <一些 DNS servers>   |     |
  |    |<--------------------------------------|     |
  |    |                                       |     |
  |    | [DHCP request]                        |     |
  |    |   src: 0.0.0.0:68                     |     |
  |    |   dst: 255.255.255.255:67             |     |
  |    |   我要：                              |     |
  |    |     IP addr: 192.168.1.100            |     |
  |    |-------------------------------------->|     |
  |    |                                       |     |
  |    | [DHCP ack]                            |     |
  |    |   src: 192.168.1.1:67                 |     |
  |    |   dst: 255.255.255.255:68             |     |
  |    |   your ip addr: 192.168.1.100         |     |
  |    |   給你：                              |     |
  |    |     mask: 255.255.255.0               |     |
  |    |     router: 192.168.1.1               |     |
  |    |     期限: 1 天                        |     |
  |    |     DNS servers: <一些 DNS servers>   |     |
  |    |<--------------------------------------|     |
  |    |                                       |     |
  |                                                  |
  '--------------------------------------------------'

* DHCP discover 裡面可以指定特定的 IP address
* Client 在真的拿到 IP address 之前都不能拿來用，所以上面所有 message 的 client IP address 都只能填 0.0.0.0 和 255.255.255.255
