========================================
Rust RFCs
========================================


PR # => RFC #

.. contents:: 目錄


別人提 RFC 的經驗
========================================

* `From Tweet to Rust Feature <https://llogiq.github.io/2016/09/14/feature.html>`_



RFC 1444 - union
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/1444-union.md
:PR: https://github.com/rust-lang/rfcs/pulls/1444
:Tracking: https://github.com/rust-lang/rust/issues/32836



RFC 1504 - int128
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/1504-int128.md
:PR: https://github.com/rust-lang/rfcs/pull/1504
:Tracking: https://github.com/rust-lang/rust/issues/35118


這個 RFC 的目標是加入 ``i128`` 和 ``u128`` 這兩個 primitive type，
藉此用比較有效率的實做取代部份需要使用 BigNum 的地方，
也避免掉使用 BigNum 時的 Heap allocation 和較高 overhead 的操作，
而 128 位元數字將由 LLVM 提供有效率的實做（在 C 中已經可以經由 Clang 來使用 ``__int128`` ）。



RFC 2025 - Enable Nested Method Calls
========================================

:RFC: https://github.com/rust-lang/rfcs/blob/master/text/2025-nested-method-calls.md
:PR: https://github.com/rust-lang/rfcs/pull/2025
:Tracking: https://github.com/rust-lang/rust/issues/44100


這 RFC 的目標是要允許巢狀的 borrow，
例如 ``vec.push(vec.len())`` ，
vec 先是 mutable borrow，
然後裡面又有 shared borrow，
原本這樣的程式碼是不能編譯的，
但是經過這 RFC 以後，
只要裡面的借用是唯讀且生命週期只在其中，
那裡面的借用就被允許。

實做上會把 MIR 的 mutable borrow 改成兩階段借用，
第一階段只保留會被更動的狀態，
此時還可以進行生命週期內的唯讀借用，
等到真的要進行更動的操作時才會變成完全地更動借用。



Misc
========================================

* `Rust RFCs - 0198 - Slice Notation <https://github.com/rust-lang/rfcs/blob/master/text/0198-slice-notation.md>`_
    - foo.as_slice()    => ``foo[]``
    - foo.slice(n, m)   => ``foo[n..m]``
    - foo.slice_from(n) => ``foo[n..]``
    - foo.slice_to(m)   => ``foo[..m]``
    - `PR <https://github.com/rust-lang/rfcs/pull/198>`_

* `Rust RFCs - 0199 - Ownership Variants <https://github.com/rust-lang/rfcs/blob/master/text/0199-ownership-variants.md>`_
    - ``_mut`` suffix
    - `PR <https://github.com/rust-lang/rfcs/pull/199>`_

* `Rust RFCs - 0520 - New Array Repeat Syntax <https://github.com/rust-lang/rfcs/blob/master/text/0520-new-array-repeat-syntax.md>`_
    - ``[T, ..N]`` => ``[T; N]``
    - `PR <https://github.com/rust-lang/rfcs/pull/520>`_

* `Rust RFCs - 0544 - Rename "int" & "uint" <https://github.com/rust-lang/rfcs/blob/master/text/0544-rename-int-uint.md>`_

    - ``int`` & ``uint`` => ``isize`` & ``usize``
    - `PR <https://github.com/rust-lang/rfcs/pull/544>`_
