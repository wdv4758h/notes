=========================
= Vim script 筆記 - API =
=========================

位置代號
--------
有些邏輯上的位置可用代號表示，這些代號可以在各種函式當成傳入值

* ``'.'`` - 游標目前的位置
* ``'$'`` - 最後一行
* 數字 - 行數/列數

編輯區
-------
* 取得編輯區內的內容

  - 取得游標所在的行的內容 ::

      getline('.')
      
  - 取得游標所在位置的單字 ::

      expand('<cword>')
      expand('<cWORD>')

* 游標位置

  - 取得游標的位置 ::

      line('.')
      col('.')
      let [@_, l:lnr, l:cur_col, @_] = getpos('.')

    + Column 為 1-based

  - 設定游標的位置 ::

      cursor(<linenum>, <col>)

* 設定游標所在行的內容 ::

    call setline('.', "abcd")

* 在游標所在行的下一行插入一行字串 ``xxx`` ::

    call append('.', "xxx")


切割
-----
* 產生一個空空的 split ::

    new
    vnew

* 調整 split 的大小 ::

    resize 5
    vertical resize 30

* ``setlocal noswapfile`` 和 ``setlocal buftype=nofile`` 可以產生「忽略內容修改」的視窗，用來顯示資訊


Menu
-----
* ``pumvisible()`` 回傳 "現在是否有 Menu 正在顯示"

  - 若 Menu 中只有一個選項，Menu 預設不會顯示，但 ``pumvisible()`` 仍會回傳 ``1``

* ``complete(<start-col>, <match>)``

  - ``complete`` 函式只能在 insert mode 被呼叫，會產生一個選單，列出 ``<match>`` 裡的選項
  - 該行會從 ``<start-col>`` 開始被切除，直到游標所在的位置為止，替換成 ``<match>`` 裡的選項
  - ``<start-col>`` 是 1-based


指令
-----
* 執行 normal mode 下的動作 ::

    normal! <movements>


編寫 vim 語法上色檔
-------------------
* 基本方法 ::

    syn match <name> <regex>
    hi def <name> <argument>

  - ``name`` 為該語法定義一個名稱
  - ``regex`` 用來定義語法的內容，如果 ``regex`` 的結尾是空格，可能會讓下一個語法區塊出問題
  - ``argument`` 定義該語法的外觀，例如 ::

      hi def agdaXXX cterm=bold,underline ctermfg=1

    + 前景和背景需分別設定，若 terminal 支援的話也可以使用底線或其他功能
    + ``ctermfg`` 和 ``ctermbg`` 都可以使用顏色的名稱或是顏色的代碼

    ===== ==== ================================
    NR-16 NR-8 COLOR NAME
    ===== ==== ================================
    0     0    Black
    1     4    DarkBlue
    2     2    DarkGreen
    3     6    DarkCyan
    4     1    DarkRed
    5     5    DarkMagenta
    6     3    Brown, DarkYellow
    7     7    LightGray, LightGrey, Gray, Grey
    8     0*   DarkGray, DarkGrey
    9     4*   Blue, LightBlue
    10    2*   Green, LightGreen
    11    6*   Cyan, LightCyan
    12    1*   Red, LightRed
    13    5*   Magenta, LightMagenta
    14    3*   Yellow, LightYellow
    15    7*   White
    ===== ==== ================================

    + 要注意 ``cyan`` 指的其實是亮色 (不論是否有 ``cterm=bold``)， ``darkcyan`` 才是暗色

* 要注意 ``syntax on`` 會讓 vim 提早載入 ``syntax/`` 裡的 script，若有需要用到 ``ftplugin/`` 定義的變數，請用一些變數辨認狀態


函式
-----
* 檢查某變數/函式/選項是否存在 ::

    exists()

  - 見 ``:help exists``

* 確認某個檔案是否可執行 ::

    executable('git')
    executable('zdict')

  - 會自動搜尋檢查使用者的 PATH


其他
-----
* ``set guitablabel`` 和 ``set tabline`` 可以指定 tab 顯示的 title
* [Windows gVim] ``call system("cmd /C start /B ". glob(l:path))`` 可以不產生小黑窗就開啟目錄
