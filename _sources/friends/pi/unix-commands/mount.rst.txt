=========
``mount``
=========
* 把目錄 ``<A>`` 以唯讀形式掛載到目錄 ``<B>`` ::

    # mount -o ro -t nullfs <A> <B>

* [single user mode] 把 ``ro`` 狀態的根目錄重新掛載為 ``rw`` ::

    # mount -a /
