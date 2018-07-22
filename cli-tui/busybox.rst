========================================
BusyBox - 人人都該備一個在身邊的執行檔
========================================


.. contents:: 目錄


Introduction
========================================

BusyBox 這專案首次釋出於 1999 年 11 月 4 日，
目標是要為嵌入式環境提供一個迷你、單一的靜態連結執行檔，
程式撰寫的時候也一直會考量到資源的限制，
現在 BusyBox 已經發展成包含數百個常見指令的單一執行檔。

BusyBox 是一個典型的 Multicall Binary 範例，
Multicall Binary 指的是一個 binary 檔同時包含好幾隻不同的程式，
依照執行這 binary 的方式而決定要跑裡面的哪種程式，
這技巧的知名例子就是 BusyBox，
把撰寫的許多 command 編在一起，
共用許多部份，
藉此達到省空間的目的 (BusyBox 的目標是跑在資源相對有限的嵌入式系統)，
達到這效果的方式則是利用 ``argv[0]`` 來做判斷，
如果名稱是內部程式之一的話，
就去執行該程式的部份，
因此可以看到諸多個指令都只是 BusyBox 的 symbolic link，
但執行起來效果卻不同。

例如這個樣子：

::

    -rwxr-xr-x 1 root root 931664 Aug  9 13:19 busybox*
    lrwxrwxrwx 1 root root      7 Aug  9 13:20 ls -> busybox*
    lrwxrwxrwx 1 root root      7 Aug  9 13:20 pwd -> busybox*



安裝 & 使用
========================================

