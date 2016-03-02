========================================
Intel Clear Linux
========================================

* `Clear Linux <https://clearlinux.org/>`_
* `Clear Linux - Downloads <https://download.clearlinux.org/image/>`_
    - 有好幾個用 xz 壓縮過的 image，載下來後解壓縮
    - 載下來上面提供的 UEFI 檔案 (``OVMF.fd``) 跟執行 QEMU 的 shell script (``start_qemu.sh``)
    - ``start_qemu.sh clear-xxxx-kvm.img``
* Install Software
    - ``swupd bundle-add XXX``
        + ``swupd bundle-add python-basic`` for Python 3
    - ``swupd update``
    - `Bundles overview <https://clearlinux.org/documentation/bundles_overview.html>`_
* `LWN - An introduction to Clear Containers <http://lwn.net/Articles/644675/>`_
