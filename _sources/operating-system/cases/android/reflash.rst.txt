========================================
重刷 Android 版子
========================================


.. contents:: 目錄


步驟
========================================

.. code-block:: sh

    # 重開進 fastboot 模式
    adb reboot-bootloader

    # 刷掉 userdata
    fastboot erase userdata
    fastboot flash userdata userdata.img

    # 刷掉 system
    fastboot erase system
    fastboot flash system system.img

    # 刷掉 boot
    fastboot erase boot
    fastboot flash boot boot.img

    # 重開進系統
    fastboot reboot


用 CLI 設定無線網路：

.. code-block:: sh

    # 方法一：先寫好 wpa_supplicant.conf
    adb push wpa_supplicant.conf /data/misc/wifi/
    adb shell svc wifi enable

    # wpa_supplicant.conf sample:
    #
    #   update_config=1
    #   ctrl_interface=/data/misc/wifi/sockets
    #   eapol_version=1
    #   ap_scan=1
    #   fast_reauth=1
    #   network={
    #       ssid="your_wifi_ssid"
    #       psk="your_wifi_password"
    #       key_mgmt=WPA-PSK
    #       priority=241
    #   }
    #

    # 方法二：用 wpa_cli
    adb shell svc wifi enable
    adb shell
    $ wpa_cli
    > add_network
    > set_network 0 ssid "your_wifi_ssid"
    > set_network 0 psk "your_wifi_password"
