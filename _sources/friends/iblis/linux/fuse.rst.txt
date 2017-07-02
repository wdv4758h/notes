********
Fuse
********

.. toctree::


.. highlight:: shell


stat(2)
=========

st_nlink
----------

Number of hard link

An empty dir is 2::

    $ mkdir /tmp/demo
    $ ll /tmp
    ...
    drwxr-xr-x  2 iblis   iblis    40 Jul 29 10:32 demo/
    ...

The ``2`` located at column 2 is ``st_nlink``.

* One for the dir itself
* One for linking to ``.``
