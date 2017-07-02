===========
= postfix =
===========

Quick Notes
-----------

* 查看 mail queue ::

    # postqueue -p

* 刪除 mail queue 內的信件 ::

    # postqueue -p
    (找到信件的 queue ID，例如 69C284AC48)
    # postsuper -d 69C284AC48

* 增加 mail

  - ``/etc/aliases``

    + 修改以後，需執行 ::

        # newaliases
        # postfix reload

概念
----

* MTA - transport (relay

  - postfix

* MDA - delivery

  - local

* MRA - retrive

  - dovecot

* MSA - submission

  - postfix

安裝
----

* /etc/rc.conf ::

    postfix_enable="YES"

* ``service postfix start``
* dovecot2 和 dovecot 不同

* 設定檔

  - ``/usr/local/etc/postfix/main.cf``

    + 設定 postfix 的各個參數

  - ``/usr/local/etc/postfix/master.cf``

    + 服務和 daemon 的對應

  - ``/etc/mail/mailer.conf``

    + 常用的 mail server 管理指令和實際執行指令的對應(可以改

MISC
----

* ``postfix -c /usr/local/etc/postfix set-permission``
* ``/var/log/maillog``

  - queue ID, 相關的 log

* ``/etc/mail/aliases``

  - 一些 alias, 位置在 ``/usr/local/etc/postfix/main.cf`` 可以改

* 架設 SMTPs

  1.  架一個 CA (生出 root CA cert
  2.  生一個 cert
  3.  smtpd_tls 相關設定

      * 用 ``telnet localhost 25 & STARTTLS`` 測試看看

  5.  ``master.cf``

      * ``smtps``
      * ``openssl s_client -connect localhost:465``

  6.  reference

      * http://linuxpoison.blogspot.tw/2007/10/howto-create-self-signed-ssl.html
      * http://www.weithenn.org/cgi-bin/wiki.pl?SSL_Certificate-%E8%87%AA%E8%A1%8C%E7%94%A2%E7%94%9F_SSL_%E6%86%91%E8%AD%89

  7.  [據說] 別用 dovecot 的 mkcert.sh

* smtpd_delay_reject = yes

  - 如果判定要 reject，等到 client 發出 rcpt to 再擋，一方面可以得到更多資訊，另一方面讓 log 乾淨一些

* postmap # 製作 database，格式通常是 Berkeley DB

  - postmap /etc/client_access
  - postmap -q nctu.edu.tw /etc/client_access

* mydestination

  - 寄給這些 domain，（如果經過這台機器的話）這台機器會收下並 deliver

* mynetworks_style

  - relay 的範圍

* relay_domains

  - relay 的 domain

* restrictions

  - smtpd_sender_restrictions
  - smtpd_client_restrictions
  - smtpd_helo_restrictions
  - smtpd_recipient_restrictions

* postalias # 製作 email alias 的 database

  - # alias_maps, alias_database
  - postalias /etc/aliases

