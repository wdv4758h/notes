Type
===============================================================================

.. highlight:: julia

- optional static type


Float
----------------------------------------------------------------------

- IEEE 754

- ``Inf``::

    julia> Inf > NaN
    false

- ``-Inf``

- ``NaN``::

    julia> NaN == NaN
    false

    julia> NaN != NaN
    true

    # Note
    julia> [1 NaN] == [1 NaN]
    false


functions
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- ``isequal(x, y)``::

    julia> isequal(1.0000000000000000000000001, 1.0000000000000001)
    true

    # Note
    julia> isequal(NaN, NaN)
    ture
    # diff from ``NaN == NaN``

    julia> isequal([1 NaN], [1 NaN])
    true

- ``isnan(x)``


Array
----------------------------------------------------------------------

::

    a = [1, 2, 3]

    a[1]    # 1
    a[end]  # 3

with type::

    a = Float64[1, 2, 3]
    a = Int[1, 2, 3]


Matrix
----------------------------------------------------------------------

::

    a = [1 2 3]

    a = [1 2 3; 4 5 6]

with type::

    a = Int[1 2 3]


Range
----------------------------------------------------------------------

::

	julia> [1:10]
	1-element Array{UnitRange{Int64},1}:
	1:10

	julia> [1:10;]
	10-element Array{Int64,1}:
	1
	2
	3
	4
	5
	6
	7
	8
	9
	10

::

	julia> [1:3:20;]
	7-element Array{Int64,1}:
	1
	4
	7
	10
	13
	16
	19


Dict
----------------------------------------------------------------------

::

    Dict()

    d = Dict("foo" => 1, "bar" => 2)

    keys(d)

    values(d)

    ("foo" => 1) ∈ d

    haskey(d, "foo")


Pair
----------------------------------------------------------------------

::

    p = "foo" => 1
    p[1] == "foo"
    p[2] == 1


typeof
----------------------------------------------------------------------

Int64::

    julia> typeof(42)
    Int64

    julia> typeof(Int64)
    DataType

    julia> typeof(42)
    Int64

    julia> supertype(Int64)
    Signed

    julia> supertype(Signed)
    Integer

    julia> supertype(Integer)
    Real

    julia> supertype(Real)
    Number

    julia> supertype(Number)
    Any

    julia> supertype(Any)
    Any

String::

    julia> typeof("test")
    String

    julia> supertype(String)
    AbstractString

    julia> supertype(AbstractString)
    Any


Class
----------------------------------------------------------------------

::

    type Cat
        name::String
        age::Int
    end

    Cat("meow", Int)


- note that ``::`` is type annotation.

- ``a::C`` can read as "a is an instance of C".

- concrete type cannot have subtype::

    struct S
        ...
    end

- ``struct`` are immutable


Type Assertion
----------------------------------------------------------------------

::

    (1 + 2)::Int

    (1 + 2)::Float64  # error


Type Declaration
----------------------------------------------------------------------

::

    julia> function λ()
            x::Int8 = 10
            x
        end
    λ (generic function with 2 methods)

    julia> λ()
    10

    julia> typeof(λ())
    Int8

On function definition::

    julia> function λ()::Int64
            42.0
        end
    λ (generic function with 1 method)

    julia> λ()
    42           # alway be converted to Int64


Abstract Types
----------------------------------------------------------------------

Declaration::

    abstract type MyType end
    abstract type MyType <: MySupperType end

- ``<:`` can read as "is subtype of"::

    julia> Int64 <: Int
    true

    julia> Int64 <: Real
    true

    julia> Int64 <: Float64
    false

- function will be compiled on demand with concrete type::

    f(x) = x * 2

means::

    f(x::Any) = x * 2

If we invoke ``f(1)``, the function ``f(x::Int) = ...`` will be compiled.


Parametric Types
----------------------------------------------------------------------

- like template in C++

- Generic programming: https://en.wikipedia.org/wiki/Generic_programming

一個 Parametric Type 長成這樣

.. literalinclude:: ./code/param_type.jl

這個實際上可以生產無數種 concrete type,
e.g. ``Point{Float64}``, ``Point{String}`` ...

而 ``Point`` 這個 id 本身是個 type object,
想像成所有 ``Point{...}`` 的集合::

    julia> Point{Float64} <: Point
    true

    julia> Point{AbstractString} <: Point
    true

    julia> Point{AbstractVector{Int}} <: Point
    true

每個 concrete type 彼此之間互相平行::

    julia> Point{Float64} <: Point{String}
    false

即使是 ``Real`` 之於 ``Float64`` 也是平行的::

    julia> Point{Float64} <: Point{Real}
    false

Julia 的 type parameter 是 *invariant* 。 *invariant* 代表的是我們原本 type
parameter 之間的關係，並不會帶入到新的 type 上面。
上面 ``Real`` vs ``Float64`` 的例子展現 *invariant* 的特性。
在 julia 的記憶體管理上， ``Point{Float64}`` 就會顯得比較有效率, 內容是已知的
64-bits。

如果想要類似 *covariant type* 的效果還是有的::

    Point{Float64} <: Point{<:Real}
    true

*contravariant*::

    Point{Real} <: Point{>:Float64}
    true

在 function argument 中定義 ``Point{T}``, 且 ``T`` 是 ``Real`` 的 subtype 方法
如下:

.. literalinclude:: ./code/param_func.jl



Parametric Method
----------------------------------------------------------------------

julia 0.5::

    same_type{T}(x::T, y::T) = true

    # abstract type
    same_type{T<:AbsType}(x::T, y::T) = true

0.6::

    same_type(x::T, y::T) where {T} = true

    # abstract type
    same_type(x::T, y::T) where {T<:AbsType} = true


Tuple Type
----------------------------------------------------------------------

https://docs.julialang.org/en/latest/manual/types.html#Tuple-Types-1
