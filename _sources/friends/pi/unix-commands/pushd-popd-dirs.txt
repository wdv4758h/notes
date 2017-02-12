===========================
``pushd`` ``popd`` ``dirs``
===========================
* 操作 shell 中的目錄堆疊
* 把目前目錄 push 到 stack，並 ``cd`` 到 ``dir`` ::

    $ pushd dir

* 把 stack pop 掉一次，並 ``cd`` 回 stack 最上層的目錄 ::

    $ popd

* 列出現在的 stack，左邊的是最上層的 ::

    $ dirs
