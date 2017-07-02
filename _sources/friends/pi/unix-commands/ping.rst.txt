========
``ping``
========
* 改變 ``ping`` 的 interval，每 0.1 秒 ``ping`` 一次 ::

    $ ping -i 0.1 x.x.x.x

  - 0.2 秒以下需要 root permission

* 指定從某個 interface 發出封包 ::

    $ ping -I wlan0 x.x.x.x

* 發出 5 個封包後就停止 ::

    $ ping -c 5 x.x.x.x

* flood ::

    $ ping -f localhost

  - 需要 root permission

* 改變 ``ping`` 的封包大小 ::

    $ ping -s 100 x.x.x.x

  - 實際送出的封包會再加上 header 28 bytes
