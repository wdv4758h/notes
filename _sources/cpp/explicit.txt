========================================
explicit specifier
========================================


.. contents:: 目錄


介紹
========================================

TL;DR: explicit 是控制顯性或隱性轉換


標上 explicit 就表示不接受隱式轉換或 copy-initialization，
可以套用在兩個地方：

* constructor
* conversion function

convertion function 指的是沒有明確的回傳型別的 member function，
而標上 explicit 後就必須使用顯示轉換，
例如：

.. code-block:: cpp

    struct X {
        //implicit conversion
        operator int() const { return 7; }

        // explicit conversion
        explicit operator int*() const { return nullptr; }
    }

    int main() {
        X x;
        int n = static_cast<int>(x);    // OK: sets n to 7
        int m = x;                      // OK: sets m to 7
        int* p = static_cast<int*>(x);  // OK: sets p to nullptr
    //  int* q = x;                     // Error: no implicit conversion
        int (*pa)[3] = x;               // OK
    }


標上 explicit 的 constructor 則必須使用 direct-initialization，
不能用 copy-initialization，
相對的沒有標 explicit 的 constructor 又被稱為 converting constructor，

完整範例：

.. code-block:: cpp

    class A {
    public:
        A(int) { }      // converting constructor
        A(int, int) { } // converting constructor (C++11)
        operator bool() const { return true; }
    };

    class B {
    public:
        explicit B(int) { }
        explicit B(int, int) { }
        explicit operator bool() const { return true; }
    };

    int main() {
        A a1 = 1;       // OK: copy-initialization selects A::A(int)
        A a2(2);        // OK: direct-initialization selects A::A(int)
        A a3 {4, 5};    // OK: direct-list-initialization selects A::A(int, int)
        A a4 = {4, 5};  // OK: copy-list-initialization selects A::A(int, int)
        A a5 = (A)1;    // OK: explicit cast performs static_cast
        if (a1) {}      // OK: A::operator bool()
        bool na1 = a1;  // OK: copy-initialization selects A::operator bool()
        bool na2 = static_cast<bool>(a1);   // OK: static_cast performs direct-initialization

    //  B b1 = 1;       // error: copy-initialization does not consider B::B(int)
        B b2(2);        // OK: direct-initialization selects B::B(int)
        B b3 {4, 5};    // OK: direct-list-initialization selects B::B(int, int)
    //  B b4 = {4, 5};  // error: copy-list-initialization does not consider B::B(int,int)
        B b5 = (B)1;    // OK: explicit cast performs static_cast
        if (b2) {}      // OK: B::operator bool()
    //  bool nb1 = b2;  // error: copy-initialization does not consider B::operator bool()
        bool nb2 = static_cast<bool>(b2);   // OK: static_cast performs direct-initialization
    }



參考
========================================

* `cppreference - explicit specifier <http://en.cppreference.com/w/cpp/language/explicit>`_
* `cppreference - converting constructor <http://en.cppreference.com/w/cpp/language/converting_constructor>`_
* `cppreference - user-defined conversion <http://en.cppreference.com/w/cpp/language/cast_operator>`_
