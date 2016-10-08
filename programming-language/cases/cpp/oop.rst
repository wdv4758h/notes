C++ 繼承
========================================

* class 定義
    - ``public`` : 大家都可看
    - ``protected`` : 只有子孫能看
    - ``private`` : 只有自己能看
* class 繼承
    - ``public`` : 大家都知道父母和小孩的關係
    - ``protected`` : 只有子孫知道自己與祖先的關係
    - ``private`` : 只有自己知道跟父母的關係

基本上的 priority 就是 ``private`` > ``protected`` > ``public`` 所以在繼承的時候 priority 大的會掩蓋 priorty 小的

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
base class 有寫 virtual 的 function 在被 call 到時會去 ``virtual table`` 裡面找真正要 call 的 function 的位址，
也才能有 late binding 的效果，沒有寫 virtual 的 function 依然會是 early binding (static binding)。

在 static binding 的情況下，ptr 要 call 的 function 的位址在 compile time 就決定了，
所以 func1 一直都會 call 到 class A 的版本。而在 late binding 的情況下，
要 call 的 function 的位址在 runtime 決定，會從 ``virtual table`` 中找到對應的 function 的位址，
所以可以 call 到各自的版本。

C++11 - override & final
========================================

override
------------------------------

``override`` 是提供給繼承的 class 用的，目的是確保 function 有 override 到 base class 的 virtual funcion，
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
