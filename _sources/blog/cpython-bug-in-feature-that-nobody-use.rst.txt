:title: CPython's bug in feature that nobody uses
:slug: cpython-bug-in-feature-that-nobody-uses
:date: 2015-03-12 15:34
:modified: 2015-03-12 15:34
:category: Python
:tags: CPython
:author: wdv4758h
:summary:

之前 (2015 二月初) 發現 CPython 3.4 開始支援在 command line 直接用 ``tarfile`` 這 module 來處理檔案，
也就是說可以能來當作 Unix-like 平台上常見的 ``tar`` 指令的替代品，
其中支援由指定的副檔名來選擇壓縮的演算法 (無、gzip、bz2、lzma)，
但是經過嘗試後發現不管怎麼選都只是單純的 tar file，
後來去翻了一下 CPython source code 發現有地方寫錯了，
只好去開個 `issue <http://bugs.python.org/issue23421>`_ 送 patch 修正以及補上 test cases，
才知道原來 CPython 的 code review 還是使用 `Rietveld <http://bugs.python.org/review/>`_ ，
這也是我第一次幫 CPython 加 unit test :P

[準備要報 PyCon APAC 2015 的 lighting talk，之後會補上 slide]
