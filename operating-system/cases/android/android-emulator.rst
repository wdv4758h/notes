========================================
Android Emulator
========================================


.. contents:: 目錄


goldfish
========================================

goldfish 是 QEMU 裡用來模擬 Android 系統的 virtual hardware 家族名稱，
一開始只有 ARM 架構，後來有 porting 到 x86 和 MIPS virutal CPUs。

* `QEMU - GOLDFISH-VIRTUAL-HARDWARE.TXT <https://android.googlesource.com/platform/external/qemu/+/master/docs/GOLDFISH-VIRTUAL-HARDWARE.TXT>`_



Android SDK - Android Emulator
========================================

* `Android SDK - Emulator <http://developer.android.com/tools/help/emulator.html>`_
* `How do I launch the Android emulator from the command line? <http://stackoverflow.com/questions/4974568/how-do-i-launch-the-android-emulator-from-the-command-line>`_

.. code-block:: sh

    $ ./android list targets
    Available Android targets:
    $ ./android list avd
    Available Android Virtual Devices:


Genymotion
========================================

* `Genymotion <https://www.genymotion.com/>`_
* `codepath/android_guides - Genymotion 2.0 Emulators with Google Play support <https://github.com/codepath/android_guides/wiki/Genymotion-2.0-Emulators-with-Google-Play-support>`_


Genymotion 後面會接 VirtualBox 來運作


Installation
------------------------------

.. code-block:: sh

    $ yaourt -S genymotion


Usage
------------------------------

開啟 GUI，登入帳號，選擇 device 後會開始下載檔案

.. code-block:: sh

    $ genymotion


BlueStacks
========================================

Manymo
========================================

* `Manymo <https://www.manymo.com/>`_

in-browser Android emulators for embedding apps in websites
