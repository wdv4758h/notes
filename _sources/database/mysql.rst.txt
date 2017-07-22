========================================
MySQL
========================================


.. contents:: 目錄


重置密碼
========================================

.. code-block:: sql

    SET PASSWORD FOR 'root'@'localhost' = PASSWORD('')


* `Reset a MySQL root password <https://support.rackspace.com/how-to/mysql-resetting-a-lost-mysql-root-password/>`_



備份
========================================

.. code-block:: sql

    mysqldump -h hostname -u username -p mydatabase > mydatabase.sql


* `Backup Your MySQL Databases Manually With Mysqldump <http://www.ducea.com/2006/05/20/backup-your-mysql-databases-manually-with-mysqldump/>`_



建立帳號
========================================

.. code-block:: sh

    mysql -e "CREATE USER 'newuser'@'localhost' IDENTIFIED BY 'mypassword'; GRANT ALL PRIVILEGES ON . TO 'newuser'@'localhost'; FLUSH PRIVILEGES;" -u root -p



插入
========================================

.. code-block:: sql

    INSERT INTO mydata (uuid, mynumber) VALUES ('275fb8566bcb11e69d34025fb2f1683d', 42);



Event
========================================

.. code-block:: sql

    SET GLOBAL event_scheduler = ON;

.. code-block:: sql

    CREATE EVENT
      clear_executed_command
    ON SCHEDULE EVERY 5 SECOND
    DO
      DELETE FROM command_queue WHERE mynumber = 42;

.. code-block:: sql

    DROP EVENT clear_executed_command;



參考
========================================
