============
= Vim 筆記 =
============

程式參數
---------
* 用 buffer 模式開啟 ::

    vim file1 file2 file3

* 用 tab 模式開啟 ::

    vim -p file1 file2 file3

  - 有數量上限，實測大約為 10 頁，超出的檔案不會被開啟

* 用唯讀模式開啟 ::

    vim -M

* ``sudoedit``

  - ``sudoedit`` 是 ``sudo`` 和 ``vim`` 的組合，會將檔案先複製到 ``/tmp`` 下，在 ``:wq`` 以後才會用 root 權限置換掉原本的檔案

  - 只有第一個分頁有 ``sudo`` 效果

* 從暫存檔復原內容 ::

    vim -r {{filename}}.swp

  - 不保證能完整的復原


快捷鍵們
---------

移動
``````
* 回到檔首 ::

    gg

* 跳到檔尾 ::

    G

* 移到頁首 / 頁尾 / 中間

  - ``H`` / ``L`` / ``M``

* 一次翻動一頁

  - ``<C-f>`` / ``<C-b>``

* 一次翻動半頁

  - ``<C-u>`` / ``<C-d>``

* 移到行首 / 行尾

  - ``^`` / ``$``

* 向右尋找，把游標移到第一個找到的 ``C`` 字元處 ::

    fC

  - ``FC`` 會向左尋找

* 跳回游標的上一個位置，可在檔案之間跳躍 ::

    <C-o>

* 以游標所在的字串為標名開啟檔案 ::

    gf

  - 跳回原檔 ::

      :bf

  - 跳到 "上一個位置" ::

      <C-o>

  - 在新分頁中開檔 ::

      <C-w>gf

* 在 ``:help`` 頁面中跳到別的章節

  - 把游標移到 tag 上然後按下 ``<C-]>``

* 移畫面

  - 只移畫面，類似設多文字編輯器的 Ctrl+UP, Ctrl+Down

    + ``<C-e>`` / ``<C-y>``

  - 把游標所在的行移到畫面中間 / 上面 / 下面

    + ``zz`` / ``zt`` / ``zb``


貼上
``````
* 在 insert/replace/command mode 下，從 register ``a`` 貼上內容 ::

    <C-r>a

* 指定從 yank 的 register 貼上 ::

    "0p

* 在多行前面貼上同樣的字串

  A.  用 ``<C-v>`` 選取一整條
  B.  大寫 ``I``
  C.  ``<C-r>0``


反白
``````
* 以字元為單位反白 ::

    v

* 以行為單位反白 ::

    V

* 區塊反白 ::

    <C-v>

  - ``o`` / ``O`` 可以在區塊反白時讓游標跳到反白區的對面

* 把反白內容轉為 小/大 寫

  - 反白後按下 ``u`` / ``U``


刪除
``````
* 從游標開始刪除直到字元 ``C`` 為止， ``C`` 不被刪除 ::

    dtC

* 從游標開始刪除，刪到 ``C`` 為止， ``C`` 也被刪除 ::

    dfC

* 從游標開始從下刪 3 行，共刪 4 行 ::

    d3j

