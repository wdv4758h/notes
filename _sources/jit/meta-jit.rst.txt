========================================
Meta-JIT
========================================


.. contents:: 目錄


介紹
========================================

Meta-JIT 基本上的概念就是寫一個直譯器，
然後讓工具幫忙生成 JIT 版本，
其中可以使用一些標注來幫忙 JIT 做處理，
藉此可以簡化 JIT 的撰寫方式。



RPython Toolchain
========================================



HolyJIT
========================================

:Repo: https://github.com/nbp/holyjit
:Articles: https://blog.mozilla.org/javascript/2017/10/20/holyjit-a-new-hope/


HolyJIT 是利用 Rust 實做的 Meta-JIT，
使用 Rust 撰寫一個直譯器後，
透過一個 ``jit!`` macro 把直譯器實做包起來，
藉此生成 JIT 的實做，
其中會透過 Rust 編譯器的 IR 來處理，
從中轉換出適合的 JIT 實做。
