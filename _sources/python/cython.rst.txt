========================================
Cython
========================================


.. contents:: 目錄


介紹
========================================

Cython 可以把 Python 程式碼轉成使用 CPython C API 的程式碼，
轉完後使用 C 編譯器編譯來產生出 shared library，
藉此可以獲得一些效能提昇和節省一點記憶體使用。
但是使用純 Python 轉換的成效沒有很大，
如果要有更大的成效就要使用 Cython 提供的額外 decorator 來調整，
或是使用 Cython 所定義的語言來撰寫，
Cython 定義的語言是 Python 的 superset，
但是多了一些定義靜態型別的方式，
藉此可以讓編譯器做更多優化來提昇效能。



基本使用
========================================

``setup.py`` :

.. code-block:: python

  from Cython.Build import cythonize

  ...

  setup(
    ...,
    ext_modules=cythonize("myproj/**/*.py"),
    ...,
  )


編譯：

.. code-block:: sh

    python setup.py bdist_wheel



Cython + NDK
========================================

基本上會動，只要把一些編譯的環境變數設定好就可以（例如 ``CC`` ），
除非要跟其他非 Python 的程式碼一起處理，
可能就還要看怎麼跟專案本來的 build system 合作。



Cython + Type Hinting
========================================

範例：

.. code-block:: python

    import cython
    import ctypes

    # still be PyObject for compatibility
    def func_py(n: int) -> int:
        return n**n

    # will be C int
    def func_cy_int(n: cython.int) -> int:
        return n**n

    # will be C long long
    def func_cy_longlong(n: cython.longlong) -> cython.longlong:
        return n**n

    # still be PyObject !?
    def func_cy_ctypes(n: ctypes.c_longlong) -> ctypes.c_longlong:
        return n**n


編譯：

.. code-block:: sh

  cython -v -Wextra -Werror -3 --no-docstrings -X annotation_typing=True test.py
  cc test.c -I /usr/include/python3.7m/ -l python3.7m -shared -fPIC -o test.so


參考：

* `Cython - Python Typing Proposal <https://github.com/cython/cython/wiki/Python-Typing-Proposal>`_
* `Cython - Pure Python Mode <http://cython.readthedocs.io/en/latest/src/tutorial/pure.html>`_
* `Cython - Extension types (aka. cdef classes) <http://cython.readthedocs.io/en/latest/src/tutorial/cdef_classes.html>`_
* `Cython 0.27 speeds Python by moving away from oddball syntax - InfoWorld <https://www.infoworld.com/article/3227890/python/cython-027-speeds-python-by-moving-away-from-oddball-syntax.html>`_



Cython + PyInstaller
========================================
