========================================
Rust RFCs
========================================


PR # => RFC #

.. contents:: 目錄


別人提 RFC 的經驗
========================================

* `From Tweet to Rust Feature <https://llogiq.github.io/2016/09/14/feature.html>`_



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
