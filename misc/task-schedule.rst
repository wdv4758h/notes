========================================
Task Schedule
========================================


.. contents:: 目錄


Taskwarrior
========================================

:site: https://taskwarrior.org/
:repo: https://github.com/GothenburgBitFactory/taskwarrior
:docs: https://taskwarrior.org/docs/

.. code-block:: sh

    sudo pacman -S task


.. code-block:: sh

    # task [<filter>] [<command>] [<modifications>|<miscellaneous>]

    # 列出接下來要處理的 task
    $ task
    [task next]
    No matches.

    # 加入新 task
    $ task add pay my bill
    Created task 1.

    # 列出接下來要處理的 task
    $ task
    [task next]

    ID Age Description Urg
     1 1s  pay my bill    0

    1 task

    # 加入新 task
    $ task add priority:H due:2018-10-15 buy a cake
    Created task 2.

    # 列出接下來要處理的 task
    $ task
    [task next]

    ID Age  P Due Description Urg
     2 11s  H 8h  buy a cake  14.6
     1 1min       pay my bill    0

    2 tasks

    # 列出優先度高的 task
    $ task priority:H
    [task next ( priority:H )]

    ID Age  P Due Description Urg
     2 1min H 8h  buy a cake  14.6

    1 task

    # 列出明天以前要完成的 task
    $ task due:tomorrow
    [task next ( due:tomorrow )]

    ID Age  P Due Description Urg
     2 2min H 8h  buy a cake  14.6

    1 task

    # 搜尋關鍵字
    $ task /buy/
    [task next ( /buy/ )]

    ID Age  P Due Description Urg
     2 4min H 8h  buy a cake  14.6

    1 task

    # 搜尋關鍵字，較長的訊息
    $ task /buy/ long

    ID Created    Mod  P Due        Description
     2 2018-10-14 4min H 2018-10-15 buy a cake

    1 task

    # 搜尋關鍵字，支援 regex
    $ task "/(buy)|(pay)/"
    [task next ( /(buy)|(pay)/ )]

    ID Age  P Due Description Urg
     2 7min H 8h  buy a cake  14.6
     1 8min       pay my bill    0

    2 tasks

    # 列出 task
    $ task list
    ID Age   P Due        Description     Urg
     2 13min H 2018-10-15 buy a cake      14.6
     1 15min              pay my bill        0

    2 tasks

    # 完成 task
    $ task 2 done
    Completed task 2 'buy a cake'.
    Completed 1 task.

    # 列出接下來要處理的 task
    $ task
    [task next]

    ID Age   Description Urg
     1 16min pay my bill    0

    1 task

    # 概覽
    $ task summary

    Project Remaining Avg age Complete 0%                        100%
    (none)          1   15min      50%

    1 projects


    # 新增標註
    $ task 1 annotate bill is on the table
    Annotating task 1 'pay my bill'.
    Annotated 1 task.

    $ task
    [task next]

    ID Age   Description                       Urg
     1 21min pay my bill                        0.8
               2018-10-14 bill is on the table

    1 task


    # 刪除標註
    $ task 1 denotate bill is on the table
    Found annotation 'bill is on the table' and deleted it.
    Denotated 1 task.

    $ task
    [task next]

    ID Age   Description Urg
     1 23min pay my bill    0

    1 task


    # 更改 task
    $ task 1 modify due:2018-10-16
    Modifying task 1 'pay my bill'.
    Modified 1 task.

    $ task
    [task next]

    ID Age   Due Description Urg
     1 24min 1d  pay my bill 8.19

    1 task


    # 刪除 task
    $ task add test task
    Created task 2.
    $ task 2 delete
    Delete task 2 'test task'? (yes/no) y
    Deleting task 2 'test task'.
    Deleted 1 task.

    # context
    $ task context define today due:today
    Are you sure you want to add 'context.today' with a value of 'due:today'? (yes/no) y
    Context 'today' defined. Use 'task context today' to activate.
    $ task context today
    Context 'today' set. Use 'task context none' to remove.
    $ task
    No matches.
    $ task add today task due:today
    Created task 2.
    $ task

    ID Age Due  Description Urg
     2 1s  -15h today task   9.1

    1 task
    $ task context none
    Context unset.
    $ task
    [task next]

    ID Age   Due  Description Urg
     2 59s   -15h today task   9.1
     1 28min 1d   pay my bill 8.19

    2 tasks


    # context，用更多條件 filter
    $ task context define work project:mycompany
    $ task add project:mycompany hire a programmer
    $ task context work


    # 紀錄 task 處理時間
    $ task 2 start
    $ task 2 stop


    # 圖表
    $ task burndown
    $ task burndown.daily
    $ task burndown.monthly

    # export 成 JSON
    $ task export


    # task 需要另一個 task

    # 日曆
    $ task calendar

    # 一次為 routine 事項建立 tasks
    $ task add Go to work due:monday recur:weekly


結合 Timewarrior：

.. code-block:: sh

    $ sudo pacman -S timew
    $ cp /usr/share/doc/timew/ext/on-modify.timewarrior ~/.task/hooks/
    $ chmod +x ~/.task/hooks/on-modify.timewarrior
    $ task diagnostics

    # timew 會追蹤每個 task 每次花費的時間並加總
    $ task <id> start
    $ task <id> stop


情境：

.. code-block:: sh

    TODO



參考
========================================

* `TrelloWarrior - sync Taskwarrior projects with Trello boards <https://github.com/ogarcia/trellowarrior>`_
* `Timewarrior <https://taskwarrior.org/docs/timewarrior/>`_
