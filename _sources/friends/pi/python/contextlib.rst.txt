==============
``contextlib``
==============
Python 提供 ``with`` statement 對 Context 做成對的操作，例如開啟/關閉檔案：

.. code:: python

    with open('<filename>') as f:
        # operation on f

``f`` 在進出 ``with`` statement 時會自動被開啟/關閉，不需要 ``f.close()``

``contextlib`` 提供方便的方式自訂類似的功能：

.. code:: python

    from contextlib import contextmanager

    @contextmanager
    def supress(*args):
        try:
            yield
        except args:
            pass

    def foo():
        raise OSError

    with supress(OSError):
        foo()
