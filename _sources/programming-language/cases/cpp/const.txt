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


注意的是在 Pass by Value 的情況下，
參數有沒有加 ``const`` 都不會影響函式的 signature，
所以如果有使用 forward declaration 的話，
不需要在宣告時為參數加上 const，
在寫實做時再依需求決定是否加上 const 來向內部標注 read-only 即可。
（反正 Pass by Value 會複製一份，原本的資料到底是不是 const 已經不重要了）



const member function
------------------------------

const member function 又稱為 inspectors，
不會更動 object 的 observable state，
也就是對於這個 object 沒有副作用
（內部有標明 mutable 的變數仍然可以更動，例如 Cache，
維護的是 logically const 而不是 physically const）：

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
則須把該 member 宣告為 mutable
（writable but logically const）。

.. code-block:: cpp

    class MyClass {
    public:

        void inspect() const { ++count; }

        mutable unsigned int count = 0;

    };


如果要在多執行緒下跑，
mutable 變數要額外做同步，
例如用 mutex 或 atomic 的型別。


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



注意事項
========================================

同樣是 member function 的 const，
C++98 思考的是 single-thread model，
隱含 logically const。
C++11 後思考的是 concurrency model，
隱含的是真的 read-only 或是會同步，
不需要 caller 做額外的同步處理。



Reference
========================================

* `C++ FAQ - Const Correctness <https://isocpp.org/wiki/faq/const-correctness>`_
* `GotW #6a Solution: Const-Correctness, Part 1 <https://herbsutter.com/2013/05/24/gotw-6a-const-correctness-part-1-3/>`_
    - With C++98, we taught a generation of C++ developers that "const means logically const, not physically/bitwise const".
    - With C++11 and onward, const now really does mean "read-only, or safe to read concurrently"-either truly physically/bitwise const, or internally synchronized so that any actual writes are synchronized with any possible concurrent const accesses so the callers can't tell the difference.
    - "Concurrent const operations on the same object are required to be safe without the calling code doing external synchronization."
* `GotW #6b Solution: Const-Correctness, Part 2 <https://herbsutter.com/2013/05/28/gotw-6b-solution-const-correctness-part-2/>`_
* `Does const mean thread-safe in C++11? <http://stackoverflow.com/questions/14127379/does-const-mean-thread-safe-in-c11>`_
