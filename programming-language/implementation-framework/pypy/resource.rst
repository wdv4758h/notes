========================================
RPython Toolchain 相關資源
========================================


.. contents:: 目錄


使用 RPython Toolchain 的專案
========================================

官方有一個 `清單 <https://rpython.readthedocs.io/en/latest/examples.html>`_ ，
底下則是蒐集我看到的，
可能有的不在官方清單上：

* `PyPy <http://pypy.org/>`_
    - fast, compliant alternative implementation of the Python language
* `Topaz <https://github.com/topazproject/topaz>`_
    - an implementation of the Ruby programming language
    - `Announcing Topaz, an RPython powered Ruby interpreter <https://morepypy.blogspot.tw/2013/02/announcing-topaz-rpython-powered-ruby.html>`_
* `HippyVM <https://github.com/hippyvm/hippyvm>`_
    - an implementation of the PHP language using PyPy technology
* `PyHP <https://github.com/juokaz/pyhp>`_
    - an implementation of the PHP language using PyPy technology
* `Pixie <https://github.com/pixie-lang/pixie>`_
    - an implementation of lightweight Lisp
* `RSqueak <https://github.com/HPI-SWA-Lab/RSqueak/>`_
    - an implementation of Squeak (a dialect of Smalltalk)
* `Pyrolog <https://bitbucket.org/cfbolz/pyrolog>`_
    - an implementation of Prolog
* `Pycket <https://github.com/pycket/pycket>`_
    - a rudimentary Racket implementation using RPython
* `SQPyte <https://bitbucket.org/softdevteam/sqpyte>`_
    - an implementation of the SQLite bytecode on top of RPython and its JIT
* `Pydgin <https://github.com/cornell-brg/pydgin>`_
    - a Python DSL for generating instruction set simulators
* `RPySOM <https://github.com/SOM-st/RPySOM>`_
    - The Simple Object Machine Smalltalk implemented in RPython
* `Pyrlang <https://bitbucket.org/hrc706/pyrlang/overview>`_
    - an Erlang BEAM bytecode interpreter in RPython
    - `Experiments in Pyrlang with RPython <https://morepypy.blogspot.tw/2015/02/experiments-in-pyrlang-with-rpython.html>`_



相關 Talks
========================================

* [PyCon 2016] `Building an interpreter in RPython <https://us.pycon.org/2016/schedule/presentation/1738/>`_



相關論文
========================================

* [2016] `Parallel Virtual Machines with RPython <http://people.inf.ethz.ch/meierrem/DLS_2016.pdf>`_



相關文章
========================================

* `Running Numba on PyPy <http://www.embecosm.com/2017/01/19/running-numba-on-pypy>`_



相關專案
========================================

* `RPLY <https://github.com/alex/rply>`_
    - A pure Python parser generator, that also works with RPython
* `divspl <https://github.com/di/divspl>`_
    - An implementation of a FizzBuzz DSL using rply
* webkit_bridge
    - a bridge between WebKit and a PyPy-based interpreter, create browsers which can natively load scripts in your language via script tags and even access the DOM, just like JavaScript
    - mirror: https://github.com/wdv4758h/ampify/tree/master/src/webkit_bridge
    - mirror: https://github.com/wdv4758h/pypy-lang/tree/master/webkit_bridge
