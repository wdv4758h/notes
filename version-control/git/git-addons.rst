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


diff-so-fancy
------------------------------

:Repo: https://github.com/so-fancy/diff-so-fancy


一個 Perl script 輔助 diff 的顯示，
例如把兩行的差異用不同底色標起來、把有差異的檔案名稱特別突顯等等。


安裝：

.. code-block:: sh

    sudo pacman -S diff-so-fancy


搭配 Git 的方式：

.. code-block:: sh

    git config --global core.pager "diff-so-fancy | less --tabs=4 -RFX"



參考
========================================

* `Awesome Git Addons <https://github.com/stevemao/awesome-git-addons>`_
