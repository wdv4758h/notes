Meta Programming
===============================================================================

.. highlight:: julia


Generated Functions
----------------------------------------------------------------------

- special macro ``@generated``

- return a quoted expression

- 根據 caller 提供的 type 資訊做 code generation.

e.g.::

    @generated function foo(x)
        # x denote type here
        # will show Int, Float64, String, ... etc
        println(x) # invoke at copmile, and only *once*
        return :(x * x)


- 可以做出 loop unroll 的效果
  (當需要的資訊在 type 裡就有的時候)


Macros in Base
----------------------------------------------------------------------

- ``Base.@pure``

- ``Base.@nexprs``

- ``Base.@_inline_meta``
