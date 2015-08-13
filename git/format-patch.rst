========================================
Git Format Patch
========================================

Intrudoction
========================================

把 git commit 變成一個一個的 patch，
並且會利用 commit message 來命名

Usage
========================================

最新的 N 個 commit
------------------------------

``git format-patch -N``

ex :

.. code-block:: sh

    $ git format-patch -3
    0001-shell.c-A-full-RBuffer-with-no-NL-can-freeze-shell-o.patch
    0002-test-cover-grep.patch
    0003-runtime-Do-install-generated-syntax-file-also-test-t.patch


打 patch
------------------------------

``git am PATCH``

ex :

.. code-block:: sh

    $ git am 0001-shell.c-A-full-RBuffer-with-no-NL-can-freeze-shell-o.patch
    Applying: shell.c: A full RBuffer with no NL can freeze shell output. #3156


指定某個 commit 後的 N 個 commit
--------------------------------

``git format-patch -N <SHA>``

ex :

.. code-block:: sh

    $ git format-patch -10 41e9ebc



把 N 個 format-patch 和在一起
------------------------------

ex :

.. code-block:: sh

    $ git format-patch -10 HEAD --stdout > 0001-last-10-commits.patch


Reference
========================================

* `Git - git-format-patch <http://git-scm.com/docs/git-format-patch>`_
