========================================
SQLite
========================================


.. contents:: 目錄


Data Type
========================================

SQLite 的型別是 Dynamic、Weak。（Type Affinity）

SQLite 的欄位型別只是參考用（像是 Python 的 Type Hinting，沒有強制性），
就算事先說要存數值，
其實還是可以儲存字串或其他東西，
型別是在資料身上不是在欄位宣告上，
而且會在操作時嘗試幫你轉換。


.. code-block:: sql

    CREATE TABLE dynamic_type(data int);

    INSERT INTO dynamic_type (data) VALUES (1);
    INSERT INTO dynamic_type (data) VALUES (2);
    INSERT INTO dynamic_type (data) VALUES (3);
    INSERT INTO dynamic_type (data) VALUES ("test");
    INSERT INTO dynamic_type (data) VALUES ("wtf");
    INSERT INTO dynamic_type (data) VALUES ("99");
    INSERT INTO dynamic_type (data) VALUES ("99asd");

    SELECT * FROM dynamic_type;           /* you can see everything here */
    SELECT SUM(data) FROM dynamic_type;   /* 204 */



Trigger
========================================

SQLite 可以設定在更動資料時觸發特定操作。

.. code-block:: sql

    CREATE TABLE our_command(id id, executed bool);

    INSERT INTO our_command (id, executed) VALUES (42, 1);
    INSERT INTO our_command (id, executed) VALUES (43, 0);
    INSERT INTO our_command (id, executed) VALUES (44, 1);
    INSERT INTO our_command (id, executed) VALUES (45, 0);

    SELECT * FROM our_command;  /* you can see everything */

    /* setup a trigger */
    CREATE TRIGGER clear_executed_command UPDATE OF executed ON our_command
      BEGIN
        DELETE FROM our_command WHERE id = OLD.id;  /* OLD is a reference to current row */
      END;

    /* update to trigger the command */
    UPDATE our_command SET executed = 1 WHERE id = 42;

    SELECT * FROM our_command;  /* you can see new result here */

    /* remove the trigger */
    DROP TRIGGER clear_executed_command;



Helper Functions
========================================

* .tables
* .schema



參考
========================================

* `Datatypes In SQLite Version 3 <http://www.sqlite.org/datatype3.html>`_
* `The SQLite Bytecode Engine <https://www.sqlite.org/opcode.html>`_
