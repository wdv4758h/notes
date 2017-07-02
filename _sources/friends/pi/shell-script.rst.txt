============================
= Shell Script Syntax Note =
============================

bourne sh
----------

``if``
````````

* 語法 ::

    if cmd
    then
      ...
    elif cmd
    then
      ...
    else
      ...
    fi

  - ``if`` 會執行 ``cmd`` ，若 Return Status 為 ``0`` 則條件成立。
  - Return Status (Exit Status)

    + 一個「指令」可以由多個指令組成
    + 數個指令依序執行時，最後一個指令的 Return Status 為整串指令的 Return Status
    + 數個指令用 pipe (``|``)、And (``&&``)、Or (``||``) 串起來執行時亦同


* ``[`` / ``test``

  - ``[`` 是 ``test`` 指令的 hard link，故在使用時有許多空白字元不能省略
  - 檢查檔案是否存在 ::

      [ -f file ]

  - 檢查目錄是否存在 ::

      [ -d dir ]

  - And Operator ::

      if [ $# -eq 1 ] && [ $? -eq 0 ]

  - 其他見 ``man test``

``while``
```````````

* 語法 ::

    while [ 1 ]; do
      ...
    done

``for`` loop
``````````````

* 語法 ::

    for i in 1 2 3; do
      echo $i
    done

* 對別的指令的 stdout 做迭代 ::

    for i in $(echo 1 2 3 a b c); do
      echo $i
    done


``case``
``````````

* 範例 ::

    while [ $# -gt 0 ]; do
      case "$1" in
        -f) force_replace=1;;
        -a) echo "a"; echo "b";;
      esac
      shift
    done

``function``
-------------

語法 ::

  function_name () {
    ...
  }

* Bash 允許在 function 名稱前加上 ``function`` 關鍵字，但這不是 POSIX 的規範
* 內容不可以是空的
* 可以用 ``return`` 指令來指定 Return Status

字串處理
---------

* 字串相等 ::

    if [ "$str" = "a" ]; then
    fi

  - 不是雙等號

* 以下範例使用假設 ::

    #!/usr/local/env sh
    var=foodforthought.jpg

* 切掉左邊

  - 從左邊開始尋找 ``fo`` ，找到最後一個 ``fo`` ，右邊剩下的字串為結果 (不包含比對到的 ``fo``) ::

      ${var##*fo}

  - 從左邊開始尋找 ``fo`` ，找到第一個 ``fo`` ，右邊剩下的字串為結果 (不包含比對到的 ``fo``) ::

      ${var#*fo}

* 切掉右邊

  - 從右邊開始尋找 ``fo`` ，找到最後一個 ``fo`` ，左邊剩下的字串為結果 (不包含比對到的 ``fo``) ::

      ${var%%fo*}

  - 從右邊開始尋找 ``fo`` ，找到第一個 ``fo`` ，左邊剩下的字串為結果 (不包含比對到的 ``fo``) ::

      ${var%fo*}

* slice

  - 取出第 1 到第 5 個字元，包含第 1 及第 5 個，字串從 0 開始算 ::

      ${var:1:5}

IO 重導向
----------

* 去除 stderr ::

    $ command 2>less

* 去除 stdout，把 stderr 轉為 stdout ::

    $ command 2>&1 1>/dev/null

其他
-----

* 把 local 變數傳給 subprocess

  - 把 ``var`` 變為自己的環境變數 (才可以傳給 subprocess) ::

      export var

  - 把 ``var`` 刪除 (同時也從環境變數中消失) ::

      unset var

csh/tcsh
---------

* Global 的設定檔: ``/etc/csh.cshrc``

* ``alias`` 參數

  - ``\!:1`` 代表第一個參數，依此類推

  - ``alias t echo test_\!:1_test``

* 每次更新的 prompt ::

    alias precmd "`date`"
