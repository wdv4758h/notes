========================================
Yocto
========================================


.. contents:: 目錄


介紹
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


.. code-block:: sh

    . ./oe-init-build-env
    cp meta-poky/conf/bblayers.conf.sample conf/bblayers.conf

    # conf/local.conf



musl
------------------------------

musl 支援已經在 ``OE-Core`` 裡面，
不需要額外的 layer，
只需要設定 ``TCLIBC = "musl"``


meta/recipes-core/musl/


Clang/LLVM
------------------------------

:Repo: https://github.com/kraj/meta-clang/


git clone git://github.com/kraj/meta-clang.git

# conf/bblayers.conf
BBLAYERS ?= " \
  /home/kraj/openembedded-core/meta-clang \
  /home/kraj/openembedded-core/meta \
  "

TOOLCHAIN ?= "clang"


Static Build
------------------------------


Bionic
------------------------------

Yocto for Android
------------------------------



參考
================================================================================

* `Yocto Project Quick Start <https://www.yoctoproject.org/docs/current/yocto-project-qs/yocto-project-qs.html>`_
* `Yocto Project Reference Manual <https://www.yoctoproject.org/docs/current/ref-manual/ref-manual.html>`_
* `Yocto - Supported Linux Distributions <http://www.yoctoproject.org/docs/2.4/ref-manual/ref-manual.html#detailed-supported-distros>`_
* `Yocto - CROPS (leverage Docker Containers) <https://www.yoctoproject.org/docs/current/yocto-project-qs/yocto-project-qs.html#qs-crops-build-host>`_
* `Yocto Project Development Tasks Manual <https://www.yoctoproject.org/docs/2.4/dev-manual/dev-manual.html>`_
* `Wikipedia - Yocto Project <https://en.wikipedia.org/wiki/Yocto_Project>`_
