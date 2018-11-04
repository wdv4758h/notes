========================================
LDAC codec
========================================


.. contents:: 目錄


介紹
========================================

LDAC 是 Sony 在 2015 年開始大量使用的 audio codec，
針對藍牙的使用環境做優化，
最高支援 990 kbit/s 24bit/96khz。

LDAC 是有損壓縮（Lossy），
採用基於 MDCT (Modified Discrete Cosine Transform) 的混合式編碼來提供更有效率的壓縮，
主要競爭者是 Qualcomm 的 aptX-HD。

自 Android 8.0 Oreo 開始，
來自 Sony 的 libldac 以 Apache 條款釋出，
LDAC 的支援被加入 AOSP 專案中。



實做
========================================

* `libldac (encoder only) <https://android.googlesource.com/platform/external/libldac/>`_



PulseAudio 支援
========================================

目前 PulseAudio 的官方 Bluetooth module 還沒有支援，
但是第三方的已經有支援了。

.. code-block:: sh

    # https://github.com/EHfive/ldacBT
    # https://github.com/EHfive/pulseaudio-modules-bt

    # 編譯 libldac
    $ git clone https://aur.archlinux.org/libldac.git
    $ cd libldac
    $ makepkg
    $ sudo pacman -U libldac-*.pkg.tar.xz

    $ cd ..

    # 編譯 PulseAudio Bluetooth module
    $ git clone https://aur.archlinux.org/pulseaudio-modules-bt-git.git
    $ makepkg
    $ sudo pacman -U pulseaudio-modules-bt-git-*.pkg.tar.xz

    # 殺掉現在的 PulseAudio，讓他重開
    $ pulseaudio -k

    # 重新連上藍牙裝置
    $ bluetoothctl connect FF:FF:FF:FF:FF:FF

    # 檢查使用的 codec
    $ pactl list sinks | rg -e bluez -e a2dp_codec
        Name: bluez_sink.FF_FF_FF_FF_FF_FF.a2dp_sink
        Driver: module-bluez5-device.c
        Monitor Source: bluez_sink.FF_FF_FF_FF_FF_FF.a2dp_sink.monitor
          bluetooth.a2dp_codec = "LDAC"     # <----- 使用 LDAC !
          device.api = "bluez"
          bluez.path = "/org/bluez/hci0/dev_FF_FF_FF_FF_FF_FF"
          bluez.class = "0x240414"
          bluez.alias = "SRS-XB30"



ALSA 支援
========================================

* `bluez-alsa - LDAC issue <https://github.com/Arkq/bluez-alsa/issues/104>`_
    - `bluez-alsa wiki - LDAC <https://github.com/Arkq/bluez-alsa/wiki/Installing-libldac-library>`_



參考
========================================

* `Sony - LDAC <https://www.sony.net/Products/LDAC/>`_
* `Wikipedia - LDAC (codec) <https://en.wikipedia.org/wiki/LDAC_(codec)>`_
* `Wikipedia - Bluetooth stack <https://en.wikipedia.org/wiki/Bluetooth_stack>`_
* `Wikipedia - List of Bluetooth protocols <https://en.wikipedia.org/wiki/List_of_Bluetooth_protocols>`_
* `Wikipedia - High-resolution audio <https://en.wikipedia.org/wiki/High-resolution_audio>`_
* `AOSP - libldac <https://android.googlesource.com/platform/external/libldac>`_
