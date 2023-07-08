========================================
lambda function
========================================


.. contents:: 目錄


介紹
========================================

lambda function 又稱為 anonymous function，
中文翻譯叫匿名函式，
其定義沒有名稱，
而且會依據定義的位置而有不同的 context，
而 function instance 和其綁定的 non-local 資料又稱為 closure。



C++ lambda
========================================

最簡單的定義語法為 ``[]{}`` ，
這邊沒有指定參數和回傳型別，
這些都會自動判斷，
而呼叫方式跟一般函式一樣，
部份範例：

.. code-block:: cpp

    [&]{};              // ok: by-reference capture default
    [=]{};              // ok: by-copy capture default
    [&, i]{};           // ok: by-reference capture, except i is captured by copy
    [=, &i]{};          // ok: by-copy capture, except i is captured by reference
    // [&, &i] {};         // error: by-reference capture when by-reference is the default
    // [=, this] {};       // error: this when = is the default
    [&, this]{};        // ok: captures the enclosing class by reference
    [=, *this]{};       // ok: captures the enclosing class by copy (C++17)
    [&, *this]{};       // ok: captures the enclosing class by copy (C++17)
    // [i, i] {};          // error: i repeated
    // [this, *this] {};   // error: "this" repeated (C++17)


在指定好 capture 模式後，
lambda 內用到 scope 內不存在的變數就會自動往外尋找，
copy mode 就會複製一份，
reference mode 就會參考過去，
但是也可以特別指定某些變數是要 copy 或 reference。


lambda function 也可以特別指定呼叫時要傳的參數，
語法就變成 ``[] () {}`` ，
部份範例：

.. code-block:: cpp

    auto f = [](auto&& a, auto&& b) { return a < b; };


lambda function 也可以指定回傳型別，
語法就變成 ``[] () -> type {}`` 。
還可以再加上 mutable 或 constexpr 的屬性，
語法就變成 ``[] () constexpr -> type {}`` 。


lambda function 本身不會造成 Heap allocation，
只有 closure 內的物件需要 Heap allocation 時才可能會觸發。


lambda function 有什麼好處？
========================================

lambda function 可以在要使用時直接寫定義，
所以馬上就可以看到函式內的操作，
也容易在使用時直接寫一小段需要的函式（例如呼叫 STL 內的函式），
而不必在外面寫比較麻煩的函式定義。

藉由 lambda function 我們可以做到動態產生函式，
依據執行期間的資訊，
來做出不一樣的 lambda function。



參考
========================================

* `cppreference - lambda expression <http://en.cppreference.com/w/cpp/language/lambda>`_
* `Wikipedia - Anonymous function <https://en.wikipedia.org/wiki/Anonymous_function>`_
* `Wikipedia - Closure (computer programming) <https://en.wikipedia.org/wiki/Closure_(computer_programming)>`_
* `Another myth, about C++ lambdas <http://www.elbeno.com/blog/?p=1068>`_
