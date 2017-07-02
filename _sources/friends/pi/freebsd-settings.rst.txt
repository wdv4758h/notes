================
FreeBSD 各種設定
================

軟體
----

* ``sshd``

  - ``/etc/pam.d/sshd`` ::

      auth required pam_unix.so no_warn try_first_pass
      authtok_prompt="Password:"

  - ``/etc/ssh/sshd_config`` ::

      UseDNS no

    + 避免查詢 Client 的 Hostname，查詢若不成功，連線要等很久才會建立

* ``visudo``

* MariaDB ::

    # /etc/my.cnf
    [mysqld] collation-server = utf8_unicode_ci
    init-connect = 'SET NAMES utf8'
    character-set-server = utf8

  - 範例設定檔在 ``/usr/local/share/mysql`` 裡面
  - 在 MariaDB 中列出設定值 ::

      mysql -e ‘show variables;’ | less
      mysql> show variables like "%char%";

* ``portmaster``

  - #/usr/local/etc/portmaster.rc
  - 開啟參數
  - ``-B`` 移除 Ports 時不要備份
  - ``-d`` 安裝 Ports 後刪除 distfiles
  - ``-w`` 備份舊的 Shared Library

系統設定
--------

網路相關設定
~~~~~~~~~~~~

* 設定 IP Address ::

    #/etc/rc.conf
    ifconfig_em0="inet x.x.x.x netmask x.x.x.x"

  - 在 Command Line 設定（即時，一次）

    + ``ifconfig em0 inet x.x.x.x netmask x.x.x.x``

* 設定 Default Router ::

    #/etc/rc.conf
    defaultrouter="x.x.x.x"

  - 在 Command Line 設定（即時，一次） ::

      route add default 8.8.8.8

* 設定 DNS server ::

    #/etc/resolv.conf
    nameserver 140.113.1.1
    nameserver 8.8.8.8

* 設定 Hostname ::

    $ hostname
    # hostname {{new-host-name}}
    # /etc/rc.d/hostname restart

其他設定
~~~~~~~~

* 進站訊息: ``/etc/motd``

* 設定 Console 下送字速度 ::

    #/etc/rc.conf
    keyrate="fast"

* 關掉 FreeBSD 內建的 sendmail ::

    #/etc/rc.conf
    sendmail_enable="NONE"
    sendmail_msp_queue_enable="NO"
    sendmail_outbound_enable="NO"
    sendmail_submit_enable="NO"

帳號設定
--------

* 新增使用者： ``adduser``
* 若要修改使用者的「第一個 group」，用 ``vipw`` 指令修改

  - 會更動 ``/etc/passwd`` 、 ``/etc/master.passwd``

* 若要修改使用者的「第二個 group」，可以直接改 ``/etc/group``

  - 下次登入以後生效
