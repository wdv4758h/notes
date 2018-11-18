============================================
ICE (Interactive Connectivity Establishment)
============================================


.. contents:: 目錄


介紹
========================================

ICE 是一個 P2P 的 protocol，
目的是尋找出可以建立連線的路徑，
裡頭利用了先前已經存在的 STUN 和 TURN。


連線種類：

0. IP 直接連線
    - 如果雙方都在外網或是雙方在同一個內網
1. STUN
    - 如果雙方在不同內網，而且不是 Symmetric NAT
2. TURN
    - 如果雙方在不同內網，而且是 Symmetric NAT
    - 透過 TRUN 伺服器轉送（Relay）
3. STUN/TURN over TCP
    - 某些公司會擋掉 UDP 封包，此時就要把東西都跑在 TCP 上


速度衡量有兩種：

* Delay：連線建起來所需的時間
* Latency：連線建起之後，封包傳需所需的時間



Trickle ICE
========================================

Trickle ICE 的目的是要解決 ICE 處理太慢的問題，
先前 ICE candidate 要全部蒐集完成才能跟對方交換，
為了盡可能地迅速建立連線，
Trickle ICE 會在新取得一個 ICE candidate 時就馬上跟對方交換，
有新的候選人就再交換一次，
藉此讓連線可以盡早開始處理，
以提升連線速度。



加速連線建立
========================================

ICE 在嘗試各個路徑需要不少時間，
狀況差一點可能會花超過十幾秒。
對於這種狀況的解法其中一部分是使用 Trickle ICE，
Trickle ICE 可以在所有 ICE 嘗試完之前就先建立可以用的連線，
但是這仍然需要時間，
所以常見作法是先使用 TURN 傳輸（TURN first），
同時進行 ICE 去尋找可替代方案，
如果找到 P2P 的路徑就轉換過去。



libnice
========================================

:Repo: https://github.com/libnice/libnice


測試程式：

* simple-example


.. code-block:: sh

    $ stunbdc -4 stun1.l.google.com 19302
    Server address: 173.194.202.127 port 19302
    Mapped address: 114.44.38.52 port 34733

    $ stund



參考
========================================

* `PJNATH - Open Source ICE, STUN, and TURN Library <https://github.com/pjsip/pjproject/tree/master/pjnath>`_
* `coturn - TURN + STUN server <https://github.com/coturn/coturn>`_
* `MDN - RTCPeerConnection <https://developer.mozilla.org/en-US/docs/Web/API/RTCPeerConnection>`_
