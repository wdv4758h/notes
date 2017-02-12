==========
``getopt``
==========
* 過濾出有效的參數

* ``getopt`` 和 ``getopts`` 不一樣, 據說 ``getopts`` 比較強, 但因為 bourne shell 沒有內建, 所以我選擇 ``getopt``

* 基本用法

  - ``getopt OPTSTRING PARAMETERS``
  - ``OPTSTRING`` 格式

    + ``"abc,def:"``
    + ``def`` 參數會以 ``-d value`` 的形式被處理
    + ``abc`` 會以 ``-a`` 的形式被處理

  - ``PARAMETERS``

    + 待 parse 的字串

* 例子 ::

    $ getopt f:abc -c -f file -ab
    -c -f file -a -b --

* 在 Shell Script 中使用 ::

    #!/bin/sh
    set -- `getopt :f $@`
    force_replace=0
    while [ $# -gt 0 ]; do
        case "$1" in
            -f) force_replace=1;;
        esac
        shift
    done

  - 上述程式 parse ``-f`` 參數，若有該參數則 ``force_replace`` 被設為 1
