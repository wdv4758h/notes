========
``find``
========
* 用各種條件尋找檔案

* 從 ``<dir>`` 目錄開始尋找檔名開頭為 ``Kalafina`` 的項目 ::

    $ find <dir> -name 'Kalafina*'

* ``<dir>`` 目錄中包含的所有子目錄 ::

    $ find <dir> -type d

* ``<dir>`` 目錄中包含的所有子檔案 ::

    $ find <dir> -type f

* 過濾出權限為 755 的項目 ::

    $ find <dir> -perm 755

* 過濾出權限不是 755 的項目 ::

    $ find <dir> ! -perm 755

* 對於每一個項目，都執行後面的指令, ``{}`` 會被代換成檔名 ::

    $ find <dir> -exec sh -c "...{}..."

  - 〔失敗例子〕後面餵給 ``sh`` 的參數中, backtick 中的 ``{}`` 不會被代換 ::

      $ find <dir> -exec sh -c "printf `stat -c %a {}`'text'" \;

  - 需要改用 ``$()``, 並把 ``$`` escape 掉 ::

      $ find <dir> -exec sh -c "printf \$(stat -c %a {})'text'" \;

* 把 ``<dir>`` 目錄裡的目錄權限設為 755 ::

    $ find <dir> -type d ! -perm 755 -exec sh -c "chmod 755 '{}'" \;

* 把 ``<dir>`` 目錄裡的檔案權限設為 644 ::

    $ find <dir> -type f ! -perm 644 -exec sh -c "chmod 644 '{}'" \;
