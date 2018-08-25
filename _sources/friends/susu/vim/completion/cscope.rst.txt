Cscope note
===========

cscope CLI options
------------------

generate file ``cscope.out`` at local directory.

Basic Usage

- ``find . -name "*.h" -o -name "*.c" -o -name "*.cpp" > cscope.files``
- ``cscope -Rbkq cscope.files``

More

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

Trouble Shooting
----------------

- use the cscope in the project we are developing.

  - we update code after we generate cscope database.
  - howto?

      當你的 source code 有改變或是新增加檔案,
      你就要將新增加的檔案加入到 cscope.files (步驟3),
      然後再次重新 build 你的 database(步驟4).

      參考: https://hamisme.blogspot.tw/2013/11/using-cscope-on-large-projects.html

