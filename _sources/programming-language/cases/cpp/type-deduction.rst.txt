========================================
型別推斷 (Type Deduction)
========================================


.. contents:: 目錄


Reference Collapsing
========================================

Reference Collapsing 會把過多的 Reference 收起來，
例如 Reference to Reference 會變成 Reference，
發生在以下狀況：

* Template
* auto
* typedef
* decltype



種類一：Template Type Deduction
========================================

.. code-block:: cpp

    template<typename T>
    void f(ParamType param);

    f(expr);    // deduce T and ParamType from expr


ParamType 是 Reference 或 Pointer，不是 Universal Reference：

.. code-block:: cpp

    template<typename T>
    void f(T& param);   // param is a reference

    int x = 27;         // x is an int
    const int cx = x;   // cx is a const int
    const int& rx = x;  // rx is a reference to x as a const int

    f(x);   // T is int,
            // param's type is int&
    f(cx);  // T is const int,
            // param's type is const int&
    f(rx);  // T is const int,
            // param's type is const int&

    ////////////////////////////////////////

    template<typename T>
    void f(const T& param);     // param is now a ref-to-const

    int x = 27;         // x is an int
    const int cx = x;   // cx is a const int
    const int& rx = x;  // rx is a reference to x as a const int

    f(x);   // T is int, param's type is const int&
    f(cx);  // T is int, param's type is const int&
    f(rx);  // T is int, param's type is const int&

    ////////////////////////////////////////

    template<typename T>
    void f(T* param);   // param is now a pointer

    int x = 27;         // as before
    const int *px = &x; // px is a ptr to x as a const int

    f(&x);  // T is int, param's type is int*
    f(px);  // T is const int,
            // param's type is const int*


ParamType 是 Universal Type：

.. code-block:: cpp

    template<typename T>
    void f(T&& param);  // param is now a universal reference

    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x);   // x is lvalue, so T is int&,
            // param's type is also int&
    f(cx);  // cx is lvalue, so T is const int&,
            // param's type is also const int&
    f(rx);  // rx is lvalue, so T is const int&,
            // param's type is also const int&
    f(27);  // 27 is rvalue, so T is int,
            // param's type is int&&

ParamType 不是指標也不是 Reference：

.. code-block:: cpp

    template<typename T>
    void f(T param);    // param is now passed by value

    int x = 27;
    const int cx = x;
    const int& rx = x;

    f(x);   // T's and param's types are both int
    f(cx);  // T's and param's types are again both int
    f(rx);  // T's and param's types are still both int



種類二： ``auto`` Type Deduction
========================================

``auto`` Type Deduction 的規則基本上都跟 Template Type Deduction 相同，
只有一個差異，
就是會把 braced initilizer 視為 ``std::initializer_list`` ，
但是 Template Type Deduction 不會。

另外 ``auto`` 用於函式的回傳型別或是 lambda 的 parameter，
是屬於 Template Type Deduction。

.. code-block:: cpp

    auto x1 = 27;       // type is int, value is 27
    auto x2(27);        // type is int, value is 27
    auto x3 = { 27 };   // type is std::initializer_list<int>,
                        // value is { 27 }
    auto x4{ 27 };      // type is std::initializer_list<int>,
                        // value is { 27 }

    auto x5 = { 1, 2, 3.0 };    // error! can't deduce T for
                                // std::initializer_list<T>



種類三： ``decltype`` Type Deduction
========================================

.. code-block:: cpp

    const int i = 0;            // decltype(i) is const int

    bool f(const Widget& w);    // decltype(w) is const Widget&
                                // decltype(f) is bool(const Widget&)

    struct Point {              // decltype(Point::x) is int
        int x, y;               // decltype(Point::y) is int
    }

    Widget w;                   // decltype(w) is Widget

    if (f(w)) ...               // decltype(f(w)) is bool

    template<typename T>
    class vector {
    public:
        ...
        T& operator[](std::size_t index);
        ...
    };
    vector<int> v;              // decltype(v) is vector<int>

    if (v[0][ == 0) ...         // decltype(v[0]) is int&


C++11 加入了 Trailing Return Type 的語法，
也就是可以把回傳的型別寫到後面，
前面原本寫回傳型別的地方寫 ``auto`` ，
但是這個 ``auto`` 跟型別推斷沒有關係：

.. code-block:: cpp

    auto myfunc(int param) -> int;


這種語法在回傳型別會根據參數而變動時很有用：

.. code-block:: cpp

    template<typename Container, typename Index>
    auto authAndAccess(Container& c, Index i) -> decltype(c[i]) {
        ...
    }

而 C++14 則擴充了相關能力，
讓原本的函式宣告語法可以在回傳值直接寫 ``auto`` ，
編譯器會根據程式碼做推斷：

.. code-block:: cpp

    template<typename Container. typename Index>
    auto authAndAccess(Container& c, Index i) {
        ...
        return c[i];
    }



種類四： ``decltype(auto)`` Type Deduction
==========================================

在原本的回傳型別推斷中，
會把 Reference 的資訊丟棄，
所以不能拿來做後續更動，
例如：

.. code-block:: cpp

    template<typename Container, typename Index>
    auto authAndAccess(Container& c, Index i) {
        ...
        return c[i];
    }

    ...

        authAndAccess(c, i) = 42;   // compile error !!!


要自動推斷出包含 Reference 資訊的型別要使用 C++14 加入的 ``decltype(auto)`` ，
``decltype(auto)`` 就像是 ``auto`` ，
但是使用的是 ``decltype`` 的規則，
例如：

.. code-block:: cpp

    template<typename Container, typename Index>
    decltype(auto) authAndAccess(Container& c, Index i) {
        ...
        return c[i];
    }

    ...

        authAndAccess(c, i) = 42;   // compile success


``decltype(auto)`` 也可以用在變數定義：

.. code-block:: cpp

    Widget w;
    const Widget& cw = w;
    auto myWidget1 = cw;            // auto type deduction
                                    // type is Widget
    decltype(auto) myWidget2 = cw;  // decltype type deduction
                                    // type is const Widget&

最後的版本：

.. code-block:: cpp

    template<typename Container, typename Index>
    decltype(auto) authAndAccess(Container&& c, Index i) {  // universal reference
        ...
        return std::forward<Container>(c)[i];
    }



種類五： Class Template Deduction
========================================

C++17 加入了 Class Template Deduction 的支援，
可以讓程式撰寫更簡便，
例如：

.. code-block:: cpp

    std::pair p(2, 4.5);                // deduces to std::pair<int, double> p(2, 4.5);

    std::tuple t(4, 3, 2.5);            // same as auto t = std::make_tuple(4, 3, 2.5);

    auto lck = std::lock_guard(mtx);    // deduces to std::lock_guard<std::mutex>



參考
========================================

* [Book] Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14
* `cppreference - Template argument deduction <http://en.cppreference.com/w/cpp/language/template_argument_deduction>`_
* `cppreference - auto specifier <http://en.cppreference.com/w/cpp/language/auto>`_
* `cppreference - decltype specifier <http://en.cppreference.com/w/cpp/language/decltype>`_
* `cppreference - Class template deduction <http://en.cppreference.com/w/cpp/language/class_template_deduction>`_
* `cppreference - Declaring functions <http://en.cppreference.com/w/cpp/language/function>`_
* `GotW #94 Solution: AAA Style (Almost Always Auto) <https://herbsutter.com/2013/08/12/gotw-94-solution-aaa-style-almost-always-auto/>`_
