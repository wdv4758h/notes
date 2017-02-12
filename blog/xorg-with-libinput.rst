:title: Xorg with libinput as driver
:slug: xorg-with-libinput-as-driver
:date: 2015-01-24 21:21
:modified: 2015-01-24 21:21
:category: Linux
:tags: Linux, Xorg, libinput
:author: wdv4758h
:summary:

libinput
========================================

這是 Xorg 上的 Input Stack :

.. image:: /images/linux/x-input-stack.png
    :alt: Xorg Input Stack

這是 Wayland 上的 Input Stack :

.. image:: /images/linux/wayland-input-stack.png
    :alt: Wayland Input Stack

Xorg 上的 Input Stack 有以下問題

* Features distributed across modules
* No communication between modules
* Impossible to test
* Lots of user-exposed options

driver feature 比對

.. table::
    :class: table table-bordered

    +------------------+-------+-----------+-------+
    | Feature          | evdev | synaptics | wacom |
    +==================+=======+===========+=======+
    | Tapping          | no    | yes       | yes   |
    +------------------+-------+-----------+-------+
    | MB emulation     | yes   | yes       | no    |
    +------------------+-------+-----------+-------+
    | Gestures         | no    | no        | yes   |
    +------------------+-------+-----------+-------+
    | Finger Scrolling | no    | yes       | some  |
    +------------------+-------+-----------+-------+
    | Calibration      | yes*  | no*       | yes*  |
    +------------------+-------+-----------+-------+

(* means server provides some calibration on top)

為了讓 Wayland 的 compositor 能有共通的 input stack 實作，
所以獨立出了 libinput 來解決問題，
libinput 把很多內部的東西都處理掉 (藏起來)，
有著以下特色 :

* multiple backends, but not exposed to the users
* struct udev* in, devices out
* only the configuration options that make sense
* everything else is handled based on the hardware


Touchpad features (normal):

* proper multitouch support
* top and bottom software button on clickpads
* two-finger scrolling
* 1/2/3-finger tapping
* clickfinger on Apple touchpads
* palm detection


Touchpad features (exotic):

* re-routing of T440 software buttons through trackstick
* trackstick wheel emulation on T440
* smart disabling of the touchpad
* auto-scaling of the top software buttons
* disable touchpad while using the trackstick
* normalized pointer acceleration


A useful test suite

* tests multiple devices automatically
* uinput based
* tests without a compositor

Future plans (non-obvious):

* "buttonbox" interface/gamepads
* raw/unaccelerated mouse input
* device identification system
* touchpad handwriting
* touchpad gestures

近況
========================================

libinput 最近發展的漸漸成熟，在 2015-01-15 釋出了 0.8 版，
Fedora 22 也要把 Xorg 底下的 input driver 換成使用 libinput (xf86-input-libinput)，
目前 xf86-input-libinput 在 AUR 裡，不過相信未來應該會進 official repositories。

Users
========================================

在 Arch Linux 上，要把 Xorg 底下的 input driver 換成 libinput 的話，
先去 AUR 裝 ``xf86-input-libinput`` ，
接著就可以在 Xorg 的設定檔裡選擇 ``libinput`` 當 driver，
不過要注意的是，一些 Options 會不一樣，所以設定要調整過，
例如 :

原本 ::

    # xorg.conf.d/50-synaptics.conf

    # Original

    Section "InputClass"
      Identifier "enable tapping"
      MatchProduct "my touchpad"
      Driver "synaptics"
      Option "TapButton1" "1"
    EndSection

後來 ::

    # xorg.conf.d/50-synaptics.conf

    # libinput version

    Section "InputClass"
      Identifier "enable tapping"
      MatchProduct "my touchpad"
      Driver "synaptics"
      Option "TapButton1" "1"
    EndSection

這邊注意到，之前是把 driver assign 給 device，接著設定 options，
後來 libinput 的版本是 match 到一個 driver。

Reference
========================================

* `Consolidating the input stacks with libinput <http://www.x.org/wiki/Events/XDC2014/XDC2014HuttererLibInput/xdc-2014.html>`_
* `XDC2014: Peter Hutterer - Consolidating the input stacks with libinput <https://www.youtube.com/watch?v=vxhdba4RS8s>`_
* `Replacing Xorg input-drivers with libinput <https://fosdem.org/2015/schedule/event/libinput/>`_
* `libinput - a common input stack for Wayland compositors and X.Org drivers <http://who-t.blogspot.tw/2014/09/libinput-common-input-stack-for-wayland.html>`_
* `xf86-input-libinput compatibility with evdev and synaptics <http://who-t.blogspot.tw/2015/01/xf86-input-libinput-compatibility-with.html>`_
* `Fedora - Changes/LibinputForXorg <https://fedoraproject.org/wiki/Changes/LibinputForXorg>`_
* `libinput documentation <http://wayland.freedesktop.org/libinput/doc/latest/pages.html>`_
* `Freedesktop.org - xf86-input-libinput <http://cgit.freedesktop.org/xorg/driver/xf86-input-libinput/>`_
