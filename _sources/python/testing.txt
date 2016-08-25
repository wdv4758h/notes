========================================
Python Testing
========================================

Tools
========================================

doctest
------------------------------

- https://docs.python.org/3/library/doctest.html

doctest 就是在 Python source code 裡爬 docstring，
docstring 包含 module 最一開始的匿名字串和 function 下最開始的匿名字串 (也就是 help 可以看到的)，
找出 docstring 裡面格式為 interactive Python sessions 的部份，
拿出來執行並檢查 output

- 利用測試來確保 docstrings 是 up-to-date 的
- regression testing

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

或是 command line 直接下 ``python -m doctest -v xxx.py``

unittest (PyUnit)
------------------------------

- https://docs.python.org/3/library/unittest.html

- inspired by JUnit
- support
    * test automation
    * sharing of setup and shutdown code for tests
    * aggregation of tests into collections
    * independence of the tests from the reporting framework

command line 直接下 ``python -m unittest discover -v``

nose
------------------------------

install : ``sudo pacman -S python-nose``

``nosetests --with-doctest -v``

pytest
------------------------------

install : ``sudo pacman -S python-pytest``

.. code-block:: ini

    # pytest.ini
    [pytest]
    python_files=*.py

``py.test --doctest-modules -v --strict``
