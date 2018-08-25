============
隱藏顯示字元
============

在 vim 中，可以使用 ``syntax`` 指令定義關鍵字，也可以將其隱藏，或是改為顯示其他的字元

關鍵字的顏色則是用 ``highlight`` 定義

``syntax`` 可縮減為 ``syn`` ， ``highlight`` 可縮減為 ``hi`` ，以下會使用縮減後的指令來舉例

上色
----

::

  syn match SyntaxName /regex/
  hi def SyntaxName cterm=bold ctermfg=white ctermbg=black

上述指令會把檔案中出現的符合 ``regex`` 的字串定義為 ``SyntaxName`` 的關鍵字， ``SyntaxName`` 則被設為粗體、白色前景、黑色背景

vim 的各個 Theme 中，已經有設定好各種關鍵字的顏色，若希望使用那些風格而不自行設定，可以使用 ``link`` 參數，並附上關鍵字的名稱

::

  hi def link SyntaxName Comment

常見的預設關鍵字如 ``Comment`` ``Function`` 等等

隱藏/取代
---------

若希望將檔案中的空白字元都隱藏，可以為 ``syn`` 指令加上 ``conceal`` 參數

::

  syn match WhiteSpace / / conceal cchar=.

這會把空白字元標記為「可隱藏」，但實際上如何顯示需參考 ``conceallevel``

* 0: 不隱藏
* 1: 每一組符合的文字塊被顯示為一個字元，顯示的字元由以下方式決定

  - 若 ``cchar`` 選項有定義，則以該字元顯示
  - 若否，且 ``listchars`` 有定義，則以該字元顯示
  - 若否，則顯示為一個空白

* 2: 每一組符合的文字塊被顯示為一個字元，顯示的字元由以下方式決定

  - 若 ``cchar`` 選項有定義，則以該字元顯示
  - 否則隱藏

* 3: 符合的文字塊完全隱藏


游標所在的行仍會以原文顯示，以便編輯；但這個行為可以由 ``concealcursor`` 的值改變 ::

  set concealcursor=nvic

``nvic`` 分別為 ``normal`` ``visual`` ``insert`` ``command`` ，不同的 mode 可以分別設定是否 **不** 要顯示

範例
----

把行首的空格都改顯示為深灰色的點點 ::

  :syn match IndentWhiteSpace /\(^ *\)\@<= / conceal cchar=.
  :hi Conceal ctermfg=black cterm=bold
  :set conceallevel=2
  :set concealcursor=ni
