========================================
Type System
========================================

Substructural Type System
========================================

* Linear type systems
* Affine type systems
* Relevant type system
* Ordered type system


Affine Type System
------------------------------

Affine Type System 的特性是 "最多只能用一次"，
主要用於避免 "use-after" 系列的 bugs，
常用於 threads、connections、files、allocations 等地方。

Affine Type System in Rust
++++++++++++++++++++++++++

* `Rust - Affine Types, Borrows and Regions, Mutable XOR Shared, Unsafe Rust <https://github.com/Gankro/thesis/blob/master/chapters/rust.tex>`_

大概的內容：一開始想要在 data ownership 引入 Affine Type System 來避開一些常見問題，後來為了增加實用性而需解決若干狀況，最後給出了各狀況的解決方案形成現在 Rust 語言的基底

keyword: Rust, Affine, Ownership, Lifetime, Traits, Unsafe

----

Rust 的 data "Ownership" 是採用 Affine Type System (有例外，不是唯一)，
和一般 Affinte Type 不同的在於是從 "Ownership" 的角度來看，
也就是說 value 只會單獨被佔有 (uniquely owned)。

.. code-block:: rust

    fn main() {
        // A growable array
        let data = Vec::new();

        // transfer ownership of `data` to `data2`
        let data2 = data;
        // `data` is now statically inaccessible,
        // and logically uninitialized

        // transfer ownership of `data2` to `consume`
        consume(data2)
        // `data2` is now statically inaccessible,
        // and logically uninitialized
    }

    fn consume(mut data3: Vec<u32>) {
        // Mutating the collection is known to be safe, because
        // `data3` knows it's the only one who can access it.
        data3.push(1);
    }
