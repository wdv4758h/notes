========================================
Python Testing
========================================


.. contents:: 目錄



TL;DR
========================================

用 ``pytest``


::

    pytest
    pytest-sugar          # show better test result
    pytest-timeout        # abort hanging tests
    pytest-forked         # run each test in a forked subprocess
    pytest-xdist          # -n JOBS
    pytest-cov            # coverage
    pytest-runner         # "setup.py test" support
    pytest-benchmark      # benchmark
    pytest-profiling      # profile graph
    pytest-rerunfailures  # re-runs failed tests up to -n times to eliminate flakey failures
    pytest-incremental    # modify the order of test cases base on your code modification
    pytest-echo           # print env, software version, attributes
    pytest-bdd            # behavioral driven development
    hypothesis            # property based testing, has pytest plugin
    pytest-faker          # Faker integration, generate fake data
    pytest-randomly       # randomly order tests
    pytest-html           # generating HTML reports for pytest results
    pytest-instafail      # show failures instantly
    pytest-factoryboy
    pytest-mock
    pytest-faulthandler
    pytest-xprocess
    pytest-asyncio
    pytest-variables
    pytest-play
    pytest-cloud
    pytest-cpp
    pytest-splinter
    ##############################
    # some frameworks support
    ##############################
    pytest-django
    pytest-flask
    pytest-twisted
    pytest-qt
    pytest-selenium



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

pytest 會自動去發現符合 convention 的測試，
也就是 ``test_*.py`` 或 ``*_test.py`` ，
對於這些檔案會進去找 ``test_*`` 的函式或是 ``Test*::test_*`` method。

一般 Python 專案放置的測試位置有兩種，
一種是最上層的 ``tests/`` 資料夾：

::

    layout1
    ├── mypkg
    │   ├── __init__.py
    │   └── mymodule.py
    ├── setup.py
    └── tests
        └── test_mymodule.py

另一種是在 Python Package 內的 ``tests/`` 資料夾：

::

    layout2
    ├── mypkg
    │   ├── __init__.py
    │   ├── mymodule.py
    │   └── test
    │       └── test_mymodule.py
    └── setup.py


相關範例可以參考 `examples 資料夾 <https://github.com/wdv4758h/notes/tree/master/programming-language/cases/python/examples/py.test>`_


pytest 雖然自己提供了直接定義函式並使用 ``assert`` 的方法來撰寫測試，
但是原本使用 ``unittest`` 的方反撰寫的測試也仍然支援。


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
    pytest --doctest-modules -v --strict


pytest fixture
------------------------------

pytest 的 fixture 是接在函式參數寫上對應的名稱即可，
例如需要暫時的資料夾就寫 ``tempdir`` ：

.. code-block:: python

    def test_needsfiles(tmpdir):
        print(tmpdir)
        pass


列出支援的 fixture：

.. code-block:: sh

    $ pytest --fixtures
    ...
    cache -- /tmp/venv/lib/python3.6/site-packages/_pytest/cacheprovider.py:190
        Return a cache object that can persist state between testing sessions.

        cache.get(key, default)
        cache.set(key, value)

        Keys must be a ``/`` separated value, where the first part is usually the
        name of your plugin or application to avoid clashes with other cache users.

        Values can be any object handled by the json stdlib module.
    capsys -- /tmp/venv/lib/python3.6/site-packages/_pytest/capture.py:160
        Enable capturing of writes to sys.stdout/sys.stderr and make
        captured output available via ``capsys.readouterr()`` method calls
        which return a ``(out, err)`` tuple.
    ...


如果 fixture 不夠用可以安裝第三方套件或是自行撰寫，
安裝完後一樣可以在列表中看到：

.. code-block:: sh

    $ pytest --fixtures
    ...

    -------------------------------- fixtures defined from pytest_django.fixtures --------------------------------
    db -- /tmp/venv/lib/python3.6/site-packages/pytest_django/fixtures.py:142
        Require a django test database

        This database will be setup with the default fixtures and will have
        the transaction management disabled. At the end of the test the outer
        transaction that wraps the test itself will be rolled back to undo any
        changes to the database (in case the backend supports transactions).
        This is more limited than the ``transactional_db`` resource but
        faster.

        If both this and ``transactional_db`` are requested then the
        database setup will behave as only ``transactional_db`` was
        requested.
        transactional_db -- /tmp/venv/lib/python3.6/site-packages/pytest_django/fixtures.py:164
        Require a django test database with transaction support

        This will re-initialise the django database for each test and is
        thus slower than the normal ``db`` fixture.

        If you want to use the database with transactions you must request
        this resource.  If both this and ``db`` are requested then the
        database setup will behave as only ``transactional_db`` was
        requested.
    ...


另外這邊有各 pytest plugins 跟 Python 版本的相容狀況 `網站 <http://plugincompat.herokuapp.com/>`_


pytest 設定檔
------------------------------

