========================================
file - 檢查檔案種類
========================================


.. contents:: 目錄


範例
========================================

* `[GitHub] file/file <https://github.com/file/file>`_

.. code-block:: sh

    $ file --version
    file-5.24
    magic file from /usr/share/file/misc/magic


.. code-block:: sh

		$ file /usr/bin/file
		/usr/bin/file: ELF 64-bit LSB pie executable x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=e5ee84aad451e144bb06804743c1cd88a957d44e, stripped


處理 device files：

.. code-block:: sh

    $ sudo file /dev/sda
		/dev/sda: block special (8/0)

    $ sudo file -s /dev/sda
    /dev/sda: DOS/MBR boot sector; partition 1 : ID=0xee, start-CHS (0x0,0,1), end-CHS (0x3ff,254,63), startsector 1, 250069679 sectors, extended partition table (last)

    $ sudo file -s /dev/sda1
    /dev/sda1: DOS/MBR boot sector, code offset 0x58+2, OEM-ID "mkfs.fat", sectors/cluster 8, Media descriptor 0xf8, sectors/track 63, heads 255, hidden sectors 2048, sectors 1046528 (volumes > 32 MB), FAT (32 bit), sectors/FAT 1020, reserved 0x1, serial number 0x35c23725, unlabeled
