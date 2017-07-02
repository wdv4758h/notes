========================================
CPython
========================================

Build From Source
========================================

.. code-block:: sh

    # CPython source code 已經從自己 Hosting 轉移到 GitHub 上了
    $ git clone https://github.com/python/cpython
    $ cd cpython
    $ ./configure --with-pydebug
    $ make -j8
    $ ./python -m test -j8

* `Python Developer's Guide <https://docs.python.org/devguide/index.html>`_
* `BuildBot: Python - Waterfall <http://buildbot.python.org/all/waterfall>`_
* `Mercurial for git developers <https://docs.python.org/devguide/gitdevs.html>`_
* `CPython - Code Review <https://bugs.python.org/review/>`_


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


Articles
========================================

* [2010] `Python internals: Symbol tables, part 1 <http://eli.thegreenplace.net/2010/09/18/python-internals-symbol-tables-part-1/>`_
* [2010] `Python internals: Symbol tables, part 2 <http://eli.thegreenplace.net/2010/09/20/python-internals-symbol-tables-part-2>`_
* [2011] `Python list implementation <http://www.laurentluce.com/posts/python-list-implementation/>`_
* [2014] `CPython internals: A ten-hour codewalk through the Python interpreter source code <http://pgbovine.net/cpython-internals.htm>`_

* `CPython - Execution model <https://docs.python.org/3/reference/executionmodel.html>`_

* [GitHub] `Notes on making CPython faster <https://github.com/haypo/faster_cpython>`_



Talks
========================================

* [YouTube] `Architecture of CPython, the bricks! (Stéphane Wirtel) <https://www.youtube.com/watch?v=ZkAc6hzGun4>`_
* [YouTube] `From Source to Code: How CPython's Compiler Works - Brett Cannon <https://www.youtube.com/watch?v=R31NRWgoIWM>`_
* [YouTube] `Stepping Through CPython <https://www.youtube.com/watch?v=XGF3Qu4dUqk>`_
* [YouTube] `Hacking the CPython Interpreter | SciPy 2016 | James Powell <https://www.youtube.com/watch?v=1SqRRrmQHx0>`_



Other Python Implementations
========================================

* `Pyston <https://github.com/dropbox/pyston>`_
    - performance-oriented Python implementation built using LLVM and modern JIT techniques
* PyPy
    - Python implementation written in RPython framework with JIT and modern GC
* Jython
    - Python implementation written in Java to integrate with JVM
* IronPython
    - Python implementation written in C# to integrate with .NET framework