.. code-block:: ini

    # pytest.ini
    [pytest]
    addopts = --doctest-modules -v --strict -n8


自製 fixture 和 plugin
------------------------------

檢查哪些 plugins 是目前會使用到的：

.. code-block:: sh

    $ pytest --trace-config


不使用特定 plugin：

.. code-block:: sh

    $ pytest -p no:NAME


在每個測試程式碼的資料夾都可以放 ``conftest.py`` 來擴充 pytest，
可以操控的內容包含：

* fixtures
* external plugin loading: ``pytest_plugins = "someapp.someplugin"``
* hooks


範例一：

.. code-block:: python

    # conftest.py

    import pytest


    @pytest.fixture()
    def myitem():
        return "this is my item"

.. code-block:: python

    # test_mymodule

    def test_myitem(myitem):
        assert myitem == "this is my item"


範例二（更改錯誤訊息）：

.. code-block:: python

    # conftest.py

    def pytest_assertrepr_compare(op, left, right):
        if isinstance(left, int) and isinstance(right, int) and op == "==":
            return ['Comparing number:',
                    '   vals: %s != %s' % (left, right)]

.. code-block:: python

    # test_mymodule

    def test_myint():
        assert 1 == 0



客製化測試失敗時的輸出
------------------------------

.. code-block:: python

    # conftest.py

    from mymodule import Foo

    def pytest_assertrepr_compare(op, left, right):
        if isinstance(left, Foo) and isinstance(right, Foo) and op == "==":
            return ['Comparing Foo instances:',
                    '   vals: %s != %s' % (left.val, right.val)]



pytest-xdist - 同時執行多項測試
-------------------------------

:URL: https://github.com/pytest-dev/pytest-xdist

``pytest-xdist`` 是一個 ``pytest`` 的 plugin，
可以使用多顆 CPU 或是多台機器來同時執行測試，
以加速所需要花費的時間。


.. code-block:: sh

    $ pytest -n auto tests/



pytest-cov - 測試涵蓋率
-------------------------------

:URL: https://github.com/pytest-dev/pytest-cov

可以產生出多種格式的 Report，
例如直接在終端機顯示、HTML、XML 等。


pytest-icdiff
-------------------------------

:repo: https://github.com/hjwp/pytest-icdiff

利用 `ICDiff <https://www.jefftk.com/icdiff>`_ 改善比較的結果


範例
-------------------------------


socket
++++++++++++++++++++


https://pypi.python.org/pypi/pytest-socket



Hypothesis
========================================

`Hypothesis <https://github.com/HypothesisWorks/hypothesis>`_
支援「property-based testing」，
藉由定義可接受的資料來產生測試程式，
為人熟知的是 Haskell 的 QuickCheck，
但是 Hypothesis 的設計跟 QuickCheck 有很大的差異，
並且著重於跟現有其他測試風格整合。
Hypothesis 在安裝後直接可以跟 pytest 整合，
所以不需要改動既有的測試架構。

property-based testing 源自於 2000 年
由 Koen Claessen 和 John Hughes 提出的論文
「QuickCheck: A Lightweight Tool for Random Testing of Haskell Programs」，
論文中提出一個叫 QuickCheck 的 Haskell library，
可以藉由函式參數的型別來隨機產生測試資料，
此作法後來在函數式程式語言廣為流行，
也漸漸在更多語言中出現。

在使用 Hypothesis 時主要有兩種方式，
一種是使用 Hypothesis 提供的 strategy 針對不同型別的資料做調整，
另一種是寫好 type hinting 後使用
Hypothesis 的 infer 模式來自動選出需要的 strategy，
此外也可以額外指定一定要跑到的範例資料。


參考：

* `Brief Introduction to Haskell - Chapter 8: Property based testing <https://github.com/fpinscala/fpinscala/wiki/Chapter-8:-Property-based-testing>`_



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



Robot Framework
========================================

:URL: http://robotframework.org/

Robot Framework 是針對 ATDD（Acceptance Test-Driven Development）的 Framework，
採用 Keyword-Driven 的方式來撰寫 User Story 作為測試，
因此和 ``pytest`` 這種比較偏技術性的測試不同（若要相比的話以 ``pytest-bdd`` 比較類似），
屬於比較著重客戶需求的方式。

適用於測試人員和 QA，
尤其是專門的測試人員的程式設計能力不強時，
藉由 Keyword 的方式可以讓他們能夠撰寫測試。

Robot Framework 的 Report 是一大強項，
可以產生完整詳細的測試 Report。


安裝
------------------------------

.. code-block:: sh

    $ pip install robotframework
    $ robot --version
    Robot Framework 3.0.2 (Python 3.6.0 on linux)


使用
------------------------------

Robot Framework 提供了兩個 Stript 來輔助使用：

* ``rebot`` 來執行測試（例如 ``rebot tests.robot`` ）
* ``rebot`` 來處理產生的資料（例如 ``rebot output.xml`` ）


