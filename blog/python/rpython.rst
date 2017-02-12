:title: RPython Intro.
:slug: RPython
:date: 2014-10-21 08:50
:category: Python
:tags: PyPy
:author: wdv4758h
:summary: a brief view of RPython

(not complete)

What's RPython
========================================

RPython is a subset of Python

.. table::
    :class: table table-bordered

    +----------+--------------------------------------------------+
    | Language | RPython                                          |
    +----------+--------------------------------------------------+
    | Type     | Static (not Manifest Typing, but Type Inference) |
    +----------+--------------------------------------------------+


- http://stackoverflow.com/questions/7161856/what-is-statically-typed-in-rpython

Not all code in the PyPy repository is RPython.
For example, there are code generators (e.g. in rlib.parsing) that run at compile time and produce RPython code,
but are not RPython (frequently with a "NOT_RPYTHON" docstring, by the way).
Also, large parts of the standard library are written in full Python (mostly taken straight from CPython).

To make a C code generator, code on interpreter level has to restrict to a subset of Python.
(Code on application level cat still use full Python)

PyPy is **not source-to-source translations**, it start translation from live **python code objects** .

Type Inference & Static Typing
------------------------------

Types are not stated explicitly, they are infered, so RPython is static typing.

Static typing doesn't mean the type has to be written out (that's **manifest typing**),
it means each expression has a single type that never changes.

Analysis
++++++++++++++++++++

.. code-block:: python

    def add(a, b):
        return a + b

We cann't infer a (non-generic) type for a function like above,
the return type depends on arguments,
so the return type is determined by analysis the arguments (when the function is called)

RPythonic
------------------------------

Flow restrictions
++++++++++++++++++++

.. table::
    :class: table table-bordered

    +--------------------+---------------------------------------------------------------------------------+
    | variable           |                                                                                 |
    +--------------------+---------------------------------------------------------------------------------+
    | constant           | globals are considered constants (global instances don't have this restriction) |
    +--------------------+---------------------------------------------------------------------------------+
    | control structures |                                                                                 |
    +--------------------+---------------------------------------------------------------------------------+
    | range              |                                                                                 |
    +--------------------+---------------------------------------------------------------------------------+
    | definitions        | run-time definition of classes or functions is not allowed                      |
    +--------------------+---------------------------------------------------------------------------------+
    | generators         |                                                                                 |
    +--------------------+---------------------------------------------------------------------------------+
    | exceptions         | fully supported                                                                 |
    +--------------------+---------------------------------------------------------------------------------+

Object restrictions
++++++++++++++++++++

.. table::
    :class: table table-bordered

    +------------------+-------------------------------------------------------------------------+
    | int, float, bool | works                                                                   |
    +------------------+-------------------------------------------------------------------------+
    | strings          |                                                                         |
    +------------------+-------------------------------------------------------------------------+
    | tuple            | no variable-length tuples                                               |
    +------------------+-------------------------------------------------------------------------+
    | lists            | annotator can figure out most of the time that your list is fixed-size, |
    |                  | even when you use list comprehension                                    |
    +------------------+-------------------------------------------------------------------------+
    | dicts            | unique key type only                                                    |
    +------------------+-------------------------------------------------------------------------+
    | functions        |                                                                         |
    +------------------+-------------------------------------------------------------------------+

Integer Types
++++++++++++++++++++

build a Python VM with RPython
========================================
