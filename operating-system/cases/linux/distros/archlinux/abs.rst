========================================
Arch Build System
========================================


.. contents:: 目錄


介紹
========================================

Arch Build System 是一個像 FreeBSD ports tree 結構的系統，
讓使用者可以自己從原始碼編譯出平常用 pacman 安裝的套件。



安裝
========================================

.. code-block:: sh

    sudo pacman -S abs


.. code-block:: sh

    sudo abs    # 利用 rsync 把資料下載到 /var/abs/



使用
========================================

.. code-block:: sh

    cp -r /var/abs/<repo>/<pkgname> ./
    cd <pkgname>/
    makepkg     # 編譯



其他
========================================

設定檔在 ``/etc/abs.conf``



參考
========================================

* `Arch Wiki - Arch Build System <https://wiki.archlinux.org/index.php/Arch_Build_System>`_
