========================================
Kindle
========================================

我自己使用的是 Kindle PaperWhite (PW3)。


.. contents:: 目錄


基本使用
========================================

剛拿到的時候不太會用 :P

* 閱讀時回首頁：點左上方可以出現選單，可選擇回首頁
* 截圖：同時點左下和右上
* USB 傳檔案：接上後直接 mount 就可以



Jailbreak
========================================

以下為依照 `這篇 <https://www.mobileread.com/forums/showthread.php?t=275877>`_
教學稍做翻譯。


事前準備
------------------------------

1. 綁定 Amazon 帳號（有些 Firmware 版本需要有綁定帳號後才能看到 Menu 上的某些功能）
2. 停用 Device Passcode 和 Parental Control Passcode
3. 關閉廣告
4. 充滿電
5. 保持飛航模式
6. 一次只做一個項目，做完才做下一個


正式開始
------------------------------

1. 正確地用 Serial Number 前六碼找到擁有的 Kindle model 的代稱（ `表格 <https://wiki.mobileread.com/wiki/Kindle_Serial_Numbers>`_ ）
2. 備份 Kindle 的 /documents 資料夾
3. 使用 Kindle 內建的原廠設定（e.g. Home -> Menu -> Settings -> Device Options -> Reset）
4. 下載 Initial Factory Firmware（原網站上有連結）
5. 把下載的 Initial Factory Firmware 存入 Kindle 最上層，並移除 USB 線
6. 在 Kindle 內選擇更新（e.g. Home -> Menu -> Settings -> Device Options -> Update Your Kindle）
7. 下載並存入最新版本由 Branch Delay 製作的 Factory Firmware，在下一步安裝後會在 /documents 內增加「Jail Broken」資料夾（原網站上有連結）
8. 回到 Kindle 首頁，在搜尋框輸入 ";installHtml"
9. 下載最新的 Hotfix（原網站上有連結），解開後存入並安裝（e.g. Home -> Menu -> Settings -> Menu -> Update Your Kindle）
10. 更新 Kindle 到最新的 Fireware（打開網路更新）



透過搜尋框執行指令
========================================

Kindle 的搜尋框其實可以呼叫一些特殊的指令，
詳細的指令支援可以參考：

* `Kindle PaperWhite - Search Bar Shortcuts <https://wiki.mobileread.com/wiki/Kindle_Touch_Hacking#Kindle_Paperwhite_Shortcuts>`_



Jailbreak 後安裝軟體
========================================

KUAL - Kindle Unified Application Launcher
------------------------------------------

:URL: https://www.mobileread.com/forums/showthread.php?t=203326
:Repo: https://bitbucket.org/ixtab/kindlelauncher


MRPI - MobileRead Package Installer
-----------------------------------

:URL: https://www.mobileread.com/forums/showthread.php?t=251143

安裝後就能支援從 mrpackages 資料夾以 bin 的格式安裝。


KOReader - 支援許多格式的閱讀器
-------------------------------

:URL: https://github.com/koreader/koreader/releases
:Repo: https://github.com/koreader/koreader


Kterm - Terminal Emulator
------------------------------

:URL: http://www.fabiszewski.net/kindle-terminal/
:Repo: https://github.com/bfabiszewski/kterm


Kindle VNC Viewer
------------------------------

:URL: https://www.mobileread.com/forums/showthread.php?t=150434
:Repo: https://github.com/hwhw/kindlevncviewer


SSH Server
========================================

在透過 MRPI 安裝完 USBNetwork 後，
可以在 KUAL 的 USBNetwork 設定把 USBNetwork 打開，
打開後就不會在接上 USB 時被視為儲存裝置，
而是另外的網路來源。

在安裝完後會在 Mount Point（預設是系統上的 ``/mnt/us`` ）多一個「usbnet」資料夾，
其中的 ``usbnet/etc/config`` 是 USBNetwork 的設定檔，
更改設定檔跟在 KUAL 的管理界面點選更動的效力相同，
預設 Kindle 端在透過 USB 連線時的 IP 為「192.168.15.244」。
要開啟透過 WiFi 來 SSH 進 Kindle 可以把其中的 ``USE_WIFI`` 改成 ``true`` ，
如果只想開啟 SSH over WiFI 但不想開啟 USB over Ethernet 可以再加上 ``USE_WIFI_SSHD_ONLY="true"`` 。
（也可以在 KUAL 管理界面點選）

Kindle 系列產品預設的 Root 密碼可能為「mario」或是以「fiona」開頭加上編號，
可以用 KindleTool 嘗試找預設的密碼，
或是裝了 Kterm 後直接在 Kindle 上用 su 變成 root 改掉，
又或者用 USB over Ethernet 來 SSH 登入（此作法在 SSH 時密碼輸入空的即可登入）。


透過 USB 的範例：

.. code-block:: sh

    $ ip link set up enp0s20f0u1
    $ ip addr add dev enp0s20f0u1 192.168.15.201/24
    $ ssh root@192.168.15.244

    Welcome to Kindle!

    root@192.168.15.244's password:                     #' 不要輸入，直接 Enter
    #################################################
    #  N O T I C E  *  N O T I C E  *  N O T I C E  #
    #################################################
    Rootfs is mounted read-only. Invoke mntroot rw to
    switch back to a writable rootfs.
    #################################################
    [root@kindle root]#


更改 Root 密碼：

.. code-block:: sh

    [root@kindle root]# mntroot rw
    system: I mntroot:def:Making root filesystem writeable
    [root@kindle root]# passwd
    Changing password for root
    New password:
    Retype password:
    Password for root changed by root
    [root@kindle root]# mntroot ro
    system: I mntroot:def:Making root filesystem read-only



Python on Kindle
========================================

Writing Application for Kindle
========================================

相關系統資訊
========================================

.. code-block:: sh

    $ [root@kindle root]# uname -a
    Linux kindle 3.0.35-lab126 #3 PREEMPT Fri Nov 4 12:52:26 PDT 2016 armv7l GNU/Linux
    $ [root@kindle root]# cat /proc/cpuinfo
    Processor       : ARMv7 Processor rev 10 (v7l)
    BogoMIPS        : 790.16
    Features        : swp half thumb fastmult vfp edsp neon vfpv3
    CPU implementer : 0x41
    CPU architecture: 7
    CPU variant     : 0x2
    CPU part        : 0xc09
    CPU revision    : 10

    Hardware        : Freescale i.MX 6SoloLite based Wario Board
    Revision        : 60000
    Serial          : "G090G10000000000"
    BoardId         : "0670200000000000"
    [root@kindle root]# free
    total       used       free     shared    buffers     cached
    Mem:        514760     500456      14304          0     149848     135916
    -/+ buffers/cache:     214692     300068
    Swap:            0          0          0



Awesome WM
========================================

相關檔案：

* /etc/xdg/awesome/rc.lua
* /usr/share/awesome/



參考
========================================

* `Kindle paperwhite 3 <https://wiki.mobileread.com/wiki/Kindle_paperwhite_3>`_
* `Kindle Hacks Information <https://wiki.mobileread.com/wiki/Kindle_Hacks_Information>`_
* `Kindle Touch Hacking <https://wiki.mobileread.com/wiki/Kindle_Touch_Hacking>`_
* `On my Kindle I am root <https://www.turnkeylinux.org/blog/kindle-root>`_
* `Snapshots of NiLuJe's hacks <https://www.mobileread.com/forums/showthread.php?t=225030>`_
