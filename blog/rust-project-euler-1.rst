:title: Rust Example - Project Euler #1 - Try Some Features in Simple Problem
:slug: rust-example-project-euler-1
:date: 2015-07-26 16:17
:modified: 2015-07-28 21:46
:category: Rust
:tags: Rust, macro
:author: wdv4758h
:summary:

心血來潮跑去用 Rust 寫一下 Project Euler #1 的題目，
題目其實很簡單，算出 1000 以下 3 或 5 的倍數的總和，
就是個簡單的數學題，這樣的題目如果也只用非常簡單的作法來解就太無聊了，
所以就拿簡單的題目試試看可以展現出 Rust 的哪些 features (?

.. code-block:: rust

    #![feature(iter_arith)]     // for .sum()
                                // unstable library feature 'iter_arith' : bounds recently changed

    fn p1_sol1() -> u64 {
        // formula solution

        //  3,  6,  9, ...
        //  5, 10, 15, ...
        // 15, 30, 45, ...

        //  3 * 1,  3 * 2,  3 * 3, ...,  3 * a => sum:  3 * a * (1 + a) / 2
        //  5 * 1,  5 * 2,  5 * 3, ...,  5 * b => sum:  5 * b * (1 + b) / 2
        // 15 * 1, 15 * 2, 15 * 3, ..., 15 * c => sum: 15 * c * (1 + c) / 2

        fn sum_range(start: u64, end: u64) -> u64 {
            end * (start + end) / 2
        }

        fn sum_multiples_of_two_below(base_num: &[u64], end: u64) -> u64 {
            let v1 = base_num[0];
            let v2 = base_num[1];
            let a = (end - 1) / v1;
            let b = (end - 1) / v2;
            let c = (end - 1) / (v1 * v2);
            let sum_a = v1 * sum_range(1, a);
            let sum_b = v2 * sum_range(1, b);
            let sum_c = (v1 * v2) * sum_range(1, c);
            sum_a - sum_c + sum_b
        }

        sum_multiples_of_two_below(&[3, 5], 1000)

        // -C opt-level=3 :
        //
        //      p1_sol1::h7b3c1cda8687c063eaa:
        //          cmpq     %fs:112, %rsp
        //          ja       .LBB0_2
        //          movabsq  $8, %r10
        //          movabsq  $0, %r11
        //          callq    __morestack
        //          retq
        //      .LBB0_2:
        //          pushq    %rbp
        //          movq     %rsp, %rbp
        //          movl     $233168, %eax
        //          popq     %rbp
        //          retq
        //
        // -C opt-level=3 -C no-stack-check :
        //
        //      p1_sol1::h7b3c1cda8687c063eaa:
        //          pushq   %rbp
        //          movq    %rsp, %rbp
        //          movl    $233168, %eax
        //          popq    %rbp
        //          retq
    }

    fn p1_sol2() -> u64 {
        // simple filter solution
        (1..1000)
            .filter(|&n| (n % 3 == 0) || (n % 5 == 0))
            .sum()
    }

    fn p1_sol3() -> u64 {
        // general filter solution
        fn sum_multiples_of_base_below(base_num: &[u64], start: u64, end: u64) -> u64 {
            (start..end)
                .filter(|&n| base_num.iter().any(|&base| n % base == 0))
                .sum()
        }

        sum_multiples_of_base_below(&[3, 5], 1, 1000)
    }

    fn p1_sol4() -> u64 {
        // macro version for filter
        macro_rules! sum_multiples_of_base_below {
            ( OωO $($base:expr),+ OωO , $start:expr, $end:expr ) => {
                ($start..$end)
                    .filter(|&n| $(n % $base == 0)||+)
                    .sum()
            }
        }

        sum_multiples_of_base_below!(OωO 3, 5 OωO, 1, 1000)
    }

    fn p1_sol5() -> u64 {
        // closure

        let mut s = 0;
        let mut v = 0;

        {
            // only borrow in this scope

            let mut f = || {
                v = v + 1;
                s = s + ((v % 3) * (v % 5) < 1) as u64 * v;
            };

            for _ in 1..1000 {
                f();
            }
        }

        s
    }

    fn p1_sol6() -> u64 {
        // static variable

        fn f() -> u64 {
            static mut s: u64 = 0;
            static mut v: u64 = 0;

            // static mut is unsafe
            unsafe {
                v = v + 1;
                s = s + ((v % 3) * (v % 5) < 1) as u64 * v;

                s
            }
        }

        let mut result = 0;

        for _ in 1..1000 {
            result = f();
        }

        result
    }

    fn p1_sol7() -> u64 {
        // iterator

        struct Euler {
            s: u64,
            v: u64,
        }

        impl Iterator for Euler {
            type Item = u64;

            fn next(&mut self) -> Option<u64> {
                let s = self.s;
                let v = self.v;
                let s = s + ((v % 3) * (v % 5) < 1) as u64 * v;
                let v = v + 1;
                self.s = s;
                self.v = v;

                Some(self.s)
            }
        }

        let euler = Euler { s: 0, v: 0 };

        euler.skip(1000-1)
            .next().unwrap_or(0)
    }

    fn p1_sol8() -> u64 {
        // overload index
        // index has side-effect, it's bad :P

        use std::ops::{Index, IndexMut};

        struct Euler {
            s: u64,
            v: u64,
        }

        impl Index<u64> for Euler {
            type Output = u64;

            fn index(&self, _index: u64) -> &u64 {
                &self.s
            }
        }

        impl IndexMut<u64> for Euler {
            fn index_mut(&mut self, _index: u64) -> &mut u64 {
                let v = self.v;
                let s = self.s;
                let v = v + 1;
                let s = s + ((v % 3) * (v % 5) < 1) as u64 * v;
                self.v = v;
                self.s = s;
                &mut self.s
            }
        }

        let mut euler = Euler { s: 0, v: 0 };

        for _ in 1..1000 {
            &mut euler[0];
        }

        euler[0]
    }

    fn main() {
        // sum of all the multiples of 3 or 5 below 1000
        // ans : 233168
        println!("p1_sol1 : {}", p1_sol1());
        println!("p1_sol2 : {}", p1_sol2());
        println!("p1_sol3 : {}", p1_sol3());
        println!("p1_sol4 : {}", p1_sol4());
        println!("p1_sol5 : {}", p1_sol5());
        println!("p1_sol6 : {}", p1_sol6());
        println!("p1_sol7 : {}", p1_sol7());
        println!("p1_sol8 : {}", p1_sol8());
    }


Solution 1
========================================

一般的公式解，但是還沒全部完成，
目前只能吃兩個 base number，需要更 general。

這邊剛好可以看到幾個地方，
一個是 Rust 會用 ``&`` 符號來表示 pass by reference，
array 的 reference 就會變成 ``&[type]`` 。
再來是 Rust 的 function 裡面可以定義 function，
個人有在寫 Python，
而 Python 對於這種 function 裡面定義 function 是蠻方便且常見的 (看看 decorator)，
看到 Rust 可以有 local function 就有種熟悉感，
雖然 Python 跟 Rust 這兩個語言在本質上有很大的差異 XD


Solution 2
========================================

Rust 可以用 ``..`` 這個特殊的 operator 來產生 Python 中 range 的效果，
使用方法就直接寫 ``start..end`` 就可以了。

另外 Rust 有支援豐富的 iterator 操作，
可以使用 ``.filter`` 來對 iterator 做篩選，
而 .filter 中可以直接寫 lambda function 傳入，
lambda function 的 syntax 是用 ``| ... |`` 把參數夾住，
可以指定參數的 type 以及是否要用 reference，
如果要寫多行的 lambda function 的話，
可以用 ``{ ... }`` 來撰寫 (在 Rust 中 ``{}`` 是個 expression)。

* `Struct std::ops::Range <https://doc.rust-lang.org/std/ops/struct.Range.html>`_

Solution 3
========================================

Solution 2 的改版，
利用傳入的 array 來做出 ``.filter`` 需要的 lambda function，
如此一來可以適用於任何長度的 array。

Solution 4
========================================

Solution 3 的改版，
刻意拿 macro 出來玩 (?)。
這邊要先注意一件事，
Rust 的 macro 跟 C 和 C++ 的不同，
並不是單純的字串取代，
而是跟 AST 息息相關的一部份。
這個範例把 ``OωO`` 當作前面 base numbers 的開頭和結尾，
中間的數字都會被 ``$($base:expr),*`` 吃進去，
``$base:expr`` 表示說我要爬的是 expression，
而爬到的資料我稱它為 "base"，
最外面的 ``$(...),+`` 則表示裡面的 pattern 會重複一次以上 (中間用 ``,`` 區隔)，
後面分別是 ``$start:expr`` 和 ``$end:expr`` 兩個 expression，
到這邊已經把東西 parse 完了，
接下來是要生出想要的程式碼，
``$start`` 和 ``$end`` 直接拿去用在 range 上，
而 ``$(n % $base == 0)||*`` 則把寫的 base numbers 都展開成判斷式 (用 ``||`` 接起來)，
最後就達到類似 Solution 3 的效果啦~


* `Wikipedia - Hygienic macro <https://en.wikipedia.org/wiki/Hygienic_macro>`_

Todo
========================================

* 把 Solution 1 改的更 general
* 觀察 Rust 編譯完後出來的結果
* 觀察 Rust 底下的記憶體操作
* 不同優化下生出的 assembly
* ...
