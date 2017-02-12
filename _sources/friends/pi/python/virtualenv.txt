==============
= virtualenv =
==============

概念
----

在 UNIX-like 系統中，當使用者執行某個指令時，系統會根據 ``$PATH`` environment variable 去尋找它。virtualenv 就是透過修改 ``$PATH`` 的值，讓使用者可以找到特定的 Python package，這樣可以把不同的 package 隔離，避免衝突。

virtualenv 甚至可以隔離不同版本的 Python，讓 Python2.7 和 Python3.4 共存於系統中（較麻煩，後述）

註：Python 3.4 開始內建 ``venv`` ，和底下提到的 virtualenv 功能類似，但無法隔離不同的 Python 版本

安裝 virtualenv
---------------

- Freebsd ::

    # portmaster devel/py-virtualenv

建立 virtualenv 環境
--------------------

1.  建立 virtualenv 環境 ::

      $ virtualenv {{ virtualenv-name }} [--python={{ python-path }}]

    + ``{{ virtualenv-name }}`` 是隔離區的名字，可以將 package 集中成一包，方便管理

    + ``{{ python-path }}`` 是 Python 的直譯環境

    + 範例 ::

        $ virtualenv .virtualenv --python=.py27/bin/python

2.  套用某個 virtualenv 環境 ::

      $ source .virtualenv/bin/activate

    + ``tcsh`` / ``csh`` 請改 ``source`` ``activate.csh``
    + ``fish`` 請改 ``source`` ``activate.fish``

3.  在套用 virtualenv 環境以後，安裝 package ::

      $ pip install {{ package-name }}

4.  離開 virtualenv 環境 ::

      $ deactivate

隔離 Python 環境
----------------

以下以 Python2.7 為例，把 Python2.7 安裝進家目錄中，並用 virtualenv 包裝

1.  下載 Python2.7 的壓縮檔並解壓 ::

      $ wget http://www.python.org/ftp/python/2.7.1/Python-2.7.1.tgz

2.  編譯 Python2.7 ::

      cd Python-2.7.1
      make clean
      ./configure --prefix=/home/<user>/.py27
      make
      make install

    + ``--prefix`` 是設定 Python 的所在位置，通常預設為 ``/usr/local/bin`` 。基於安全考量，如果實際所在位置和 ``--prefix`` 設定不同，Python 會拒絕執行

3.  建立 virtualenv 環境

