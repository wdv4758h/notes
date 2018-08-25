Macro
===============================================================================

.. highlight:: c

ref: http://clang.llvm.org/docs/LanguageExtensions.html#builtin-macros


__COUNTER__
----------------------------------------------------------------------

Useful for createing :ref:`static-assertion` in C.

::

	#include <stdio.h>

	int main(int argc, char *argv[])
	{
		printf("%d\n", __COUNTER__);
		printf("%d\n", __COUNTER__);
		printf("%d\n", __COUNTER__);
		return 0;
	}
