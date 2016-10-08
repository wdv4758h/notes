========================================
C++ const
========================================

``const`` qualifiers 在 C 和 C++ 裡面都很常見，
但是觀念不清楚的話就不能好好利用，
以下做些觀念紀錄。

加上 ``const`` 關鍵字可以確保不該被改到的變數不被更動，
如果不小心寫錯更動到的話，
會在編譯時噴出錯誤。

* 該加 const 的儘量加
* 愈早加愈好


const in declaration
------------------------------

由右至左解釋變數宣告：

.. code-block:: cpp

    const X p       // p is an X that is const
    X const p       // p is a const X

    const X * p     // p points to an X that is const
    X const * p     // p points to a const X

    X * const p     // p is a const pointer to an X

    X const * const p     // p is a const pointer to a const X
    const X * const p     // p is a const pointer to an X that is const

    const X& p      // p is a reference to an X that is const
    X const& p      // p is a reference to a const X


const in function parameters
------------------------------

.. code-block:: cpp

    void f1(const std::string& s);     // Pass by reference-to-const
    void f2(const std::string* sptr);  // Pass by pointer-to-const
    void f3(std::string s);            // Pass by value


const member function
------------------------------

const member function 又稱為 inspectors，不會更動 object 裡的東西，也就是對於這個 object 沒有副作用：

.. code-block:: cpp

    class MyClass {
    public:
        void inspect() const;   // This member promises NOT to change *this
        void mutate();          // This member function might change *this
    };


如果想要從 const member function 裡用 reference 的方式回傳 ``this`` object 裡的 member 的話，
必須使用 reference-to-const 或是 by value：

.. code-block:: cpp

    class MyClass {
    public:

        // inspect member function will return ``this`` object's member

        const std::string& inspect_pass_1() const;    // Pass, the caller can't change the object
              std::string& inspect_fail_1() const;    // Compile-time error, the caller can change the object
        const std::string  inspect_pass_2() const;    // Pass, the caller can't change the object
              std::string  inspect_pass_2() const;    // Pass, the caller can't change the object

        const std::string& inspect_pass_3();          // Pass
              std::string& inspect_pass_4();          // Pass
        const std::string  inspect_pass_5();          // Pass
              std::string  inspect_pass_5();          // Pass
    };


如果有 member 在 const member function 是會更動的，
但是仍然要把它視為 const member function，
則須把該 member 宣告為 mutable。

.. code-block:: cpp

    class MyClass {
    public:

        void inspect() const { ++count; }

        mutable unsigned int count = 0;

    };


const overloading
------------------------------

const-overloading 指的是有兩個名稱相同的 member function，差別只在 const，
所以 const 和 non-const 的 object 會呼叫到不同函數，
形成 overloading。

.. code-block:: cpp

    class MyClass {
    public:

        // Subscript operators often come in pairs

        const MyClass& operator[] (unsigned index) const;
              MyClass& operator[] (unsigned index);
    };


Reference
========================================

* `C++ FAQ - Const Correctness <https://isocpp.org/wiki/faq/const-correctness>`_
