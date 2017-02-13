***************
Erlang Function
***************

.. toctree::


.. highlight:: erlang


Basic
======================================================================

::

    1> F = fun(X) ->
               math:sqrt(X) * 10
           end.

    2> G = fun(X) ->
               Y = math:sqrt(X),
               10 * Y
           end.

Bind function from module
------------------------------------------------------------

Assume we have a function ``f/1`` in the module ``hello``.
If we want to bind ``hello:f`` to variable::

    1> F = fun hello:f/1.
    2> F(...).

Pattern Matching
================

Function Clause
-------------------

Sample: replace if

.. code-block:: python

    def g(gender, name):
        if gender == 'male':
            print('Hello, Mr. {}'.format(name))
        elif:
            print('Hello, Mrs. {}'.format(name))
        else:
            print('Hello, {}'.format(name))


In Erlang::

    g(male, Name) ->
        io:format("Hello, Mr. ~s", [Name]);
    g(female, Name) ->
        io:format("Hello, Mrs. ~s", [Name]);
    g(_, Name) ->
        io.format("Hello, ~s", [Name]).


Guards
=======

Addictional clause to check vars.
Let us check the content of argument, not only shape/position.

It's indicated by ``when``.

It can use only a small set of builtin functions to
guarantee there is'nt no side effect.

Multiple conditions:

- ``,`` (commas): like *and*,
  e.g.: ``when X >= 60, X =< 100 -> ...``
- ``;`` (semicolons): like *or*

::

    is_pass(X)
        when X >= 60, X =< 100 ->
            true.
    is_pass(_) ->
        false.

    > module:is_pass(80).
    true

    > module:is_pass(a).
    true
    %% what happend ?!


``case`` expression
============================================================

It let you move pattern matching inside function.


``if`` expression
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

It's similar to ``case`` but without pattern matching.
