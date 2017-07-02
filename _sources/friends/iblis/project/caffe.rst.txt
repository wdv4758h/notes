Caffe
===============================================================================

Installation
----------------------------------------------------------------------

Requirements:

- aur/openblas-lapack

- community/cuda

- extra/boost

- extra/protobuf

- community/google-glog

- community/gflags

- extra/hdf5

- extra/opencv

- extra/leveldb

- extra/lmdb

- python 3.3+ for pycaffe

::

    yaourt -Syu aur/openblas-lapack

    pacman -Syu cuda boost protobuf gflags hdf5 opencv leveldb lmdb


``Makefile.config``
----------------------------------------------------------------------

::

    cp Makefile.config.example Makefile.config

Patch ``Makefile.config``:

.. literalinclude:: files/Makefile.config.patch
    :language: diff
