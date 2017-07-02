:title: Rust - Closure
:slug: rust-closure
:date: 2015-07-27 23:38
:modified: 2015-07-27 23:38
:category: Rust
:tags: Rust, closure, trait, move
:author: wdv4758h
:summary:

----

**tl;dr**

* Rust's closures are syntax sugar for ``trait``
* default
    - closure environment on **stack** (borrow)
    - **static** dispatch
* return from function
    - closure environment on **heap** (use ``Box``)
    - use ``move`` to create own stack frame
* dynamic dispatch
    - use reference

.. code-block:: rust

    ////////////////////////////////////////

    // Syntax

    fn  plus_one_v1   (x: i32 ) -> i32 { x + 1 }    // function
    let plus_one_v2 = |x: i32 | -> i32 { x + 1 };   // closure
    let plus_one_v3 = |x: i32 |          x + 1  ;   // closure
    let plus_one_v4 = |x      |          x + 1  ;   // closure

    ////////////////////////////////////////

    // dynamic dispatch (reference)

    fn f(closure: &Fn(i32) -> i32) -> i32 {
        closure(1)
    }

    let answer = f(&|x| x + 2);

    ////////////////////////////////////////

    // return closure from function

    fn factory() -> Box<Fn(i32) -> i32> {
        let num = 5;
        Box::new(move |x| x + num)
    }

    let f = factory();

    ////////////////////////////////////////

----

等待的時間總是無聊，
只好打開電腦研究點東西。

今天在 Slack 上聊天時，
聊到了在 Python 可以利用 function 回傳 function 來做一些特別的事，
對於一個 Python 使用者來說這件事很常遇到 (又看看 decorator)，
這時突然就連結到 Rust，
Rust 裡面也可以定義 local function，
那是否可以像 Python 一樣回傳出去使用？

於是，來翻翻 Rust 的 closure 吧 ~

----

Rust 不只支援 named function，
還支援匿名函式，
當匿名函式裡有跟當時環境相關的變數時，
就稱為 closure，
以下就描述如何在 Rust 裡運用它。



Syntax
========================================

Rust 的 closure 是用兩個 ``|`` 把變數夾住，
後面接處理的 code，
可以用 ``{}`` 把多個處理包起來 (Rust 的 ``{}`` 是 expression)

.. code-block:: rust

    let plus_one = |x| x + 1;

    assert_eq!(2, plus_one(1));

    ////////////////////////////////////////

    let plus_two = |x| {
        let mut result: i32 = x;

        result += 1;
        result += 1;

        result
    };

    assert_eq!(4, plus_two(2));

    ////////////////////////////////////////

    let plus_one = |x: i32| -> i32 { x + 1 };

    assert_eq!(2, plus_one(1));

    ////////////////////////////////////////

    // compare

    fn  plus_one_v1   (x: i32 ) -> i32 { x + 1 }
    let plus_one_v2 = |x: i32 | -> i32 { x + 1 };
    let plus_one_v3 = |x: i32 |          x + 1  ;
    let plus_one_v4 = |x      |          x + 1  ;



這邊可以看到 Rust 的 closure 和一般 function 不同，
不需要寫明傳入和回傳的 type (但可以寫明)，
這設計是為了方便使用 (一般 function 要寫明是為了 documentation、type inference)。



Closure 和外部變數
========================================

先看一段範例 code：

.. code-block:: rust

    let num = 5;
    let plus_num = |x| x + num;

    assert_eq!(10, plus_num(5));

這邊的 closure 有用到一個不是參數的變數 ``num`` ，
他是靠外面的 ``num`` 來取得資料，
更明確來說這個 closure 裡的 num 借 (borrow) 了外面 num 的 binding。


如果在那之後又更動了 num 這個變數，
則會在 compile time 時出錯：

.. code-block:: rust

    let mut num = 5;
    let plus_num = |x: i32| x + num;

    // error
    num = num + 1;

    // error: cannot assign to `num` because it is borrowed
    //     num = num + 1;
    //     ^~~~~~~~~~~~~
    // note: borrow of `num` occurs here
    //     let plus_num = |x: i32| x + num;
    //                 ^~~~~~~~~~~~~~~~


但是可以用 ``{}`` 把借用的區域包起來，
這樣超出這段範圍後就會停止借用：

.. code-block:: rust

    let mut num = 5;

    {
        let plus_num = |x: i32| x + num;

    } // plus_num goes out of scope, borrow of num ends

    num = num + 1;


