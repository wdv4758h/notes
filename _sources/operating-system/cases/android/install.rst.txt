========================================
安裝新 Android
========================================


步驟
========================================

TWRP
------------------------------

.. code-block:: sh

    $ fastboot flash boot twrp-3.0.2-0-nozomi.img

    $ fastboot reboot
    # or $ adb reboot recovery

    # 選擇 Advanced -> ADB Sideload
    #
    # * click clean dalvik-cache
    # * click clean cache
    # * swipe to start sildeload mode

    $ adb sideload nAOSProm-6.0-b10.zip     # 也可以在 TWRP 的 Install 選手機上的 zip
    $ adb reboot


sideload & reboot
------------------------------

.. code-block:: sh

    $ adb reboot sideload-auto-reboot



升到 Android 6.0
========================================

重新切割並使用 F2FS

* `nAOSProm for Xperia S <http://forum.xda-developers.com/showpost.php?p=65233973&postcount=3797>`_



參考
========================================

* `TeamWin - TWRP <https://twrp.me/>`_
* `The Open GApps Project <http://opengapps.org/>`_
* `SuperSU <https://forum.xda-developers.com/apps/supersu>`_
* `Xposed <https://forum.xda-developers.com/xposed>`_
