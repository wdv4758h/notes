Performance Tips
===============================================================================

Ref: https://docs.julialang.org/en/latest/manual/performance-tips/


Avoid global variables
----------------------------------------------------------------------

global var 的內容會變， type 也會動態的變。 compiler 就無法最佳化。
如果用 ``const`` 就可以 optimize 沒問題。


Benchmark and Memory allocation
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

* builtin: ``@time``

* ``BenchmarkTools``


Avoid constainer with abstract type parameters
----------------------------------------------------------------------

e.g: :math:`a = Real[]` 這個 array 因為使用了 ``Real`` , 而 ``Real`` 的
element size 無法事先得知, ``a`` 會被實作成
array of pointer points to ``Real`` object. 裡面的每個 ``Real`` object 是
各自獨立的 allocation
