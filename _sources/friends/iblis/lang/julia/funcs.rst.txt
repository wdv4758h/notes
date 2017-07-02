Functions
===============================================================================

.. highlight:: julia

built-in
----------------------------------------------------------------------

``typeof``::

    julia> typeof(:foo)
    Symbol

``in``::

    julia> a
    2×3 Array{Int64,2}:
    1  2  3
    4  5  6

    julia> 1 ∈ a
    true

    julia> 1 ∉ a
    false

``length`` and ``size``::

    julia> a
    2×3 Array{Int64,2}:
    1  2  3
    4  5  6

    julia> length(a)
    6

    julia> size(a)
    (2, 3)


Anonymous Function
----------------------------------------------------------------------

::

    x -> x + 42


Multiple-Dispatch
----------------------------------------------------------------------

::

    julia> function λ(a::Int, b::Int)
            a + b
        end
    λ (generic function with 1 method)

    julia> function λ(a::Float, b::Float
    Float16 Float32  Float64
    julia> function λ(a::Float64, b::Float64)
            a * b
        end
    λ (generic function with 2 methods)
