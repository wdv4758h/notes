========================================
Type Theory
========================================

Dependent Type
========================================

[跑去問 Ole 得到的說明 XD]

程式語言有個性質叫做 Phase distinction，
不正式的來說就是 type （e.g. Int, String -> IO ()）與 term （e.g. 3, True）之間有明確的區別與界線
type 上面有自己的各種操作，term 上面也有自己的，
通常是井水不犯河水，兩邊是不同的世界不會混在一起或者有交互作用。

現在假設 type 與 term 之間有交互作用，這樣排列組合起來會有 4 種情形：

1. terms depending on types
2. terms depending on terms
3. types depending on types
4. types depending on terms

----

1. terms depending on types ： term 由 type 決定，也就是說當 type 不同時，會得到不同的 term 。在什麼情形下會這樣子呢？例如 ad hoc polymorphism ：
假設有個語言有兩種數字的型別 Int 與 Float ，都可以做加法，而這加法底下實作起來的方式其實不一樣，但我們還是想用同一個 operator _+_ 去做這件事情。這時候就是 type （ Int , Float）去決定 term （ Int 的加法, Float 的加法）
2. terms depending on terms ： 由 term 決定 term ，就隨便一個你想得到的普通函數
3. types depending on types ： 由 type 決定 type ，跟上面那條類似，只不過這次這函數是作用在 type 的層級上。例如 Haskell 的 _->_ ，讓你可以把兩個 type A, B 組成一個新的 type A -> B
4.  types depending on terms ： 由 term 決定 type ，這就是 dependent type 特別的地方了，例子待會舉

----

在幾乎所有語言，有 Phase distinction 的情形下，type 與 term 是分開的，就像天與地。
但是當 term 能決定 type 時，phase distinction 就模糊掉了。
type 與 term 變成一種相對關係，term 上面有 type ， type 上面有更高層的 type ，可以無限一直疊上去
我們把第一層 type 叫做 Set₀ （或直接簡稱 Set），更上一層叫 Set₁，再上一層叫 Set₂ …..

在有 phase distinction 的語言，term 與 type 上面有各自的操作，通常有不同的語法。
但當現在你有無限層 type 的時候，總不能每一層都弄一種新語法，所以在 dependent type 語言裡， term 跟所有層的 type 都用同一套語言去操作他們，沒有區別。啊所以說那麼多 term 跟 type 混在一起到底是能幹嘛？

一些例子：

* 你的 type 現在可以超級精確： Vec ℕ 3 : 所有長度為 3 裡面裝 ℕ 的 list
* 無限的抽象化空間：現在唯一的限制是你的智商
* 讓電腦幫你寫程式：常常當 type 變精確時， term 的範圍會縮小並且會有許多限制去提示他應該長什麼樣子，這時候常常電腦都可以幫你猜出程式來
* 我臨時想不到幹來寫就對了啦

----

C++ STL 或是 Rust 裡的 Vector 就是個例子，
我定 vector 的時候長的是 ``Vec<T>`` ，
之後用的時候丟入我要的 type (好比 ``Vec<int>``)，
只不過 C++ 或 Rust 的 vector ，都是作用在同一層上 ``Vec<_> : Set₀ → Set₀`` ，
像例子的 ``Vec : Set₀ → ℕ → Set₀`` 有把下面一層 (ℕ 的 term) 的東西提上來所以有 dependent type

.. code-block:: agda

    module Test where

    -- definition of natural number ℕ
    data ℕ : Set where  -- ℕ is a Set₀
        zero : ℕ        -- zero is a ℕ
        suc : ℕ → ℕ     -- if `n` is a ℕ, then `suc n` is also a ℕ

    one : ℕ
    one = suc zero

    二 : ℕ
    二 = suc (suc zero)

    data List (A : Set) : Set where     -- if `A` is a `Set₀`, then `List A` is a `Set₀`
        [] : List A                         -- `[]` is a `List A`
        _∷_ : (a : A) → List A → List A     -- if `a` is a `A`, and `xs` is a `List A`, then `a ∷ xs` is a `List A`

    空的 : List ℕ
    空的 = []

    長一點der : List ℕ
    長一點der = one ∷ (二 ∷ (suc zero ∷ []))

    data Vec (A : Set) : ℕ → Set where
        [] : Vec A zero
        _∷_ : {n : ℕ} → (a : A) → Vec A n → Vec A (suc n)

    長度是3 : Vec ℕ (suc (suc (suc zero)))
    長度是3 = zero ∷ (zero ∷ (zero ∷ []))
    -- 不用給長度 3，因為自動推得出來，所以第 26 行宣告時故意用 {n : ℕ} ，還可以縮寫成 ∀ {n}


Reference
========================================

* `Wikipedia - Lambda cube <https://en.wikipedia.org/wiki/Lambda_cube>`_
* `Wikipedia - Dependent type <https://en.wikipedia.org/wiki/Dependent_type>`_
