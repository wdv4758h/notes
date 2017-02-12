==========================
= Vim script 筆記 - VimL =
==========================

變數
-----
* 變數沒有型態，且為弱型別（不同型態的資料運算時可能會自己轉型）

* 前綴

  - ``&``: 選項 (可以用 ``set`` 指令更改的那些)
  - ``l:``: Function 的區域變數
  - ``a:``: Function 參數
  - ``t:``: Tab 的區域變數
  - ``s:``: Script 的區域變數
  - ``b:``: Buffer 的區域變數
  - ``w:``: Window 的區域變數
  - ``g:``: 全域變數
  - ``v:``: vim 預設的變數

* 使用 ``let a = 3`` 來賦值

* 取得設定值 ::

    let a = &shiftwidth

語法
-----
* if condition ::

    if <condition>
      ...
    elseif <condition>
      ...
    endif

* while loop ::

    while <condition>
      ...
    endwhile

* for loop ::

    for i in list
      ...
    endfor

* function definition ::

    function! <function-name> (<arguments>)
      ...
    endfunction

  - ``function!`` 代表要 override 同名的 function

字串
-----
* Literal string

  - ``"abc\n"`` - 一般字串， ``\n`` 會被 interprete 成 newline 字元
  
    + 在一般字串中要跳脫 double quote 字元（ ``"`` ）的話用 ``\"`` ，例如 ``"Here comes a \"string\""``

  - ``'abc\n'`` - literal string，類似 Python 的 raw string
  
    + 在 literal string 中要跳脫 single quote 字元（ ``'`` ）的話用 ``''`` ，例如 ``'Here comes a ''string'''``
  
* 字串比對

  - 避免使用 ``==`` ，因為其 case sensitive 設定是根據 set ignorecase
  - case sensitive 的字串比對 ``==#``
  - case insensitive 的字串比對 ``==?``
  - 字串 regex match

    + case sensitive ``=~#``
    + case insensitive ``=~?``
    + pattern 建議用單引號字串

  - Regex group ::

      matchlist('test, test2', '\v^([a-z]*), (.*)$')
      -> ['test, test2', 'test', 'test2', '', '', '', '', '', '', '']

    + 看起來最多到 9 個 group

* 字串長度 (bytes) ::

    strlen(s)

* 字串 "外觀" 長度 ::

    strdisplaywidth(s)

* 重複字串 ::

    repeat('-', 80)

* 字串取代 ::

    substitute(l:text, '^\s*', '', '')

* 切片

  - slice ::

      "abcdefg"[1:3] ==# "bcd"

    + 和 Python 不同，Vim 的 slice 是上下都包含的

  - strpart ::

      strpart("abcdefg", 3, 2)    == "de"
      strpart("abcdefg", -2, 4)   == "ab"
      strpart("abcdefg", 5, 4)    == "fg"
      strpart("abcdefg", 3)       == "defg"

* 轉數字 ::

    str2nr("42", 10)

  - base 可以是 8、10、16

* 與 unicode code point 轉換 ::

    char2nr("中文字")
    nr2char(20013)

  - ``char2nr`` 會回傳第一個字的 code point（ ``中`` → U+4e2d → 20013）


Functional Programming
-----------------------
* ``filter(<list-or-dict>, string)``

  - ``<list-or-dict>`` 內的每個元素依序被代入 ``string`` 的 ``v:val`` ，然後 ``string`` 被 eval，若結果為 0 則該元素被移除
  - Metaprogramming
  
* ``map(<list-or-dict>, string)``

  - ，所有元素被 **inplace 取代** 為 ``string eval 的結果
  - Metaprogramming

其他
-----
* 不定數量參數的函式 ::

    function! foo(arg1, ...)
    endfunction

  - ``a:0`` 代表 ``...`` 的參數數量
  - ``a:1`` 為 ``...`` 的第一個參數

* 長度 ::

    len(list_a)
