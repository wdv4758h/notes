===============
Python argparse
===============
Python ``argparse`` module 是個用來處理參數邏輯的 framework

速查
-----
* 初始化 ::

    import argparse
    parser = argparse.ArgumentParser(description='說明文字')

* ``-a`` 格式的參數 ::

    parser.add_argument('-a', action='store_true', help='說明文字')

* ``-f file ...`` 格式的參數 ::

    parser.add_argument('-f', nargs=1, dest='var')

  - ``nargs`` 指定 ``-f`` 後面可接的參數數量，後有詳述
  - ``dest`` 指定實際儲存值的變數名稱

* ``a b c ...`` 格式的參數 ::

    parser.add_argument('var')

* 處理參數 ::

    args = parser.parse_args()


``add_argument`` 筆記
----------------------

::

  import argparse
  parser = argparse.ArgumentParser(description='說明文字')
  parser.add_argument(...)

``add_argument`` 可以傳入很多參數，調整參數的行為

* ``dest``

  - 指定負責儲存值的變數名稱

* ``action="store_true"`` ``action="store_false"``

  - ``-a`` 讓格式的參數儲存 ``True``/``False`` 的值

* ``action="store_const", const="<value>"``

  - ``-a`` 讓格式的參數儲存 ``<value>`` 的值， ``store_true`` 和 ``store_false`` 算是特殊狀況

* ``default="<value>"``

  - 若 ``-a`` 參數完全沒有出現，則存入 ``<value>``

* ``const="<value>"``

  - 若 ``-a`` 參數有被給予，則存入 ``<value>``

* ``nargs``

  - 可用的選項有

    + ``nargs=整數``
    + ``nargs='?'`` 表示可接 1 個或 0 個參數，需搭配 ``default=預設值`` 使用
    + ``nargs='*'`` 表示任意數量的參數，並輸出成一個 ``list``
    + ``nargs='+'`` 表示 1 個以上的參數，並輸出成一個 ``list``
    + ``nargs=argparse.REMAINDER`` 表示吃掉剩下的所有參數，並輸出成一個 ``list``

  - 可以和 ``default`` 以及 ``const`` 搭配，e.g. ``nargs="?", default="d", const="c"``

    + 若 ``-a`` 參數沒有被給予，存入 ``"d"``
    + 若給予 ``-a`` ，存入 ``"c"``
    + 若給予 ``-a v`` ，存入 ``"v"``

* ``action="append"``

  - 讓 ``-a 1 -a 2`` 存入 ``[1, 2]``
