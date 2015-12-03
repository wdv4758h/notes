========================================
find
========================================


find specific file
========================================

directory :

.. code-block:: sh

    $ find -type d
    $ find . -type d
    $ find /tmp -type d


regular file :

.. code-block:: sh

    $ find -type f


specific filename :

.. code-block:: sh

    $ find . -name "*.rst"
    $ find . -type f -name "*.rst"


execute command for specific file :

.. code-block:: sh

    $ find . -type f -exec ls -al {} \;
    $ find . -type f -exec chmod 644 {} \;
