:title: closure 概念
:slug: closure
:date: 2014-02-07 21:06
:category: Misc
:tags: closure, program
:author: wdv4758h
:summary: closure

Closure 擁有非區域變數且非參數的變數

.. code-block:: javascript

    // Javascript
    function func() {
        var x = 10;
        function f(y) {
            return x + y;
        }
        return f;
    }

    var test = func();
    func(10);   // 20
    func(5);    // 15

這個例子可以看到 x 是個 func 的區域變數，但是在 f 當中又用到 x，
對於 f 來說 x 既不是區域變數又不是參數

.. code-block:: python

    # Python 3
    def gen(num):
        def func(inc):
            nonlocal num
            print(num + inc)
        return func

    s = gen(10)
    s(2)    # 12
    s(5)    # 15

Reference
========================================

- `Closure (computer programming) - Wikipedia <https://en.wikipedia.org/wiki/Closure_(computer_programming)>`_
- `[JavaScript] Closure 概念 <http://www.kvzhuang.net/posts/109906-javascript-closure>`_
- `[Closure] JavaScript使用 Closure模擬出 Private Member <http://www.kvzhuang.net/posts/109890-closure-javascript-closure-private>`_
- `JavaScript Essence: Closure <http://openhome.cc/Gossip/JavaScript/Closure.html>`_
