Static Function
===============================================================================

.. highlight:: console

- scope limited to current source file

..

    If the function or variable is visible *outside* of the current source file,
    it is said to have *global*, or *external* scope.

..

    If the function or variable is *not* visible outside of the current source file,
    it is said to have *local*, or *static* scope.


Sample
----------------------------------------------------------------------

https://github.com/iblis17/notes/tree/master/lang/c/static-func

::

	$ make
	cc -O2 -pipe   -Wall -c foo.c
	cc -O2 -pipe   -Wall main.c foo.o -o main
	$ ./main
	func f


Break It Down
----------------------------------------------------------------------

::

    $ make break
