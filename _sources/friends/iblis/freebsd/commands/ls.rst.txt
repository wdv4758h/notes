*********************************
ls
*********************************

.. toctree::



``-D``
======

Syntax
^^^^^^^
    ``ls -l -D {format}``

This will replace *date time* in ``ls -l`` with *format*.

e.g.::

    % ls -lD "$PWD/"
    total 4
    -rw-r--r--  1 iblis  iblis   0 /tmp/demo/ README
    -rw-r--r--  1 iblis  iblis   0 /tmp/demo/ bar
    -rw-r--r--  1 iblis  iblis   0 /tmp/demo/ foo
    -rw-r--r--  1 iblis  iblis  91 /tmp/demo/ test2.cpp

Trick
^^^^^
    ``ls -lD $PWD/ | sed -e "s%$PWD/ %$PWD/%g"``
