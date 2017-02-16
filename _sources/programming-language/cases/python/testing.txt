========================================
Python Testing
========================================


.. contents:: 目錄



doctest
========================================

* `Python - doctest <https://docs.python.org/3/library/doctest.html>`_
* `PEP 257 - Docstring Conventions <https://www.python.org/dev/peps/pep-0257/>`_
* `PEP 287 - reStructuredText Docstring Format <https://www.python.org/dev/peps/pep-0287/>`_
* `A Guide to NumPy/SciPy Documentation <https://github.com/numpy/numpy/blob/master/doc/HOWTO_DOCUMENT.rst.txt>`_


doctest 就是在 Python source code 裡爬 docstring，
docstring 包含 module 最一開始的匿名字串和 function 下最開始的匿名字串 (也就是 help 可以看到的)，
找出 docstring 裡面格式為 interactive Python sessions 的部份，
拿出來執行並檢查 output

* 利用測試來確保 docstrings 是 up-to-date 的
* regression testing

.. code-block:: python

    def f(x):
        '''
        >>> f(123)
        123
        '''
        return x

    if __name__ == "__main__":
        import doctest
        doctest.testmod()


或是 CLI 直接下 ``python -m doctest -v xxx.py``



unittest (PyUnit)
========================================

* `Python - unittest <https://docs.python.org/3/library/unittest.html>`_


從 JUnit 發展過來的產品，
但是個人感覺有些東西還留有跟 Python convention 不合的地方（例如 ``setUp`` 不是 ``set_up`` ），
為 Python Standard Library 內提供來撰寫測試的主要方式，
但是第三方套件還有一些好用的實做（例如 ``pytest`` ）。

要利用 ``unittest`` 實做測試就要建立新的 class 並繼承 ``unittest.TestCase`` ：

.. code-block:: python

    import unittest

    class TestStringMethods(unittest.TestCase):

        def test_upper(self):
            self.assertEqual('foo'.upper(), 'FOO')

    if __name__ == '__main__':
        unittest.main()

執行測試：

.. code-block:: sh

    # 直接執行
    $ python mytest.py

    # 指定
    $ python -m unittest mytest
    $ python -m unittest mytest.TestStringMethods
    $ python -m unittest mytest.TestStringMethods.test_upper

    # 自動尋找
    $ python -m unittest discover -v


為測試事前準備、事後回收：

.. code-block:: python

    import unittest

    class TestSomething(unittest.TestCase):
        def setUp(self):
            self.file = open("some_file.txt", "r")

        def tearDown(self):
            self.file.close()

        def test_file_access(self):
            self.assertEqual(self.file.readline(), 'XD\n')

    if __name__ == '__main__':
        unittest.main()


把特定的測試標為預期會失敗或是跳過：

.. code-block:: python

    import sys
    import unittest

    class TestSomething(unittest.TestCase):
        def setUp(self):
            self.file = open("some_file.txt", "r")

        def tearDown(self):
            self.file.close()

        @unittest.skip("demonstrating skipping")
        def test_skip(self):
            self.fail("WTF")

        @unittest.skipIf(tuple(sys.version_info)[:2] < (3, 6),
                         "not supported in this library version")
        def test_fstring(self):
            name = self.file.name
            self.assertEqual(f"{name}", name)

        @unittest.skipUnless(sys.platform.startswith("linux"), "requires Linux")
        def test_linux(self):
            pass

        @unittest.expectedFailure
        def test_fail(self):
            self.fail("WTF")


    if __name__ == '__main__':
        unittest.main()


利用 subtest 來區隔不同 iteration：

.. code-block:: python

    import unittest

    class TestSomething(unittest.TestCase):
        def test_even(self):
            for i in range(0, 6):
                with self.subTest(i=i):
                    self.assertEqual(i % 2, 0)


    if __name__ == '__main__':
        unittest.main()


自製 decorator：

.. code-block:: python

    def skipUnlessHasattr(obj, attr):
        if hasattr(obj, attr):
            return lambda func: func
        return unittest.skip("{!r} doesn't have {!r}".format(obj, attr))



pytest
========================================

Python Standard Library 雖然有內建 ``unittest`` ，
但是使用上的方便性還是不夠高，
第三方套件中個人覺得 ``pytest`` 非常好用，
擴充 Plugins 也很多。


安裝
------------------------------

.. code-block:: sh

    pip install pytest


使用
------------------------------

.. code-block:: sh

    # --doctest-modules: 跑 doctest
    # -v: verbose
    # --strict: 把 warning 當 error
    py.test --doctest-modules -v --strict


pytest 設定檔
------------------------------

.. code-block:: ini

    # pytest.ini
    [pytest]
    addopts = --doctest-modules -v --strict -n8


pytest-xdist - 同時執行多項測試
-------------------------------

:URL: https://github.com/pytest-dev/pytest-xdist

``pytest-xdist`` 是一個 ``pytest`` 的 plugin，
可以使用多顆 CPU 或是多台機器來同時執行測試，
以加速所需要花費的時間。


pytest-cov - 測試涵蓋率
-------------------------------

:URL: https://github.com/pytest-dev/pytest-cov

可以產生出多種格式的 Report，
例如直接在終端機顯示、HTML、XML 等。



nose
========================================

安裝
------------------------------

.. code-block:: sh

    pip install nose


使用
------------------------------

.. code-block:: sh

    nosetests --with-doctest -v

