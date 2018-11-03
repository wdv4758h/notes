========================================
Bluetooth
========================================


.. contents:: 目錄


Arch Linux
========================================

.. code-block:: sh

    $ sudo pacman -S bluez bluez-tools
    $ sudo pacman -S pulseaudio-bluetooth

    $ modprobe btusb
    $ sudo systemctl start bluetooth

    $ pulseaudio -k
    $ pulseaudio --start

    $ bluetoothctl
    # select your bluetooth MAC
    [bluetooth]# select FF:FF:FF:FF:FF:FF
    [bluetooth]# power on
    [bluetooth]# devices
    [bluetooth]# scan on
    # pair your target MAC
    [bluetooth]# pair EE:EE:EE:EE:EE:EE
    [bluetooth]# trust EE:EE:EE:EE:EE:EE
    [bluetooth]# connect EE:EE:EE:EE:EE:EE


.. code-block:: sh

    $ sudo pacman -S blueman
    $ blueman-applet



選擇 Profile
========================================

.. code-block:: sh

    $ pacmd list-cards

    $ pacmd set-card-profile <id> <profile>
    $ pacmd set-card-profile <tab> <tab>
    $ pacmd set-card-profile 4 a2dp_sink
    $ pacmd set-card-profile 4 headset_head_unit
    $ pacmd set-card-profile 4 off



參考
========================================

* `Wikipedia - Bluetooth <https://en.wikipedia.org/wiki/Bluetooth>`_
* `Arch Wiki - Bluetooth <https://wiki.archlinux.org/index.php/bluetooth>`_
