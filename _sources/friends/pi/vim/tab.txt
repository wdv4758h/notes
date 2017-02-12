==========
vim 的 tab
==========

vim 和 tab 相關的設定有數個變數

* ``tabstop``

  - 設定每個 tab 顯示的寬度

* ``softtabstop``

  - 當使用者按下 tab 和 backspace 時，游標一次跳的格數
  - 會讓游標對齊 ``softtabstop`` 的整數倍位置

* ``expandtab``

  - 設定按下 tab 時，改為輸入空格，空格數量由 ``softtabstop`` 決定

* ``shiftwidth``

  - 使用 ``<<``, ``>>`` 縮排時，一次移動的格數
