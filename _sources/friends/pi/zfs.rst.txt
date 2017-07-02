========
ZFS 筆記
========

概念
----

* ``zpool`` 指令可以把硬碟/檔案做成 zfs 硬碟
* ``zfs`` 指令可以產生 Volume、做 snapshot
* 在 FreeBSD 上要先啟動這個服務 ::

    zfs_enable="YES"

指令用法
--------

* 產生一個 zpool，裡面包含一個用 ``/dev/da1`` 和 ``/dev/da2`` 產生的 mirror::

    # zpool status
    # zpool create my_pool mirror /dev/da1 /dev/da2
    # df -h
    # zpool status
    # zfs list -t all

  - 似乎會自動產生一個 zfs 在裡面

* 對某個 zfs 做 snapshot ::

    # zfs snapshot my_pool@snapshot1

  - snapshot 的名稱格式要固定，不過裡面的名稱可以自己取

* rollback ::

    # zfs rollback my_pool@snapshot1
