tput
===============================================================================

::

    tput AF 3 && echo 'test'

The attribute (e.g. ``AF``) is documented in ``terminfo(5)``

but on linux is::

    tput setaf 3 && echo 'test'
