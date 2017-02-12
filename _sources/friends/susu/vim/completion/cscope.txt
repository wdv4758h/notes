generate file ``cscope.out`` at local directory.

- ``find . -name "*.h" -o -name "*.c" -o -name "*.cpp" > cscope.files``
- ``cscope -Rbkq cscope.files``

- ``-F<symfile>``: symbol file (symbol reference line)
- ``-f<reffile>``: use ``<reffile>`` instead of ``cscope.out``
- ``-I<include_dir>``


Vim and cscope
--------------
* vim use cscope in line-oriented mode

http://vimhelp.appspot.com/if_cscop.txt.html

::

    $ cscope -dl -f cscope.out
    >> 1socks4_service
    cscope: 1 lines
    src/socks4d.cpp socks4_service 103 void socks4_service(socketfd_t client_socket, SocketAddr& client_addr){
    >> 0socks4_service
    cscope: 3 lines
    src/socks4d.cpp <global> 39 void socks4_service(socketfd_t client_socket, SocketAddr& client_addr);
    src/socks4d.cpp main 65 start_multiprocess_server(sock4_listen_socket, socks4_service);
    src/socks4d.cpp socks4_service 103 void socks4_service(socketfd_t client_socket, SocketAddr& client_addr){
    >> q

    # 1 is find definition, and 0 is find symbol

