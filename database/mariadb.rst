========================================
MariaDB
========================================


.. contents:: 目錄


介紹
========================================

MariaDB 是從 MySQL fork 出去的資料庫，
原因是開發者擔心 Oracle 的種種政策會影響到 MySQL 的未來發展。
MariaDB 仍然維持和 MySQL 的相容性，
可以直接替換。



一些指令
========================================

安裝完後第一件事
------------------------------

.. code-block:: sh

    sudo mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
    sudo systemctl start mariadb    # 啟動服務
    # sudo systemctl enable mariadb    # 設定開機自動啟動服務
    mysql_secure_installation   # 設定 root 密碼以及其他權限


新增使用者
------------------------------

.. code-block:: sh

    mysql -u root -p
    MariaDB> CREATE USER 'myuser'@'localhost' IDENTIFIED BY 'mypassword';
    MariaDB> GRANT ALL PRIVILEGES ON mydb.* TO 'myuser'@'localhost';
    MariaDB> FLUSH PRIVILEGES;
    MariaDB> quit


建立資料庫
------------------------------

.. code-block:: sh

    mysqladmin -u myuser -p create mydb


重建 MediaWiki 的資料
------------------------------

.. code-block:: sh

    mysql -u myuser -p mydb < wikidb.sql


確保 UTF8：

.. code-block:: sh

    mysql -u myuser -p --default-character-set=utf8 mydb
    mysql> SET names 'utf8'
    mysql> SOURCE utf8.dump



參考
========================================

* `Arch Wiki - MySQL <https://wiki.archlinux.org/index.php/MySQL>`_
