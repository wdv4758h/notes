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


更多應用
========================================

簡易 supervisor
------------------------------

.. code-block:: sh

    while true; do
        (ps aux | grep MYPROG > /dev/null) || \
            MYPROG --start
        sleep 1
    done


取得目前程式碼路徑
------------------------------


等待網路通到外面
------------------------------

.. code-block:: sh

    until ping -c 1 8.8.8.8; do
        echo "Network is not good, waiting"
        sleep 1
    done



參考
========================================

* `The Bash Hackers Wiki <http://wiki.bash-hackers.org/start>`_
* `Using "${a:-b}" for variable assignment in scripts <https://unix.stackexchange.com/questions/122845/using-a-b-for-variable-assignment-in-scripts>`_
* `bash - What's a concise way to check that environment variables are set in a Unix shell script? <https://stackoverflow.com/questions/307503/whats-a-concise-way-to-check-that-environment-variables-are-set-in-a-unix-shell>`_
* `Bash Pitfalls <https://mywiki.wooledge.org/BashPitfalls>`_
* `Framework for writing modular, discoverable, testable Bash scripts <https://github.com/mbland/go-script-bash>`_
* `Bash Handbook <https://github.com/denysdovhan/bash-handbook>`_
* `Learn you how to write your first bash script <https://github.com/denysdovhan/learnyoubash>`_
* `Bash Guide <https://github.com/Idnan/bash-guide>`_
* `Bash Boilerplate <https://github.com/alphabetum/bash-boilerplate>`_
* `A best practices Bash script template with several useful functions <https://github.com/ralish/bash-script-template>`_
* `100 shell script examples <https://github.com/epety/100-shell-script-examples>`_
