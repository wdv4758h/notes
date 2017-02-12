=============
FreeBSD Jails
=============

FreeBSD Jails 可以當成很省很省資源的虛擬機

建置步驟
--------

1.  放置 ``/etc/jail.conf`` ::

      exec.start = "/bin/sh /etc/rc";
      exec.start += "/usr/sbin/tzsetup Asia/Taipei";

      exec.stop = "/bin/sh /etc/rc.shutdown";

      exec.clean;
      mount.devfs;

      path = "/home/jails/$name";

      mount =  "/usr/ports $path/usr/ports nullfs ro 0 0";
      mount += "/home/pi314/.rcfiles $path/root/.rcfiles nullfs ro 0 0";

      django_apk {
          host.hostname = "$name";
          ip4.addr = 192.168.0.2;
          #allow.raw_sockets;
      }

2.  ``# echo jail_enable="YES" >> /etc/rc.conf``

3.  為 Jails 設定網路

    a.  網卡增加 IP 給 Jails 用 ::

          # echo ipv4_addrs_lo0="192.168.0.2-10/24" >> /etc/rc.conf
          # /etc/netstart

    b.  設定 NAT 和 port forwarding ::

          # /etc/pf.conf
          jails_net="192.168.0.0/24"
          nat on $ext_if proto { tcp, udp, icmp } from $jails_net to any -> ( $ext_if )
          rdr on $ext_if proto { tcp } from any to any port 60000 -> $jails_django_apk port 8000

        - ``nat`` 和 ``rdr`` 語法在不同 pf 之間有差異

4.  安裝 Jails

    a.  用 ``bsdinstall`` 安裝 (範例為 10.0 RELEASE) ::

          # export BSDINSTALL_DISTSITE=ftp://ftp.tw.freebsd.org/pub/FreeBSD/releases/amd64/10.0-RELEASE/
          # bsdinstall jail { jail-path }

        - ``doc`` ， ``game`` ， ``ports`` 不用裝，沒有特別需求的話也不需要開 sshd

    b.  把外面的 Port tree 掛載到 Jails 裡面

        A)  建立 ports 的 mount point ::

              # mkdir { jail-path }/usr/ports

            * 自動掛載的動作已經寫在上面 ``/etc/jail.conf`` 裡面

            * 以 Readonly 方式 mount 進去 ::

                # mount -o ro -t nullfs /usr/ports { jail-path }/usr/ports

        B)  修改 Jails 裡面的 ``/etc/make.conf``

            * 把 ports 編譯的 folder 到 ``/tmp`` 去::

                WRKDIRPREFIX=/tmp/ports
                DISTDIR=/tmp/ports/distfiles

            * 設定 Python 版本為 3.4 ::

                PYTHON_DEFAULT=3.4

        D)  調整 ``/usr/local/etc/portmaster.rc``

            * 開啟參數 ``-Bdw``

5.  啟動 Jail ::

      # service jail start { jail-name }

6.  查看目前開啟的 Jails instance ::

      $ jls

7.  進入 Jails ::

      # jexec { jail-id | jail-name } tcsh

    + 預設進入 jails 後 ``pwd`` 會在根目錄，可以在 local 的設定檔裡面加上 ::

        # local to this jails
        cd
        if [[ -a ~/.venv/bin/activate ]]; then
            source ~/.venv/bin/activate
        fi

8.  在外面用 ``pkg`` 幫 Jails 裝東西 ::

      # pkg -j { jail-id | jail-name } install zsh
      # pkg -j { jail-id | jail-name } install python3

