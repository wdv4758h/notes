:title: Python - @wraps
:slug: python-wraps
:date: 2014-02-06 11:30
:category: Python
:tags: Python
:author: wdv4758h
:summary: 認識 Python 的 @wraps

在這邊先假設看這篇文章的都知道 decorator

在使用 decorator 時，若沒有經過處理，可能會造成 function 的 property 改變，例如:

.. code-block:: python

    def test(func):
        """this is in test function"""

        def haha():
            """this is in haha function"""

            print("haha")

        return haha

    @test
    def func1():
        """this is in func1"""

        print("func1")

    print(func1.__name__, ',',  func1.__doc__)

    # OUTPUT :
    #   haha , this is in haha function

可以看到 func1 的 `__name__` 和 `__doc__` 都改變了，這通常不是我們想要的，還有可能在 debug 的時候造成麻煩

因此 Python 有了 wraps 這個 decorator 去處理這個問題 (在 functools 裡)

.. code-block:: python

    from functools import wraps

    def test(func):
        """this is in test function"""

        @wraps(func)
        def haha():
            """this is in haha function"""

            print("haha")

        return haha

    @test
    def func1():
        """this is in func1"""

        print("func1")

    print(func1.__name__, ',', func1.__doc__)

    # OUTPUT :
    #   func1 , this is in func1

可以看到，加上了 @wraps 後維持了 function 本來的 property ~
