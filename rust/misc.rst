========================================
Rust - Misc
========================================

.. contents:: Table of Contents

Rust Macro
========================================

* `Macros <http://www.ncameron.org/blog/macros/>`_
* `Macros in Rust pt1 <http://ncameron.org/blog/macros-in-rust-pt1/>`_
* `Macros in Rust pt2 <http://www.ncameron.org/blog/macros-in-rust-pt2/>`_
* `Macros in Rust pt3 <http://www.ncameron.org/blog/macros-in-rust-pt3/>`_
* `Macros in Rust pt4 <http://www.ncameron.org/blog/macros-in-rust-pt4/>`_
* `Macros in Rust pt5 <http://www.ncameron.org/blog/macros-in-rust-pt5/>`_

* `Rust Books - Macros <https://doc.rust-lang.org/nightly/book/macros.html>`_
* `The Little Book of Rust Macros <https://danielkeep.github.io/tlborm/book/index.html>`_



Get Data Type
========================================

* `Module std::intrinsics <https://doc.rust-lang.org/std/intrinsics/index.html>`_

.. code-block:: rust

    #![feature(core_intrinsics)]

    fn print_type_of<T>(_: &T) {
        let type_name =
            unsafe {
                std::intrinsics::type_name::<T>()
            };
        println!("{}", type_name);
    }

    fn main() {
        print_type_of(&32.90);           // prints "f64"
        print_type_of(&(vec!(1, 2, 4))); // prints "collections::vec::Vec<i32>"
    }



Rust's Traits v.s. Haskell's Type class
========================================

Rust 的 Traits 和 Haskell 的 Type class 基本上相似

* `What is the difference between traits in Rust and typeclasses in Haskell? <http://stackoverflow.com/questions/28123453/what-is-the-difference-between-traits-in-rust-and-typeclasses-in-haskell>`_


function static variable
========================================

* `"const" and "static" <https://doc.rust-lang.org/book/const-and-static.html>`_
* use of mutable static requires unsafe function or block
* 在 multithread 的情況下，一個 thread 在改值時，另外一個 thread 可能還在讀，所以需要加上 unsafe

.. code-block:: rust

    fn f(n: i32) {
        static mut x: i32 = 0;
        unsafe {
            println!("before: {}", x);
            x = n;
            println!("after:  {}", x);
        }
    }

    fn main() {
        f(1);
        f(2);
    }

    // before: 0
    // after:  1
    // before: 1
    // after:  2


Lint
========================================

* `rust-clippy <https://github.com/Manishearth/rust-clippy>`_
* `Wikipedia - Lint (software) <https://en.wikipedia.org/wiki/Lint_%28software%29>`_


Iterator
========================================

* `Itertools <https://github.com/bluss/rust-itertools>`_

.. code-block:: rust

    let x = vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]];

    println!("{:?}", x);    // [[1, 2, 3], [4, 5, 6], [7, 8, 9]]

    ////////////////////////////////////////
    // transpose
    ////////////////////////////////////////

    let y: Vec<_> = x[0].iter()
                        .zip(&x[1])
                        .zip(&x[2])
                        .map(|((&a, &b), &c)| (a, b, c))
                        .collect();

    println!("{:?}", y);    // [(1, 4, 7), (2, 5, 8), (3, 6, 9)]

    ////////////////////////////////////////
    // column
    ////////////////////////////////////////

    let y = x[0].iter()
                .zip(&x[1])
                .zip(&x[2])
                .map(|((&a, &b), &c)| (a, b, c))
                .nth(2)        // last column
                .unwrap();

    println!("{:?}", y);    // (3, 6, 9)

    ////////////////////////////////////////
    // column (inspect)
    ////////////////////////////////////////

    let y = x[0].iter()
                .inspect(|&x| println!("stage 0 :\t{:?}", x))
                .zip(&x[1])
                .inspect(|&x| println!("stage 1 :\t{:?}", x))
                .zip(&x[2])
                .inspect(|&x| println!("stage 2 :\t{:?}", x))
                .map(|((&a, &b), &c)| (a, b, c))
                .inspect(|&x| println!("stage 3 :\t{:?}", x))
                .nth(2)     // last column
                .unwrap();

    // stage 0 :       1
    // stage 1 :       (1, 4)
    // stage 2 :       ((1, 4), 7)
    // stage 3 :       (1, 4, 7)
    // stage 0 :       2
    // stage 1 :       (2, 5)
    // stage 2 :       ((2, 5), 8)
    // stage 3 :       (2, 5, 8)
    // stage 0 :       3
    // stage 1 :       (3, 6)
    // stage 2 :       ((3, 6), 9)
    // stage 3 :       (3, 6, 9)
    // (3, 6, 9)

    println!("{:?}", y);    // (3, 6, 9)

    ////////////////////////////////////////
    // flat
    ////////////////////////////////////////

    let y: Vec<_> = x[0].iter()
                        .chain(&x[1])
                        .chain(&x[2])
                        .collect();

    println!("{:?}", y);    // [1, 2, 3, 4, 5, 6, 7, 8, 9]


    let y: Vec<_> = x.iter()
                     .flat_map(|tmp| tmp.iter())
                     .collect();

    println!("{:?}", y);    // [1, 2, 3, 4, 5, 6, 7, 8, 9]

    ////////////////////////////////////////
    // sum each row
    ////////////////////////////////////////

    #![feature(iter_arith)]

    fn main() {

        let x = vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]];

        let y:Vec<i32> = x.iter()
                          .map(|x| x.iter().sum())
                          .collect();

        println!("{:?}", y);    // [6, 15, 24]
    }

    ////////////////////////////////////////
    // scalar
    ////////////////////////////////////////

    let n = 10;
    let y:Vec<i32> = (0..10).map(|x| x * n)
                            .collect();

    println!("{:?}", y);    // [0, 10, 20, 30, 40, 50, 60, 70, 80, 90]

    ////////////////////////////////////////
    // factorial
    ////////////////////////////////////////

    let n = 10;
    let y = (1..).take_while(|&i| i <= n).product()

    println!("{:?}", y);    // 3628800

    ////////////////////////////////////////
    // diagonal
    ////////////////////////////////////////

    let y: Vec<i32> = x.iter()
                       .enumerate()
                       .map(|(i, values)| values[i])
                       .collect();

    println!("{:?}", y);    // [1, 5, 9]

    ////////////////////////////////////////
    // specific two cols
    ////////////////////////////////////////

    let cols = vec![0, 2];
    let y: Vec<_> = x.iter()    // Vec<&Vec<i32>>
                     .enumerate()
                     .filter_map(|(i, value)| if cols.contains(&i) { Some(value) } else { None })
                     .collect();

    println!("{:?}", y);    // [[1, 2, 3], [7, 8, 9]]