另外 Rust 的 closure 對於 non-copyable 的變數還會拿走 ownership、move 資源：

.. code-block:: rust

    let nums = vec![1, 2, 3];

    let takes_nums = || nums;

    println!("{:?}", nums);


    // error: use of moved value: `nums` [E0382]
    //     println!("{:?}", nums);
    //                     ^~~~
    // note: `nums` moved into closure environment here because it has type `collections::vec::Vec<i32>`, which is non-copyable
    //     let takes_nums = || nums;
    //                     ^~~~~~~



"move" closures
========================================

對於不會自動觸發 ownership 轉移的情況，
我們可以使用 ``move`` 來強制轉移
(注意的是這邊雖然叫 move，但是表示的是 closure 可以拿到 ownership，
不一定是 resourse 的 move，可能是 copy 一份)：

.. code-block:: rust

    let mut num = 5;

    {
        let mut add_num = |x: i32| num += x;

        // modify the original num
        add_num(5);
    }

    assert_eq!(10, num);

.. code-block:: rust

    let mut num = 5;

    {
        let mut add_num = move |x: i32| num += x;

        // modify a copy version of num
        add_num(5);
    }

    assert_eq!(5, num);


在沒有使用 ``move`` 的情況下，
closure 會綁在建立這 closure 的 stack frame 上，
``move`` closure 則是 self-contained 的，
這裡也可以發現要回傳一個 non-move closure 是不行的 (因為綁在 function stack frame 上，回傳後會被清掉)。



Closure implementation
========================================

Rust closure 的實作和其他語言有點不同，
Rust 的 closure 是 trait 的 syntax sugar

* `Rust Book - Traits <https://doc.rust-lang.org/book/traits.html>`_
* `Rust Book - Trait Objects <https://doc.rust-lang.org/book/trait-objects.html>`_


在 Rust 裡，用 ``()`` 來 call function 這件事是 overloadable 的，
我們可以用 trait 來 overload 這個 operator (有三種 trait 可以 overload)：

.. code-block:: rust

    pub trait Fn<Args> : FnMut<Args> {
        extern "rust-call" fn call(&self, args: Args) -> Self::Output;
    }

    pub trait FnMut<Args> : FnOnce<Args> {
        extern "rust-call" fn call_mut(&mut self, args: Args) -> Self::Output;
    }

    pub trait FnOnce<Args> {
        type Output;

        extern "rust-call" fn call_once(self, args: Args) -> Self::Output;
    }


三種不同的情況，讓我們可以有良好的掌控性：

.. table::
    :class: table table-bordered

    +--------+-----------+
    | trait  | self      |
    +========+===========+
    | Fn     | &self     |
    +--------+-----------+
    | FnMut  | &mut self |
    +--------+-----------+
    | FnOnce | self      |
    +--------+-----------+


``|| {}`` 則是這三種情況的 syntax suger，
Rust 會為 closure 的外部變數生出 struct，
``impl`` 需要的 trait，然後使用它。



closures as arguments
========================================

到這邊我們得知 Rust 的 closure 其實就是 trait，
所以如何傳入和回傳 closure 就跟 trait 一樣 (這也表示我們可以選擇 static 或 dynamic dispatch)。

.. code-block:: rust

    fn call_with_one<F>(some_closure: F) -> i32
        where F : Fn(i32) -> i32 {

        some_closure(1)
    }

    let answer = call_with_one(|x| x + 2);

    assert_eq!(3, answer);

這邊可以看到傳入的 type 為 ``Fn(i32) -> i32`` ，
Fn 就是個 trait，這邊寫明說會傳入 i32、回傳 i32，
這也就是我們 closure 需要的 type。

這邊一個重點是 Rust 的 closure 可以做 static dispatch，
在許多語言裡，closure 是 heap allocation 並且是 dynamic dispatch，
但是 Rust 可以做 stack allocation 和 static dispatch，
這很常被使用，尤其是在 iterator 那邊常常會傳入 closure 做篩選。

雖然 Rust 支援 static dispatch 的 closure，
但是想要使用 dynamic dispatch 還是可以的：

.. code-block:: rust

    fn call_with_one(some_closure: &Fn(i32) -> i32) -> i32 {
        some_closure(1)
    }

    let answer = call_with_one(&|x| x + 2);

    assert_eq!(3, answer);



returning closures
========================================

第一次失敗的嘗試：

