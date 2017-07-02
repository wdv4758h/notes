========================================
Linter & Formatter
========================================


.. contents:: 目錄


Linter
========================================

檢查程式的問題，比較嚴重的例如」使用沒宣告的變數」，
比較沒那麼嚴重的例如「Coding Style 不符合規定」。


Pylint
------------------------------

`Pylint <https://github.com/PyCQA/pylint>`_ 是一個豐富且有彈性的 Python Linter，
可以設定各種功能。

只回報嚴重錯誤：

.. code-block:: sh

    $ pylint -E foo.py


回報完整訊息（包含 Coding Style 檢查）：

.. code-block:: sh

    $ pylint foo.py


輸出結果報告：

.. code-block:: sh

    $ pylint -r y foo.py




Flake8
------------------------------

`Flake8 <https://github.com/PyCQA/flake8>`_ 是一套結合許多工具的包裝，
除了內建的整合外，
也提供擴充其他工具的機制，
所以可以把許多工具整合成同一個界面使用。


一次安裝 Flake8 和多個擴充：

.. code-block:: sh

    $ pip install flake8 pep8-naming flake8-import-order flake8_docstrings flake8-bugbear



Formatter
========================================

YAPF
------------------------------

`YAPF <https://github.com/google/yapf>`_
是一套自動排版 Python 程式碼的工具，
用來自動化地改善程式碼的風格。
