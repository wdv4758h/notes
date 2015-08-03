========================================
Git Tips
========================================

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
