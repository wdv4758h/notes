========================================
Iterator
========================================


Peakable
========================================

.. code-block:: rust

    fn main() {
        let s = "這是測試";
        let mut it = s.chars().peekable();

        while !it.is_empty() {
            let (i, j) = (it.next(), it.peek());
            println!("{} {}", i.unwrap(), j.unwrap_or(&' '));
        }
    }


Output : ::

    這 是
    是 測
    測 試
    試


Reference
========================================

* `Rust - Module std::iter <https://doc.rust-lang.org/std/iter/index.html>`_
