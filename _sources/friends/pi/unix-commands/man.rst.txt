===============================================================================
``man``
===============================================================================
.. code:: shell

  $ man program


放置自己的 manpage
-------------------------------------------------------------------------------
有時在沒有權限的情況下，會需要自己 build from source，這時候系統裡的 manpage
和實際上使用的軟體會是不同版本

以下以 ``tmux`` 為例，在家目錄部屬新版本的 tmux 以及 man page

1.  Build 出新版本的 ``tmux`` ，得到 ``tmux`` 以及 ``tmux.1``
2.  產生 ``~/bin`` 目錄，用來放新版的 ``tmux``

    .. code:: shell

      $ mkdir ~/bin
    
    * 將新版的 ``tmux`` 放進去

3.  產生 ``man`` 需要的目錄結構

    .. code:: shell

       $ mkdir ~/bin/man1

    * 將 ``tmux.1`` 丟進去

4.  透過 shell 設定 ``PATH`` 以及 ``MANPATH``

    .. code:: shell

       PATH=${HOME}/bin:${PATH}
       export PATH

       MANPATH=${HOME}/bin:${MANPATH}
       export MANPATH

    * 如果是透過設定檔做設定，重開 shell
    * 用 ``manpath`` 確認 ``man`` 搜尋的路徑順序

5.  用 ``man -w tmux`` 確認 ``man`` 會使用新的 man page
