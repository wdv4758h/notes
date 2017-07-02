================
Zsh 補完系統筆記
================
Zsh 的補完系統實在是太複雜，但是文件又幾乎沒有範例，我得做些筆記，不然一定會忘光

補完的指令不一定要存在，你可以為 ``hello`` 寫補完的函式，但是實際上沒有這個指令


基本
-----
* 準備一個目錄，專門用來放 Completion Script，並且把目錄的路徑加入 ``fpath``

  .. code:: sh

    fpath=($HOME/.rcfiles/zsh/completions $fpath)

  - ``fpath`` 的型態是 Zsh Array，而不像 ``path`` 一樣是字串
  - 記得原本的 ``fpath`` 要留著，不然內建的都會讀不到

* 建立 ``_hello`` 檔案

  .. code:: sh

    #compdef hello
    _hello () {
        _arguments "*:argument:(arg1 arg2 XD)"
    }
    _hello "$@"

  - 現在輸入 ``hello `` 按下 ``tab`` 會補完


``_describe`` 基本使用方式
---------------------------
以下 Code 可以產生選單補完

.. code:: sh

    local -a options arguments
    options=('-c:description for -c opt' '-d:description for -d opt')
    arguments=('e:description for e arg' 'f:description for f arg')
    _describe 'values' options -- arguments

產生選單 ::

  -c  -- description for -c opt
  -d  -- description for -d opt
  e   -- description for e arg
  f   -- description for f arg


``_alternative`` 基本使用方式
------------------------------
當你想要把兩個函式的結果都拿來補完的時候，可以用 ``_alternative`` 達成

.. code:: sh

  _alternative \
    'users:user:_users' \
    'hosts:host:_hosts'


``_arguments`` 基本使用方式
----------------------------
``_arguments`` 的使用方法非常多，可以根據參數把選項做成選單

* 單字類的補完

  - 格式： ``TAG:DESCRIPTION:ACTION``
  - ``TAG`` 可以是參數的位置，例如 ``1`` 代表這個項目在第 1 個參數使用。 ``*`` 則是每個位置都套用
  - ``DESCRIPTION`` 目前不確定用途，但不能是空字串，可以是一個空白字元
  - ``ACTION``

    + ``ACTION`` 和它前面的 ``:`` 之間不能有空白字元
    + 補完一些單字： ``(France Germany Italy)``
    + 補完一些單字，並附上說明： ``((Paris\:France Berlin\:Germany Rome\:Italy))``
    + 更多用法見 ``ACTION`` 章節

  - 範例

    .. code:: sh

      _arguments '*:Countries:((Paris\:France Berlin\:Germany Rome\:Italy))'

    + 會產生如下的選單 ::

        Berlin  -- Germany
        Paris   -- France
        Rome    -- Italy

* ``-`` 開頭的選項

  - 格式： ``-OPT[DESCRIPTION]``
  - 格式： ``-OPT[DESCRIPTION]:MESSAGE:ACTION``
  - ``-OPT`` 為補完選項
  - ``DESCRIPTION`` 為說明文字
  - ``MESSAGE`` 目前不確定用途
  - ``ACTION`` 如上述
  - 範例

    .. code:: sh

      _arguments\
        '-s[short output]'\
        '--l[long output]'\
        '-f[input file]:filename:_files'\
        '*:filename:{_files}'

    + ``-o[text]`` 會產生 ``-o`` 的補完，附上它的說明
    + ``-o[text]:message:action`` 會產生 ``-o`` 的補完、說明。若 ``-o`` 被選到了，下一個參數會使用 ``action`` 來補完
    + 預設選項 ``*:filename:{_files}`` 會以檔名做補完

  - 若有多個選項需要分享同一個說明

    .. code:: sh

      _arguments {-f,--force}'[description]'

  - 若需要有多個選項之間互斥

    .. code:: sh

      _arguments \
          - '(set1)' {-a,--arg}'[description1]'
          - '(set2)' {-b,--brg}'[description2]'

    + zsh 只會補完 ``-a`` 和 ``-b`` 其中一個

