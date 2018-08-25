==================================
在不關閉檔案的情況下讀取並新增內容
==================================
同時讀寫一個檔案是個大部份人都建議避免的狀況[來源請求]，因為這樣很容易把檔案內容弄壞，且過程較複雜

但若真的有此需求，可以使用 ``file.tell()`` ``file.seek()`` 來達成

--------

首先用讀寫模式開啟檔案

.. code:: python

    f = open('rw.txt', 'a+')

定義 ``read_cur`` 和 ``write_cur`` 兩個變數用來維護讀取以及寫入的位置

.. code:: python

    read_cur, write_cur = 0, f.tell()

``read_cur`` 指定為 0，準備從開頭讀取資料

由於使用了 ``a+`` 開檔，檔案游標的位置預設會在檔案的結尾，故 ``write_cur`` 可以直接指定為 ``f.tell()``

讀取一行，並更新 ``read_cur``

.. code:: python

    f.seek(read_cur)
    f.readline()
    read_cur = f.tell()

寫入一行，並更新 ``write_cur``

.. code:: python

    f.seek(write_cur)
    f.write('content\n')
    write_cur = f.tell()

根據測試（Mac OS X / Python 3.5 from MacPorts）， ``f.tell()`` 帶有 ``f.flush()`` 的效果
