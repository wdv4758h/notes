=======
``ftp``
=======
* 開啟 FreeBSD 內建的 ftp server ::

    $ /usr/libexec/ftpd -D -l -l

  - ``-D`` 讓 ftp 以 daemon 的方式啟動
  - ``-l -l`` 叫 ``syslogd`` 記錄每次的連線，用兩次 ``-l`` 則可以連使用的動作都記錄
  - ``-l`` 要留下連線記錄還需要配合修改 ``/etc/syslog.conf`` 才會啟動記錄

* 指令列表（在連上 ftp server 後） ::

    ls
    cd
    less
    get remote-file <local-file>
    put local-file <remote-file>
    quit