* 就算是連續，兩次 ``_arguments`` call 的效果會分開

  - 參數可以重覆
  - 參數與說明的對齊會分開計算


``ACTION``
-----------
``ACTION`` 定義一個參數實際被補完時的行為

* 補完一些單字： ``(France Germany Italy)``
* 補完一些單字，並附上說明： ``((Paris\:France Berlin\:Germany Rome\:Italy))``

  - 也可以不附說明，且若選項有空白， ``(())`` 的效果會比 ``()`` 好

* 使用函式產生補完選項： ``func_name``

  - ``func_name`` 需要能夠產生補完，無法用 stdout 傳回結果
  - 補完檔案名稱： ``_file``
  - 補完以逗點分隔的選項：見 ``_values``
  - 用 ``{`` ``}`` 包起來的話可以傳參數，e.g. ``{_values -s , dicts urban yahoo all moe}``
  - 若遇到不容易在一行內嵌入的狀況，分離成另一個函式應該可以解決

* 不補完，但改變狀態，以後可根據狀態做不同的補完： ``->state1``

  - 狀態會被存在 ``$state`` 變數中


``_values``
`````````````
* 補完以逗點分隔的選項： ``{_values -s , dicts urban yahoo all moe}``

  - ``dicts`` 是說明而不是選項之一，但用途未知
  - zsh 會自己判斷選項是否已被選進 BUFFER

* 補完 ``foo@news:woo`` 格式的字串： ``_sep_parts '(foo bar)' @ '(news ftp)' : '(woo laa)'``


``compadd``
------------
``_arguments`` 實際上是 ``compadd`` 的包裝

``_arguments`` 預設會在單字後方加上一個空白字元，此為 ``compadd -S ' '`` 的效果

若補完的選項有共同的前綴，且這些前綴不希望顯示在 menu 時，可以使用 ``compadd -p $pre``


``zstyle``
-----------
``zstyle`` 可以快速、簡短的設定很多東西，用在 completion 上時，可以設定：

* completion menu 每個分區的 title
* 為特定程式過濾掉特定檔名（例如讓 ``vim`` 的補完不要出現 ``*.o`` 選項）
* 應該還有很多可以設定

語法： ``zstyle <context> <styles>``

context 為 ``:completion:function:completer:command:argument:tag`` 格式的字串，中間可以用 ``*`` 做 wildcard matching

分區 title 範例，每一種 title 可以套用不同的格式：

.. code:: sh

  zstyle ':completion:*' verbose yes
  zstyle ':completion:*:descriptions' format "$fg[yellow]%B--- %d%b"
  zstyle ':completion:*:messages' format '%d'
  zstyle ':completion:*:warnings' format "$fg[red]No matches for:$reset_color %d"
  zstyle ':completion:*:corrections' format '%B%d (errors: %e)%b'
  zstyle ':completion:*' group-name ''

過濾檔名範例，讓 ``vim`` 的補完不要出現 ``*.o`` 以及 ``*.out`` 選項

.. code:: sh

  zstyle ':completion:*:*:vim:*:*' ignored-patterns '(*.py|*.out)'

在 ``2>`` 後方補完 ``*.log`` 的檔名

.. code:: sh

  zstyle ':completion:*:*:-redirect-,2>,*:*' file-patterns '*.log'

更多資訊請見 ``man zshcompsys`` 的 ``COMPLETION SYSTEM CONFIGURATION`` section



其他
-----
* ``$BUFFER`` 儲存整行指令的內容
* ``$PREFIX`` 儲存目前游標所在的單字
* ``_hosts`` 基本上是查看 ``~/.ssh/known_hosts`` 的內容，zsh 只在開啟時載入一次（並非每次補完時都查看）


特別感謝這些淺顯易懂的說明
-----------------------
* https://github.com/zsh-users/zsh-completions/blob/master/zsh-completions-howto.org
* http://www.masterzen.fr/2009/04/19/in-love-with-zsh-part-one/


其他文件
---------
* http://zsh.sourceforge.net/Doc/Release/Expansion.html
