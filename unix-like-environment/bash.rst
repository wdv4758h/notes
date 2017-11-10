========================================
Bash
========================================


.. contents:: 目錄


Job Control
========================================

.. code-block:: sh

    $ set -o monitor  # enable script job control
    $ trap 'echo "child died"' CHLD   # get notification when a child exits



範例
========================================

取得目前檔案的資料夾：

.. code-block:: sh

    echo $(dirname $0)



參考
========================================

* `The Bash Hackers Wiki <http://wiki.bash-hackers.org/start>`_
