=============
= Vim Regex =
=============
* Magic

  - 根據 ``magic`` option 的值，特殊字元可能需要/不需要跳脫
  - Very magic - 幾乎所有字元都為特殊字元，例如 ``$`` ``%`` ``@`` ``(`` ``)``
  - Magic - ``(`` ``)`` 需要跳脫才會被視為特殊字元
  - Very nomagic - 幾乎所有字元都需要跳脫才會被視為特殊字元
  - 從 ``\v`` 開始的 pattern 為 very magic

* 個人建議

  - regex 統一以單引號字串編寫
  - regex 統一以 ``\v`` 編寫

以下的 pattern 都以 very magic 表示

* Regex lookahead/behind

  - 比對 match 字串的 **前後** ，不會被算在最後 match 的字串中
  - ``@<=`` positive lookbehind
  - ``@<!`` negative lookbehind
  - ``@=`` positive lookahead
  - ``@!`` negative lookahead

  - 範例

    + 比對所有的 ``foo`` ，但後面不能接 ``bar`` ::

        foo(bar)@!

    + 比對所有的 ``bar`` ，但前面不能接 ``foo`` ::

        (foo)@<!bar

* ``%()`` 可以把 pattern 包成 atom 但不算成 group
* ``matchlist(<str>, <pattern>)`` -> ``List``
