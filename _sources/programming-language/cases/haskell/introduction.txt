========================================
Haskell Introduction
========================================


.. contents:: 目錄


歷史發展
========================================


基本介紹
========================================

安裝
------------------------------

.. code-block:: sh

    $ sudo pacman -S ghc    # Glasgow Haskell Compiler

    # 安裝完後取得的指令
    $ pacman -Ql ghc | rg -N usr/bin/
    ghc /usr/bin/
    ghc /usr/bin/ghc
    ghc /usr/bin/ghc-8.0.1
    ghc /usr/bin/ghc-pkg
    ghc /usr/bin/ghc-pkg-8.0.1
    ghc /usr/bin/ghci
    ghc /usr/bin/ghci-8.0.1
    ghc /usr/bin/haddock
    ghc /usr/bin/haddock-ghc-8.0.1
    ghc /usr/bin/hp2ps
    ghc /usr/bin/hpc
    ghc /usr/bin/hsc2hs
    ghc /usr/bin/runghc
    ghc /usr/bin/runghc-8.0.1
    ghc /usr/bin/runhaskell


在安裝完後可以取得以下工具：

+------------+----------------------------------------------------------------------+
| 指令名稱   | 功能                                                                 |
+============+======================================================================+
| ghc        | Haskell 編譯器                                                       |
+------------+----------------------------------------------------------------------+
| ghci       | Haskell 互動式環境                                                   |
+------------+----------------------------------------------------------------------+
| haddock    | 文件產生器                                                           |
+------------+----------------------------------------------------------------------+
| hp2ps      | Heap Profile 轉 PostScript                                           |
+------------+----------------------------------------------------------------------+
| hpc        | Haskell Program Coverage                                             |
+------------+----------------------------------------------------------------------+
| hsc2hs     | 自動替 C 程式碼產生 Haskell 的 Binding                               |
+------------+----------------------------------------------------------------------+
| runghc     | 執行 Haskell 程式（不事先編譯）                                      |
+------------+----------------------------------------------------------------------+
| runhaskell | 系統 Haskell 直譯器的 Wrapper，便於切換編譯器（例如 GHC、Hugs、Jhc） |
+------------+----------------------------------------------------------------------+


基本 Haskell 撰寫
------------------------------

Haskell 的程式碼會以 ``.hs`` 作為副檔名，
對於任意一個 Haskell 程式（例如 ``mycode.hs`` ）而言，
在 ``ghci`` 互動式環境中可以使用 ``:l`` 進行讀取（例如 ``:l mycode`` ），
在更動過已讀取的程式碼後，
可以使用 ``:r`` 或再次使用原本的 ``:l mycode`` 來重新讀取。

