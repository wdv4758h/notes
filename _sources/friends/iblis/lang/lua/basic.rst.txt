Lua basic
===========================

.. toctree::

.. highlight:: lua


Terms
---------------------------

:Chunk: a sequence of statements


Quote
---------------------------

::

    > 'hello' == "hello"  -- true


Function
---------------------------

::

    function t(args)
        ...
    end


Assignment
---------------------------

::

    -- ugly, but valid
    > a = 1  b = a * 2


Commend Line
---------------------------

-l <chunk>
+++++++++++++++++++++++++++

Execute *chunk*

.. code-block:: shell

    $ cat c1.lua
    a = 100

    $ cat c2.lua
    b = 3

    $ cat c3.lua
    print(a * 3)

    $ lua -l c1 -l c2 c3
    300

This will execute ``c1`` and ``c2`` first.
