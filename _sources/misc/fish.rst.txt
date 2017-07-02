========================================
Fish Shell
========================================

Array Slicing:

.. code-block:: fish

    $ set x a b c d     # assign
    $ echo $x[2..-1]
    b c d
    $ echo $x[1..(count $x)]
    a b c d


* `fish-shell - tests <https://github.com/fish-shell/fish-shell/tree/master/tests>`_
* `Dive into Fish <https://gist.github.com/weakish/836729>`_
* `Programming with fish shell <https://butterflyprogramming.neoname.eu/programming-with-fish-shell/>`_
    - Fish 的 ``math`` 是 ``bc`` 的 wrapper
    - ``set x (math 1 + 1)``
