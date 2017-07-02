========================================
Perfect Forwarding
========================================


.. contents:: 目錄


介紹
========================================

Perfect Forwarding
------------------------------

Perfect Forwarding 指的是函式可以原封不動
（保持原 lvalue/rvalue 性質）地把資料傳給真正要建立的地方，
藉此可以省去中間傳遞時不必要的複製。



std::forward
------------------------------

std::forward 是一個 conditional cast，
如果傳入的參數原本是 rvalue 的話，
才會進行轉換，
把它轉成 rvalue。

相對的 std::move 是無論如何都會把傳入的參數轉成 rvalue。

.. code-block:: cpp

    template<class T>
    void wrapper(T&& arg)   // universal reference
    {
        // arg is always lvalue
        foo(std::forward<T>(arg)); // Forward as lvalue or as rvalue, depending on T
    }


emplace
------------------------------

在 C++11 之後 STL 內的資料結構都多了 emplace 相關的函式可以呼叫，
以 vector 為例：

* ``push_back(mystring)`` ：copy
* ``push_back(std::move(mystring))`` ：move
* ``emplace_back(mystring)`` ：copy，等同於 ``push_back(mystring)``
* ``emplace_back(std::move(mystring))`` ：move，等同於 ``push_back(std::move(mystring))``
* ``emplace_back("mydata")`` ：in-place construction

使用 emplace 版本的結果可能會等同於原本的版本，
但在直接傳入內部資料時，
emplace	版本就會比較有效率。


搭配 Variadic Template
------------------------------

.. code-block:: cpp

    template<typename... Args>
    void stepper::rturn(Args&&... args) const
    {
        turn(std::forward<Args>(args)..., true);
    }




結論
========================================

* 對 rvalue reference 使用 std::move
	- ``Widget&&`` 是 rvalue reference
	- ``vector<T>&&`` 是 rvalue reference
* 對 universal reference 使用 std::forward
	- ``T&&`` 是 universal reference
	- ``auto&&`` 是 universal reference
* 如果是會被 RVO/NRVO 優化掉的 local 物件，不要套用 std::move 或 std::forward

rvalue reference:

.. code-block:: cpp

    class Widget {
    public:
        Widget(Widget&& rhs)    // rhs is rvalue reference
        : name(std::move(rhs.name)),
          p(std::move(rhs.p))
        { ... }
        ...

    private:
        std::string name;
        std::shared_ptr<SomeDataStructure> p;
    };


universal reference:

.. code-block:: cpp

    class Widget {
    public:
        template<typename T>
        void setName(T&& newName)   // universal reference
        { name = std::forward<T>(newName); }
        ...
    };



參考
========================================

* `cppreference - std::forward <http://en.cppreference.com/w/cpp/utility/forward>`_
* `cppreference - std::move <http://en.cppreference.com/w/cpp/utility/move>`_
* `cppreference - std::move_if_noexcept <http://en.cppreference.com/w/cpp/utility/move_if_noexcept>`_
* `cppreference - std::vector::emplace <http://en.cppreference.com/w/cpp/container/vector/emplace>`_
* `cppreference - std::vector::emplace_back <http://en.cppreference.com/w/cpp/container/vector/emplace_back>`_
* `cppreference - Parameter pack <http://en.cppreference.com/w/cpp/language/parameter_pack>`_
* `Wikipedia - Variadic Template <https://en.wikipedia.org/wiki/Variadic_template>`_
