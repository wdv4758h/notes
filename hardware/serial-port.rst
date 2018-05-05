========================================
Serial Port
========================================


.. contents:: 目錄


介紹
========================================

Serial Port 是用 RS-232 界面來跟裝置溝通，
而 UART 則是讓裝置可以使用
Serial Line （例如 RS-232、RS-485、RS-422）溝通的晶片。



工具
========================================

使用重點：

* 選對 device，例如： ``/dev/ttyUSB0``
* 選對 baud rate，例如： ``115200``


screen
------------------------------

.. code-block:: sh

    sudo screen /dev/ttyUSB0 115200


minicom
------------------------------

.. code-block:: sh

    sudo pacman -S minicom


picocom
------------------------------


moserial
------------------------------

使用 GTK 做的 GUI，畫面簡潔，上下顯示 TX/RX

.. code-block:: sh

    sudo pacman -S moserial
    sudo moserial



參考
========================================

* `Arch Wiki - Working with the serial console <https://wiki.archlinux.org/index.php/working_with_the_serial_console>`_
* `OpenWrt - Serial Console <https://wiki.openwrt.org/doc/hardware/port.serial>`_
* `96board - Setting Up the UART console <https://github.com/96boards/documentation/blob/master/consumer/dragonboard410c/guides/uart-serial-console.md>`_
* `Wikipedia - UART (Universal asynchronous receiver-transmitter) <https://en.wikipedia.org/wiki/Universal_asynchronous_receiver-transmitter>`_
* `Difference between UART, SPI and I2C <https://www.rfwireless-world.com/Terminology/UART-vs-SPI-vs-I2C.html>`_
* `FPGA-based I2C to RS-232 serial converter / bus monitor <https://github.com/jhallen/i2cmon>`_
