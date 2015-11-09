========================================
Rust - Misc
========================================

Overhead of Option
=========================================================

.. code-block:: rust

    use std::mem::size_of;

    macro_rules! show_size {
        (header) => (
            println!("{:<22} {:>4}    {}", "Type", "T", "Option<T>");
        );
        ($t:ty) => (
            println!("{:<22} {:4} {:4}", stringify!($t), size_of::<$t>(), size_of::<Option<$t>>())
        )
    }

    fn main() {
        show_size!(header);
        show_size!(i32);
        show_size!(&i32);
        show_size!(Box<i32>);
        show_size!(&[i32]);
        show_size!(Vec<i32>);
        show_size!(Result<(), Box<i32>>);
    }



64-bit (pointers are 8 bytes) :

+----------------------+----+-----------+
| Type                 | T  | Option<T> |
+======================+====+===========+
| i32                  | 4  | 8         |
+----------------------+----+-----------+
| &i32                 | 8  | 8         |
+----------------------+----+-----------+
| Box<i32>             | 8  | 8         |
+----------------------+----+-----------+
| &[i32]               | 16 | 16        |
+----------------------+----+-----------+
| Vec<i32>             | 24 | 24        |
+----------------------+----+-----------+
| Result<(), Box<i32>> | 8  | 16        |
+----------------------+----+-----------+

((大部分的狀況下) Compiler 會把 Option<ptr> 優化成單一一個 pointer，這對於所有 "Option-like" 的 enums 都適用，包含 user 自己定義的 Option)



RFC 1242 - Rust Lang Crates (Policy For Rust Lang Crates)
=========================================================

* `RFC 1242 <https://github.com/rust-lang/rfcs/blob/master/text/1242-rust-lang-crates.md>`_

Rust 對於先前在官方 GitHub Organization 底下的一些 crates 的 Policy (非 compiler 本身或是 standard library)。

這些 crates 有以下特色：

* 像 standard library 一樣地管理
* 像 standard library 一樣地維護 (包含平台的支援)
* 精心規劃過的品質



此 RFC 有三大目的：

1. 保持小量的 ``std``
    * ``std`` 保證的穩定性讓 ``std`` 的版本跟 Rust 綁在一起，所以會比 crates 有較少的彈性
2. 讓 ``std`` 分階段
3. 清理


新的兩個 GitHub Organization：

* rust-lang-nursery
* rust-lang-deprecated


放在 rust-lang-nursery 會從版本 ``0.X`` 開始，裡面的 crates 必須符合以下條件：

1. 已經有可以使用的程式碼
2. library subteam 同意把它加進去的請求 (表示對於讓這個 crate 成為 Rust 核心的一塊有興趣)

加入 rust-lang-nursery 之後 library subteam 和更多 community 會參與，
在進入下一個階段前增加更多的檢查。

最後，nursery 裡的 crates 會成功或失敗，
失敗的會被移到 rust-lang-deprecated，
否則會發展到 1.0 release 後被接受。

crates 在發展到 1.0 之後，就準備好提升到 rust-lang 了。
因此會需要撰寫 RFC 表明動機，community 擁有它的重要性，
檢視 API design 和緣由。當 1.0 RFC 被接受了之後，
crate 會移至 rust-lang 底下，轉由整個 Rust community 來掌控。
