========================================
Julia
========================================


.. contents:: 目錄


介紹
========================================

設計起源
------------------------------

Julia 始於 2009 年 Jeff Bezanson、Stefan Karpinski、Viral B. Shah、Alan Edelman
想要建立一個既快速又高階的程式語言。



現有特色
------------------------------

* 重點放在數值運算
* 動態語言
* 使用 GC
* Multiple Dispatch
* Parametric Polymorphism
    - 函式
        + Generic
            * ``function f(x, y) x + y end``
            * ``f(x, y) = x + y``
            * ``f{T}(x::T, y::T) = x + y``
        + 寫死
            * ``function f(x::Float64, y::Float64) x + y end``
            * ``f(x::Float64, y::Float64) = x + y``
* 可以透過 PyCall 直接使用 Python 套件
* 可以透過 ``ccall`` 直接使用 C 函式
    - ``ccall(("clock", "libc"), Int32, ())``
    - ``ccall((:clock, "libc"), Int32, ())``
    - ``unsafe_string(ccall((:getenv, "libc"), Cstring, (Cstring,), "SHELL"))``



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
