************
Erlang Basic
************

.. toctree::


.. highlight:: erlang


Shell
=====

Quit
    ``^G`` then ``q``

History
    ``h()``
        list history
    ``v(N)``
        show the value of ``history n``

Show variable bindings
    ``b()``

Clean variable binding(s)
    ``f(Var)``
        Set the ``Var`` to unbound
    ``f()``
        Clean all variables

Compile Module
    ``c(module_name)``


Variable
========

+ Capitalize

::

 > One = 1.
 1


Anonymou var
    ``_``

Pattern matching
    ``=``


Atom
====

No matter how long,
cost 4 bytes in 32 bits system,
8 in 64 bits.

No overhead in copy, so it's good for message passing.

::

 > red.
 red

 > red = 'red'.
 red

 > red == 'red'.
 true


Bool
====

+ ``and``
+ ``or``
+ ``xor``
+ ``andalso``: short-circuit operator
+ ``orelse``: short-circuit operator
+ ``not``
+ ``=:=``
+ ``=/=``
+ ``==``
+ ``/=``
+ ``>``
+ ``<``
+ ``>=``
+ ``=<`` *Note this*


Order
-----
     number < atom < reference < fun < port < pid < tuple < list < bit string


Tuples
======

::

 > Point = {3, 4}.
 {3,4}

 > {X, Y} = Point.
 {3,4}

 > {X, _} = Point.


tagged tuple
    ``{km, 100}``


Builtins
------------------------------------------------------------

``element``::

    > element(2, Point).
    3

``setelement``::

    > setelement(2, Point, 100).
    {3, 100}

``tuple_size``::

    > tuple_size(Point).
    2


List
====

Syntax
    ``[e1, e2 ...]``

String is a list (no built-in string type)::

 > [97, 98, 99].
 "abc"

 > [97, 98, 99, 4, 5, 6].
 [97,98,99,4,5,6]

 >[233].
 "é"


*Note*
    Erlang is lack of string manipulations functions.


Operators
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


``++``
    right-associative, eval from right to left.

    This operator (or ``append`` function) will build a *NEW* copy of list,
    it will cost more and more memory in recursive function.

    ref: http://erlang.org/doc/efficiency_guide/listHandling.html
``--``
    right-associative.

They are *right-associative*.

::

    9> [1,2,3] -- [1,2] -- [3].
    [3]
    10> [1,2,3] -- [1,2] -- [2].
    [2,3]


Functions
---------

hd (head)
    pick up the first element::

    > hd([1, 2, 3]).
    1

tl (tail)
    pick up [1:]::

    > tl([1, 2, 3]).
    [2, 3].

    > tl([1, 97, 98]).
    "ab"

length
    ``length(List)``


Cons operator
--------------

* Constructor operator

Syntax
    ``[Term1 | [Term2 | [TermN]]]...``

e.g.
``[Head | Tail]``::

    > Ls = [1, 2, 3, 4].
    [1,2,3,4]

    > [0|Ls].
    [0,1,2,3,4]

    > [Head | Tail] = [1, 2, 3].
    [1,2,3]

    > Head.
    1

    > Tail.
    [2,3]

*Note*
    Do not use ``[1 | 2]``.
    This only work in pattern matching, but break all other functions like ``length``.


List Comprehension
------------------

Syntax
    ``NewList = [Expression || Pattern <- List, Condition1, Condition2, ... ConditionN].``

e.g.::

    > [X * X || X <- [1, 2, 3, 4]].
    [1,4,9,16]

    > [X * X || X <- [1, 2, 3, 4], X rem 2 =:= 0].
    [4,16]


Generator expression
    ``Pattern <- List``.

    This could be more than one in list comprehension::

        > [X + Y || X <- [1, 2], Y <- [10, 20]].
        [11,21,12,22]


Bit Syntax
==========

Erlang provide powerful bit manipulations.

Syntax
-------

quote in ``<<...>>``::

    Value
    Value:Size
    Value/TypeSpecifierList
    Value:Size/TypeSpecifierList

Size
^^^^
    bits or bytes, depends on *Type* or *Unit*.

TypeSpecifierList
^^^^^^^^^^^^^^^^^
    :Type:
        ``integer | float | binary | bytes | bitstring | bits | utf8 | utf16 | utf32``.

        *Note*
            * bits =:= bitstring
            * bytes =:= binary
    :Sign: ``signed | unsigned``
    :Endian: ``big | little | native``
    :Unit:
        ``unit:Integer``

        e.g.: ``unit:8``

e.g.::

    > Color = 16#1200FF.
    1179903
    > Pixel = <<Color:24>>.
    <<18,0,255>>

    > <<X/integer-signed-little>> =  <<-44>>.
    <<"Ô">>
    > X.
    -44

Pattern matching
^^^^^^^^^^^^^^^^

::

    > P = <<255, 0, 0, 0, 0, 255>>.
    <<255,0,0,0,0,255>>

    > <<Pix1:24, Pix2:24>> = P.
    <<255,0,0,0,0,255>>


Bit string
^^^^^^^^^^
    efficient but hard to manipulate

    ::

        <<"this is a bit string!">>.


Operators
---------

* ``bsl``: bit shift left
* ``bsr``: bit shift right
* ``band``: and
* ``bor``: or
* ``bxor``: xor
* ``bnot``: not


Binary Comprehension
--------------------

::

    > [ X || <<X>> <= <<"abcdefg">>, X rem 2 =:= 0 ].
    "bdf"

    > Pixels = <<213,45,132,64,76,32,76,0,0,234,32,15>>.
    <<213,45,132,64,76,32,76,0,0,234,32,15>>
    > RGB = [ {R,G,B} || <<R:8,G:8,B:8>> <= Pixels ].
    [{213,45,132},{64,76,32},{76,0,0},{234,32,15}]

    > << <<R:8, G:8, B:8>> ||  {R,G,B} <- RGB >>.
    <<213,45,132,64,76,32,76,0,0,234,32,15>>
