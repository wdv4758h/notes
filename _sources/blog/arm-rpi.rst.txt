:title: ARM - Raspberry Pi
:slug: arm-rpi
:date: 2015-06-13 21:27
:modified: 2015-06-13 21:27
:category: Misc
:tags: ARM, Raspberry Pi
:author: wdv4758h
:summary:

最近因為一些事需要嘗試看看 Raspberry Pi 跑 Computer Vision 相關程式的狀況，
手邊拿到的 Raspberry Pi 是第一代的 Model B，
硬體狀況如下：

* CPU 是單核的 ARM1176JZFS (架構為 ARMv6l) (Broadcom BCM2835 700MHz)，
* RAM 則是 512 MB (CPU、GPU 共用)，
* GPU 為 Broadcom VideoCore IV (250 MHz)。

根據 Wikipedia 上的紀錄，這顆 CPU 的效能大約到 0.041 GFLOPS，
差不多是 1997 ~ 1999 年 300 MHz Pentium II 的效能。
而 GPU 則可以達到 24 GFLOPS，大約為 2001 年的 Xbox。

今年 (2015) Raspberry Pi 有推出了第二代，
Raspberry Pi 2 的 CPU 有升級，GPU 則維持不變，
CPU 變為四核的 ARM Cortex-A7 (架構就變為 ARMv7l) (Broadcom BCM2836 900MHz)，
相比 2012 年推出的第一代，CPU 效能應該有不少的提升。

Installation
========================================

這邊因為本身是 Arch Linux 慣用者，
所以選用了 Arch Linux ARM，
在安裝上官網直接提供 `針對 Raspberry Pi <http://archlinuxarm.org/platforms/armv6/raspberry-pi#qt-platform_tabs-ui-tabs2>`_ 的整個流程

這邊的官方 Installation 會直接把準備好的系統檔案放進去 SD Card，
照著說明做完後，
預設啟動會使用 DHCP 來連網路，
可以在 ``/etc/systemd/network/eth0.network`` 做修改，
預設：

::

    [Match]
    Name=eth0

    [Network]
    DHCP=yes

修改成 static IP (假如想要的話)：(IP 純脆亂設當範例)

::

    [Match]
    Name=eth0

    [Network]
    DNS=8.8.8.8

    [Address]
    Address=202.169.175.123

    [Route]
    Gateway=202.169.175.256


剛裝完的系統很多開發用的工具都沒有，
所以需要的話都要另外裝 XD

Cross Compile
========================================

[Todo]

由於 Raspberry Pi 上面的運算能力沒有很強，
如果想要編譯大量東西時會需要不少時間，
所以開始尋求在一般伺服器 (Intel x86-64 CPU) 上編譯出適合 Raspberry Pi ARM 的執行檔

Raspberry Pi 上面如果有裝 GCC 可以用的話，
可以用以下 command 來看一些優化之不支援：

.. code-block:: sh

    $ gcc -march=native -Q --help=target

這邊也可以從吐出來的訊息中看到可以在 GCC 裡使用 ``-march=armv6zk`` 來針對這顆 CPU 做優化。

Control
========================================

* `Simple Guide to the RPi GPIO Header and Pins <http://www.raspberrypi-spy.co.uk/2012/06/simple-guide-to-the-rpi-gpio-header-and-pins/>`_

Layout (Raspberry Pi GPIO Layout – Revision 2)：

.. image:: /images/rpi/layout-rpi-model-b.png
    :alt: Raspberry Pi GPIO Layout – Revision 2


GPIO
------------------------------

WiringPi
++++++++++++++++++++

`官網 <http://wiringpi.com>`_ 如是說：
"WiringPi is a GPIO access library written in C for the BCM2835 used in the Raspberry Pi."

安裝只要用 git 把 repo clone 下來後執行 script 就可以了：

.. code-block:: sh

    $ git clone git://git.drogon.net/wiringPi
    $ cd wiringPi
    $ ./build

裝完後會出現之後要 compile 相關程式時，
所需要的 linker 參數提示：

::

    NOTE: To compile programs with wiringPi, you need to add:
        -lwiringPi
      to your compile line(s) To use the Gertboard, MaxDetect, etc.
      code (the devLib), you need to also add:
        -lwiringPiDev
      to your compile line(s).

除此之外，也多了一個 command 叫 ``gpio`` ；

.. code-block:: sh

    $ gpio -v
    gpio version: 2.26
    Copyright (c) 2012-2015 Gordon Henderson
    This is free software with ABSOLUTELY NO WARRANTY.
    For details type: gpio -warranty

    Raspberry Pi Details:
      Type: Model B, Revision: 2, Memory: 512MB, Maker: Sony

