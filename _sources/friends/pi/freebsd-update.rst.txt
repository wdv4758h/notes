==============
Freebsd Update
==============
``freebsd-update`` 指令可以用來安裝 Patch 以及升級 FreeBSD


安裝 Patch
-----------
::

  # freebsd-update fetch
  # freebsd-update install
  # freebsd-version -k
  $ uname -a


升級 FreeBSD
-------------
::

  # freebsd-update -r 10.3-RELEASE upgrade

若要跳 major 版本號，建議先升級到 major 版的最後一版

接下來基本上按照 prompt 說明即可

::

  # freebsd-update install
  # reboot
  # freebsd-update install

根據說明，有時會需要把 ports 重編以後再 install 一次，請 **務必** 執行

  我在 2016/11/11 從 FreeBSD 10.3 RELEASE 升級至 11.0 RELEASE 時沒有照做，直接 ``freebsd-update install``

  結果 ``sudo`` 就壞掉了
