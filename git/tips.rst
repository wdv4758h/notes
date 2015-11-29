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

delete branch
========================================

delete remote branch

.. code-block:: sh

    git push origin --delete <branch>  # Git version 1.7.0 or newer
    git push origin :<branch>          # Git versions older than 1.7.0



delete local branch

.. code-block:: sh

    git branch --delete <branch>
    git branch -d <branch> # Shorter version
    git branch -D <branch> # Force delete un-merged branches


delete local remote-tracking branch

.. code-block:: sh

    git branch --delete --remotes <remote>/<branch>
    git branch -dr <remote>/<branch> # Shorter

    git fetch <remote> --prune # Delete multiple obsolete tracking branches
    git fetch <remote> -p      # Shorter


* `Delete a Git branch both locally and remotely <http://stackoverflow.com/questions/2003505/delete-a-git-branch-both-locally-and-remotely/23961231#23961231>`_


see the content from snapshot
========================================

git 會把 SHA1 hash 結果的前 2 個字元當作資料夾名稱，
剩下的 38 字元作為檔案名稱，
這樣的作法可以把檔案大致上地平均分佈在不同的資料夾 (前 2 個字元 collision 時才會出現在同一個資料夾)，
一來可以降低同一個資料夾底下的檔案數量 (有些 File System 有上限)，
二來在一些 File System 中少量檔案的資料夾效能比較好。

.. code-block:: sh

    $ ls -al .git/objects/
    total 0
    drwxr-xr-x 11 user users 220 Nov 24 22:52 .
    drwxr-xr-x  8 user users 280 Nov 25 00:43 ..
    drwxr-xr-x  2 user users  60 Nov 24 22:52 39
    drwxr-xr-x  2 user users  60 Nov 24 22:52 4e
    drwxr-xr-x  2 user users  60 Nov 24 22:39 87
    drwxr-xr-x  2 user users  60 Nov 24 22:39 bc
    drwxr-xr-x  2 user users  60 Nov 24 22:52 c1
    drwxr-xr-x  2 user users  60 Nov 24 22:26 e6
    drwxr-xr-x  2 user users  60 Nov 24 22:39 fb
    drwxr-xr-x  2 user users  40 Nov 24 22:26 info
    drwxr-xr-x  2 user users  40 Nov 24 22:26 pack
    $ git cat-file -p HEAD
    tree c18618f605144e1bb0b9bdd4874fbb1b2a40455b
    parent bc5eda9be357b85bec167e1a63765c1879f5b1d2
    author User <user@gmail.com> 1448376727 +0800
    committer User <user@gmail.com> 1448376727 +0800

    asd2123
    $ git cat-file -p c18618f605144e1bb0b9bdd4874fbb1b2a40455b
    100644 blob 871aa5518316c6e89d102c79d4e2bc29371ae124	asd
    $ git cat-file -p 871aa5518316c6e89d102c79d4e2bc29371ae124
    asdasd213
    $ ls -l .git/objects/87/1aa5518316c6e89d102c79d4e2bc29371ae124
    -r--r--r-- 1 user users 24 Nov 24 22:39 .git/objects/87/1aa5518316c6e89d102c79d4e2bc29371ae124


* `Git Internals - Git Objects <https://git-scm.com/book/en/v2/Git-Internals-Git-Objects>`_
* `Advantages of categorizing objects into folders named as the first 2 characters of SHA-1 string? <http://stackoverflow.com/questions/30662521/advantages-of-categorizing-objects-into-folders-named-as-the-first-2-characters>`_


git describe
========================================

.. code-block:: sh

    $ git describe --long
    v0.1.0-136-g538a57c
    # finds the most recent tag that is reachable from a commit
    # (136th commit since tag v0.1.0 that points at object 538a57c)
    # ${TAG}-${COMMITS_SINCE_TAG}-g${FIRST_7_CHARS_OF_HASH}
