======================================
FreeBSD Ports 系統對 Python 版本的判斷
======================================

2015/01/25 測試結果
-------------------

* ``/usr/local/bin/python`` 的優先權比 ``/etc/make.conf`` 中的 ``DEFAULT_VERSIONS=python=3.4`` 高
* ``PYTHON_VERSION`` 的優先權最高

* 在 ``/etc/make.conf`` 中設定 ``DEFAULT_VERSIONS=python=3.4 python2=2.7 python3=3.4``

處理 Warning
------------

若 ``/etc/make.conf`` 中有寫 ``DEFAULT_VERSIONS=python=3.4`` ，
且與 ``/usr/local/bin/python -c 'import sys; print("%d.%d" % sys.version_info[:2])'`` 的版本不同，
則會有 Warning