.. code-block:: rust

    let fibonacci_iter = (0..).map(|_| {
                                    static mut m: i32 = 0;
                                    static mut n: i32 = 1;
                                    unsafe {
                                        let tmp = m;
                                        m = n;
                                        n += tmp;
                                        n
                                    }
                                });

    for i in fibonacci_iter {
        println!("{}", i);
    }


    // 1
    // 2
    // 3
    // 5
    // 8
    // 13
    // 21
    // 34
    // 55
    // 89
    // 144
    // 233
    // 377
    // 610
    // 987
    // 1597
    // 2584
    // 4181
    // 6765
    // 10946
    // 17711
    // 28657
    // 46368
    // 75025
    // 121393
    // 196418
    // 317811
    // 514229
    // 832040
    // 1346269
    // 2178309
    // 3524578
    // 5702887
    // 9227465
    // 14930352
    // 24157817
    // 39088169
    // 63245986
    // 102334155
    // 165580141
    // 267914296
    // 433494437
    // 701408733
    // 1134903170
    // 1836311903
    // thread '<main>' panicked at 'arithmetic operation overflowed', transpose.rs:8


    let fibonacci_iter = (0..).scan((0, 1), |state, _| {
                                                *state = (state.1, state.0 + state.1);
                                                Some(state.1)
                                            });

    for i in fibonacci_iter {
        println!("{}", i);
    }

    // 1
    // 2
    // 3
    // 5
    // 8
    // 13
    // 21
    // 34
    // 55
    // 89
    // 144
    // 233
    // 377
    // 610
    // 987
    // 1597
    // 2584
    // 4181
    // 6765
    // 10946
    // 17711
    // 28657
    // 46368
    // 75025
    // 121393
    // 196418
    // 317811
    // 514229
    // 832040
    // 1346269
    // 2178309
    // 3524578
    // 5702887
    // 9227465
    // 14930352
    // 24157817
    // 39088169
    // 63245986
    // 102334155
    // 165580141
    // 267914296
    // 433494437
    // 701408733
    // 1134903170
    // 1836311903
    // thread '<main>' panicked at 'arithmetic operation overflowed', transpose.rs:3



rustc
========================================

* `A tutorial on creating a drop-in replacement for rustc. <https://github.com/nrc/stupid-stats>`_




Cargo
=========================================================

.. code-block:: sh

    $ cargo search python
        Updating registry `https://github.com/rust-lang/crates.io-index`
    python_mixin (0.0.2)               Deprecated in favour of `external_mixin`. Use Python to generate your Rust, right in your Rust.
    external_mixin (0.0.1)             Use your favourite interpreted language to generate your Rust, right in your Rust. Supports Python, Ruby and shell (`sh`) out o…
    python_rub (0.0.3)                 Rust Builder for Python
    rust_mixin (0.0.1)                 Yo dawg, use Rust to generate Rust, right in your Rust. (See `external_mixin` to use scripting languages.)
    external_mixin_umbrella (0.0.2)    Backing library for `rust_mixin` and `external_mixin` to keep them DRY.
    cpython (0.0.4)                    Bindings to Python
    python3-sys (0.1.1)                FFI Declarations for Python 3
    python27-sys (0.1.0)               FFI Declarations for Python 2.7
    adorn (0.1.1)                      A plugin to provide python-style decorators in Rust
    lonlat_bng (0.1.3)                 Convert longitude and latitude coordinates to BNG coordinates, and vice versa



Overhead of Option
=========================================================

* `std::stringify! <https://doc.rust-lang.org/std/macro.stringify!.html>`_
    - 把傳入的 tokens 轉成字串

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
