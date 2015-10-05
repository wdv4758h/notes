========================================
Monomorphization
========================================

Monomorphization 指的是會把 generic function 依照呼叫的 type 來生出特化版本 (像是 C++ Template)，
這名稱是相對於程式語言中 "Polymorphism" 這個詞 (一個 function 可以處理許多種型別的資料)，
而 Monomorphization 就是在把 polymorphic 的 code 轉成 monomorphic。


Monomorphization 範例，假設我們寫了一個 generic function :

.. code-block:: rust

    fn first<A, B>(pair: (A, B)) -> A {
        let (a, _) = pair;
        return a;
    }

    fn main() {
        println!("{} {}", first((42, "abc")), first(("abc", 42)));
    }


其中 first() 會在編譯時生成兩個版本，分別針對 ``(int, str)`` 和 ``(str, int)`` ，
由於這邊都已經做完特化了，在編譯時就可以決定呼叫的版本，
所以可以達到 Static Dispatch。
