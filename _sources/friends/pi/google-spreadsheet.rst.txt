=======================
Google Spreadsheet 筆記
=======================
Google Spreadsheet 可以在表格內放入許多種運算功能，自動化判斷狀況並顯示

在 Cell 內輸入 ``=`` 開頭的字串，即會被視為要運算的函式


Cell Reference
---------------
* ``B3`` 連結到 B3 儲存格的內容
* ``$B3`` 效果同上，但此格被「複製」時，Column ``B`` 不會改變（ ``3`` 會被改變）
* ``B$3`` 效果同上，但此格被「複製」時，Row ``3`` 不會改變（ ``B`` 會被改變）
* ``$B$3`` 效果同上，Column ``B`` 和 Row ``3`` 固定不變


Range Reference
----------------
* ``B`` 表示整條 Column B
* ``B:H`` 表示 B 到 H 所有連續的 Column
* ``B3:H5`` 表示一個矩形範圍

``$`` 的效果和 Cell Reference 相同


Functions
----------
* ``AND(v1, [v2, ...])`` 做 Boolean And 運算
* ``OR(v1, [v2, ...])`` 做 Boolean OR 運算
* ``COUNTIF(range, value)`` 算出 ``range`` 內和 ``value`` 相同值的數量
* ``COUNTUNIQUE(range)`` 算出 ``range`` 內所有不相同的值的數量
* ``ISBLANK(cell)`` 檢查內容是否為空（注音空白字元會被判斷為非空）
* ``ISNUMBER(cell)`` 檢查內容是否為數字
* ``TRIM(cell)`` 將前後空白字串清除


筆記
-----
* 判斷一段 row 內的值，若有相同值則將它們上色 ::

    =COUNTIF($B3:$H3, B3)>1

  - 若把這條式子套用在一個範圍上，會有複製的效果，故 ``B`` 和 ``H`` 需要加上 ``$`` 避免被改變
