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

mv :

.. code-block:: sh

    # files that create in last 30 minutes
    # move to tmpdir/
    $ find . -cmin -30 -type f -exec mv -t tmpdir/ {} +


case insensitive:

.. code-block:: sh

    find . -iname ...


尋找後依照檔案大小排序：

.. code-block:: sh

    find . -type f -exec ls -s {} \;  | sort -nr | head


尋找後搬進特定資料夾：

.. code-block:: sh

    find . -newermt 2016-08-24 -maxdepth 1 -exec mv {} ../newdir/ \;
