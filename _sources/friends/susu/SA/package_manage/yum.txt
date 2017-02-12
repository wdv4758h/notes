yum
===

yum 為 Redhat/Fedora/CentOS 的套件管理系統 (更新: Fedora 已換到 dnf)

commands::

    yum update: 不加套件名稱則為 all
    yum search
    yum install
    yum remove
    yum clean: 清除安裝時下載的暫存套件原始檔案, 位於 /var/cache/yum
    yum clean all
    yum list
    yum list updates
    yum list installs

- list repo files: ``rpm -ql <repo_name>``. e.g. ``rpm -ql qemu-kvm``

- rpm fusion (unofficial rpm(yum) 套件庫) http://rpmfusion.org/
- Ref: http://www.pupuliao.info/2011/12/fedora%E8%BB%9F%E9%AB%94%E5%AE%89%E8%A3%9D%E6%8C%87%E4%BB%A4yum/

bootstrap centos7
-----------------
- my test (failed)
  
  ::

      $ cd ~/container/
      $ mkdir -p ~/container/centos7/var/lib/rpm
      $ rpm --root $(pwd)/centos7/ --initdb

      # Download the CentOS release RPM
      # https://rpmfind.net/linux/rpm2html/search.php?query=centos-release
      $ wget <url>
      $ rpm --root=$(pwd)/centos7/ --nodeps --nosignature -i <centos7_rpm>
      $ yum --installroot=$(pwd)/centos update
      $ yum --installroot=$(pwd)/centos --nogpgcheck install -y yum
      
  
- http://prefetch.net/articles/yumchrootlinux.html

  - rpm, yumdownloader, yum
  ::

      $ mkdir -p /chroot/webapp1/var/lib/rpm
      $ rpm --root /chroot/webapp1 --initdb
      $ yumdownloader --destdir=/var/tmp fedora-release
      $ cd /var/tmp
      $ rpm --root /chroot/webapp1 -ivh --nodeps fedora-release*rpm

      # install httpd and run
      $ yum --installroot=/chroot/webapp1 -y install httpd
      $ chroot /chroot/webapp1 /usr/sbin/apachectl start

- https://watchmysys.com/blog/2015/02/installing-centos-7-with-a-chroot/

  ::

      # Download the CentOS release RPM
      $ wget http://mirror.centos.org/centos/7/os/x86_64/Packages/centos-release-7-0.1406.el7.centos.2.3.x86_64.rpm
      $ rpm --root=/mnt --nodeps -i centos-release-7-0.1406.el7.centos.2.3.x86_64.rpm
      $ yum --installroot=/mnt update
      $ yum --installroot=/mnt install -y yum
      $ yum --installroot=/mnt install -y @core kernel
      $ yum --installroot=/mnt install -y grub2-efi efibootmgr lvm2 mdadm dosfstools kernel

      $ cp /etc/resolv.conf /tmp/ramdisk/mnt/etc/
      $ mkdir /mnt/centos
      $ mount /dev/vg0/centos /mnt/centos
      $ mount -t proc proc /mnt/centos/proc
      $ mount --rbind /dev /mnt/centos/dev
      $ mount --rbind /sys /mnt/centos/sys
      $ chroot /mnt/centos /bin/bash

Misc
----
- g++ in yum

  - ``yum install gcc-c++`` (用這名子有點困擾, yum search g++ 找不到它, 還會跑出一堆其他套件)
