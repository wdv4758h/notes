========================================
簡單介紹
========================================

路過在 Neovim 的 issue 上發現有提到，
只好跑過取幫忙補充資料 (?

以下是回復訊息

----------------------------------------

just some comments about PyPy :P

AFAIK, they are creating a framework (and toolchain) for writing dynamic languages' VM. They use a language called RPython to implement interpreter, and the toolchain can generate Tracing JIT and GC for you. The RPython is a language similar to Python with some restriction of features which are too much dynamic. The major concept is the toolchain will do type inference and some analysis for RPython to generate better result. The overall result is decided by backend, they are using a backend called GenC which generate C code now (but someone can still make other backends, e.g. generate Java bytecode).

So, PyPy is a Python interpreter written in RPython and compiled by GCC or Clang (with RPython's GenC backend).

Pros:

* you can write interpreter in RPython which may cost less effort compare to C or C++ or something.
* you can get a JIT easily (3 lines for a basic version, use some Python decorator can improve it)
* you can get a incremental generational mark-and-sweep GC easily (by just a CLI option)
* you can get some improvement by just update RPython toolchain in the future (JIT or GC or something) (or maybe Software Transactional Memory which they still working on)

Cons:

* RPython's restriction is still not well documented (they have written something, but not specific)
* the toolchain to generate JIT is still slow and need some resource (IIRC, about 16 mins for just generating and compiling a normal Brainfuck interpreter, I tried it last winter)
* we need to make the new VM available for a lot of platforms (effort here)
* maybe the debugging will be much more complex ?

Notice: I'm not a master of this :P

----

Documentation

* `RPython's documentation <http://rpython.readthedocs.org/en/latest/index.html>`_

Other Languages' implementation

* Lisp : `Pixie <https://github.com/pixie-lang/pixie>`_
* PHP : `HippyVM <https://github.com/hippyvm/hippyvm>`_
* Ruby : `Topaz <https://github.com/topazproject/topaz>`_
* Prolog : `Pyrolog <https://bitbucket.org/cfbolz/pyrolog/>`_
* Smalltalk : `RSqueak <https://github.com/HPI-SWA-Lab/RSqueak>`_
