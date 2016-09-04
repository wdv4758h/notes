========================================
Macro
========================================


.. contents:: 目錄



介紹
========================================

基本觀念
------------------------------

syntactic programming language


使用方式
------------------------------

Rust 的 macros 使用就像 function 一樣，
但是結尾會多 ``!`` 表示其為 macros，
例如： ``mymacro!(mydata)``



我會其他語言
========================================

如果你會 C 或 C++
------------------------------

很抱歉，
這邊要討論的 macros 跟一般 C 或 C++ 在討論的不太一樣，
C 或 C++ 的 macros 會被分類為「Text-substitution macros」，
也就是說是以字串取代為基底架構成的。


如果你會 Lisp
------------------------------


如果你會 Python
------------------------------

很抱歉，
預設並沒有提供好專門的相關語法可以使用，
但是有相關的 Library （例如 `MacroPy <https://github.com/lihaoyi/macropy>`_ ）
可以達成類似的事情。


如果你會 Scheme
------------------------------


macros 歷史發展
========================================



``macro_rules`` macros
========================================

"macros by example"

``macro_rules!`` 讓程式設計師可以利用 Pattern Matching 來撰寫 syntactic macros，
以下是一個非常簡單的範例：

.. code-block:: rust

    macro_rules! hello {
        () => { println!("hello world"); }
    }

    fn main() {
        hello!();
    }

加上簡單的參數：

.. code-block:: rust

    macro_rules! hello {
        ($name: expr) => { println!("{}: hello world", $name); }
    }

    fn main() {
        hello!("Rust");     // Rust: hello world
        hello!(5566);       // 5566: hello world
    }


注意幾個地方：

* macros 的參數宣告和使用必須以 ``$`` 作為開頭，例如 ``$name``
* macros 的參數型別必須是以下幾種：
    - ident ： identifier
    - expr ： expression

.. code-block:: rust

    macro_rules! hello {
        (robot > $name: expr) => {
            println!("robot/{}: hello world", $name);
        };
        ($name: expr) => {
            println!("{}: hello world", $name);
        };
        ($var: ident, $name: expr) => {
            let $var = format!("{}: hello world", $name);
        };
    }

    fn main() {
        hello!("Rust");             // Rust: hello world
        hello!(5566);               // 5566: hello world
        hello!(x, "Rust");
        println!("{}", x);          // Rust: hello world
        hello!(robot > "Rust");     // robot/Rust: hello world
    }

* 注意 pattern 寫的順序，以免比較 general 的先被 match 到



macros 並不是處處都可以使用的，
對於 AST 來說要支援 macros 必須提供進入點，
例如 expression 會有 ``ExprMac`` 提供給 macros。

Macros 可以用於：

* expression
* statement
* item
* type
* pattern
* impl item

Macros 不能用於：

* trait item
* field


Macros 的使用可以搭配不同的括弧，
不同的括弧並不影響功能，
例如：

.. code-block:: rust

    macro_rules! hello {
        () => { println!("hello world"); }
    }

    fn main() {
        hello!();   // function-like
        hello![];   // array-like
        hello!{}    // item-like （可以不加「;」）
        hello!{};   // item-like
    }


Macros 還支援重複的 pattern，
例如 ``$(...)*`` 就會 match 到許多的 ``...`` 。
另外可以在外面加上分隔符號，
例如 ``$($x:expr),*`` 可以 match 到 ``a`` 或 ``a, b, c`` 等等，
而 ``$($x:expr),*`` 則會 match 到 ``a,`` 或 ``a, b, c,`` 等等。
除此之外可以使用 ``+`` 來取代 ``*`` 以限制至少要 match 一次。



procedural macros
========================================

「procedural macros」又被稱為「syntax extensions」或「syntax plugins」
或「compiler plugins」。

procedural macros 是使用純 Rust 在 meta level 實做，
和「macro by example」的語法不同。
因為轉換的結果可以是任何 AST 能表示的樣子，
所以這種 macros 非常強大。
但是要實做這種 macros 必須直接或間接使用到編譯器內部，
因此可能也容易有 breaking change。
雖然這部份還尚未 stable，
但是目前已經積極在改善中。

和 ``macro_rules`` macros 不同的地方在於，
procedural macro 的使用可以不限於前面提到的幾種，
例如：

* ``foo!(...)`` ，像 ``macro_rules`` 一樣，function-like
* ``foo! bar (...)`` ，像是 ``macro_rules`` 本身
* ``#[foo(...)]`` ，attribute-like

attribute-like 的 macros 會符合以下 grammar
（其中 ``lit`` 是 Rust literal，包含字串、數字）：

