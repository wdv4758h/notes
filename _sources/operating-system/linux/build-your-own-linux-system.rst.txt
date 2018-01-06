===================================================
建立自己的 Linux 系統 (Build Your Own Linux System)
===================================================


.. contents:: 目錄


Buildroot
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



Yocto
========================================

:Site: https://www.yoctoproject.org/


介紹
------------------------------

「Yocto 做出的是一個 distribution」

Yocto 支援的平台比 Buildroot 多，
使用的是眾多 recipes，
可以產生出套件系統，
升級時可以只升級特定套件，
但是也可以做出完整的 image。


參考：

* `Yocto Project Quick Start <https://www.yoctoproject.org/docs/current/yocto-project-qs/yocto-project-qs.html>`_
* `Yocto Project Reference Manual <https://www.yoctoproject.org/docs/current/ref-manual/ref-manual.html>`_
* `Yocto - Supported Linux Distributions <http://www.yoctoproject.org/docs/2.4/ref-manual/ref-manual.html#detailed-supported-distros>`_
* `Yocto - CROPS (leverage Docker Containers) <https://www.yoctoproject.org/docs/current/yocto-project-qs/yocto-project-qs.html#qs-crops-build-host>`_
* `Yocto Project Development Tasks Manual <https://www.yoctoproject.org/docs/2.4/dev-manual/dev-manual.html>`_
* `Wikipedia - Yocto Project <https://en.wikipedia.org/wiki/Yocto_Project>`_


musl
------------------------------

musl 支援已經在 ``OE-Core`` 裡面，
不需要額外的 layer，
只需要設定 ``TCLIBC = "musl"``


Clang/LLVM
------------------------------

:Repo: https://github.com/kraj/meta-clang/


Static Build
------------------------------


Bionic
------------------------------



參考
========================================

* [2016] `Deciding between Buildroot & Yocto <https://lwn.net/Articles/682540/>`_
