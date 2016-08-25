========================================
dd
========================================

.. code-block:: sh

    $ dd if=/dev/zero of=/tmp/swapfile bs=1M count=1024

    # display progress
    $ sudo dd if=xxx.iso of=/dev/sdb status=progress
