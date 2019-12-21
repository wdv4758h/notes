========================================
Makefile
========================================


.. contents:: 目錄


介紹
========================================



實做
========================================

* GNU Make
* BSD Make



範例
========================================

並行執行
------------------------------

.. code-block:: make

    taskA:
        @echo "this is task A"
        @sleep 1
        @echo "end task A"

    taskB: taskA
        @echo "this is task B"
        @sleep 3
        @echo "end task B"

    taskC: taskA
        @echo "this is task C"
        @sleep 2
        @echo "end task C"

    taskD: taskC
        @echo "this is task D"
        @sleep 4
        @echo "end task D"

    taskE: taskB taskD
        @echo "this is task E"


切換 Shell
------------------------------

.. code-block:: make

    SHELL := python3
    .ONESHELL:

    foo:
        import os
        import platform
        print(os.getpid())
        print(platform.platform())


help
------------------------------

.. code-block:: make

    help:
        @grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

    foo:    ## task foo
    bar:    ## task bar


.. code-block:: sh

    $ make help
    bar                            task bar
    foo                            task foo


執行指令前都先輸出是在跑哪一行
------------------------------

.. code-block:: make

    _SHELL := $(SHELL)
    SHELL = $(warning [$@])$(_SHELL)

    task1:
        @echo 1.1
        @echo 1.2

    task2:
        @echo 2.1
        @echo 2.2

    task3: task1 task2
        @echo 3.1
        @echo 3.3


.. code-block:: sh

    $ make task3
    Makefile:5: [task1]
    1.1
    Makefile:6: [task1]
    1.2
    Makefile:9: [task2]
    2.1
    Makefile:10: [task2]
    2.2
    Makefile:13: [task3]
    3.1
    Makefile:14: [task3]
    3.3

    $ make task3 -j 2
    Makefile:5: [task1]
    Makefile:9: [task2]
    1.1
    Makefile:6: [task1]
    2.1
    Makefile:10: [task2]
    1.2
    2.2
    Makefile:13: [task3]
    3.1
    Makefile:14: [task3]
    3.3


根據平台客製化
------------------------------

.. code-block:: make

    OS=$(shell uname)

    run: run-${OS}

    run-Linux:
        @echo "this is Linux"

    run-Darwin:
        @echo "this is macOS"


開發流程整合
------------------------------

.. code-block:: make

    test: test-unit test-integration

    test-unit:
        @echo "=> running unit test"

    test-integration:
        @echo "=> running integration test"

    linter:
        @echo "=> running linter"

    build-container:
        @echo "=> building container"

    ci: linter test build-container
        @echo "=> done!!!"


.. code-block:: sh

    make ci -j$(proc)



參考
========================================

* `Your Makefiles are wrong - Jacob Davis-Hansson <https://tech.davis-hansson.com/p/make/>`_
