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

    -- Guard，用於檢驗某些性質是 True 還是 False，用「|」區隔，參數定義後不需要「=」
    -- 有點像是 Rust 中的 match
    bmiTell :: (RealFloat a) => a -> String
    bmiTell bmi
        | bmi <= 18.5 = "You're underweight."
        | bmi <= 25.0 = "You're supposedly normal."
        | bmi <= 30.0 = "You're fat."
        | otherwise   = "You're a whale, congratulations!"

    max' :: (Ord a) => a -> a -> a
    max' a b | a > b = a | otherwise = b

    myCompare :: (Ord a) => a -> a -> Ordering
    a `myCompare` b     -- 定義函式時也可以使用 infix
        | a > b     = GT
        | a == b    = EQ
        | otherwise = LT

    -- where，可以把重複的操作替換成變數，在 Guards 最後面使用「where」指定
    bmiTell :: (RealFloat a) => a -> a -> String
    bmiTell weight height
        | bmi <= 18.5 = "You're underweight."
        | bmi <= 25.0 = "You're supposedly normal."
        | bmi <= 30.0 = "You're fat."
        | otherwise   = "You're a whale, congratulations!"
        where bmi = weight / height ^ 2

    bmiTell :: (RealFloat a) => a -> a -> String
    bmiTell weight height
        | bmi <= skinny = "You're underweight."
        | bmi <= normal = "You're supposedly normal."
        | bmi <= fat    = "You're fat."
        | otherwise   = "You're a whale, congratulations!"
        where bmi = weight / height ^ 2
              skinny = 18.5
              normal = 25.0
              fat = 30.0

    -- where 內也可以使用 Pattern Matching
    bmiTell :: (RealFloat a) => a -> a -> String
    bmiTell weight height
        | bmi <= skinny = "You're underweight."
        | bmi <= normal = "You're supposedly normal."
        | bmi <= fat    = "You're fat."
        | otherwise   = "You're a whale, congratulations!"
    where bmi = weight / height ^ 2
          (skinny, normal, fat) = (18.5, 25.0, 30.0)

    initials :: String -> String -> String
    initials firstname lastname = [f] ++ ". " ++ [l] ++ "."
        where (f:_) = firstname
              (l:_) = lastname

    -- where 內還可以定義函式
    calcBmis :: (RealFloat a) => [(a, a)] -> [a]
    calcBmis xs = [bmi w h | (w, h) <- xs]
        where bmi weight height = weight / height ^ 2   -- 定義 bmi 函式

    -- Let Binding
    -- 「let <bindings> in <expression>」
    -- 在 list comprehension 中使用時，可以省略 in，因為 scope 是已知的
    cylinder :: (RealFloat a) => a -> a -> a
    cylinder r h =
        let sideArea = 2 * pi * r * h
            topArea = pi * r ^2
        in  sideArea + 2 * topArea

    ghci> 4 * (let a = 9 in a + 1) + 2
    42
    ghci> [let square x = x * x in (square 5, square 3, square 2)]
    [(25,9,4)]
    ghci> (let a = 100; b = 200; c = 300 in a*b*c, let foo="Hey "; bar = "there!" in foo ++ bar)
    (6000000,"Hey there!")
    ghci> (let (a,b,c) = (1,2,3) in a+b+c) * 100    -- with Pattern Matching
    600

    calcBmis :: (RealFloat a) => [(a, a)] -> [a]
    calcBmis xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2]

    calcBmis :: (RealFloat a) => [(a, a)] -> [a]
    calcBmis xs = [bmi | (w, h) <- xs, let bmi = w / h ^ 2, bmi >= 25.0]

    ghci> let zoot x y z = x * y + z    -- 省略 in，scope 為整個 GHCi Session
    ghci> zoot 3 9 2
    29

    ghci> let boot x y z = x * y + z in boot 3 4 2  -- 沒有省略 in，scope 為後面的 expression
    14
    ghci> boot
    <interactive>:1:0: Not in scope: `boot'

    -- case
    -- Rust 中的 Match
    head' :: [a] -> a
    head' xs = case xs of [] -> error "No head for empty lists!"
                          (x:_) -> x

    -- 在函式定義時，Pattern Matching 是 case expression 的語法糖
    describeList :: [a] -> String
    describeList xs = "The list is " ++ case xs of [] -> "empty."
                                                   [x] -> "a singleton list."
                                                   xs -> "a longer list."

    describeList :: [a] -> String
    describeList xs = "The list is " ++ what xs
        where what [] = "empty."
              what [x] = "a singleton list."
              what xs = "a longer list."

    --
    -- Recursion
    --

    maximum' :: (Ord a) => [a] -> a
    maximum' [] = error "maximum of empty list"
    maximum' [x] = x
    maximum' (x:xs) = max x (maximum' xs)

    replicate' :: (Num i, Ord i) => i -> a -> [a]
    replicate' n x
        | n <= 0    = []
        | otherwise = x:replicate' (n-1) x


    take' :: (Num i, Ord i) => i -> [a] -> [a]
    take' n _
        | n <= 0   = []
    take' _ []     = []
    take' n (x:xs) = x : take' (n-1) xs

    reverse' :: [a] -> [a]
    reverse' [] = []
    reverse' (x:xs) = reverse' xs ++ [x]

    zip' :: [a] -> [b] -> [(a,b)]
    zip' _ [] = []
    zip' [] _ = []
    zip' (x:xs) (y:ys) = (x,y):zip' xs ys

    elem' :: (Eq a) => a -> [a] -> Bool
    elem' a [] = False
    elem' a (x:xs)
        | a == x    = True
        | otherwise = a `elem'` xs

    quicksort :: (Ord a) => [a] -> [a]
    quicksort [] = []
    quicksort (x:xs) =
        let smallerSorted = quicksort [a | a <- xs, a <= x]
            biggerSorted = quicksort [a | a <- xs, a > x]
        in  smallerSorted ++ [x] ++ biggerSorted

    --
    -- Higher Order Functions
    --

    -- Curried Functions
    -- 所有 Haskell 函式其實都只能接收一個參數，
    -- 可以接收多個參數的其實是 Curried Functions

    ghci> max 4 5
    5
    ghci> (max 4) 5
    5
    ghci> :t max
    max :: Ord a => a -> a -> a     -- 可以解讀為 a -> (a -> a)
    ghci> :t max 4  -- partially applied function
    max 4 :: (Ord a, Num a) => a -> a
    ghci> :t max 4 5
    max 4 5 :: (Ord a, Num a) => a

    -- 指定一定要接收 Function

    applyTwice :: (a -> a) -> a -> a    -- 用括弧包起來
    applyTwice f x = f (f x)

    ghci> applyTwice (+3) 10
    16
    ghci> applyTwice (++ " HAHA") "HEY"
    "HEY HAHA HAHA"
    ghci> applyTwice ("HAHA " ++) "HEY"
    "HAHA HAHA HEY"
    ghci> applyTwice (multThree 2 2) 9
    144
    ghci> applyTwice (3:) [1]
    [3,3,1]

    zipWith' :: (a -> b -> c) -> [a] -> [b] -> [c]
    zipWith' _ [] _ = []
    zipWith' _ _ [] = []
    zipWith' f (x:xs) (y:ys) = f x y : zipWith' f xs ys

    ghci> zipWith' (+) [4,2,5,6] [2,6,2,3]
    [6,8,7,9]
    ghci> zipWith' max [6,3,2,1] [7,3,1,5]
    [7,3,2,5]
    ghci> zipWith' (++) ["foo ", "bar ", "baz "] ["fighters", "hoppers", "aldrin"]
    ["foo fighters","bar hoppers","baz aldrin"]
    ghci> zipWith' (*) (replicate 5 2) [1..]
    [2,4,6,8,10]
    ghci> zipWith' (zipWith' (*)) [[1,2,3],[3,5,6],[2,3,4]] [[3,2,2],[3,4,5],[5,4,3]]
    [[3,4,6],[9,20,30],[10,12,12]]

    -- map

    map :: (a -> b) -> [a] -> [b]
    map _ [] = []
    map f (x:xs) = f x : map f xs

    ghci> map (+3) [1,5,3,1,6]
    [4,8,6,4,9]
    ghci> map (++ "!") ["BIFF", "BANG", "POW"]
    ["BIFF!","BANG!","POW!"]
    ghci> map (replicate 3) [3..6]
    [[3,3,3],[4,4,4],[5,5,5],[6,6,6]]
    ghci> map (map (^2)) [[1,2],[3,4,5,6],[7,8]]
    [[1,4],[9,16,25,36],[49,64]]
    ghci> map fst [(1,2),(3,5),(6,3),(2,6),(2,5)]
    [1,3,6,2,2]

    -- filter

    filter :: (a -> Bool) -> [a] -> [a]
    filter _ [] = []
    filter p (x:xs)
        | p x       = x : filter p xs
        | otherwise = filter p xs

    ghci> filter (>3) [1,5,3,2,1,6,4,3,2,1]
    [5,6,4]
    ghci> filter (==3) [1,2,3,4,5]
    [3]
    ghci> filter even [1..10]
    [2,4,6,8,10]
    ghci> let notNull x = not (null x) in filter notNull [[1,2,3],[],[3,4,5],[2,2],[],[],[]]
    [[1,2,3],[3,4,5],[2,2]]
    ghci> filter (`elem` ['a'..'z']) "u LaUgH aT mE BeCaUsE I aM diFfeRent"
    "uagameasadifeent"
    ghci> filter (`elem` ['A'..'Z']) "i lauGh At You BecAuse u r aLL the Same"
    "GAYBALLS"

    quicksort :: (Ord a) => [a] -> [a]
    quicksort [] = []
    quicksort (x:xs) =
        let smallerSorted = quicksort (filter (<=x) xs)
            biggerSorted = quicksort (filter (>x) xs)
        in  smallerSorted ++ [x] ++ biggerSorted

    -- takeWhile

    ghci> sum (takeWhile (<10000) (filter odd (map (^2) [1..])))
    166650
    ghci> sum (takeWhile (<10000) [n^2 | n <- [1..], odd (n^2)])
    166650

    -- Lambda
    -- Haskell 中要撰寫匿名函式要使用「\」作為開頭
    -- 並且我們通常會把匿名函式用括弧包起來，避免一路展開到後面
    -- (\NAME PARAMETERS -> FUNCTION_BODY)

    ghci> map (\xs -> replicate 3 xs) [1..5])
    [[1,1,1],[2,2,2],[3,3,3],[4,4,4],[5,5,5]]
    ghci> zipWith (\a b -> (a * 30 + 3) / b) [5,4,3,2,1] [1,2,3,4,5]
    [153.0,61.5,31.0,15.75,6.6]
    ghci> map (\(a,b) -> a + b) [(1,2),(3,5),(6,3),(2,6),(2,5)]
    [3,8,9,8,7]

    addThree :: (Num a) => a -> a -> a -> a
    addThree = \x -> \y -> \z -> x + y + z      -- 不使用括弧把匿名函式包住

    flip' :: (a -> b -> c) -> b -> a -> c
    flip' f = \x y -> f y x

    -- foldl (left fold)

    sum' :: (Num a) => [a] -> a
    sum' xs = foldl (\acc x -> acc + x) 0 xs

    ghci> sum' [3,5,2,1]
    11

    -- foldr (right fold)

    map' :: (a -> b) -> [a] -> [b]
    map' f xs = foldr (\x acc -> f x : acc) [] xs

    -- foldl1
    -- foldr1
    -- 和 foldl、foldr 類似，但不用給起始值，會使用第一個 element 作為起始值

    maximum' :: (Ord a) => [a] -> a
    maximum' = foldr1 (\x acc -> if x > acc then x else acc)

    reverse' :: [a] -> [a]
    reverse' = foldl (\acc x -> x : acc) []

    product' :: (Num a) => [a] -> a
    product' = foldr1 (*)

    filter' :: (a -> Bool) -> [a] -> [a]
    filter' p = foldr (\x acc -> if p x then x : acc else acc) []

    head' :: [a] -> a
    head' = foldr1 (\x _ -> x)

    last' :: [a] -> a
    last' = foldl1 (\_ x -> x)

    -- scanl
    -- scanr
    -- 和 foldl、foldr 類似，但回傳一個 list 包含所有中間值

    ghci> scanl (+) 0 [3,5,2,1]
    [0,3,8,10,11]
    ghci> scanr (+) 0 [3,5,2,1]
    [11,8,3,1,0]
    ghci> scanl1 (\acc x -> if x > acc then x else acc) [3,4,5,3,7,9,2,1]
    [3,4,5,5,7,9,9,9]
    ghci> scanl (flip (:)) [] [3,2,1]
    [[],[3],[2,3],[1,2,3]]

    -- $ Function Application
    -- 「$」具有最低的優先權，且為 right-associative
    -- 使用「 」作為 Function Applicatoin，「f a b c」等同於「((f a) b) c)」，為 left-associative
    -- 使用「$」作為 Function Applicatoin，「f $ a $ b c」等同於「(f (a (b c)))」，為 right-associative
    -- 「$」可以用來減少括弧

    ($) :: (a -> b) -> a -> b
    f $ x = f x

    ghci> sum (map sqrt [1..130])
    993.6486803921487
    ghci> sum $ map sqrt [1..130]
    993.6486803921487

    ghci> sqrt (3 + 4 + 9)
    4.0
    ghci> sqrt $ 3 + 4 + 9
    4.0

    ghci> map ($ 3) [(4+), (10*), (^2), sqrt]
    [7.0,30.0,9.0,1.7320508075688772]
    ghci> map (\f -> f 3) [(4+), (10*), (^2), sqrt]
    [7.0,30.0,9.0,1.7320508075688772]

    -- Function Composition

    (.) :: (b -> c) -> (a -> b) -> a -> c
    f . g = \x -> f (g x)

    ghci> map (\x -> negate (abs x)) [5,-3,-6,7,-3,2,-19,24]
    [-5,-3,-6,-7,-3,-2,-19,-24]
    ghci> map (negate . abs) [5,-3,-6,7,-3,2,-19,24]    -- 比較簡短且容易理解
    [-5,-3,-6,-7,-3,-2,-19,-24]

    ghci> map (\xs -> negate (sum (tail xs))) [[1..5],[3..6],[1..7]]
    [-14,-15,-27]
    ghci> map (negate . sum . tail) [[1..5],[3..6],[1..7]]
    [-14,-15,-27]

    oddSquareSum :: Integer     -- version 1
    oddSquareSum = sum (takeWhile (<10000) (filter odd (map (^2) [1..])))
    oddSquareSum :: Integer     -- version 2, with function composition
    oddSquareSum = sum . takeWhile (<10000) . filter odd . map (^2) $ [1..]
    oddSquareSum :: Integer     -- version 3, more readable
    oddSquareSum =
        let oddSquares = filter odd $ map (^2) [1..]
            belowLimit = takeWhile (<10000) oddSquares
        in  sum belowLimit


    --
    -- Modules
    --

    -- 前面我們呼叫和使用的函式、型別、Typeclasses 都是在「Prelude」module 內

    ghci> import Data.List          -- 預設會把裡面的功能直接拉到現在的全域中
    ghci> nub ([1..5] ++ [3..10])   -- Data.List 內的 nub 會把重複的 element 去除
    [1,2,3,4,5,6,7,8,9,10]

    ghci> :m + Data.List            -- 在 GHCi 中也可以使用 :m 來新增要使用的 module
    ghci> :m + Data.List Data.Map Data.Set

    ghci> import Data.List (nub, sort)  -- 只拉入特定的函式
    ghci> import Data.List hiding (nub) -- 拉入所有的東西，除了指定的函式不要拉進來
    ghci> import qualified Data.Map     -- 保留 module scope，要使用 Data.Map.xxx 來呼叫
    ghci> import qualified Data.Map as M    -- 重新命名

    -- Data.List

    -- intersperse，在每個 element 間加上特定資料

    ghci> intersperse '.' "MONKEY"
    "M.O.N.K.E.Y"
    ghci> intersperse 0 [1,2,3,4,5,6]
    [1,0,2,0,3,0,4,0,5,0,6]

    -- intercalate，在每個 element 間加上特定資料後，把資料展平

    ghci> intercalate " " ["hey","there","guys"]
    "hey there guys"
    ghci> intercalate [0,0,0] [[1,2,3],[4,5,6],[7,8,9]]
    [1,2,3,0,0,0,4,5,6,0,0,0,7,8,9]

    -- transpose，轉置

    ghci> transpose [[1,2,3],[4,5,6],[7,8,9]]
    [[1,4,7],[2,5,8],[3,6,9]]
    ghci> transpose ["hey","there","guys"]
    ["htg","ehu","yey","rs","e"]

    -- foldl'
    -- foldl1'
    -- 為 foldl 和 foldl1 的嚴格版本，如果在使用 lazy 版時遇到 Stack Overflow
    -- 可以改用此版本

    -- concat，把巢狀 list 展平成一層 list

    ghci> concat ["foo","bar","car"]
    "foobarcar"
    ghci> concat [[3,4,5],[2,3,4],[2,1,1]]
    [3,4,5,2,3,4,2,1,1]

    -- concatMap，map 後 concat

    ghci> concatMap (replicate 4) [1..3]
    [1,1,1,1,2,2,2,2,3,3,3,3]

    -- and，所有 list 內的值都為 True 時才回傳 True，等同 Python 內的 all

    ghci> and $ map (>4) [5,6,7,8]
    True
    ghci> and $ map (==4) [4,4,4,3,4]
    False

    -- or，list 內任意值為 True 時就回傳 True，等同 Python 的的 any

    ghci> or $ map (==4) [2,3,4,5,6,1]
    True
    ghci> or $ map (>4) [1,2,3]
    False

    -- any
    -- all
    -- map 後接 or 或是 and

    ghci> any (==4) [2,3,5,6,1,4]
    True
    ghci> all (>4) [6,9,10]
    True
    ghci> all (`elem` ['A'..'Z']) "HEYGUYSwhatsup"
    False
    ghci> any (`elem` ['A'..'Z']) "HEYGUYSwhatsup"
    True

    -- iterate，不斷地把值丟入函式內，製造 list
    -- [init, f(init), f(f(init)), ...]

    ghci> take 10 $ iterate (*2) 1
    [1,2,4,8,16,32,64,128,256,512]
    ghci> take 3 $ iterate (++ "haha") "haha"
    ["haha","hahahaha","hahahahahaha"]

    -- splitAt，在第 N 個 element 切割

    ghci> splitAt 3 "heyman"
    ("hey","man")
    ghci> splitAt 100 "heyman"
    ("heyman","")
    ghci> splitAt (-3) "heyman"
    ("","heyman")
    ghci> let (a,b) = splitAt 3 "foobar" in b ++ a
    "barfoo"

    -- takeWhile，取出符合條件的值，直到第一次 False 時停止

    ghci> takeWhile (>3) [6,5,4,3,2,1,2,3,4,5,4,3,2,1]
    [6,5,4]
    ghci> takeWhile (/=' ') "This is a sentence"
    "This"

    -- dropWhile，略過符合條件的值，直到第一次 False 時停止

    ghci> dropWhile (/=' ') "This is a sentence"
    " is a sentence"
    ghci> dropWhile (<3) [1,2,2,2,3,4,5,4,3,2,1]
    [3,4,5,4,3,2,1]

    -- span，類似 takeWhile，但是會回傳一個 pair 內含兩個 list，
    -- 第一個 list 為會被 takeWhile 回傳的部份，第二個為會被丟棄的部份

    ghci> break (==4) [1,2,3,4,5,6,7]
    ([1,2,3],[4,5,6,7])
    ghci> span (/=4) [1,2,3,4,5,6,7]
    ([1,2,3],[4,5,6,7])

    -- sort

    ghci> sort [8,5,3,2,1,6,4,2]
    [1,2,2,3,4,5,6,8]
    ghci> sort "This will be sorted soon"
    "    Tbdeehiillnooorssstw"

    -- group，把相連一樣的值放到同個 list 內

    ghci> group [1,1,1,1,2,2,2,2,3,3,2,2,2,5,6,7]
    [[1,1,1,1],[2,2,2,2],[3,3],[2,2,2],[5],[6],[7]]
    ghci> group [1,1,2,1,1,2,2,2,2,3,3,2,2,2,5,6,7]
    [[1,1],[2],[1,1],[2,2,2,2],[3,3],[2,2,2],[5],[6],[7]]
    ghci> map (\l@(x:xs) -> (x,length l)) . group . sort $ [1,1,1,1,2,2,2,2,3,3,2,2,2,5,6,7]
    [(1,4),(2,7),(3,2),(5,1),(6,1),(7,1)]

    -- inits
    -- tails
    -- 不斷地套用 init 或 tail，直到沒有值

    ghci> inits "w00t"
    ["","w","w0","w00","w00t"]
    ghci> tails "w00t"
    ["w00t","00t","0t","t",""]
    ghci> let w = "w00t" in zip (inits w) (tails w)
    [("","w00t"),("w","00t"),("w0","0t"),("w00","t"),("w00t","")]

    -- isInfixOf，是否為子字串

    ghci> "cat" `isInfixOf` "im a cat burglar"
    True
    ghci> "Cat" `isInfixOf` "im a cat burglar"
    False
    ghci> "cats" `isInfixOf` "im a cat burglar"
    False

    -- isPrefixOf，是否為前綴
    -- isSuffixOf，是否為後綴

    ghci> "hey" `isPrefixOf` "hey there!"
    True
    ghci> "hey" `isPrefixOf` "oh hey there!"
    False
    ghci> "there!" `isSuffixOf` "oh hey there!"
    True
    ghci> "there!" `isSuffixOf` "oh hey there"
    False

    -- elem
    -- notElem
    -- 是否存在於 list 中

    -- partition，分割

    ghci> partition (`elem` ['A'..'Z']) "BOBsidneyMORGANeddy"   -- partition 會完整分割
    ("BOBMORGAN","sidneyeddy")
    ghci> partition (>3) [1,3,5,6,3,2,1,0,3,7]
    ([5,6,7],[1,3,3,2,1,0,3])

    ghci> span (`elem` ['A'..'Z']) "BOBsidneyMORGANeddy"        -- span 只到第一次 False
    ("BOB","sidneyMORGANeddy")

    -- find，回傳第一個符合條件的值，值會用 Maybe 包起來，若沒有找到就是 Nothing
    -- 類似 Rust 的 Option

    ghci> find (>4) [1,2,3,4,5,6]
    Just 5
    ghci> find (>9) [1,2,3,4,5,6]
    Nothing
    ghci> :t find
    find :: (a -> Bool) -> [a] -> Maybe a

    -- elemIndex，回傳第一個找的值的 index

    ghci> :t elemIndex
    elemIndex :: (Eq a) => a -> [a] -> Maybe Int
    ghci> 4 `elemIndex` [1,2,3,4,5,6]
    Just 3
    ghci> 10 `elemIndex` [1,2,3,4,5,6]
    Nothing

    -- elemIndices，找出所有 index

    ghci> ' ' `elemIndices` "Where are the spaces?"
    [5,9,13]

    -- findIndex
    -- findIndices

    ghci> findIndex (==4) [5,3,2,1,6,4]
    Just 5
    ghci> findIndex (==7) [5,3,2,1,6,4]
    Nothing
    ghci> findIndices (`elem` ['A'..'Z']) "Where Are The Caps?"
    [0,6,10,14]

    -- zip3, zip4
    -- zipWith3, zipWith4

    ghci> zipWith3 (\x y z -> x + y + z) [1,2,3] [4,5,2,2] [2,2,3]
    [7,9,8]
    ghci> zip4 [2,3,3] [2,2,2] [5,5,3] [2,2,2]
    [(2,2,5,2),(3,2,5,2),(3,2,3,2)]

    -- lines

    ghci> lines "first line\nsecond line\nthird line"
    ["first line","second line","third line"]

    -- unlines

    ghci> unlines ["first line", "second line", "third line"]
    "first line\nsecond line\nthird line\n"

    -- words
    -- unwords

    ghci> words "hey these are the words in this sentence"
    ["hey","these","are","the","words","in","this","sentence"]
    ghci> words "hey these           are    the words in this\nsentence"
    ["hey","these","are","the","words","in","this","sentence"]
    ghci> unwords ["hey","there","mate"]
    "hey there mate"

    -- nub

    ghci> nub [1,2,3,4,3,2,1,2,3,4,3,2,1]
    [1,2,3,4]
    ghci> nub "Lots of words and stuff"
    "Lots fwrdanu"

    -- delete

    ghci> delete 'h' "hey there ghang!"
    "ey there ghang!"
    ghci> delete 'h' . delete 'h' $ "hey there ghang!"
    "ey tere ghang!"
    ghci> delete 'h' . delete 'h' . delete 'h' $ "hey there ghang!"
    "ey tere gang!"

    -- \\，diff

    ghci> [1..10] \\ [2,5,9]
    [1,3,4,6,7,8,10]
    ghci> "Im a big baby" \\ "big"
    "Im a  baby"

    -- union

    ghci> "hey man" `union` "man what's up"
    "hey manwt'sup"
    ghci> [1..7] `union` [5..10]
    [1,2,3,4,5,6,7,8,9,10]




    -- TODO: http://learnyouahaskell.com/modules



Stack
========================================

Stack 是 Haskell 的專案開發工具，
可以為特定專案安裝特定版本的 GHC，
安裝相依套件，
對專案編譯、測試、效能測量，
感覺像 Rust 的 Cargo。

安裝
------------------------------

.. code-block:: sh

    $ curl -sSL https://get.haskellstack.org/ | sh
    # 或是
    $ wget -qO- https://get.haskellstack.org/ | sh


基本使用
------------------------------

.. code-block:: sh

    $ stack new myproj

    $ stack build



Haskell Platform
========================================

Software Transactional Memory
========================================




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
* `Replacing GHCi's pretty-printer <http://teh.id.au/posts/2017/02/13/interactive-print/index.html>`_
