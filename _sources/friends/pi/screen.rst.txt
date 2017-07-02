=====================
= screen 用法及設定 =
=====================

用詞
====

本文件統一稱呼（可能非正式）

* 每個 ``screen`` process 為一個 ``session``
* ``screen`` 中的每一個頁面為一個 ``window``

command line arguments
======================

* 開啟一個新的 ``screen session`` ::

    $ screen

* 開啟一個新的 ``screen session`` 並取名為 ``<session_name>`` ::

    $ screen -S <session_name>

* 查看目前的 ``screen session`` 列表 ::

    $ screen -ls

  - 會列出 ``id`` ，如果有 ``session`` 名稱的話，也會列出

* attach 一個被 detach 的 ``session`` ::

    $ screen -r [id | session_name]

  - ``id``/``session_name`` 不需要完整提供，只要提供的長度足夠辨別即可

* 把當前的 ``screen session`` detach ::

    $ screen -d

* attach 一個 ``session`` ，若有必要的話，先 detach ::

    $ screen -rd

  - 突然斷網時， ``screen`` 會停留在 attach 狀態，此時無法 attach

* 多重 attach，每個使用者會同時得到同一個 ``session`` 的控制權 ::

    $ screen -x [id | session_name]

* 連接 Serial Port ::

    screen /dev/tty.Bluetooth-Incoming-Port 115200

  - 沒錯，GNU Screen 可以連接 Serial Port

hot keys
========

* ``screen`` 的 hot key 預設都以 ``^a`` 為前綴

* 把當前 ``screen`` detach ::

    ^a d

* 新增一個 ``window`` ::

    ^a c

* 切換回上一個 ``window`` ::

    ^a ^a

* 切換到下/上一個 ``window`` ::

    ^a n/p

* 切換到編號 k 的 ``window`` ::

    ^a [0123456789]

* 進入指令模式 ::

    ^a A

* 砍掉當前的 ``window`` ::

    ^a k

* 複製之前的文字 ::

    ^a ^[

  - 貼上 ::

      ^a ^]

* Split

  - ``^a S`` 橫著切
  - ``^a |`` 直著切
  - ``^a X`` 刪除一個 Split
  - ``^a TAB`` 跳到下一個 Split

screen 內部指令
===============

* 按下 ``^a A`` 後會進入指令模式

* 把該 ``window`` 的標題文字換成 ``test`` ::

    :title test

* 重新讀取設定檔 ::

    :source ~/.screenrc

* 更改 ``windows`` 的順序 ::

    :number <number>

  - 若 ``<number>`` 已經存在，則目前的 window 會和對方交換號碼以及位置

* 更改 session name ::

    :sessionname <new-session-name>

設定
====

* 個人設定檔

  - ``~/.screenrc``

* 按鍵設定

  - for ``Cygwin`` ``mintty`` ``xterm``

    + ``bindkey \033[1;5D prev # ctrl+left``
    + ``bindkey \033[1;5C prev # ctrl+right``

* 編碼

  - ``defutf8 on``
  - ``defencoding utf8``

顏色設定
========

* 資料來源

  - ``man screen``

    + 搜尋 ``STRING ESCAPE``

* 排版

  - ``%=`` 的效果為一堆空白，儘可能把所有空間佔滿

    + ``aa%=bb`` 顯示為 ``aa`` 在最左方， ``bb`` 在最右方
    + ``aa%=bb%=cc`` 顯示為 ``aa`` 在最左方， ``bb`` 在正中間， ``cc`` 在最右方

  - ``%<`` 會設定切斷點，目前不太了解作用方式

    + ``aa%<cc`` 顯示為 ``aacc``
    + ``aa%=%<cc`` 顯示為 ``aa%=``
    + ``aa%=%=%<cc`` 顯示為 ``aa%=%=``

* 元件

  - ``%w`` 為所有的 window

    + 顯示為 ``0 title0  1* title1  2 title2``
    + 被 focus 的 window 編號旁會有 ``*``

    + ``%-w`` 為所有 focus window 左方的 window
    + ``%n`` 為 focus windows 的編號
    + ``%t`` 為 focus windows 的標題
    + ``%+w`` 為所有 focus window 右方的 window
    + ``%-w_%n %t_%+w`` 會讓 focus windows 的編號以及標題旁被底線夾著，其他 window 則無

  - ``%``` 顯示 ``screen`` 的 ``backtick`` 指令的輸出

    + ``backtick id lifespan autorefresh cmd args``
    + 每 ``lifespan`` 秒，output 就被視為過期，並重新執行一次
    + 每 ``autorefresh`` 秒更新一次畫面

      * 若 ``lifespan`` 和 ``autorefresh`` 都是 0，則該指令被視為在背景執行，一有新的 output 就更新

  - ``%Y/%m/%d %c:%s`` 顯示 ``2015/02/06 12:34`` 格式的時間

* 顏色

  - 色碼格式為 ``%{12 34}``

    + ``1`` 為套用的方式

      * ``+`` 把值加在目前的值上，重覆的覆蓋過去
      * ``-`` 把目前的值減掉套用的值
      * ``!`` 把目前的值反轉
      * ``=`` 把目前的值直接洗掉（舊的不保留），再套用新的值

    + ``2`` 為套用的屬性

      * ``d`` 為深色
      * ``u`` 為底線
      * ``b`` 為粗體
      * ``r`` 為反轉
      * ``s`` 為強調
      * ``B`` 為閃礫
      * 有些 terminal 顯示反轉和強調的方式都是反轉

    + ``3`` 為 **背景**
    + ``4`` 為 **前景**

      * ``k`` 黑
      * ``r`` 紅
      * ``g`` 綠
      * ``y`` 黃
      * ``b`` 藍
      * ``m`` 紫
      * ``c`` 靛
      * ``w`` 白
      * ``d`` 預設
      * ``.`` 不更改
      * 大寫為亮色
