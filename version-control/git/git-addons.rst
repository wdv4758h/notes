========================================
Git Addons
========================================


.. contents:: 目錄


如何撰寫
========================================

利用 .gitconfig
------------------------------



範例
========================================

git ignore
-------------------------------

:Repo: https://github.com/joeblau/gitignore.io
:Site: https://www.gitignore.io/


用途是快速地產生需要的 .gitignore 設定。


安裝：

.. code-block:: sh

    git config --global alias.ignore '!gi() { curl -L -s https://www.gitignore.io/api/$@ ;}; gi'


使用：

.. code-block:: sh

    git ignore python > .gitignore


git standup
------------------------------

用途是快速地回顧最近的更動。


安裝：

.. code-block:: sh

    curl -O -L -C - https://github.com/kamranahmedse/git-standup/raw/master/git-standup
    chmod +x git-standup
    mv git-standup /some/path/for/bin/git-standup


使用：

.. code-block:: sh

    # 顯示最近 10 天我的 commits
    git standup -d 10

    # 顯示最近 2 天所有人的 commits
    git standup -a all -d 2

    # 顯示最近 2 天某人的 commits
    git standup -a "somebody's name or mail" -d 2



參考
========================================

* `Awesome Git Addons <https://github.com/stevemao/awesome-git-addons>`_
