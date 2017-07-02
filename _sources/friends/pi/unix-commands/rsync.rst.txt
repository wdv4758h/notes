=========
``rsync``
=========
* 參數格式 ::

    $ rsync options <source> <destination>

* 取代 ``cp`` ，一樣是 copy 但是有進度條 ::

    $ rsync -ah --progress

* 放棄 permission，owner，group ::

    $ rsync --no-p --no-o --no-g

* 範例 ::

    $ rsync -arvzh --progress

  - ``-a``: archive mode，保留大部份資訊
  - ``-r``: recursive
  - ``-v``: verbose
  - ``-z``: 傳送時壓縮資料
  - ``-h``: 用人類好讀方式顯示資訊