.. code-block:: sh

    $ sudo pacman -S busybox
    resolving dependencies...
    looking for conflicting packages...

    Package (1)        New Version  Net Change

    community/busybox  1.23.2-1       0.90 MiB

    Total Installed Size:  0.90 MiB

    :: Proceed with installation? [Y/n]
    (1/1) checking keys in keyring                       [##########################################] 100%
    (1/1) checking package integrity                     [##########################################] 100%
    (1/1) loading package files                          [##########################################] 100%
    (1/1) checking for file conflicts                    [##########################################] 100%
    (1/1) checking available disk space                  [##########################################] 100%
    (1/1) installing busybox                             [##########################################] 100%
    You may want to do setuid on /usr/bin/busybox
    chmod 4555 /usr/bin/busybox
    $ pacman -Ql busybox
    busybox /usr/
    busybox /usr/bin/
    busybox /usr/bin/busybox
    $ ls -l /usr/bin/busybox
    -rwxr-xr-x 1 root root 931664 Mar 23 17:43 /usr/bin/busybox
    $ file /usr/bin/busybox
    /usr/bin/busybox: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), statically linked, stripped


裝起來就這麼個執行檔，靜態連結，沒有其他 dependency，
總共 931664 bytes (不到 1 MB)，
裡面卻包含了眾多系統常見的基本功能：

.. code-block:: sh

    $ busybox
    BusyBox v1.23.2 (2015-03-23 12:42:42 MSK) multi-call binary.
    BusyBox is copyrighted by many authors between 1998-2012.
    Licensed under GPLv2. See source distribution for detailed
    copyright notices.

    Usage: busybox [function [arguments]...]
    or: busybox --list[-full]
    or: busybox --install [-s] [DIR]
    or: function [arguments]...

    	BusyBox is a multi-call binary that combines many common Unix
    	utilities into a single executable.  Most people will create a
    	link to busybox for each function they wish to use and BusyBox
    	will act like whatever it was invoked as.

    Currently defined functions:
    	[, [[, acpid, addgroup, adduser, adjtimex, ar, arp, arping, ash, awk, base64, basename,
    	bbconfig, beep, blkid, blockdev, bootchartd, brctl, bunzip2, bzcat, bzip2, cal, cat, catv,
    	chat, chattr, chgrp, chmod, chown, chpasswd, chpst, chroot, chrt, chvt, cksum, clear, cmp,
    	comm, cp, cpio, crond, crontab, cryptpw, cttyhack, cut, date, dc, dd, deallocvt, delgroup,
    	deluser, depmod, df, dhcprelay, diff, dirname, dmesg, dnsd, dnsdomainname, dos2unix, du,
    	dumpkmap, dumpleases, echo, ed, egrep, eject, env, envdir, envuidgid, ether-wake, expand,
    	expr, fakeidentd, false, fatattr, fbset, fbsplash, fdflush, fdformat, fdisk, fgconsole,
    	fgrep, find, findfs, flock, fold, free, freeramdisk, fsck, fsck.minix, fstrim, fsync,
    	ftpd, ftpget, ftpput, fuser, getopt, getty, grep, groups, gunzip, gzip, halt, hd, hdparm,
    	head, hexdump, hostid, hostname, httpd, hwclock, id, ifconfig, ifdown, ifenslave, ifplugd,
    	ifup, inetd, init, inotifyd, insmod, install, ionice, iostat, ip, ipaddr, ipcalc, ipcrm,
    	ipcs, iplink, iproute, iprule, iptunnel, kbd_mode, kill, killall, killall5, klogd, last,
    	less, linux32, linux64, linuxrc, ln, loadfont, loadkmap, logger, login, logname, logread,
    	losetup, lpd, lpq, lpr, ls, lsattr, lsmod, lsof, lspci, lsusb, lzcat, lzma, makedevs,
    	makemime, man, md5sum, mdev, mesg, microcom, mkdir, mkdosfs, mke2fs, mkfifo, mkfs.ext2,
    	mkfs.minix, mkfs.vfat, mknod, mkpasswd, mkswap, mktemp, modinfo, modprobe, more, mount,
    	mountpoint, mpstat, mt, mv, nameif, nbd-client, nc, netstat, nice, nmeter, nohup,
    	nslookup, ntpd, od, openvt, passwd, patch, pgrep, pidof, ping, ping6, pipe_progress,
    	pivot_root, pkill, pmap, popmaildir, poweroff, powertop, printenv, printf, ps, pscan,
    	pstree, pwd, pwdx, raidautorun, rdate, rdev, readahead, readlink, readprofile, realpath,
    	reboot, reformime, renice, reset, resize, rev, rfkill, rm, rmdir, rmmod, route, rpm2cpio,
    	rtcwake, run-parts, runlevel, runsv, runsvdir, rx, script, scriptreplay, sed, sendmail,
    	seq, setarch, setconsole, setfont, setkeycodes, setlogcons, setserial, setsid, setuidgid,
    	sh, sha1sum, sha256sum, sha3sum, sha512sum, showkey, shuf, slattach, sleep, smemcap,
    	softlimit, sort, split, start-stop-daemon, stat, strings, stty, su, sulogin, sum, sv,
    	svlogd, swapoff, swapon, switch_root, sync, sysctl, syslogd, tac, tail, tar, taskset,
    	tcpsvd, tee, telnet, telnetd, test, tftp, tftpd, time, timeout, top, touch, tr,
    	traceroute, traceroute6, true, tty, ttysize, tunctl, tune2fs, ubiattach, ubidetach,
    	ubimkvol, ubirmvol, ubirsvol, ubiupdatevol, udhcpc, udhcpc6, udhcpd, udpsvd, umount,
    	uname, uncompress, unexpand, uniq, unix2dos, unlink, unlzma, unxz, unzip, uptime, users,
    	usleep, uudecode, uuencode, vconfig, vi, vlock, volname, wall, watch, watchdog, wc, wget,
    	which, who, whoami, whois, xargs, xz, xzcat, yes, zcat, zcip


這麼多功能，這樣的檔案大小，當然不是像 GNU coreutils 那樣有一大堆的 options 支援，
但是作為基本的功能還是有的，
其中甚至有 ``httpd`` 可以當作小小的 SimpleHTTPServer 來使用。

使用方式可以把要用的指令接在 BusyBox 後頭 (例如 ``$ busybox ls``)，
或者用 symbolic link 來換成想要的指令 (例如 ``$ ln -s busybox ls; ./ls``)，
可以這麼做的原因是 BusyBox 會根據 ``argv[0]`` 來判斷要執行的 command，
如果 ``argv[0]`` 是 ``busybox`` 的話就吃 ``argv[1]`` 來決定 command，
不然就直接用 ``argv[0]`` 來決定 command。



Build From Source
========================================

.. code-block:: sh

    $ git clone git://git.busybox.net/busybox
    $ cd busybox
    $ make menuconfig   # 或 oldconfig/defconfig，可以選擇要編進去的功能
    $ make -j4
    $ ls -l busybox
    -rwxr-xr-x 1 dv users 831440 Aug  9 12:34 busybox



Reference
========================================

* `BusyBox: The Swiss Army Knife of Embedded Linux <http://www.busybox.net/>`_
* `BusyBox - Source Code <http://git.busybox.net/busybox/>`_
* `Wikipedia - BusyBox <https://en.wikipedia.org/wiki/BusyBox>`_
* `Multicall binaries <https://blog.flameeyes.eu/2009/10/multicall-binaries>`_
* `Creating a Multi-Call Linux Binary <http://www.redbooks.ibm.com/abstracts/tips0092.html>`_
* `[GitHub] extemporalgenome/multicall-example - Hybrid multi-call/single-call binaries in Go <https://github.com/extemporalgenome/multicall-example>`_
