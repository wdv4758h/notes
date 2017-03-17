========================================
Julia
========================================


.. contents:: 目錄


Symbol
========================================

類似 Lisp 的 Symbol，
但是以 ``:`` 作為開頭。

.. code-block:: julia

    julia> typeof(:red)
    Symbol



Expression
========================================

.. code-block:: julia

    # 直接從字串 Parse 成 Expression
    julia> x = parse("(1+1)/(2+3)")
    :((1 + 1) / (2 + 3))

    # 輸出 Expression 內部結構（類似 AST）
    julia> dump(x)
    Expr
      head: Symbol call
      args: Array{Any}((3,))
        1: Symbol /
        2: Expr
          head: Symbol call
          args: Array{Any}((3,))
            1: Symbol +
            2: Int64 1
            3: Int64 1
          typ: Any
        3: Expr
          head: Symbol call
          args: Array{Any}((3,))
            1: Symbol +
            2: Int64 2
            3: Int64 3
          typ: Any
      typ: Any

    # 以類似 Lisp S-Expression 的方式輸出
    julia> Meta.show_sexpr(x)
    (:call, :/, (:call, :+, 1, 1), (:call, :+, 2, 3))

    # 執行 Expression
    julia> eval(x)
    0.4

    julia> eval(Expr(:call, :+, 1, 1))
    2



型別轉換
========================================



Macro
========================================

:URL:
    * http://docs.julialang.org/en/stable/manual/metaprogramming/
    * http://docs.julialang.org/en/stable/devdocs/cartesian/

Macro 是 AST 層級的



參考
========================================
