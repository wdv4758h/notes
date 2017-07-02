MXNet
===============================================================================

MXNet.jl
----------------------------------------------------------------------

Get network weight

    ``model.arg_params`` -> ``Dict{Symbol => NDArray}``


Extract data from NDArray

    在 Julia 的 wrapper 中，所有操作必須是 MXNet 的 NDArray，這是 MXNet 的
    tensor 資料結構。而且有可能在 GPU 中，必須透過 ``mx.copy!(Array, NDArray)``
    來取得::

        # w is NDArray
        arr = zeros(eltype(w), size(w))
        mx.copy!(arr, w)

    or breifly::

        # w
        arr = copy(w)

Show net layers::

    julia> mx.list_arguments(net)
    24-element Array{Symbol,1}:
     :data
     :fullyconnected0_weight
     :fullyconnected0_bias
     :fullyconnected1_weight
     :fullyconnected1_bias
     :fullyconnected2_weight
     :fullyconnected2_bias
     :fullyconnected3_weight
     :fullyconnected3_bias
     :fullyconnected4_weight
     :fullyconnected4_bias
     :fullyconnected5_weight
     :fullyconnected5_bias
     :fullyconnected6_weight
     :fullyconnected6_bias
     :fullyconnected7_weight
     :fullyconnected7_bias
     :fullyconnected8_weight
     :fullyconnected8_bias
     :fullyconnected9_weight
     :fullyconnected9_bias
     :fullyconnected10_weight
     :fullyconnected10_bias
     :label
