socket
======
socket(), bind(), connect(), listen()
-------------------------------------
- headers::

    - <sys/socket.h>
    - <sys/types.h>
    - <netinet/in.h>

      - struct sockaddr_in 

    - <arpa/inet.h> 

- int socket(int domain, int type, int protocol)

  - domain: AF_INET, AF_INET6, AF_UNIX (ipv4, ipv6, unix socket)
  - type: SOCK_STREAM, SOCK_DGRAM, SOCK_RAW (tcp, udp, ip)
  - protocol: 可先填 0, non-zero for multiple-protocol??
  
- int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen)

  - sockfd: socket 函式 return 的 socket file descriptor
  - (struct sockaddr*) addr

    - 此參數真實的型態根據 address family(AF_INET or AF_UNIX) 決定, sockaddr 像是 OO 中的 abstract class.
    - struct sockaddr_in (ipv4)
    - struct sockaddr_un (unix socket)

  - addrlen
    - sizeof(addr)

- int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen)

  - 跟 bind 參數一樣

- int listen(int sockfd, int backlog)

  - maximum length to which the queue of pending connections for sockfd may grow.

- int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);

  - 如果 connection 建立成功, 此 connection 會開一個 fd.
  - return connection's fd.

IO function
-----------
- ssize_t read(int fd, void* buf, size_t count);
- ssize_t write(int fd, const void* buf, size_t count); 

  - count: 要寫幾 bytes
  - return value: 總共寫了幾 bytes (有可能不完全寫入)

- int send(int sockfd, const void* buf, int len, int flags)

  - return 實際傳送的 bytes
  - return -1 for error

- int recv(int sockfd, void* buf, int len, int flags)

  - return 實際傳送的 bytes
  - return 0, 對方已終止 connection 
  - return -1 for error

- recv flags

  - MSG_DONTWAIT: nonblocking read, 等同 fcntl set O_NONBLOCK
  - MSG_PEEK: 收資料, 但不從 recieve queue 清掉收的資料 (代表下次 recv 會在收到一樣的資料).

ipv4 ip address and port
------------------------
- 在 bind/connect 的 API 中皆為數字 (ip/port: 32/16 bits), 要考慮 endianness.

  - network bytes order: big endian, 應該大部份的網路 protocol 都使用, ip protocol 的數字全部使用

    - http://en.wikipedia.org/wiki/endianness#endianness_in_networking

  - host bytes order: cpu 的 endianness, 例如 x86 為 little-endian
  - BSD socket API 有設計 host 跟 network endianness 轉換的 API

    - host 跟 network 雙向 (hton, ntoh)
    - 16 跟 32 bits (short, long)

- struct sockaddr_in::

     // This API is on Linux 3.11/LinuxMint 16
     // from /usr/include/netinet/in.h, gcc include path 可透過 ``gcc -E -v -`` 指令尋找.

     struct sockaddr_in {
         sa_family_t sin_family;      // unsigned short int 
         in_port_t sin_port;          // uint16_t 
         struct in_addr sin_addr;
         unsigned char sin_zero[xxx]; // for padding
     }

     struct in_addr {
         in_addr_t s_addr; // uint32_t 
     }

- int inet_aton(const char* cp, struct in_addr* inp); 

  - converts IPv4 address cp from string into binary form (network byte order).
  - stores result in inp(struct in_addr).

- char* inet_ntoa(struct in_addr in);

  - converts IPv4 address cp from string into binary form (network byte order).
  - return value(string) is statically allocated buffer, subsequent calls will overwrite it.

IP address data structure detail
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- 3 type of IPv4 address

  - ``char*``: string
  - ``uint32_t``: number
  - ``struct in_addr``: struct, it is used to transfer data.

- int inet_aton(const char* cp, struct in_addr* inp); 

  - converts IPv4 address: string [cp] => binary(network byte order) [inp].
  - binary at struct in_addr.s_addr

- char* inet_ntoa(struct in_addr in);

  - converts IPv4 address: binary(network byte order) [in] => string [return value].
  - return value(string) is statically allocated buffer, subsequent calls will overwrite it.

----

- int inet_aton(const char* cp, struct in_addr* inp);

  - string => nbytes binary

- char* inet_ntoa(struct in_addr in);

  - nbytes binary => string

- in_addr_t inet_addr(const char* cp);
- in_addr_t inet_network(const char* cp);

- struct in_addr inet_makeaddr(in_addr_t net, in_addr_t host);

  - uint32_t (host byte) => struct in_addr

- in_addr_t inet_lnaof(struct in_addr in);
- in_addr_t inet_netof(struct in_addr in);

  - struct in_addr => uint32_t (host byte)

Misc API
--------
- fcntl: manipulate fd
- ioctl: control device