讀資訊：

.. code-block:: sh

    $ gpio readall
     +-----+-----+---------+------+---+-Model B2-+---+------+---------+-----+-----+
     | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
     +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
     |     |     |    3.3v |      |   |  1 || 2  |   |      | 5v      |     |     |
     |   2 |   8 |   SDA.1 |   IN | 1 |  3 || 4  |   |      | 5V      |     |     |
     |   3 |   9 |   SCL.1 |   IN | 1 |  5 || 6  |   |      | 0v      |     |     |
     |   4 |   7 | GPIO. 7 |   IN | 1 |  7 || 8  | 1 | ALT0 | TxD     | 15  | 14  |
     |     |     |      0v |      |   |  9 || 10 | 1 | ALT0 | RxD     | 16  | 15  |
     |  17 |   0 | GPIO. 0 |   IN | 0 | 11 || 12 | 1 | IN   | GPIO. 1 | 1   | 18  |
     |  27 |   2 | GPIO. 2 |   IN | 0 | 13 || 14 |   |      | 0v      |     |     |
     |  22 |   3 | GPIO. 3 |   IN | 0 | 15 || 16 | 0 | IN   | GPIO. 4 | 4   | 23  |
     |     |     |    3.3v |      |   | 17 || 18 | 0 | IN   | GPIO. 5 | 5   | 24  |
     |  10 |  12 |    MOSI |   IN | 0 | 19 || 20 |   |      | 0v      |     |     |
     |   9 |  13 |    MISO |   IN | 0 | 21 || 22 | 0 | IN   | GPIO. 6 | 6   | 25  |
     |  11 |  14 |    SCLK |   IN | 0 | 23 || 24 | 1 | IN   | CE0     | 10  | 8   |
     |     |     |      0v |      |   | 25 || 26 | 1 | IN   | CE1     | 11  | 7   |
     +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
     |  28 |  17 | GPIO.17 |   IN | 0 | 51 || 52 | 0 | IN   | GPIO.18 | 18  | 29  |
     |  30 |  19 | GPIO.19 |   IN | 0 | 53 || 54 | 0 | IN   | GPIO.20 | 20  | 31  |
     +-----+-----+---------+------+---+----++----+---+------+---------+-----+-----+
     | BCM | wPi |   Name  | Mode | V | Physical | V | Mode | Name    | wPi | BCM |
     +-----+-----+---------+------+---+-Model B2-+---+------+---------+-----+-----+


Physical 是原本 Layout 上的編號，wPi 是 WiringPi 內部用的編號，
在使用 **gpio** 指令時預設是吃 wPi 的編號 (pin)


GPIO 的模式：

.. table::
    :class: table table-bordered

    +-------+---------+
    | Mode  | Display |
    +=======+=========+
    | in    | IN      |
    +-------+---------+
    | out   | OUT     |
    +-------+---------+
    | pwm   | ALT5    |
    +-------+---------+
    | clock |         |
    +-------+---------+
    | up    |         |
    +-------+---------+
    | down  |         |
    +-------+---------+

模式切換 :

.. code-block:: sh

    $ gpio mode <pin> <mode>

* `The GPIO utility <http://wiringpi.com/the-gpio-utility/>`_

Camera Module
------------------------------

* `Camera Module - Raspberry Pi <https://www.raspberrypi.org/products/camera-module/>`_

Raspberry Pi 的 Camera Module 可用在 Raspberry Pi 和 Raspberry Pi 2，
支援到 1080p30、720p60、VGA90

Python 上控制 Raspberry Pi camera module 的 library 常見的為 `picamera <http://picamera.readthedocs.org>`_

Performance Testing
========================================

目前只先拿了 OpenCV 的 Image Stitching 範例來跑看看，
實際的東西放在這邊 `[GitHub] wdv4758h/image_stitching <https://github.com/wdv4758h/image_stitching>`_ ，
測資為 images 資料夾裡的 A001.jpg ~ A003.jpg，
"OpenCV 2.4 sample" 在我的筆電上跑 (Intel i5-3210M) 大約需要 1.5 秒，
在 Raspberry Pi 上面則大約需要 81 秒。

之後應該要看能不能利用 GPU 來跑快一點 ~"~

Reference
========================================

* `Raspberry Pi | Arch Linux ARM <http://archlinuxarm.org/platforms/armv6/raspberry-pi>`_
* `讓你的 Raspberry Pi 透過 GPIO 閃爍 LED 燈  <http://coldnew.github.io/blog/2013/06/27_1aced.html>`_
    - 用純 C 控制 GPIO，不依靠 library