範例一 - 架構輪廓
++++++++++++++++++++

Robot Framework 支援用好幾個不同的格式來撰寫測試，
包含：

* Plain Text
* HTML
* reStructuredText


``mytests.robot`` ：

.. code-block:: robotframework

    *** Settings ***
    Documentation     A simple test example
    ...
    ...               This is just a really simple one.

    *** Test Cases ***
    Test Robot Framework Logging
        Log   "Test Logging"


.. code-block:: sh

    # 執行測試
    $ robot mytests.robot
    ==============================================================================
    Mytests :: A simple test example
    ==============================================================================
    Test Robot Framework Logging                                          | PASS |
    ------------------------------------------------------------------------------
    Mytests :: A simple test example                                      | PASS |
    1 critical test, 1 passed, 0 failed
    1 test total, 1 passed, 0 failed
    ==============================================================================
    Output:  /tmp/myproj/output.xml
    Log:     /tmp/myproj/log.html
    Report:  /tmp/myproj/report.html

    # 跑完測試會產生 report.html，可以在瀏覽器中看整體的狀況
    $ python -m http.server



範例二 - 使用內建 Library
+++++++++++++++++++++++++

以下嘗試使用 Robot Framework 內建的 Library 來輔助撰寫測試，
這邊使用了 ``String`` 內的 ``Generate Random String`` 。

.. code-block:: robotframework

    *** Settings ***
    Documentation     A simple test example
    ...
    ...               This is just a really simple one.

    Library    String


    *** Test Cases ***
    Test Robot Framework Logging
        Log   "Test Logging"
        Log Many  First Entry  Second Entry
        Log To Console  still running

    Test For Loop
        : FOR    ${INDEX}    IN RANGE    1    3
        \    Log    ${INDEX}
        \    ${RANDOM_STRING}=    Generate Random String    ${INDEX}
        \    Log    ${RANDOM_STRING}


.. code-block:: sh

    $ robot mytests.robot
    ==============================================================================
    Mytests :: A simple test example
    ==============================================================================
    Test Robot Framework Logging                                          ..still running
    Test Robot Framework Logging                                          | PASS |
    ------------------------------------------------------------------------------
    Test For Loop                                                         | PASS |
    ------------------------------------------------------------------------------
    Mytests :: A simple test example                                      | PASS |
    2 critical tests, 2 passed, 0 failed
    2 tests total, 2 passed, 0 failed
    ==============================================================================
    Output:  /tmp/myproj/output.xml
    Log:     /tmp/myproj/log.html
    Report:  /tmp/myproj/report.html


範例三 - 自己撰寫 Keyword
+++++++++++++++++++++++++

.. code-block:: robotframework

    *** Settings ***

    *** Test Cases ***
    Test Robot Framework Logging
        Log    Test Logging

    Test My Robot Framework Logging
        My Logging    My Message    WARN

    *** Keywords ***
    My Logging
        [Arguments]    ${msg}    ${level}       # 兩個參數
        Log    ${msg}    ${level}


.. code-block:: sh

    $ robot mytests.robot
    ==============================================================================
    Mytests
    ==============================================================================
    Test Robot Framework Logging                                          | PASS |
    ------------------------------------------------------------------------------
    [ WARN ] My Message
    Test My Robot Framework Logging                                       | PASS |
    ------------------------------------------------------------------------------
    Mytests                                                               | PASS |
    2 critical tests, 2 passed, 0 failed
    2 tests total, 2 passed, 0 failed
    ==============================================================================
    Output:  /tmp/myproj/output.xml
    Log:     /tmp/myproj/log.html
    Report:  /tmp/myproj/report.html



範例四 - 把 Keyword 獨立出來以便共用
++++++++++++++++++++++++++++++++++++

``myresource.robot`` ：

.. code-block:: robotframework

    *** Keywords ***
    My Logging
        [Arguments]    @{arg}
        Log Many    @{arg}


``mytests.robot`` ：

.. code-block:: robotframework

    *** Settings ***
    Resource        myresource.robot

    *** Test Cases ***
    Test Robot Framework Logging
        Log    "Test Logging"

    Test My Logging
        My Logging   "Test My Logging 1"   "Test My Logging 2"


.. code-block:: sh

    $ robot mytests.robot
    ==============================================================================
    Mytests
    ==============================================================================
    Test Robot Framework Logging                                          | PASS |
    ------------------------------------------------------------------------------
    Test My Logging                                                       | PASS |
    ------------------------------------------------------------------------------
    Mytests                                                               | PASS |
    2 critical tests, 2 passed, 0 failed
    2 tests total, 2 passed, 0 failed
    ==============================================================================
    Output:  /tmp/myproj/output.xml
    Log:     /tmp/myproj/log.html
    Report:  /tmp/myproj/report.html


參考
========================================

* `In py.test, what is the use of conftest.py files? <http://stackoverflow.com/a/34520971/3880958>`_
