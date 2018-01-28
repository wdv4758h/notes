========================================
iperf - TCP/UDP/SCTP 網路效能測量
========================================


.. contents:: 目錄


介紹
========================================

`iperf <https://github.com/esnet/iperf>`_ 是一套測試網路狀況的工具，
可以用來觀察不同情況下的 packet loss。



使用
========================================

Server:

.. code-block:: sh

    iperf3 -s


Client:

.. code-block:: sh

    # -R: client 送，server 收
    iperf3 -c $IP -p $PORT -u -b 1M -w 1M -t 180

    # -R: server 送，client 收
    iperf3 -c $IP -p $PORT -u -b 1M -w 1M -t 180 -R
