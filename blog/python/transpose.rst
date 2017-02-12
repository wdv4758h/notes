:title: PTT - Python 版 - transpose 問題
:slug: ptt-python-transpose
:date: 2014-10-11 23:33
:category: Python
:tags: python
:author: wdv4758h
:summary: 路過玩一下 PTT Python 版上的問題

這篇在解 PTT Python 版上的一個問題 (#1KEG5cfG)

基本上就是要做 transpose，但是資料長度不依，
所以就來試試囉 : https://gist.github.com/wdv4758h/1f4090ee9b0035dbcee0

以下都以 Python 3 為考量，而且以 zip 為出發點來解這個問題。

如果是一個完整 n x m 的資料，
類似的工作可以用 zip 就完成。

.. code-block:: python

    data = [range(10) for i in range(8)]

    def transpose(data):
        return zip(*data)

    for i in transpose(data):
        print(i)

現在的狀況不是完整 n x m 的資料，而是長短不一的，
一種解是用 itertools 裡的 zip_longest，
參數是 iterables 還有 fillvalue (預設是 None)，
fillvalue 會拿來填滿資料短缺的部份。

.. code-block:: python

   import itertools as it

   def transpose(data):
       return it.zip_longest(*data)

   # 跟前面文章借測資

   data = [list(range(i)) for i in range(10, 0, -1)]
   del data[3]
   del data[6]

   for i in transpose(data):
       print(i)

這邊會把不夠的地方都補 None，
所以輸出會是:

::

    (0, 0, 0, 0, 0, 0, 0, 0)
    (1, 1, 1, 1, 1, 1, 1, None)
    (2, 2, 2, 2, 2, 2, None, None)
    (3, 3, 3, 3, 3, 3, None, None)
    (4, 4, 4, 4, 4, None, None, None)
    (5, 5, 5, 5, None, None, None, None)
    (6, 6, 6, None, None, None, None, None)
    (7, 7, 7, None, None, None, None, None)
    (8, 8, None, None, None, None, None, None)
    (9, None, None, None, None, None, None, None)

如果前面那種剛好符合需求，那就可以開心的拿來用了，
如果真的不想要看到多補的那些資料，就再把結果處理過。

.. code-block:: python

    def transpose(data):
        return (tuple(it.filterfalse(lambda x: x is None, i))
                    for i in it.zip_longest(*data))

    for i in transpose(data):
        print(i)

如此一來結果就變成:

::

    (0, 0, 0, 0, 0, 0, 0, 0)
    (1, 1, 1, 1, 1, 1, 1)
    (2, 2, 2, 2, 2, 2)
    (3, 3, 3, 3, 3, 3)
    (4, 4, 4, 4, 4)
    (5, 5, 5, 5)
    (6, 6, 6)
    (7, 7, 7)
    (8, 8)
    (9,)

不過上面處理是以輸入 data 裡沒有 None 為前提的 XD
資料裡面可能有 None 的話就另外用別的值囉。
