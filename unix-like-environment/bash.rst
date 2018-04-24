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


如果有值 A 就使用值 A，不然使用值 B：

.. code-block:: sh

    VAR1="${VAR1:-default value}"

    VAR2="test"
    VAR1="${VAR2:-default value}"



參考
========================================

* `The Bash Hackers Wiki <http://wiki.bash-hackers.org/start>`_
* `Using "${a:-b}" for variable assignment in scripts <https://unix.stackexchange.com/questions/122845/using-a-b-for-variable-assignment-in-scripts>`_
* `bash - What's a concise way to check that environment variables are set in a Unix shell script? <https://stackoverflow.com/questions/307503/whats-a-concise-way-to-check-that-environment-variables-are-set-in-a-unix-shell>`_
