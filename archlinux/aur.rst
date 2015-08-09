========================================
Arch Linux Arch User Repository
========================================

注意事項： `Arch packaging standards <https://wiki.archlinux.org/index.php/Arch_packaging_standards>`_

在 AUR 上，每個 commit 階段裡面都必須有 .SRCINFO 存在，所以如果一開始沒有加 .SRCINFO 的話，
後面要 rebase 回去補上後才可以送到 AUR (不然會被 reject)

一個 package 最少會有：

1. PKGBUILD
2. .SRCINFO (可用 ``mksrcinfo`` 來從 PKGBUID 生出)

.SRCINFO
========================================

.. code-block:: sh

    # Tools for generating .AURINFO files and PKGBUILD data extraction

    $ sudo pacman -S pkgbuild-introspection
    $ mksrcinfo   # generate .SRCINFO from PKGBUILD

Submit
========================================

要上傳到 AUR 需要先生個上傳 AUR 用的 SSH key：

.. code-block:: sh

    $ ssh-keygen -t rsa -b 4096 -C "yourmail@domain"
    ...

登入 AUR 後，在帳號資訊那邊把 public key 加上去


(Optional) 接下來可以對 OpenSSH 做設定

``~/.ssh/config`` ::

    Host aur
        HostName aur.archlinux.org
        User aur
        IdentityFile ~/.ssh/aur

最後在要上傳的 repo 裡直接用想上傳的 package name 來 push

.. code-block:: sh

    $ git push ssh://aur/PACKAGE_NAME.git
