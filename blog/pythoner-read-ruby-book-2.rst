:title: Pythoner 讀 「松本行弘的程式世界」 - part 2
:slug: pythoner-read-ruby-book-2
:date: 2014-10-10 20:50
:category: Misc
:tags: book
:author: wdv4758h
:summary: 讀書紀錄

ch 2-5 Duck Typing
========================================

duck typing 實在很常聽到，尤其自己常寫的是 Python XD

在講到 type 時，常聽到的有 static 和 dynamic，static 的話不用執行就可以知道，
dynamic 的話要執行下去才能確認

硬體看得懂的是二進位數字，其他寫程式用到的型別都是建立在這之上的，
如果沒有做成更好用的 type 的話會造成程式撰寫上的負擔，
於是 Fortran 提供了型別 (整數資料、浮點數陣列等等)，
於是有了 static type (宣告型別)

Lisp & Dynamic type
------------------------------

在 Fortran 出現後幾年，出現了 Lisp，
1958 年的 Lisp 只有兩種型別 : list、atom，不是 list 的都是 atom

- cons cell
- car, cdr
- S-expression


Lisp 的 list 裡事先無法知道 cons cell 裡面指到的是 cons cell 還是 atom，
本質上可說是 polymorphism 的 data structure，
所以 Lisp 採用的是 "資料本身還有描述自己型別的資訊"，又稱為動態型別

::

          cons cell

        +-----+-----+
        | car | cdr |
        +-----+-----+
           |     |
           |     |
         +---+  +-----+-----+
         | 5 |  | car | cdr |
         +---+  +-----+-----+
         atom      |     |
                   |     |
                +----+  nil
                | 13 |  atom
                +----+
                 atom

Static Type 起自 Fortran、Dynamic Type 起自 Lisp，
在最初的物件導向語言 Simula 裡，出現了和 Dynamic Type 類似的型別 Ref (Simula 中除了物件之外都是靜態型別)，
之後從 Simula 的物件導向概念延生出的 Smalltalk 和 Lisp 一樣全面採用動態型別，
1980 年代前半，受到 Simula 影響而誕生了 C++，重要概念 : "subclass 可以視為 base class 的 instance"

Duck Typing 的概念是: "走路像鴨子，看起來像鴨子，那就可以把他當成鴨子"

Dynamic Type 裡避免名去檢查型別，而改以檢查是否有某 method
