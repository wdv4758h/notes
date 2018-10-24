========================================
Buildroot
========================================


.. contents:: 目錄


介紹
========================================

:Repo: https://github.com/buildroot/buildroot
:Site: https://buildroot.org/


「Buildroot 做出的是一個 root filesystem image」

Buildroot 維護一系列設定來編譯各個專案，
使用 menuconfig 做選擇，
最後做出很小的 rootfs。

跟 Yocto 比起來編譯比較快，
結果通常比較小，
但是支援的套件比 Yocto 少，
也不支援做出數個套件。



.. code-block:: sh

    make menuconfig
    # 選擇要的 toolchain、架構、系統、套件

    make -j8

    ls output/images


* `文件 <https://www.buildroot.net/docs.html>`_
