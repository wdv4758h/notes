Debug ncurse-like program
-------------------------

- stdin/stdout redirect::

    (gdb) run < infile
    (gdb) run > outfile

- run target program using console device ``/dev/pts/<num>`` as stdin/out::

    $ gdb --tty /dev/pts/<num>

  - ``$ sleep 100000000`` at ``/dev/pts/<num>`` shell
  - http://www.dirac.org/linux/gdb/07-Debugging_Ncurses_Programs.php

Misc
----

- dprintf
