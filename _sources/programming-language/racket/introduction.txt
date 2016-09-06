========================================
Racket
========================================


.. contents:: Table of Contents / 目錄




歷史發展
========================================


Lisp 方言時間表
------------------------------

.. image:: /images/programming-language/lisp-dialects-timeline.png


Typed Racket
------------------------------

Typed Racket 是在原本的 Racket 之上加了 gradually-typed 的能力，



實做
========================================

* [GitHub] `Racket <https://github.com/racket/racket>`_
* [GitHub] `Pycket - A rudimentary Racket implementation using RPython <https://github.com/pycket/pycket>`_



安裝
========================================

正常版：

.. code-block:: sh

    $ sudo pacman -S racket
    ...
    Packages (1) racket-6.6-1

    Total Download Size:    43.31 MiB
    Total Installed Size:  227.15 MiB
    ...


瘦身版：

.. code-block:: sh

    # without DrRacket
    $ sudo pacman -S racket-minimal
    ...

    Packages (1) racket-minimal-6.6-1

    Total Download Size:    5.21 MiB
    Total Installed Size:  22.80 MiB
    ...



套件
========================================

Racket 把第三方套件都蒐集在 `Racket Packages <https://pkgs.racket-lang.org/>`_ ，
套件相關的資訊會寫在 ``info.rkt``

這是一個 ``info.rkt`` 的範例：

.. code-block:: racket

    #lang info
    (define collection 'multi)

    (define version "1.1")
    (define deps '("base" ["txexpr" #:version "0.2"] ["sugar" #:version "0.2"] ["markdown" #:version "0.18"] "htdp"
                   "at-exp-lib" "html-lib" "rackjure" "web-server-lib" "scribble-lib" "scribble-text-lib" "rackunit-lib"
                   "gui-lib"))
    (define build-deps '("plot-gui-lib" "scribble-lib" "racket-doc" "rackunit-doc"
                         "plot-doc" "scribble-doc" "slideshow-doc" "web-server-doc" "drracket"))
    (define update-implies '("txexpr" "sugar"))



入門
========================================

官方網站上有 `Cheat Sheet <https://docs.racket-lang.org/racket-cheat/index.html>`_ ，
對於學過類似程式語言的人可以直接去那邊快速上手。
另外還有 `Learn Racket in Y Minutes <https://learnxinyminutes.com/docs/racket/>`_
也是快速上手的好地方。


Hello World
------------------------------

Racket 的執行是打開程式碼後從頭開始依序跑到底的


程式碼：

.. code-block:: racket

    #lang racket

    (printf "Hello World\n")


執行：

.. code-block:: sh

    # 直接用直譯器執行
    $ racket hello.rkt
    Hello World

    # 編譯成執行檔
    $ raco exe hello.rkt
    $ ls -l hello
    -rwxr-xr-x 1 user user 6586613 Sep  6 21:39 hello
    $ ldd hello
            linux-vdso.so.1 (0x00007fffab7e5000)
            libpthread.so.0 => /usr/lib/libpthread.so.0 (0x00007f042c232000)
            libc.so.6 => /usr/lib/libc.so.6 (0x00007f042be94000)
            /lib64/ld-linux-x86-64.so.2 (0x00007f042c44f000)
    $ ./hello
    Hello World


Fibonacci
------------------------------

程式碼：

.. code-block:: racket

    #lang racket

    (define (fib n)
        (if (<= n 1) 1
            (+
                (fib (- n 1))
                (fib (- n 2))
            )
        )
    )

    (time (fib 40))


執行：

.. code-block:: sh

    # 編譯成執行檔
    $ raco exe fib.rkt
    $ ls -l fib
    -rwxr-xr-x 1 user user 6587986 Sep  6 22:05 fib
    $ ldd fib
            linux-vdso.so.1 (0x00007fffab7e5000)
            libpthread.so.0 => /usr/lib/libpthread.so.0 (0x00007f042c232000)
            libc.so.6 => /usr/lib/libc.so.6 (0x00007f042be94000)
            /lib64/ld-linux-x86-64.so.2 (0x00007f042c44f000)
    $ ./fib
    cpu time: 1556 real time: 1555 gc time: 0
    165580141



Fibonacci with Memoize
------------------------------

參考這邊 `Memoize: Lightweight Dynamic Programming <https://docs.racket-lang.org/memoize/index.html>`_

程式碼：

.. code-block:: racket

    #lang racket

    (require memoize)       ; 拉進 memoize

    (define/memo (fib n)    ; define 改成 define/memo
        (if (<= n 1) 1
            (+
                (fib (- n 1))
                (fib (- n 2))
            )
        )
    )

    (time (fib 40))


.. code-block:: sh

    # 編譯成執行檔
    $ raco pkg install memoize  # 會放在 "~/.racket/{VERSION}/pkgs/"
    $ raco exe fib.rkt
    $ ls -l fib
    -rwxr-xr-x 1 user user 6598463 Sep  6 22:27 fib
    $ ldd fib
            linux-vdso.so.1 (0x00007fffab7e5000)
            libpthread.so.0 => /usr/lib/libpthread.so.0 (0x00007f042c232000)
            libc.so.6 => /usr/lib/libc.so.6 (0x00007f042be94000)
            /lib64/ld-linux-x86-64.so.2 (0x00007f042c44f000)
    $ ./fib
    cpu time: 0 real time: 0 gc time: 0
    165580141


參考
========================================

網站
------------------------------

* `The Racket Language <https://racket-lang.org/>`_
* `The Racket Guide <https://docs.racket-lang.org/guide/index.html>`_
* `Quick: An Introduction to Racket with Pictures <https://docs.racket-lang.org/quick/index.html>`_
* `More: Systems Programming with Racket <https://docs.racket-lang.org/more/index.html>`_
* `Continue: Web Applications in Racket <https://docs.racket-lang.org/continue/index.html>`_
* `Racket Documentation <https://docs.racket-lang.org/index.html>`_

* `Learn Racket in Y Minutes <https://learnxinyminutes.com/docs/racket/>`_
* `Beautiful Racket - learn how to make your own programming languages with Racket (and why) <http://beautifulracket.com/>`_
* `How to Design Programs <http://htdp.org/>`_
    - 講 Scheme 的書，但是可以套用到 Racket


論文
------------------------------

* [2015] `Pycket: A Tracing JIT For a Functional Language <http://www.ccs.neu.edu/home/samth/pycket-draft.pdf>`_
