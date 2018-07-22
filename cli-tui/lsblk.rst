========================================
lsblk - 顯示裝置資訊
========================================


.. contents:: 目錄


範例
========================================

.. code-block:: sh

    $ lsblk
    NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
    sda      8:0    0 119.2G  0 disk
    ├─sda1   8:1    0   511M  0 part /boot
    ├─sda2   8:2    0     3G  0 part [SWAP]
    └─sda3   8:3    0 115.8G  0 part /


.. code-block:: sh

    $ lsblk -o MODEL,NAME,FSTYPE,LABEL,MOUNTPOINT,SIZE
    MODEL           NAME   FSTYPE LABEL MOUNTPOINT   SIZE
    VENDOR SSD CM87 sda                            119.2G
                    ├─sda1 vfat         /boot        511M
                    ├─sda2 swap         [SWAP]         3G
                    └─sda3 ext4         /          115.8G
