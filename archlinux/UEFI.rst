========================================
UEFI
========================================


QEMU with UEFI
========================================

先從 `TianoCore <http://www.tianocore.org/ovmf/>`_ 下載提供給 QEMU 的 smaple UEFI firmware，
載下來後會獲得一個叫 ``OVMF.fd`` 的檔案，
接著在開啟 QEMU 時加上參數指定使用這個檔案 (``-bios OVMF.fd``)，
所以參數可能像這樣：

.. code-block:: sh

    $ qemu-img create -f qcow2 test.qcow2 100G
    $ qemu-system-x86_64 \
        -enable-kvm \
        -bios ./OVMF.fd \
        -smp cpus=4,cores=2 -cpu host \
        -m 2G \
        -cdrom ./archlinux.iso -boot order=d \
        test.qcow2


接下來可以選擇進入 Arch Linux 的安裝流程，
詳情請看 `Arch Wiki 上的 Beginners' guide <https://wiki.archlinux.org/index.php/beginners'_guide>`_ ，
其中注意所有跟 **UEFI** 相關的地方。

如果主機板有開 UEFI 支援的話，
Arch Linux 的 CD/USB 會自動用 `systemd-boot <http://www.freedesktop.org/wiki/Software/systemd/systemd-boot/>`_
來啟動整個系統。
拿到 root shell 後，
可以使用指令檢查是否有 UEFI 相關的資訊：

.. code-block:: sh

    $ ls /sys/firmware/efi/efivars

確定有正確抓到 UEFI 後可以做一些基本的設定 (keyboard layout、連上網路、更新系統時間、...)。
接著準備需要的儲存裝置，
先用 ``lsblk`` 來看系統上 block devices 的狀況：

.. code-block:: sh

    $ lsblk

從中找到想要安裝到的 device 的編號 (例如 ``/dev/sdx``)，
接著開始規劃分割區：

.. code-block:: sh

    $ parted /dev/sdx

    # 建立 GPT
    (parted) mklabel gpt

    # 切出 EFI System Partition
    (parted) mkpart ESP fat32 1MiB 513MiB
    (parted) set 1 boot on

    # 剩下的使用 (這邊範例直接把全部拿來分給根目錄)
    (parted) mkpart primary ext4 513MiB 100%

    # 離開 parted
    (parted) quit


分割區畫好後開始格式化檔案系統：

.. code-block:: sh

    $ lsblk /dev/sdx    # 確認編號
    $ mkfs.fat -F32 /dev/sdx1
    $ mkfs.ext4 /dev/sdx2


完成後就可以 mount 起來使用：

.. code-block:: sh

    $ mount /dev/sdx1 /mnt
    $ mkdir /mnt/boot
    $ mount /dev/sdx2 /mnt/boot


掛起來後安裝 base system 進去：

.. code-block:: sh

    $ pacstrap -i /mnt base base-devel


為未來啟動系統時可以自動找到需要 mount 的位置而產生 fstab：

.. code-block:: sh

    # -U for UUID
    # -L for Lables
    $ genfstab -U /mnt > /mnt/etc/fstab

chroot 進去剛準備好的基本版系統：

.. code-block:: sh

    $ arch-chroot /mnt /bin/bash

此時可以做一些基本的設定 (生 local、調時間、...)。

產生 initramfs：

.. code-block:: sh

    $ mkinitcpio -p linux

安裝 boot loader：

.. code-block:: sh

    $ bootctl install   # 安裝 systemd-boot 到 EFI system partition

修改 boot loader 的設定：

.. code-block:: sh

    # sample 檔在 /usr/share/systemd/bootctl/loader.conf
    $ edit /boot/loader/loader.conf
    default  arch
    timeout  4
    editor   0

    # sample 檔在 /usr/share/systemd/bootctl/arch.conf
    $ edit /boot/loader/entries/arch.conf
    title          Arch Linux
    linux          /vmlinuz-linux
    initrd         /initramfs-linux.img
    options        root=/dev/sdx2

到這邊基本上已經建好可以開機的系統了，
剩下的就是系統上使用者想要裝哪些軟體的問題。

離開並且重新開機：

.. code-block:: sh

    $ exit
    $ umount -R /mnt
    $ reboot


Reference
========================================

* `Arch Wiki - Beginners' guide <https://wiki.archlinux.org/index.php/beginners'_guide>`_
* `Arch Wiki - systemd-boot <https://wiki.archlinux.org/index.php/Systemd-boot>`_
* `Arch Wiki - UEFI <https://wiki.archlinux.org/index.php/Unified_Extensible_Firmware_Interface>`_
* `OS Dev - UEFI <http://wiki.osdev.org/UEFI>`_