.. code-block:: rust

    fn factory() -> (Fn(i32) -> Vec<i32>) {
        let vec = vec![1, 2, 3];

        |n| vec.push(n)
    }

    let f = factory();

    let answer = f(4);
    assert_eq!(vec![1, 2, 3, 4], answer);

    // error: the trait `core::marker::Sized` is not implemented for the type
    // `core::ops::Fn(i32) -> collections::vec::Vec<i32>` [E0277]
    //     f = factory();
    //     ^
    // note: `core::ops::Fn(i32) -> collections::vec::Vec<i32>` does not have a
    // constant size known at compile-time
    //     f = factory();
    //     ^
    // error: the trait `core::marker::Sized` is not implemented for the type
    // `core::ops::Fn(i32) -> collections::vec::Vec<i32>` [E0277]
    //     factory() -> (Fn(i32) -> Vec<i32>) {
    //                  ^~~~~~~~~~~~~~~~~~~~~
    // note: `core::ops::Fn(i32) -> collections::vec::Vec<i32>` does not have a constant size known at compile-time
    //     factory() -> (Fn(i32) -> Vec<i32>) {
    //                  ^~~~~~~~~~~~~~~~~~~~~

為了要從 function 回傳東西，Rust 需要知道 return type 的大小，
但是 ``Fn`` 是一個 trait，它可以包含各種東西、是各種大小，
各種不同的 type 可以實作 ``Fn`` ，
一個可以知道回傳大小的簡單方式就是用 reference (reference 的大小是已知的)

第二次失敗的嘗試：

.. code-block:: rust

    fn factory() -> &(Fn(i32) -> Vec<i32>) {
        let vec = vec![1, 2, 3];

        |n| vec.push(n)
    }

    let f = factory();

    let answer = f(4);
    assert_eq!(vec![1, 2, 3, 4], answer);

    // error: missing lifetime specifier [E0106]
    //     fn factory() -> &(Fn(i32) -> i32) {
    //                     ^~~~~~~~~~~~~~~~~

這次缺了 lifetime，我們用了 reference，
所以需要給個 lifetime，
這邊沒有參數，狀況很單純，使用 ``'static``

第三次失敗的嘗試：

.. code-block:: rust

    fn factory() -> &'static (Fn(i32) -> i32) {
        let num = 5;

        |x| x + num
    }

    let f = factory();

    let answer = f(1);
    assert_eq!(6, answer);


    // error: mismatched types:
    // expected `&'static core::ops::Fn(i32) -> i32`,
    //     found `[closure <anon>:7:9: 7:20]`
    // (expected &-ptr,
    //     found closure) [E0308]
    //         |x| x + num
    //         ^~~~~~~~~~~

compiler 說他拿到的 type 是 ``[closure <anon>:7:9: 7:20]`` ，
不是我們寫的 ``&'static Fn(i32) -> i32`` ，
這是因為每個 closure 都是依照當時的 environment ``struct`` 、 ``Fn`` 實作，
這些 type 都是 anonymous 的，所以 Rust 把它視為 ``closure <anon>`` 。
至於為何沒有實作 ``&'static Fn`` 則是因為 environment 是借來的，
而在這 case 中 environment 是 stack 上的變數，
所以 borrow 的 lifetime 等同於 stack frame 的 lifetime，
如果把 closure 回傳了，function stack frame 就會被清除，
closure 裡取到的就是不正確的值。

第四次失敗的嘗試：

.. code-block:: rust

    fn factory() -> Box<Fn(i32) -> i32> {
        let num = 5;

        Box::new(|x| x + num)
    }
    let f = factory();

    let answer = f(1);
    assert_eq!(6, answer);

    // error: `num` does not live long enough
    // Box::new(|x| x + num)
    //          ^~~~~~~~~~~

這次把 closure 丟到 heap 上了 (用 Box)，但是發現 num 還是取到 stack 上的值，
於是又再稍做修改。

成功：

.. code-block:: rust

    fn factory() -> Box<Fn(i32) -> i32> {
        let num = 5;

        Box::new(move |x| x + num)
    }
    let f = factory();

    let answer = f(1);
    assert_eq!(6, answer);

使用 ``move`` 來為 closure 建立新的 stack frame來儲存一份使用到的外部變數，
利用 ``Box`` 來把 closure 放到 heap 上，如此一來 size 變成已知，
離開原本建立的 stack frame 後也可以使用。

Reference
========================================

* `Rust Book - Closures <https://doc.rust-lang.org/book/closures.html>`_
