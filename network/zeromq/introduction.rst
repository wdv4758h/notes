========================================
ØMQ (ZeroMQ)
========================================


.. contents:: 目錄


介紹
========================================

ZeroMQ 是一個 asynchronous messaging library，
設計來用於 distributed 或 concurrent 的應用，
並且不需要額外開專門的程式來處理，
訊息處理可以直接整合在既有的程式中。

ZeroMQ API 會提供 ``socket`` 來使用，
``socket`` 是傳統 IP 或 Unix domain socket 的抽象化，
支援多對多的傳輸。


Transport 種類：

* inproc (in-process (inter-thread) communication)
    - ``inproc://#1``
    - ``inproc://my-endpoint``
    - 直接使用記憶體在各個 threads 之間溝通
* ipc (inter-process communication)
    - ``ipc:///tmp/feeds/0``
    - 使用 UNIX domain socket
* tcp (unicast)
    - bind
        + ``tcp://127.0.0.1:5555``
        + ``tcp://*:5555``
        + ``tcp://eth0:5555``
    - connect
        + ``tcp://192.168.1.1:5555``
        + ``tcp://server1:5555`` (DNS)
* pgm, epgm (multicast)
    - ``epgm://eth0;239.192.1.1:5555``
    - ``pgm://192.168.1.1;239.192.1.1:5555``


基本模式：

* Request/Reply
* Publish/Subscribe
* Push/Pull (pipeline)
* Exclusive Pair

不同模式具有不同的網路拓樸，
例如 Request/Reply 定義了「service bus」、
Publish/Subscribe 定義了「data distribution tree」、
Push/Pull 定義了「parallelised pipeline」。

ZeroMQ 內部具有自己的 threading model，
還有一些自動的 message batching 機制（例如多筆資料一起送），
藉此達到比傳統 TCP 更好的 throughput。

ZeroMQ 底下實做了 ZMTP (ZeroMQ Message Transfer Protocol)，
定義了各種互相溝通的機制、安全保護、連線資訊等等。



模式
========================================

PAIR
------------------------------

Client/Server
------------------------------

Publish/Subscribe
------------------------------

Pull/Push
------------------------------



各語言整合
========================================

C++
------------------------------

* `cppzmq <https://github.com/zeromq/cppzmq>`_
    - 已經在 Arch Linux 上預設裝起來的 ØMQ 裡
* `zmqpp <https://github.com/zeromq/zmqpp>`_
    - 預設裝起來沒有
* `azmq <https://github.com/zeromq/azmq>`_
    - 接 Boost Asio
* `CpperoMQ <https://github.com/jship/CpperoMQ>`_


Python
------------------------------

* `pyzmq <https://github.com/zeromq/pyzmq>`_
* `aiozmq <https://github.com/aio-libs/aiozmq>`_
    - pyzmq + asyncio



範例
========================================

Socket 建立
------------------------------

Socket 參數調整
------------------------------

Socket reset
------------------------------


參考
========================================

* `Wikipedia - ØMQ <https://en.wikipedia.org/wiki/%C3%98MQ>`_
* `O'Reilly Media - ZeroMQ <http://shop.oreilly.com/product/0636920026136.do>`_
