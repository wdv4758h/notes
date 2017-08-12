========================================
Bash
========================================


.. contents:: 目錄


Job Control
========================================

.. code-block:: sh

    $ set -o monitor  # enable script job control
    $ trap 'echo "child died"' CHLD   # get notification when a child exits



參考
========================================
