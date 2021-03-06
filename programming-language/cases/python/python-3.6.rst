========================================
Python 3.6
========================================


.. contents:: 目錄


PEP 498: Formatted string literals
========================================

``f-strings`` 這個新 feature 的加入是因為先前有太多狀況是在寫冗餘的 format，
所以特別加入這個 feature 來讓使用變簡單。

原本：

.. code-block:: python

    (a, b, c) = (1, 2, 3)
    s = "{c} | {b} | {a}".format(a=a, b=b, c=c)

現在可以：

.. code-block:: python

    (a, b, c) = (1, 2, 3)
    s = f"{c} | {b} | {a}"



PEP 526: Syntax for variable annotations
========================================

把原本在 PEP 484 加入的函式 Type Hinting 擴增到變數的使用上。

.. code-block:: python

    primes: List[int] = []

    captain: str  # Note: no initial value!

    class Starship:
        stats: Dict[str, int] = {}



PEP 515: Underscores in Numeric Literals
========================================

在撰寫數字較長的數值時，
會因為長度的關係而不好閱讀及判斷，
因此有些程式語言可以在數值中任意加入分隔符號來做斷點，
而在 PEP 515 中，
Python 也加入了 ``_`` 作為分隔符號。

.. code-block:: python

    x = 1_000_000_000_000_000
    y = 0x_FF_FF_FF_FF
    z = 2_3_4_5
    s = '{:_}'.format(1000000)      # '1_000_000'
    t = '{:_x}'.format(0xFFFFFFFF)  # 'ffff_ffff'


相關 Commits：

* https://github.com/python/cpython/commit/500b6de0015cdec5cf59a6d1178892e077f3031d
* https://github.com/python/cpython/commit/c563673a67e8c725e99e4a542d74d634d965c6ae


更多 Asynchronous 的支援
========================================

* PEP 525: Asynchronous Generators
* PEP 530: Asynchronous Comprehensions



新 module — secrets
========================================

內含一些函數可以產生亂度較強的 random 數值。

* `PEP 506 - Adding A Secrets Module To The Standard Library <https://www.python.org/dev/peps/pep-0506/>`_
* https://docs.python.org/3.6/library/secrets.html



新 dict 實做
========================================

* https://morepypy.blogspot.com/2015/01/faster-more-memory-efficient-and-more.html


相關檔案：

* https://github.com/python/cpython/blob/master/Objects/dictobject.c


相關 Commits：

* https://github.com/python/cpython/commit/2330b19b3f6f0fd4e524f445eba05b8c1396736b



DTrace 和 SystemTap 支援
========================================

* https://docs.python.org/3.6/whatsnew/3.6.html#whatsnew36-tracing



參考
========================================

* `What's New In Python 3.6 <https://docs.python.org/3.6/whatsnew/3.6.html>`_
* `Python 3.6 & Performance. A Love Story <https://speakerdeck.com/playpauseandstop/python-3-dot-6-and-performance-a-love-story>`_
    - `perf <http://perf.readthedocs.io/en/latest/>`_
        + 在 Linux 下會蒐集一些例如 ASLR 有無開啟、IRQ affinity 等可能影響效率的系統層資訊
        + `perf/_collect_metadata.py <https://github.com/haypo/perf/blob/master/perf/_collect_metadata.py>`_
    - CPython 2.7 仍是目前最快的版本，但是效能 CPython 3.6 > CPython 3.5 > CPython 3.4
    - asyncio.Future 和 asyncio.Task 都用 C 重新實做
    - string 和 bytes 的處理有顯著提昇
    - glob 的處理有顯著提昇
    - dict 的新實做類似 PyPy 內的 dict，記憶體用量較小，且會保有原本的順序
* `Tiny Python 3.6 Notebook <https://github.com/mattharrison/Tiny-Python-3.6-Notebook/blob/master/python.rst>`_
    - 列了 Python 3.6 整個語言的特色範例，用於快速複習新的 Python，不適合初學者
