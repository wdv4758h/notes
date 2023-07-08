========================================
Bash
========================================


.. contents:: 目錄


Tips
========================================

Fail Fast
------------------------------

.. code-block:: sh

    set -Eeuo pipefail


Cleanup
------------------------------

.. code-block:: sh

    trap cleanup SIGINT SIGTERM ERR EXIT

    cleanup() {
      trap - SIGINT SIGTERM ERR EXIT
      # script cleanup here
    }



Job Control
========================================

.. code-block:: sh

    $ set -o monitor  # enable script job control
    $ trap 'echo "child died"' CHLD   # get notification when a child exits



文件
========================================

* `zshelldoc <https://github.com/zdharma/zshelldoc>`_
* `bashdoc <https://github.com/ajdiaz/bashdoc>`_
    - based on Pandoc
* `shocco <https://github.com/rtomayko/shocco>`_




Style
========================================

* `Google Shell Style Guide <https://google.github.io/styleguide/shell.xml>`_



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


利用函式來讓 Script 更容易讀
------------------------------

.. code-block:: sh

    has_myprog() {
        ps aux | grep myprog
    }

    init_myprog() {
        myprog --daemon
    }

    # if myprog is not running, init one
    has_myprog || init_myprog


避免程式 block 住
------------------------------

.. code-block:: sh

    CMD="sleep 10"
    timeout 3s ${CMD}


Logging
------------------------------

.. code-block:: sh

    log() {
        # style 1:
        # echo $1

        # style 2:
        TIME=$(date -u +"%Y-%m-%d|%H:%M:%S|%N")
        echo "[${TIME}]$1"
    }

    debug() {
        log "[  DEBUG] $1"
    }

    info() {
        log "[   INFO] $1"
    }

    warning() {
        log "[WARNING] $1"
    }

    error() {
        log "[  ERROR] $1"
    }



參考
========================================

* `Let's do Bash right! <https://github.com/progrium/bashstyle>`_
* `The Bash Hackers Wiki <http://wiki.bash-hackers.org/start>`_
* `pure bash bible <https://github.com/dylanaraps/pure-bash-bible>`_
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
* `Learn Bash Debugging Techniques the Hard Way <https://zwischenzugs.com/2018/10/09/learn-bash-debugging-techniques-the-hard-way/>`_
* `Minimal safe Bash script template | Better Dev <https://betterdev.blog/minimal-safe-bash-script-template/>`_
