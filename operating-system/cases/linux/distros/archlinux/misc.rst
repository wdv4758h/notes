========================================
Misc
========================================


.. contents:: 目錄


X11 - "cannot open display" after suspend/resume
================================================

問題：

.. code-block:: sh

    $ xrandr
    Invalid MIT-MAGIC-COOKIE-1 keyCan't open display :0


原因為機器上沒有設定 hostname，
而網路重新連接後（通常是 Wifi）更換了 hostname，
重新設定 hostname 即可。


解法：

.. code-block:: sh

    # 檢查授權的 hostname
    $ xauth list

    $ sudo hostname ...
