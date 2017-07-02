:title: Pythoner 讀 「松本行弘的程式世界」 - part 3
:slug: pythoner-read-ruby-book-3
:date: 2014-10-11 20:50
:category: Misc
:tags: book
:author: wdv4758h
:summary: 讀書紀錄

ch 8 Regular Expression
========================================

毫無反應就是 regular expression

書上是介紹 Ruby 裡的 re，基本上長的就是 Perl 樣 (X

基本 re 觀念都差不多

.. code-block:: ruby

    # Ruby

    '<ul><li>a</li>b</ul>'.split(/(<.*?>)/)
    => ["", "<ul>", "", "<li>", "a", "</li>", "b", "</ul>"]

.. code-block:: python

    # Python

    import re
    re.split('(<.*?>)', '<ul><li>a</li>b</ul>')
    >>> ['', '<ul>', '', '<li>', 'a', '</li>', 'b', '</ul>', '']

書上提到 Ruby 1.9 的 re 使用了 `Oniguruma <http://en.wikipedia.org/wiki/Oniguruma>`_ 這個 engine，
Ruby 2.0 後轉到 Oniguruma 的 fork : `Onigmo <https://github.com/k-takata/Onigmo>`_

Python 的話可以看 `re 的 document <https://docs.python.org/3/library/re.html>`_

這章節最後最後提到 DSL (Domain Specific Language)

ch 9-1 Integer
========================================

- 在 C 裡，型態為 int 的狀態下，5 / 2 的結果會是 2
- int 有大小上限
- bitwise operation
- bitmask
- 2's complement

ch 9-2 Float
========================================

- fixed point number (不好用)
- IEEE 754
- 電腦中的浮點數沒有結合律 (誤差會擴大)
- 誤差會累積
- Inf, 0, NaN
- 運算的值的絕對值相差過大時，計算會造成誤差
- cancellation error (相減兩個相近的數字時造成的誤差)

.. code-block:: python

    >>> 10000001.0 + 0.12345678 + 0.11111111 + (-10000000.0)
    1.234567889943719

    >>> 10000001.0 + (-10000000.0) + 0.12345678 + 0.11111111
    1.23456789

    >>> 0.0123456 - 0.0123444
    1.1999999999998123e-06
