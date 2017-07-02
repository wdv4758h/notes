zsh
===============================================================================


Bump Up the File Descriptor Limit
----------------------------------------------------------------------

We can set the soft limit up to hard limit.

Check the hard limit::

    $ ulimit -Hn
    4096

Then check the soft limit::

    $ ulimit -Sn
    1024

Bump up it::

    $ ulimit -Sn unlimited
    $ ulimit -Sn
    4096
