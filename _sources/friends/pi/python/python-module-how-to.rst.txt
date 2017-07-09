===============================================================================
Python module how to
===============================================================================

  It's not at all important to get it right the first time.
  It's vitally important to get it right the last time.

  （起初就把事情做對是完全沒必要的。但最後要把事情做對是絕對必要的）

  -- Andrew Hunt and David Thomas


這份文件將從單一檔案的 module 開始，一步一步包裝成 package，示範如何寫一個簡單的 Python module。


單一檔案的 module
-------------------------------------------------------------------------------
我想要寫個 module，用來收集一些有趣的 Python code，以後也可以 call 來用。

例如費氏數列在 Python 裡有很多種方法可以產生，而我想要收集不同的寫法。

``fibo.py`` 收集了遞廻、迭代、以及數學解：

..  code:: python

  from math import sqrt


  def recursive(n):
      if n == 0:
          return 0
      elif n == 1:
          return 1
      else:
          return recursive(n - 1) + recursive(n - 2)


  def iterative(n):
      a, b = 0, 1
      for i in range(n):
          a, b = b, a+b
      return a


  def mathematical(n):
      return ((1+sqrt(5))**n-(1-sqrt(5))**n)/(2**n*sqrt(5))

我可以把它們都裝在 ``fibo.py`` 裡面，並且在 ``main.py`` 裡面使用：

..  code:: python

  import fibo

  print(fibo.recursive(20))
  print(fibo.iterative(20))
  print(fibo.mathematical(20))

只要把 ``fibo.py`` 放在 ``main.py`` 的旁邊，Python 就能載入它： ::

  .
  |-- main.py
  `-- fibo.py

``import fibo`` 會產生 ``fibo`` 這個 module 物件，
而 ``fibo.py`` 的全域變數會通通被包在裡面。


和單一檔案沒兩樣的 package
-------------------------------------------------------------------------------
接下來，我們把 ``fibo.py`` 變成一個 package。

1.  首先，把 ``fibo.py`` 重新命名成 ``__init__.py``
2.  建立一個 ``fibo`` 目錄
3.  把 ``__init__.py`` 丟進去

現在你應該會有這些東西： ::

  .
  |-- fibo/
  |   `-- __init__.py
  `-- main.py

``__init__.py`` 的內容就是剛才費氏數列的 code。

再執行一次 ``main.py`` ，確定每樣東西都沒有壞掉。

當 ``import`` 的對象是一個目錄的時候，Python 會去那個目錄裡面尋找 ``__init__.py`` 。

如果有找到的話，執行它，並且把它的所有全域變數都包在 module 物件裡面，在這個例子裡就是 ``fibo`` 。

要注意如果 ``fibo/`` 和 ``fibo.py`` 都存在的話，目錄會優先處理。


Package
-------------------------------------------------------------------------------
``fibo.py`` 讓我很開心，但過一陣子我又看到有趣的 Python code，也想收集起來。

``factor.py`` 收集了各種不同的寫法：

..  code:: python

  def recursive(n):
      if n <= 1:
          return 1
      else:
          return n * recursive(n - 1)


  def iterative(n):
      x = 1
      for i in range(2, n + 1):
          x = x * i

      return x

我想要把 ``fibo`` 和 ``factor`` 放在同一個 module 裡面，叫做 ``toy`` 。

--------

現在整個 package 都被 ``fibo`` 佔據了，我們得先把它移一下。

1.  建立一個目錄，叫做 ``toy``
2.  把 ``fibo/__init__.py`` 重新命名成 ``fibo.py`` ，丟進 ``toy``
3.  新增一個檔案 ``toy/factor.py`` ，放入上面收集的各種階乘的 code
4.  新增一個檔案 ``toy/__init__.py`` ，裡面寫兩行

    ..  code:: python

      from . import fibo
      from . import factor

5.  把 ``main.py`` 裡面的 import 修改一下：

    ..  code:: python

      from toy import fibo
      from toy import factor

      print(fibo.recursive(20))
      print(fibo.iterative(20))
      print(fibo.mathematical(20))
      print()

      print(factor.recursive(10))
      print(factor.iterative(10))

現在你應該會有這些東西： ::

  .
  |-- toy
  |   |-- __init__.py
  |   |-- fibo.py
  |   `-- factor.py
  `-- main.py

登登，現在費氏數列和階乘的 code 都收集好，放在同一個 module 裡面了。

--------

最後的一點點說明
-------------------------------------------------------------------------------
``import xxx`` 會產生一個 module 物件 ``xxx`` 。

``from xxx import yyy`` 會將 module ``xxx`` 載入，並把 ``yyy`` 連結到 ``xxx.yyy`` 。（但 ``xxx`` 這個變數不會留著）

當 module 裡面的 ``__init__.py`` 執行了 ``from . import yyy`` 的時候，
Python 會在這個 package 裡面尋找 module ``yyy`` 。

在這個例子中， ``toy/__init__.py`` 執行了 ``from . import fibo`` ，
於是 Python 會在 ``toy`` 這個 package 裡面尋找 module ``fibo`` 。
這個 module ``fibo`` 可以是 ``fibo/`` ，也可以是 ``fibo.py`` 。