.. code-block:: haskell

    $ ghci
    GHCi, version 8.0.1: http://www.haskell.org/ghc/  :? for help

     -- 更動 Prompt 的顯示
    Prelude> :set prompt "ghci> "

    -- 基本行為
    ghci> 2 + 15
    17
    ghci> 49 * 100
    4900
    ghci> 1892 - 1472
    420
    ghci> 5 / 2
    2.5
    ghci> (50 * 100) - 4999
    1
    ghci> 50 * 100 - 4999
    1
    ghci> 50 * (100 - 4999)
    -244950
    ghci> True && False
    False
    ghci> True && True
    True
    ghci> False || True
    True
    ghci> not False
    True
    ghci> not (True && True)
    False
    ghci> 5 == 5
    True
    ghci> 1 == 0
    False
    ghci> 5 /= 5
    False
    ghci> 5 /= 4
    True
    ghci> "hello" == "hello"
    True

    -- 不符合型別時的錯誤訊息
    ghci> 42 + "test"

        • No instance for (Num [Char]) arising from a use of ‘+’
        • In the expression: 42 + "test"
          In an equation for ‘it’: it = 42 + "test"

    -- 內建函式
    ghci> succ 8    -- 下一個
    9
    ghci> min 9 10  -- 兩個當中的最小值
    9
    ghci> min 9.1 10.1
    9.1

    -- 函式呼叫可以使用括弧包起來，像似 Lisp 的 S-expression
    ghci> succ 9 + max 5 4 + 1
    16
    ghci> (succ 9) + (max 5 4) + 1
    16

    -- 函式呼叫也可以使用 infix 的方式，但是要用「`」包起來
    ghci> div 10 9
    1
    ghci> 10 `div` 9
    1

    -- 定義函式
    ghci> doubleMe x = x + x
    ghci> doubleMe 9
    18

    -- if then else
    ghci> doubleSmallNumber x = if x > 100 then x else x*2
    ghci> doubleSmallNumber 10
    20
    ghci> doubleSmallNumber 120
    120

    -- 對於 Haskell 來說「'」也是一個函式名稱可接受的字元
    -- 習慣上（Convention）會以「'」結尾表示為沒有「'」結尾的函式的嚴格版或稍微改動的版本
    ghci> doubleSmallNumber' x = (if x > 100 then x else x*2) + 1
    ghci> doubleSmallNumber' 10
    21
    ghci> doubleSmallNumber' 120
    121

    -- list 內只能含有同樣型別的值
    -- 對於 Haskell 來說 "xxx" 只是 ['x', 'x', 'x'] 的語法糖
    -- 「++」為 Haskell 的串接操作
    ghci> let lostNumbers = [4,8,15,16,23,42]
    ghci> lostNumbers
    [4,8,15,16,23,42]
    ghci> [1, 2, 3, 4] ++ [9, 10, 11, 12]
    [1,2,3,4,9,10,11,12]
    ghci> "hello" ++ " " ++ "world"
    "hello world"
    ghci> ['w', 'o'] ++ ['o', 't']
    "woot"

    -- 「:」等同於 Lisp 中的 cons
    -- 而 [1, 2, 3] 其實是 1:2:3:[] 的語法糖
    ghci> 'A':" SMALL CAT"
    "A SMALL CAT"
    ghci> 5:[1,2,3,4,5]
    [5,1,2,3,4,5]

    -- 「!!」為 Haskell 內的 subscript operator
    -- Haskell 的 index 從 0 開始
    ghci> "Steve Buscemi" !! 6
    'B'
    ghci> [9.4,33.2,96.2,11.2,23.25] !! 1
    33.2

    -- Haskell 的 list 可以比較
    -- 比較時會依序拿出裡面的值來比，比到有結果就會停止
    ghci> [3,2,1] > [2,1,0]
    True
    ghci> [3,2,1] > [2,10,100]
    True
    ghci> [3,4,2] > [3,4]
    True
    ghci> [3,4,2] > [2,4]
    True
    ghci> [3,4,2] == [3,4,2]
    True

    -- head 等同於 Lisp 中的 car 或 first，可以取出第一個值
    ghci> head [5,4,3,2,1]
    5

    -- tail 等同於 Lisp 中的 cdr 或 rest，可以除了第一個值外的剩下的值
    ghci> tail [5,4,3,2,1]
    [4,3,2,1]


    -- last 可以取出最後一個值
    ghci> last [5,4,3,2,1]
    1

    -- init 可以取出除了最後一個值外的剩下的值
    ghci> init [5,4,3,2,1]
    [5,4,3,2]

    -- 剩下還有很多內建的函式，都很好理解
    ghci> length [5,4,3,2,1]
    5

    ghci> null [1,2,3]
    False
    ghci> null []
    True

    ghci> reverse [5,4,3,2,1]
    [1,2,3,4,5]

    ghci> take 3 [5,4,3,2,1]
    [5,4,3]
    ghci> take 1 [3,9,3]
    [3]
    ghci> take 5 [1,2]
    [1,2]
    ghci> take 0 [6,6,6]
    []

    ghci> drop 3 [8,4,2,1,5,6]
    [1,5,6]
    ghci> drop 0 [1,2,3,4]
    [1,2,3,4]
    ghci> drop 100 [1,2,3,4]
    []

    ghci> minimum [8,4,2,1,5,6]
    1
    ghci> maximum [1,9,2,3,4]
    9

    ghci> sum [5,2,1,6,3,2,5,7]
    31

    ghci> product [6,2,1,2]
    24
    ghci> product [1,2,5,6,7,9,2,0]
    0

    -- 確認該值是否存在於 list 中，等同於 Python 中的 in
    ghci> 4 `elem` [3,4,5,6]    -- 為了方便閱讀，通常使用 infix
    True
    ghci> 10 `elem` [3,4,5,6]
    False

    -- range
    ghci> [1..20]
    [1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20]
    ghci> ['a'..'z']
    "abcdefghijklmnopqrstuvwxyz"
    ghci> ['K'..'Z']
    "KLMNOPQRSTUVWXYZ"
    ghci> [2,4..20]         -- 給定前兩個值來指定每次增加的大小
    [2,4,6,8,10,12,14,16,18,20]
    ghci> [3,6..20]
    [3,6,9,12,15,18]
    ghci> [0.1, 0.3 .. 1]   -- 和浮點數一起使用時要小心
    [0.1,0.3,0.5,0.7,0.8999999999999999,1.0999999999999999]

    -- cycle
    ghci> take 10 (cycle [1,2,3])
    [1,2,3,1,2,3,1,2,3,1]
    ghci> take 12 (cycle "LOL ")
    "LOL LOL LOL "

    -- repeat
    ghci> take 10 (repeat 5)
    [5,5,5,5,5,5,5,5,5,5]

    -- list comprehension
    ghci> [x*2 | x <- [1..10]]
    [2,4,6,8,10,12,14,16,18,20]
    ghci> [x*2 | x <- [1..10], x*2 >= 12]   -- 後面可以加 Condition
    [12,14,16,18,20]
    ghci> [ x | x <- [50..100], x `mod` 7 == 3]
    [52,59,66,73,80,87,94]
    ghci> boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]
    ghci> boomBangs [7..13]
    ["BOOM!","BOOM!","BANG!","BANG!"]
    ghci> [ x | x <- [10..20], x /= 13, x /= 15, x /= 19]
    [10,11,12,14,16,17,18,20]
    ghci> [ x*y | x <- [2,5,10], y <- [8,10,11]]    -- 雙變數
    [16,20,22,40,50,55,80,100,110]
    ghci> [ x*y | x <- [2,5,10], y <- [8,10,11], x*y > 50]
    [55,80,100,110]
    ghci> length' xs = sum [1 | _ <- xs]    -- 利用 list comprehension 自製 length 函式
    ghci> length' [1, 2, 3]
    3
    ghci> let xxs = [[1,3,5,2,3,1,2,4,5],[1,2,3,4,5,6,7,8,9],[1,2,4,2,1,6,3,1,3,2,3,6]]
    ghci> [ [ x | x <- xs, even x ] | xs <- xxs]    -- 巢狀 list comprehension
    [[2,2,4],[2,4,6,8],[2,4,2,6,2,6]]

    -- tuple 可以放不同型別的資料
    ghci> (1, 2, 3)
    (1,2,3)
    ghci> (1, "a", 2, "b")

    -- fst 回傳 pair （只有兩個 elements 的 tuple）的第一個值
    ghci> fst (8,11)
    8
    ghci> fst ("Wow", False)
    "Wow"

    -- snd 回傳 pair 的第二個值
    ghci> snd (8,11)
    11
    ghci> snd ("Wow", False)
    False

    -- zip
    ghci> zip [1,2,3,4,5] [5,5,5,5,5]
    [(1,5),(2,5),(3,5),(4,5),(5,5)]
    ghci> zip [1 .. 5] ["one", "two", "three", "four", "five"]
    [(1,"one"),(2,"two"),(3,"three"),(4,"four"),(5,"five")]
    ghci> zip [5,3,2,6,2,7,2,5,4,6,6] ["im","a","turtle"]
    [(5,"im"),(3,"a"),(2,"turtle")]
    ghci> zip [1..] ["apple", "orange", "cherry", "mango"]
    [(1,"apple"),(2,"orange"),(3,"cherry"),(4,"mango")]

    -- 「:t」檢查型別
    ghci> :t 'a'
    'a' :: Char
    ghci> :t "a"
    "a" :: [Char]
    ghci> :t True
    True :: Bool
    ghci> :t (True, 'a')
    (True, 'a') :: (Bool, Char)
    ghci> :t 3 == 4
    3 == 4 :: Bool

    -- 型別宣告（要寫在檔案裡，不能直接在 ghci 內宣告）
    -- 型別 Int 為有界線的整數，通常為 32 bits 或 64 bits，32 bits 介於 [-2147483648, 2147483647]
    -- 型別 Integer 為沒有界線的整數，可以用來表示非常大的整數
    -- 型別 Float 為單精準的浮點數
    -- 型別 Double 為雙精準的浮點數
    -- 型別 Bool 為 Ture 或 False
    -- 型別 Char 為字元，裡面裝 Char 的 list 就是字串
    factorial :: Integer -> Integer
    factorial n = product [1..n]

    ghci> factorial 50
    30414093201713378043612608166064768844377641568960512000000000000

    ghci> :t head
    head :: [a] -> a
    ghci> :t fst
    fst :: (a, b) -> a

    -- Typeclass 是定義某些行為的界面，類似 Rust 的 Trait
    -- 以下列出常見的 Typeclass
    -- Eq，該型別的值可以比較是否相等
    ghci> :t (==)
    (==) :: (Eq a) => a -> a -> Bool    -- 在「=>」前的為 class constraint
    -- Ord，該型別的值可以比較大小，必須先有 Eq
    ghci> :t (>)
    (>) :: (Ord a) => a -> a -> Bool
    ghci> "Abrakadabra" < "Zebra"
    True
    ghci> "Abrakadabra" `compare` "Zebra"   -- compare 接收兩個 Ord 回傳 Ordering
    LT
    ghci> 5 `compare` 3
    GT
    ghci> 3 `compare` 3
    EQ
    -- Show，可以轉成字串，類似 Rust 的 std::string::ToString
    ghci> show 3
    "3"
    ghci> show 5.334
    "5.334"
    ghci> show True
    "True"
    -- Read，可以從字串轉換成特定型別，類似 Rust 的 std::str::FromStr
    ghci> :t read
    read :: (Read a) => String -> a
    ghci> read "True" || False
    True
    ghci> read "8.2" + 3.8
    12.0
    ghci> read "5" - 2
    3
    ghci> read "[1,2,3,4]" ++ [3]
    [1,2,3,4,3]
    ghci> read "5" :: Int   -- 在一些無法推導出型別的狀況下，需要指定型別
    5
    ghci> read "5" :: Float
    5.0
    ghci> (read "5" :: Float) * 4
    20.0
    ghci> read "[1,2,3,4]" :: [Int]
    [1,2,3,4]
    ghci> read "(3, 'a')" :: (Int, Char)
    (3, 'a')
    -- Enum，可以被 enumerated
    ghci> ['a'..'e']
    "abcde"
    ghci> [LT .. GT]
    [LT,EQ,GT]
    ghci> [3 .. 5]
    [3,4,5]
    ghci> succ 'B'
    'C'
    ghci> pred 'B'
    'A'
    -- Bounded，有上下界
    ghci> minBound :: Int
    -2147483648
    ghci> maxBound :: Char
    '\1114111'
    ghci> maxBound :: Bool
    True
    ghci> minBound :: Bool
    False
    ghci> maxBound :: (Bool, Int, Char)
    (True,9223372036854775807,'\1114111')
    -- Num，可以當作數值操作
    ghci> :t 20
    20 :: (Num t) => t
    ghci> 20 :: Int
    20
    ghci> 20 :: Integer
    20
    ghci> 20 :: Float
    20.0
    ghci> 20 :: Double
    20.0
    -- Integral，可以當作整數操作
    ghci> :t fromIntegral   -- fromIntegral 可以把 Integral 轉成 Num，以便後續和其他數值操作
    fromIntegral :: (Num b, Integral a) => a -> b
    ghci> fromIntegral (length [1,2,3,4]) + 3.2     -- 沒有使用 fromIntegral 的話會無法加起來
    -- Floating，可以當作浮點數操作

    -- Pattern Matching
    -- 注意有沒有包含到所有可能，不然可能在呼叫函式時沒有 match 到，造成錯誤
    sayMe :: (Integral a) => a -> String
    sayMe 1 = "One!"
    sayMe 2 = "Two!"
    sayMe 3 = "Three!"
    sayMe 4 = "Four!"
    sayMe 5 = "Five!"
    sayMe x = "Not between 1 and 5"     -- 先後順序很重要，General 的要放在後面

    ghci> sayMe 2
    "Two!"
    ghci> sayMe 10
    "Not between 1 and 5"

    factorial :: (Integral a) => a -> a
    factorial 0 = 1
    factorial n = n * factorial (n - 1)

    first :: (a, b, c) -> a
    first (x, _, _) = x
    second :: (a, b, c) -> b
    second (_, y, _) = y
    third :: (a, b, c) -> c
    third (_, _, z) = z

    -- 利用 Pattern Matching 製作 head 函式
    -- 有點像似在 Prolog 使用的撰寫方式
    head' :: [a] -> a
    head' [] = error "Can't call head on an empty list, dummy!"
    head' (x:_) = x     -- 要 bind 多個變數時，需要用括弧包起來

    tell :: (Show a) => [a] -> String
    tell [] = "The list is empty"
    tell (x:[]) = "The list has one element: " ++ show x
    tell (x:y:[]) = "The list has two elements: " ++ show x ++ " and " ++ show y
    tell (x:y:_) = "This list is long. The first two elements are: " ++ show x ++ " and " ++ show y

    length' :: (Num b) => [a] -> b
    length' [] = 0
    length' (_:xs) = 1 + length' xs

    -- 在使用 Pattern Matching 時，也能做額外的變數 binding
    -- 但是需要使用「@」
    -- 「名稱@(Pattern)」
    capital :: String -> String
    capital "" = "Empty string, whoops!"
    capital all@(x:xs) = "The first letter of " ++ all ++ " is " ++ [x]


Haskell Platform
------------------------------



參考
========================================

* `Brief History of Haskell <https://www.futurelearn.com/courses/functional-programming-haskell/1/steps/115453>`_
    1. 1930s, Alonzo Church's lambda calculus
    2. 1950s, LISP
    3. 1980s, ML, Hope, Miranda
    4. 1990, Haskell
    5. Glasgow Haskell Compiler, Haskell Platform
* [2007] `A History of Haskell: being lazy with class <https://research.microsoft.com/en-us/um/people/simonpj/papers/history-of-haskell/>`_
* `Haskell in the Datacentre <https://simonmar.github.io/posts/2016-12-08-Haskell-in-the-datacentre.html>`_
    - Facebook 針對 GHC runtime scheduler 的改進
* `Learn You a Haskell for Great Good! <http://learnyouahaskell.com/>`_
* `Haskell Implementaiton <https://wiki.haskell.org/Implementations>`_
