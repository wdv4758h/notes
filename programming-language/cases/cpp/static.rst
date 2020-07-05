========================================
static
========================================


.. contents:: 目錄


介紹
========================================

static 關鍵字可以用在兩種地方，
一個是 class 內用於宣告不用綁定 instance 的 class method 和 class member，
一個是 class 外用於宣告會在程式一啟動就建立並在程式結束收回的變數。


在 class 內使用
------------------------------

.. code-block:: cpp

    // static 只要加在宣告時即可

    class X {
    public:
        static void f();
        const static int n = 1;
        const static int m {2};     // since C++11
        const static int k;
    };
    const int X::k = 42;
    void X::f() { std::cout << X::k << std::endl; }


如果和 constexpr 結合就必須寫好 initiailizer，
範例：

.. code-block:: cpp

    class X {
    public:
        constexpr static int arr[] = { 1, 2, 3 };           // OK
        constexpr static std::complex<double> n = {1, 2};   // OK
        constexpr static int k;     // Error: constexpr static requires an initializer
    };


在 class 外使用
------------------------------

物件的生命週期可以區分為四種：

* automatic
    - 某個 code block 內
    - 除了宣告為 static、extern、thread_local 外的 local 物件都是屬於這種
* static
    - 跟程式的存活時間一樣長
    - 所有在 namespace scope 宣告的物件加上標為 static 或 extern 的物件都屬於這種
* thread （從 C++11 開始）
    - 跟 thread 的存活時間一樣長
    - 每個 thread 有各自的 instance
    - 只有標為 thread_local 的物件屬於這種
    - 可以搭配 static 和 extern 來控制 linkage
* dynamic
    - 藉由 dynamic memory allocation 的方式來建立的物件


Linkage 狀態可以分成三種：

* no linkage
    - 只有在同個 scope 內才能存取
    - 包含沒有標為 extern 的變數
    - 包含 local class 和其 member function
    - 包含在 block scope 宣告的名字，例如 typedef、enumerations、enumerations
* internal linkage
    - 在同個 translation unit 內的所有 scope 都可以存取
    - 包含標為 static 的變數、函式
    - 包含沒有宣告標為 volatile、inline、extern 的 const 變數（包含 constexpr）
    - 包含 anonymous unions 內的 member
    - 包含 unnamed namespace 內的所有名稱（包含 unnamed namespace 內的 namespace）（從 C++11 開始）
* external linkage
    - 可以在不同 translation unit 內的 scope 存取，來自其他程式語言的 translation unit 也可以存取
    - namespace 內（外層本身和外層不是 unnamed namespace）：
        - 任何標上 extern 的變數
        - 沒有標為 static 的函式
        - namespace scope 沒有標上 static 的非 const 變數
        - enumerations 和 enumerators
    - block scope：
        - 標為 extern 的變數
        - 函式


以上可以注意到 static 可以改變物件的生命週期和 linkage，
標上 static 的物件的生命週期會是 static，
linkage 會是 internal。


範例一：

.. code-block:: cpp

    int func() {
        static int x = 0;
        return x++;
    }


範例二：

.. code-block:: cpp

    // example-file1.cpp

    extern void func();

    int main() {
        func();
        return 0;
    }


.. code-block:: cpp

    // example-file2.cpp

    class X {
    public:
        static void funcx() {};
    };

    namespace N {
        class Y {
        public:
            static void funcy() {};
        };
    }

    void func() {
        X::funcx();
        N::Y::funcy();
    }



參考
========================================

* `cppreference - static members <http://en.cppreference.com/w/cpp/language/static>`_
* `cppreference - Storage class specifiers <http://en.cppreference.com/w/cpp/language/storage_duration>`_
