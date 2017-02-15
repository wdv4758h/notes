========================================
Nuitka
========================================


.. contents:: 目錄


基本使用
========================================

餵入 Main Program：

.. code-block:: sh

    $ nuitka --recurse-all zdict/__main__.py

此時會產生：

::

    __main__.build/
    __main__.exe

``__main__.build/`` 內的是編譯過程的 C/C++ 程式碼和 Object Files，
``__main__.exe`` 則是產生的執行檔。
用這樣方式產生的執行檔仍然需要系統上對應的相依套件，
例如 ``requests`` 、 ``peewee`` 、 ``bs4`` 。

執行：

.. code-block:: sh

    $ env PYTHONPATH=venv/lib/python3.6/site-packages/ ./__main__.exe -dt urban iirc
