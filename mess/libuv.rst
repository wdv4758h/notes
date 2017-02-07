========================================
libuv
========================================

+------------+--------+
| OS         | API    |
+============+========+
| Linux      | epoll  |
+------------+--------+
| BSD family | kqueue |
+------------+--------+
| Windows    | IOCP   |
+------------+--------+



libevent
========================================

libevent 和 libev 和 libuv 三者中歷史最悠久的 library，
於 2002 年開始開發，
對各個 event 提供 callback function 的機制來進行處理。

使用者：

* Google Chrome
* Memcached
* Transmission
* ntpd
* Tor



libev
========================================

libuv
========================================

libuv 原先是為了設計給 Node.js 用的一個 C library，
一開始是 libev 的 wrapper，
因為當時 libev 不支援 Windows 的 IOCP (Windows 上類似 epoll、kqueue 的機制)，
後來拿掉 libev 這個 dependency 成為獨立的跨平台 asychronous I/O library，
後續增加一些抽象化跟功能，
例如 threads、threadpools、inter-thread communication。

使用者：

* Node.js
* Julia
* Luvit (Asynchronous I/O for Lua)
* pyuv
* Neovim
* ...



Reference
========================================

* `Wikipedia - libuv <https://en.wikipedia.org/wiki/Libuv>`_
* `[GitHub] libuv/libuv <https://github.com/libuv/libuv/>`_
* `unix: remove libev <https://github.com/joyent/libuv/issues/485>`_
    - libuv 去除 libev 的一些原因
* `How does libuv compare to Boost/ASIO? <http://stackoverflow.com/questions/11423426/how-does-libuv-compare-to-boost-asio>`_
    - 提供了非常詳細的比較
