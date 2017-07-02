:title: Try the jitviewer
:slug: jitviewer
:date: 2014-10-15 17:20
:category: Python
:tags: PyPy, Python
:author: wdv4758h
:summary: something about PyPy jitviewer

the jitviewer
========================================

target
------------------------------

analysis log from PyPy, and display Python bytecode & jit operations via the web

install
------------------------------

**jitviewer is a PyPy2 only program now (it need rpython)**

1. create the virtual environment

.. code-block:: sh

    virtualenv env-pypy -p /usr/bin/pypy

2. active the virtual environment

.. code-block:: sh

    source env-pypy/bin/activate

3. get the PyPy2 source code (for rpython)

.. code-block:: sh

    wget https://bitbucket.org/pypy/pypy/downloads/pypy-2.4.0-src.tar.bz2
    tar -xvf pypy-2.4.0-src.tar.bz2

4. install jitviewer

.. code-block:: sh

    pip install jitviewer

5. set the env

.. code-block:: sh

    setenv PYTHONPATH pypy-2.4.0-src

6. run the sample

.. code-block:: sh

    jitviewer.py --log log

create log of PyPy
------------------------------

.. code-block:: sh

    setenv PYPYLOG jit-log-opt,jit-backend-counts:myprogram.log
    pypy -c your_program.py

with PyPy3
------------------------------

As jitviewer is a PyPy2 only program now (2014-10-15),
you should run your program by PyPy3 and output the log,
then use jitviewer with PyPy2 to analysis the log.

expect in the future
----------------------------------------

There are something that I think it should have ...

- PyPy3 compatibility

    jitviewer with PyPy3 is not working now,
    the smaller part is the syntax in jitviewer (something like print function),
    the bigger part is the rpython module ...

    At the moment, rpython has a lot of Python 2 only syntax (even in PyPy3 source code).

- CPython compatibility

    This means to remove the depenency of rpython.

note
------------------------------

The PyPy does not modify the output of Python bytecodes,
so the Python bytecodes output from CPython's dis module or PyPy's are the same.
