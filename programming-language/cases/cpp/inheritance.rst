========================================
繼承 (Inheritance)
========================================


.. contents:: 目錄


基本繼承
========================================

* class 定義
    - ``public`` : 大家都可看
    - ``protected`` : 只有子孫能看
    - ``private`` : 只有自己能看
* class 繼承
    - ``public`` : 大家都知道父母和小孩的關係
    - ``protected`` : 只有子孫知道自己與祖先的關係
    - ``private`` : 只有自己知道跟父母的關係

基本上的 priority 就是 ``private`` > ``protected`` > ``public`` ，
所以在繼承的時候 priority 大的會掩蓋 priorty 小的

.. code-block:: cpp

    class A
    {
    public:
        int x;
    protected:
        int y;
    private:
        int z;
    };

    class B : public A
    {
        // x is public
        // y is protected
        // z is not accessible from B
    };

    class C : protected A
    {
        // x is protected
        // y is protected
        // z is not accessible from C
    };

    class D : private A
    {
        // x is private
        // y is private
        // z is not accessible from D
    };



Virutal Function
========================================

C++ 裡提供了一個 keyword 叫 ``virtual`` ，
使用 virtual 關鍵字的 method 會是 Late binding (dynamic binding)，
在 runtime 的時候才會決定要 call 的 function 位址

例如 :

.. code-block:: cpp

    #include <iostream>

    class A
    {
    public:
        void func1()
        {
            std::cout << "func1 in A" << std::endl;
        }

        virtual void func2()
        {
            std::cout << "func2 in A" << std::endl;
        }
    };

    class B : public A
    {
    public:
        void func1()
        {
            std::cout << "func1 in B" << std::endl;
        }

        void func2()
        {
            std::cout << "func2 in B" << std::endl;
        }
    };

    int main(int argc, char *argv[]) {

        A a = A();
        B b = B();

        a.func1();  // func1 in A
        a.func2();  // func2 in A
        b.func1();  // func1 in B
        b.func2();  // func2 in B

        A &c = b;
        c.func1();  // func1 in A
        c.func2();  // func2 in B

        A *ptr = nullptr;

        ptr = &a;
        ptr->func1();  // func1 in A
        ptr->func2();  // func2 in A

        ptr = &b;
        ptr->func1();  // func1 in A
        ptr->func2();  // func2 in B

        return 0;
    }


這邊可以看到，把 class B 的變數用 class A 去解讀的時候，func1 是呼叫到 class A 所定義的，
而 func2 是呼叫到 class B 所定義的，會有這樣的差別是因為 func1 沒有用 ``virtual`` ，
但是 func2 有用 ``virtual`` ，
base class 有寫 virtual 的 function 在被 call 到時
會去 ``virtual table`` 裡面找真正要 call 的 function 的位址，
也才能有 late binding 的效果，沒有寫 virtual 的 function 依然會是 early binding (static binding)。

在 static binding 的情況下，ptr 要 call 的 function 的位址在 compile time 就決定了，
所以 func1 一直都會 call 到 class A 的版本。而在 late binding 的情況下，
要 call 的 function 的位址在 runtime 決定，會從 ``virtual table`` 中找到對應的 function 的位址，
所以可以 call 到各自的版本。

一個函式一旦標上 ``virtual`` ，
其後續的 derived class 內的該函式也都是 ``virtual`` 。
但是如果 base class 內的函式沒有標 ``virtual`` ，
後續的 derived class 內才標上 ``virtual`` ，
base class 的指標或 Reference 不會有 Dynamic Dispatch 的效果，
就算實際上他指到的資料是 derived class 的，
也會呼叫到 base class 的函式。

* non-virtual 函式：Static Dispatch，以變數型別來決定呼叫的函式
* virtual 函式：Dynamic Dispatch，以資料型別來決定呼叫的函式



override & final (since C++11)
========================================

override
------------------------------

``override`` 是提供給繼承的 class 用的，
目的是確保 function 有 override 到 base class 的 virtual funcion，
標上 ``override`` 後，compiler 可以在 compile time 的時候檢查是否真的有 override，
可以避免不小心沒寫好造成該 override 的 function 沒有 override 到。

.. code-block:: cpp

    class A
    {
    public:
        virtual void foo();
        void bar();
    };

    class B : A
    {
    public:
        void foo() const override;  // Error: B::foo does not override A::foo
                                    // (signature mismatch)
        void foo() override;        // OK: B::foo overrides A::foo
        void bar() override;        // Error: A::bar is not virtual
    };


final
------------------------------

``final`` 是提供給 class 或 base class 的 virtual function 使用的，
標上 ``final`` 的 class 不能再被繼承，標上 ``final`` 的 virutal function 不能再被 override。

.. code-block:: cpp

    class A
    {
    public:
        virtual void foo() final;   // A::foo is final
        void bar() final;           // Error: non-virtual function cannot be final
    };

    class B final : A   // struct B is final
    {
    public:
        void foo();     // Error: foo cannot be overridden as it's final in A
    };

    class C : B         // Error: B is final
    {
    };



多重繼承
========================================

Virtual Inheritance
========================================

在多重繼承的狀況下，
可能會發生數個 parent class 也都繼承了某個 base class，
如此一來將會有數個 base class 的存在最後的 derived class 內，
Virtual Inheritance 就是要解決這種問題，
在繼承共通的 base class 時標上 virtual，
讓最後的 derived class 只有一份 base class。

（C++ 的 virtual 關鍵字會用在兩個地方，
一個是 virtual function，
另一個就是這邊的 virtual base class）


範例程式碼： `examples/virtual-base-class.cpp <examples/virtual-base-class.cpp>`_



Template & Class
========================================

一個常見的手法是讓 class 繼承自某個用 template 留空的 class，
並利用該 class 來實做相關的函式作為界面，
要為界面提供不同的 backend 時就讓他繼承不同的 class，
範例：

.. code-block:: cpp

    template<typename Transport>
    class service : Transport   // private inheritance from the Transport policy
    {
    public:
        void transmit() {
            this->send(...);    // send using whatever transport was supplied
        }
    };

    // TCP transport policy
    class tcp {
    public:
        void send(...);
    };

    // UDP transport policy
    class udp {
    public:
        void send(...);
    };

    service<tcp> service(host, port);
    service.transmit(...);      // send over TCP



參考
========================================

* `cppreference - virtual <http://en.cppreference.com/w/cpp/language/virtual>`_
* `cppreference - override <http://en.cppreference.com/w/cpp/language/override>`_
* `cppreference - final <http://en.cppreference.com/w/cpp/language/final>`_
* `cppreference - Derived class <http://en.cppreference.com/w/cpp/language/derived_class>`_
* `cppreference - abstract class <http://en.cppreference.com/w/cpp/language/abstract_class>`_
* `Wikipedia - Virtual function <https://en.wikipedia.org/wiki/Virtual_function>`_
* `Wikipedia - Virtual method table <https://en.wikipedia.org/wiki/Virtual_method_table>`_
