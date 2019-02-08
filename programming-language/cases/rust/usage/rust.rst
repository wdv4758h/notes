========================================
Rust
========================================


一些被推薦的點 (代研究)
========================================

* Immutable by default, no global variables, private by default
* borrow checker
* C like performance without nasal demons
* no big VM, no GC needed
* immutable/private by default
* pattern matching
* HM-style type inference (Turing complete)
* fully hygienic macros
* helpful compiler errors, Lint's built in
* great community
* Move by default
* channel for concurrency
    - Erlang like channel
    - https://news.ycombinator.com/item?id=7851274
* suitable for hard real time
* I don't have to worry about aliasing anymore
    - pointer aliasing
    - https://www.reddit.com/r/rust/comments/2x0h17/whats_your_killer_rust_feature/cow3zod
* https://www.reddit.com/r/rust/comments/2x0h17/whats_your_killer_rust_feature
* region-based memory management -> lifetime


Todo
========================================

* `Traits as Higher-order Functions <http://sproul.io/blog/posts/traits-as-hof-in-rust.html>`_
* `Collecting Results from Collections <http://hoverbear.org/2015/07/08/a-useful-error-pattern/>`_


Rust - Runtime Service
========================================

隨手用 Valgrind 跑個 Rust 的程式後，
發現有意料之外的 heap 使用，
後來才知道是 Rust std 做的，
之後來了解 Rust 的 Runtime Service 做了什麼事情 ...

* `[2013] Notes on the Rust runtime <http://brson.github.io/2013/02/02/redesigning-the-rust-runtime/>`_
* `Rust - Module std::rt <https://doc.rust-lang.org/std/rt/>`_
* `Rust - std - rt <https://github.com/rust-lang/rust/blob/master/src/libstd/rt/mod.rs>`_


No stdlib
========================================

* `Rust - No stdlib <https://doc.rust-lang.org/book/no-stdlib.html>`_


Rust - clone-on-write smart pointer
========================================

* `Rust - Enum std::borrow::Cow <https://doc.rust-lang.org/std/borrow/enum.Cow.html>`_

Reference
========================================

* `Wikipedia - Rust <https://en.wikipedia.org/wiki/Rust_%28programming_language%29>`_
* `Rust RFCs <https://github.com/rust-lang/rfcs>`_
