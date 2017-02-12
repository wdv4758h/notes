=====================
Distrubuting Packages
=====================
..  contents::


製作 PyPI Package
--------------------
PyPI Package 需符合一定的目錄結構 ::

  root-folder/
  ├── <package-name>/
  │   └── __init__.py
  ├── setup.py
  ├── README.rst
  └── LICENSE

以上是最基本的結構，隨著 Package 的用途，可能會有更多的目錄和檔案需要加入

以下是一個簡單的 ``setup.py`` 範例

..  code:: python

    from setuptools import find_packages, setup
    setup(
        name='<package-name>',
        packages=find_packages(exclude=['scripts']),
        version='0.1',
        description='<說明>',
        author='<作者>',
        author_email='<作者 Email>',
        url='<Package Website>',
        classifiers=[],
    )


上傳至 PyPI
------------
請確定你有一個 https://pypi.python.org/pypi 帳號

1.  第一次上傳需先註冊 Package ::

      $ python setup.py register

    + 第一次執行時會詢問是否要把登入資訊存入 ``$HOME.pypirc`` （含密碼），若不存入的話，目前（2016/05/11）官方的 CPython 在上傳時會出問題

      * ``python setup.py register`` 若 ``$HOME.pypirc`` 不存在，會詢問 username 以及 password
      * ``python setup.py register`` 若 ``$HOME.pypirc`` 沒有 password，會詢問 password
      * ``python setup.py register`` 若 ``$HOME.pypirc`` 資訊完整，不會詢問
      * ``python setup.py register upload`` 會使用 ``register`` 取得的密碼
      * ``python setup.py upload`` 若 ``$HOME.pypirc`` 不存在或資訊不完整，會 *爆炸*

2.  上傳 ::

      $ python setup.py sdist bdist_wheel upload

    + ``sdist`` 會把 Source code 包裝成壓縮檔
    + ``bdist_wheel`` 會把 Source code 編譯過再包裝成壓縮檔，這個方法的安裝過程會比較快 [1]_
    + ``bdist_wheel`` 選項需安裝 ``wheel`` Package 以後才能使用
    + 產生的壓縮檔會放在 ``dist/`` 目錄中

    ..  [1] https://packaging.python.org/en/latest/distributing/#wheels


附帶靜態檔案
-------------
若靜態檔案和 ``setup.py`` 需放在同一層（例如 ``LICENSE.txt`` ），可以加上一個 ``MANIFEST.in`` 檔案 ::

  include LICENSE.txt
