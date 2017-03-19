Flow Control
===============================================================================

.. highlight:: julia


if
----------------------------------------------------------------------

::

    if
        ...
    elseif
        ...
    end


for
----------------------------------------------------------------------

::

    for i = [1, 2, 3]
        println(i)
    end

    for i in [1, 2, 3]
        println(i)
    end

    for i in 1:5
        println(i^2)
    end

::

    for i in Dict("foo" => 1, "bar" => 2)
        println(i)
    end

    for (k, v) in Dict("foo" => 1, "bar" => 2)
        println(k, ": ", v)
    end


while
----------------------------------------------------------------------

::

    while ...
        ...
    end


try
----------------------------------------------------------------------

::

    try
        ...
    catch e
        ...
    end


Function
----------------------------------------------------------------------

Function will return the last expression.
``return`` is still allow.

::

    julia> function λ(x, y)
               x + y
           end
    λ (generic function with 1 method)

    julia> λ(2, 5)
    7

Compact declaration::

    julia> f(x, y) = x ^ y
    f (generic function with 1 method)

Return tuple::

    julia> λ(x, y) = x + y, x - y
    λ (generic function with 1 method)

    julia> λ(2, 3)
    (5,-1)

Arbitrary positional arguments::

    function λ(args...)
        println(args)  # tuple
    end

Function call unpacking::

    λ([1, 2, 3]...)


Default arguments::

    function λ(x, y=2, z=10)
        x ^ y + z
    end


Keyword *only* arguments::

    function λ(x; y=2, z=10)
        x ^ y + z
    end

    λ(10; y=3)
    # or
    λ(10; :y=>3)

Keyword args function call::

    λ(; y=2, z=10)

    λ(; :y=>2, :z=>10)

    λ(; (:y,2), (:z, 10))
