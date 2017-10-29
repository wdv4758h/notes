========================================
libhybris
========================================


.. contents:: 目錄


介紹
========================================

.. image:: /images/android/libhybris.png


Android 系統雖然是從 Linux kernel 分出去改的，
但是系統上跟常見的 Linux 系統差異很多，
例如系統上的 libc 不是常見的 GNU libc 而是 Bionic。
而相關的硬體驅動都會透過 Android HAL 層來抽象化，
所以 Android 上的 Driver 通常不能直接放到一般 Linux 系統上使用。

假如我們想要借用目前已經有的 Android Driver 來跑我們一般的 Linux，
有兩種方法：

* 在 Android 系統上建立類似一般 Linux 的開發環境
* 在一般 Linux 環境下利用 libhybris 來使用 Android 上的 Driver


libhybris 基本上是一個客製化版本的 Bionic linker，
其中會 hook Bionic 的 symbols，
抽換成 GNU libc 的 symbols，
藉此來跑在 GNU libc 上。


編譯：

.. code-block:: sh

    git clone https://github.com/libhybris/libhybris
    cd libhybris/hybris
    git clone https://github.com/Halium/android-headers/ -b halium-7.1
    # change options for your need
    ./autogen.sh \
        --prefix=/opt/libhybris \
        --build=aarch64-linux-gnu \
        --host=aarch64-linux-gnu \
        --target=aarch64-linux-gnu \
        --with-android-headers=android-headers \
        --enable-adreno-quirks \
        --enable-arch=arm64 \
        --enable-experimental \
        --with-default-hybris-ld-library-path=/vendor/lib:/system/lib
    make -j
    make install


裝完後會有一些測試程式在 ``bin`` 資料夾裡，
可以執行測試看看。



參考
========================================

* `Ubuntu Touch Internals <https://elinux.org/images/c/cf/Ubuntu_Touch_Internals_1.pdf>`_

* `Halium Project - unify the Hardware Abstraction Layer for projects which run GNU/Linux on mobile devices with pre-installed Android <https://halium.org/>`_
    - [GitHub] `Halium - GNU/Linux for Android devices <https://github.com/halium/>`_
    - `Android 7.1 Headers <https://github.com/Halium/android-headers/tree/halium-7.1>`_
    - `libhybris for Android 7.1 <https://github.com/halium-packaging/libhybris/tree/halium-7.1>`_

* `Sailfish OS - True Independent Mobile OS <https://sailfishos.org/>`_
    - [GitHub] `Sailfis OS <https://github.com/sailfishos>`_
    - `SailfishOS - Architecture <https://sailfishos.org/wiki/Architecture>`_
    - `SailfishOS - Hardware Adaptation Development Kit <https://sailfishos.org/wiki/Hardware_Adaptation_Development_Kit>`_
    - [GitHub] `mer-hybris <https://github.com/mer-hybris>`_
    - `Mer - a mobile Linux distribution <https://mer-project.blogspot.tw/>`_

* `Boot2efl <https://phab.enlightenment.org/w/boot2efl/>`_
    - LibHybris has been developped by Sailfish OS's team and is used in the Jolla Phone. It's also used by Canonical to get Ubuntu Phone running on different kind of hardware. We also found this technology in LuneOS (formerly WebOS)
