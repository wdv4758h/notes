Make
===============================================================================

After FreeBSD 10.0, the implementation of ``make(1)`` is ``bmake(1)``.
``pmake(1)`` is deprecated.

ref: http://www.crufty.net/help/sjg/bmake.html


``bmake`` and ``gmake`` compatible Makefile
----------------------------------------------------------------------

Quote from stackoverflow:

    You could put your GNU-specific stuff in ``GNUmakefile``,
    your BSD-specific stuff in ``BSDmakefile``,
    and your common stuff in a file named ``Makefile.common`` or similar.
    Then include ``Makefile.common`` at the very beginning of
    each of the other two. Downside is, now you have 3 makefiles instead of 2.
    Upside, you'll only be editing 1.


``bmake``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

The file ``BSDmakefile`` has highest priority.

::

    ┌─[/usr/share/mk]
    | [Venv(py3)] [-- INSERT --]
    └─[iblis@abeing]% grep  BSDmakefile /usr/share/mk/sys.mk
    .MAKE.MAKEFILE_PREFERENCE= BSDmakefile makefile Makefile


Ref
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

https://stackoverflow.com/questions/3848656/bsd-make-and-gnu-make-compatible-makefile


`bmake` Suffix Rules
----------------------------------------------------------------------

::

    man make

and search ``SUFFIXES``

::

    .SUFFIXES: .o
    .c.o:
        cc -o ${.TARGET} -c ${.IMPSRC}