* 刪除 ``[`` ``]`` 內的字， ``{}()<>""''`` 都可用 ::

    di[

  - ``diB`` == ``di{``
  - ``dib`` == ``di(``

* 刪除一個 html tag 內的字 ::

    dit

* 從游標刪到行尾，游標處的字也刪除 ::

    D

* 從游標刪到行尾，並進入 insert mode ::

    C

* 把整行清除，留下一空行，並進入 insert mode

  - ``cc`` / ``S``

* 把 ``[abc]`` 變成 ``abc`` ::

    di[vhp

  - 解說: "刪除" 會把內容放入 register ``"`` ，也是貼上的預設來源

* 在 insert mode 中往回刪除一個單字

  - [insert mode] ``<C-w>``

  - 和許多 shell CLI 的行為一樣，從游標開始往回刪除一個單字，最後維持在 insert mode

  - ``<C-u>`` 可用來刪除一整行


書籤
``````
* 在游標所在行設定書籤 ``a`` ::

    ma

* 跳至書籤 ``a`` ::

    'a


分頁
-----
* Tab

  - 把 buffer 轉為 tab ::

      :tab ball

  - 把 split 轉為 tab ::

      <C-w>T

  - 把 tab 往下一個位子移動 ::

      :tabm +1

  - 檔案瀏覽器

    + ``:Vex`` / ``:Sex`` / ``:Tex``
    + 在中文環境下可能會有問題

  - 跳到相鄰的分頁

    + ``gt`` / ``:tabn`` / ``gT`` / ``:tabp``

  - 對每一個 tab 都執行 ``COMMAND`` ::

      :tabdo COMMAND

  - 在新分頁開啟 help 頁面 ::

      :tab help i_CTRL-X

* Split

  - 製造切割視窗

    + 水平 ::

        <C-w>n

    + 垂直 ::

        :vnew
        :50vnew

  - 調整大小

    + 寬度 ::

        <C-w><
        <C-w>>
        :vertical resize 50
        :vertical resize +50

    + 高度 ::

        :resize 30
        :resize +30

  - 移動 split 視窗的位置

    + ``<C-w>H`` / ``<C-w>J`` / ``<C-w>K`` / ``<C-w>L``

  - 可以用滑鼠調整視窗大小 ::

      :set mouse=a

* Buffer

  - 下一個檔案 ::

      :bn

  - 上一個檔案 ::

      :bp

  - 關掉檔案 ::

      :bw

  - 查看開啟 ``vim`` 時傳入的 CLI 參數 ::

      :args

  - 設定「自動存檔」，再對每一個 buffer 都執行 ``COMMAND`` ::

      :set autowrite, :bufdo COMMAND

    + 自動存檔是指在切換 buffer 時會自動存檔

    + 需要自動存檔是因為切換 buffer 時需要先存檔，不設定的話就不能對每個 buffer 執行指令


取代
-----
指令 ::

  :<range>s/<pattern>/<string>/<flags>

* ``range``

  - ``%`` 為整個檔案
  - ``'<,'>`` 代表 Visual 範圍

* ``flags`` (``:help :s_flags``)

  - ``g`` 為 global search，每一行的每個 ``pattern`` 都會被取代成 ``string``
  - ``i`` 為 case insensitive
  - ``I`` 為 case sensitive
  - ``c`` 為 confirmation，每個取代都會詢問是否要執行

* 把每行加上行號 ::

  :%s/^/\=(1 - line("'<") + line(".")) . "\. "/


外部指令
---------

* 把當前內容用 ``sort`` 指令處理過，再直接取代現在的內容 ::

    :% !sort

* 把當前內容 pipe 給 ``python`` ::

    :w !python

* 用指令的結果取代該行內容

  - [normal] ``!!COMMAND``

* 在游標所在下一行插入指令結果 ::

    :r !cal

* 把反白的區域當成 ``stdin`` 送給外部指令，並把結果取代掉反白區

  - [visual] ``!COMMAND``


Register
---------
* 把游標所在的整行文字複製進 ``"a`` register 中 ::

    "ayy

* 系統的剪貼簿 ::

    "*

  - ``vim`` 需要在編譯時開啟 ``clipboard`` module

* 複製的預設 register ::

    "0

* 刪除 / 剪下的預設 register ::

    ""


折疊
-----
* 在檔首加上 ::

    # vim:fdm=marker
    # toggle all folding by "zi"

* 被 ``# {{{`` 和 ``# }}}`` 包起來的區塊就可以被折疊起來
* 依據不同檔案類型，可以使用不同的註解，vim 會認得

* ``zo`` 把游標所在的 fold 打開
* ``zc`` 把游標所在的 fold 關上
* ``zj`` ``zk`` 在不同 fold 之間跳躍

* ``zi`` toggle 所有的 fold

* ``zm`` 關上所有的 fold
* ``zx`` 刷新所有的 fold，有時新的 fold 會需要這個才能馬上使用


補完系統
--------
* 補完系統裡的檔名 ::

    [insert] <C-x><C-f>


其他
-----
* ``<C-[>`` 等於 ``<ESC>`` 鍵

* 輸入 ``tab`` 字元 ::

    <C-v><TAB>

* 讓 ``vim`` 以 ``scp`` 方式抓取遠端檔案，如果不用 ``scp`` 而是用 ``sftp`` 或 ``ftp`` 的話需打出絕對路徑 ::

    vim scp://pi314@HOST/FILE

* 把目前的畫面做成 html file ::

    :TOhtml

* 把本次搜尋的上色清除，但 search pattern 仍存在，故按下 ``n`` 還是可以繼續搜尋 ::

    :noh

* ``vim`` 的 regex

  - ``()`` 如果不 escape，就視為普通的括號

  - ``[]`` 需要 escape 才會是普通的括號

  - ``\<abc\>`` 可以只比對到 ``abc`` 單字，不會 match ``aabcc`` 中間的 ``abc``

    + 是 [normal] ``#`` 預設的行為

* 移除檔首的 BOM ::

    :set nobomb

* 暫時回到 normal mode，按一個按鍵後即回到 insert mode

  - [insert][replace] ``<C-o>``

* 列出一些設定 ::

    :set

  - 修改檔案格式為 ``unix`` ::

      :set ff=unix

* 把檔案中的 tab 都置換成適合長度的 space ::

    :retab

* 在太長斷行的字串上垂直移動 ::

    :nnoremap k gk

* 設定 unicode ambiguous width 字元的寬度 ::

    :set ambiwidth=single
    :set ambiwidth=double

  - terminal 也需要做相同的設定，才不會顯示錯誤
  - http://vim.1045645.n5.nabble.com/Real-displayed-width-of-a-character-td1223323.html

* 把 vim 內部的指令導到檔案中

  A.  ``redir >{{file_name}}``
  B.  ``{{command}}``
  C.  ``redir END``

* 修改 encoding ::

    :w ++enc=utf-8
    :w ++enc=utf-8 {{another_filename}}

* 有時 vim 的語法上色會壞掉 (例如整頁都變成藍色)，可能是因為失去追蹤語法結構，可以用下列指令重新同步 ::

    :syntax sync fromstart

* 列出 vim 開啟時所存取的檔案及存取時間

  - ``$ vim --startuptime <vim-log-filename>``

* 避免 vim 去連接 X Server

  - ``$ vim -X``
  - 在 ``vimrc`` 中加上 ``set clipboard=exclude:.*``

* 對每個檔案套用不同的縮排寬度 ::

    autocmd FileType html serlocal shiftwidth=2 tabstop=2
    autocmd FileType make setlocal noexpandtab

* 取得組合鍵的 help ::

    :help CTRL-X
    :help i_CTRL-X

* 用 vim 加密檔案

  - 開啟檔案後輸入 ``:X`` ，再輸入兩次密碼，存檔即生效

    + 之後都用普通的方式打開即可， vim 會在開啟時要求輸入密碼
    + 更改密碼方式亦同
    + 若要取消加密，在更改密碼時都直接按 Enter 即可

* 對每一行下指令 ::

    :g/pattern/cmd

  - 以 行 為單位，所有符合 ``pattern`` 的行都被執行 ``cmd`` （command mode 指令）
  - 把檔案內所有成對的 ``{`` ``}`` 都刪除: ``:g/{/normal f{da{``
