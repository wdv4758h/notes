===========
``chflags``
===========
* FreeBSD 提供一個 Flag 的機制，可以把檔案加上絕對唯讀的標記，使 root 不會誤刪重要檔案

* 清除該 Flag (請三思) ::

  # chflags -R noschg

* flag 列表見 ``man chflags``
