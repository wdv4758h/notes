========================================
Todo
========================================

* `Rust - A taste of dependent types <http://kmcallister.github.io/talks/rust/2015-dependent-types/slides.html>`_
* `Dependently Typed Programming in Agda <http://www.cse.chalmers.se/~ulfn/darcs/AFP08/LectureNotes/AgdaIntro.pdf>`_
* `Why do slices in a structure require a lifetime, but not vectors? <http://stackoverflow.com/questions/26371255/why-do-slices-in-a-structure-require-a-lifetime-but-not-vectors>`_
* `Rust to JS with Emscripten <https://users.rust-lang.org/t/rust-to-js-with-emscripten/587>`_
* Rust's decltype ?
* `Wikipedia - Composition over inheritance <https://en.wikipedia.org/wiki/Composition_over_inheritance>`_

Books
========================================

* `Learning Rust With Entirely Too Many Linked Lists <http://cglab.ca/~abeinges/blah/too-many-lists/book/README.html>`_
* `Rust for C++ Programmers <https://www.gitbook.com/book/aminb/rust-for-c/details>`_
* `Choosing your Guarantees <http://doc.rust-lang.org/nightly/book/choosing-your-guarantees.html>`_
    - original : http://manishearth.github.io/blog/2015/05/27/wrapper-types-in-rust-choosing-your-guarantees/
* `Unsafe <https://doc.rust-lang.org/book/unsafe.html>`_
* `"const" and "static" <https://doc.rust-lang.org/book/const-and-static.html>`_
* `The Rust Containers and Iterators Guide <https://csclub.uwaterloo.ca/~rdgawdzi/doc/guide-container.html>`_
* `The Advanced Rust Programming Language <https://doc.rust-lang.org/nightly/adv-book/>`_

Types
========================================

* `How Do Types Affect Productivity and Correctness? A Review <http://danluu.com/empirical-pl/>`_


brorrow
========================================

* `Holy std::borrow::Cow! – Redux <https://llogiq.github.io/2015/07/10/cow-redux.html>`_
* `Rust for C++ programmers - part 5: borrowed references <http://featherweightmusings.blogspot.tw/2014/05/rust-for-c-programmers-part-5-borrowed.html>`_


Docs
========================================

* `PhantomData <https://doc.rust-lang.org/core/marker/struct.PhantomData.html>`_
* `Cell <https://doc.rust-lang.org/std/cell/>`_
    - Shareable mutable containers.
* `boxed <https://doc.rust-lang.org/std/boxed/index.html>`_
    - A pointer type for heap allocation.
    - https://github.com/rust-lang/rust/blob/master/src/doc/trpl/box-syntax-and-patterns.md
    - https://doc.rust-lang.org/std/boxed/struct.Box.html


Operator Overloading
========================================

* `Rust - std::ops <https://doc.rust-lang.org/std/ops/index.html>`_


RFCs
========================================

* `DST <https://github.com/rust-lang/rfcs/blob/master/text/0490-dst-syntax.md>`_


Misc
========================================

* `Felix Klock II - Rust: Safe Systems Programming with the Fun of FP <https://vimeo.com/85253071>`_
* 傳教文
    - http://eggfan.org/2585


Question
========================================

* Python decorator like in Rust ?
* a function return a function or value (in enum ?)
* 什麼時候會 move ? heap 的話呢 ?
* who is non-copyable ?
    - euler.skip(1000-1) => this will move, non-copyable, why ?
* stack check detail ?
* gnerated assembly
* tutorial from stack / heap status
* ownership in mind programming
* memory layout
* tutorial with assembly
* Any type's pattern matching ?
* repr
* Why Rust?
    - http://www.steveklabnik.com/nobody_knows_rust/


Things
========================================

* pub
* mod
* extern crate std;
* prelude

Tips
========================================

* wants to know the type of a variable in Rust ?

::


    let () = asd;


Notice
========================================

* 變數預設是不能更動的，要更改需要加上 ``mut``
* Rust 的 reference 在 caller 跟 callee 都需加上 "&"，藉此可以確定自己在用 pass by reference
* 預設使用 jemalloc
