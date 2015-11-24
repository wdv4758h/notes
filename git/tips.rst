========================================
Git Tips
========================================

git add -p

Checkout GitHub pull requests locally
========================================

只針對單一 repo
------------------------------

假設先前跑過以下 command :

.. code-block:: sh

    $ git add remote add github git://github.com/USERNAME/REPO.git

那 repo 裡的 ``.git/config`` 會包含這些資訊：

::

    [remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = git@github.com:USERNAME/REPO.git

接下來只要加上一行變成：

::

    [remote "origin"]
        fetch = +refs/heads/*:refs/remotes/origin/*
        url = git@github.com:USERNAME/REPO.git
        fetch = +refs/pull/*/head:refs/remotes/origin/pr/*

加完後只要下 fetch 就可以取回 GitHub 上的 PRs

.. code-block:: sh

    $ git fetch github
    From git://github.com/USERNAME/REPO
    - [new ref]         refs/pull/1/head -> origin/pr/1
    - [new ref]         refs/pull/2/head -> origin/pr/2
    ...


切到 PR：

.. code-block:: sh

    $ git checkout pr/1
    Branch pr/1 set up to track remote branch pr/1 from github.
    Switched to a new branch 'pr/1'


global 設定
------------------------------

.. code-block:: sh

    $ git config --global --add remote.origin.fetch "+refs/pull/*/head:refs/remotes/origin/pr/*"


只抓特定 PR
------------------------------

.. code-block:: sh

    $ git fetch github pull/1/head:pr/1
    From git://github.com/USERNAME/REPO
    - [new ref]         refs/pull/1/head -> pr/1
    $ git checkout pr/1



Merge Two Different Repo Into One
========================================

.. code-block:: sh

    # Project Old
    mkdir projold
    cd projold
    git init
    touch test-projold
    git add test-projold
    git commit -m "Initial Commit (in projold)"
    cd ..

    # Project New
    mkdir projnew
    cd projnew
    git init
    touch test-projnew
    git add test-projnew
    git commit -m "Initial Commit (in projnew)"

    # Merge Project Old Into Project New
    git remote add -f projold ../projold
    git merge -s ours --no-commit projold/master        # use merge strategy ``ours``
    git read-tree --prefix=projold/ -u projold/master
    git commit -m "Merge projold into subdir"
    ls -lR
    # .:
    # total 0
    # drwxr-xr-x 2 dv users 60 Oct 26 12:47 projold
    # -rw-r--r-- 1 dv users  0 Oct 26 12:47 test-projnew
    #
    # ./projold:
    # total 0
    # -rw-r--r-- 1 dv users 0 Oct 26 12:47 test-projold


    #
    #   *   c073b17 - (4 seconds ago) Merge projold into subdir - XXX (HEAD -> master)
    #   |\
    #   | * fcfe4fc - (5 seconds ago) Initial Commit (in projold) - XXX (projold/master)
    #   * c56a13f - (4 seconds ago) Initial Commit (in projnew) - XXX
    #


Squash commits into one
========================================

.. code-block:: sh

    git rebase -i <不變動的commit的SHA-1>

    ########################################
    # 接下會進入編輯模式

    pick 056eef4 a
    pick da39a8a b  # 把要 squash 的改成 "squash"

    # Rebase 49687a0..d426a8a onto 49687a0
    #
    # Commands:
    #  p, pick = use commit
    #  r, reword = use commit, but edit the commit message
    #  e, edit = use commit, but stop for amending
    #  s, squash = use commit, but meld into previous commit
    #  f, fixup = like "squash", but discard this commit's log message
    #  x, exec = run command (the rest of the line) using shell
    #
    # If you remove a line here THAT COMMIT WILL BE LOST.
    # However, if you remove everything, the rebase will be aborted.
    #

diff
========================================

.. code-block:: sh

    # working v.s. commits
    $ git diff                  # working & HEAD
    $ git diff bc5eda9          # working & specific commit
    # staging v.s. working
    $ git diff --staged         # staging & HEAD
    # staging v.s. commits
    $ git diff --staged bc5eda9 # staging & specific commit
    # commits v.s. commits
    $ git diff bc5eda9 39e01d0  # specific commit & specific commit