::

    attribute-like-macro ::= #[item] | #![item]
    item ::= name | name = lit | name(item,*)


要使用 procedural macros 必須使用 ``#![plugin(foo)]`` （拉相依套件，以便於編譯時使用），
而非 ``extern crate`` （拉相依套件，以便於執行時使用），
因為 procedural macros 還沒 stable，
所以還需要加上 ``#![feature(plugin)]`` 來允許。

稍微列表比對一下，拉相依套件：

* 編譯時期使用： ``#![plugin(foo)]``
* 執行時期使用： ``extern crate foo``


想要實做 procedural macros 其實代表著要實做 Rust trait，
實做可以寫成 function 或是用 ``expand`` method 來提供。
根據不同的需求，有數個不同的 trait 可以實做：

* ``MultiItemModifier`` ： attribute-like，更動附加到的 item
* ``MultiItemDecorator`` ： attribute-like，只會建立新 item
* ``TTMacroExpander`` ： function-like，接受一個 token tree
* ``IdentMacroExpander`` ： function-like，接受一個 ident 和一個 token tree
* ``MacroRulesTT`` ： 專門給 ``macro_rules`` 使用的，除此之外不應該實做它

（前面的 ``Multi`` prefix 是歷史遺留，需要被移除）

實做完後要註冊後編譯器才能使用，
要進行註冊我們需要一個 function，
該 function 必須接受一個 type 為 ``rustc::plugin::Registry`` 的參數，
並且具有 ``#[plugin_registrar]`` attribute。
在這 function 內我們會使用 ``register_syntax_extension`` 進行註冊，
並傳入 type 為 interned string 的 macro 名稱 ``::syntax::parse::token::intern("foo")`` ，
還有 ``SyntaxExtension`` enum 的 instance。
（以上這些會需要加上 ``#![feature(plugin_registrar)]`` 來開啟）


libmacro
========================================



built-in macros
========================================

* println!
* asm!
* #[cfg]
* #[derive()]



參考
========================================

Nick Cameron

* `Macros <http://www.ncameron.org/blog/macros/>`_
* `Macros in Rust pt1 <http://ncameron.org/blog/macros-in-rust-pt1/>`_
* `Macros in Rust pt2 <http://ncameron.org/blog/macros-in-rust-pt2/>`_
* `Macros in Rust pt3 <http://ncameron.org/blog/macros-in-rust-pt3/>`_
* `Macros in Rust pt4 <http://ncameron.org/blog/macros-in-rust-pt4/>`_
* `Macros in Rust pt5 <http://ncameron.org/blog/macros-in-rust-pt5/>`_
* `Macros pt6 - more issues <http://www.ncameron.org/blog/macros-pt6-more-issues/>`_
* `concat_idents! and macros in ident position <http://www.ncameron.org/blog/untitledconcat_idents-and-macros-in-ident-position/>`_
* `Macro hygiene in all its guises and variations <http://www.ncameron.org/blog/macro-hygiene-in-all-its-guises-and-variations/>`_
* `Sets of scopes macro hygiene <http://www.ncameron.org/blog/sets-of-scopes-macro-hygiene/>`_
* `Macro plans, overview <http://ncameron.org/blog/macro-plans-overview/>`_
* `Macro plans - syntax <http://ncameron.org/blog/macro-plans-syntax/>`_
* `Procedural macros, framework <http://ncameron.org/blog/procedural-macros-framework/>`_
* `Libmacro <http://ncameron.org/blog/libmacro/>`_
* `Macros and name resolution <http://www.ncameron.org/blog/name-resolution/>`_
* `Procedural macros by nrc · Pull Request #1566 · rust-lang/rfcs <https://github.com/rust-lang/rfcs/pull/1566>`_

* `rust/src/librustc_macro/ <https://github.com/rust-lang/rust/tree/master/src/librustc_macro>`_

* `Framework for procedural macroes in Rust <http://developers-club.com/posts/274225/>`_

* [2012] `Macros that Work Together <https://www.cs.utah.edu/plt/publications/jfp12-draft-fcdf.pdf>`_

* `Rust Books - Macros <https://doc.rust-lang.org/nightly/book/macros.html>`_
* `The Little Book of Rust Macros <https://danielkeep.github.io/tlborm/book/index.html>`_

* `Wikipedia - Hygienic macro <https://en.wikipedia.org/wiki/Hygienic_macro>`_
* `Wikipedia - Macro (computer science) <https://en.wikipedia.org/wiki/Macro_(computer_science)>`_
