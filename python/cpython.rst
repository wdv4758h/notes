========================================
CPython
========================================

decimal
========================================

在改 CPython 的 PKGBUILD 時，
才發現從 3.3 開始支援了一個 library 叫 ``libmpdec`` ，
用來提升 decimal module 的效能 (``libmpdec`` 是用 C 實作的 library)。

接到 CPython 上的 module 名稱叫作 ``_decimal`` ，
在 ``import decimal`` 時會先去嘗試尋找 ``_decimal`` (看系統有沒有 ``libmpdec``)
沒有的話會使用純 Python 實作的 ``_pydecimal``

* `Python 3.3 - integrate fast native decimal arithmetic. <https://docs.python.org/3/whatsnew/3.3.html#decimal>`_
* [CPython] `Issue 7652 - Merge C version of decimal into py3k. <https://bugs.python.org/issue7652>`_
* `mpdecimal - a package for correctly-rounded arbitrary precision decimal floating point arithmetic <http://www.bytereef.org/mpdecimal/index.html>`_
* `CPython - decimal.py <https://github.com/python/cpython/blob/master/Lib/decimal.py>`_
* `CPython - _decimal <https://github.com/python/cpython/tree/master/Modules/_decimal>`_
* `CPython - _pydecimal.py <https://github.com/python/cpython/blob/master/Lib/_pydecimal.py>`_
