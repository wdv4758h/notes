========================================
型別轉換 (Type Conversion)
========================================


.. contents:: 目錄


介紹
========================================

C++ 內有許多種型別轉換的方式：

* const_cast
* static_cast
* dynamic_cast
* reinterpret_cast
* implicit conversions


const_cast
------------------------------

csont_cast 不會產生任何一個 CPU 指令，
const_cast 只是把型別的 const 移除掉，
如果操作在原本定義時是 const 的變數會是 Undefined Behavior，
但是操作在定義時不是 const 的變數則沒問題。

例如：

.. code-block:: cpp

    #include <iostream>

    void f1(const int& x) {
        const_cast<int&>(x) = 42;
    }

    void f2(const int* x) {
        *const_cast<int*>(x) = 43;
    }

    int main() {
        int foo = 0;
        const int bar = 0;
        std::cout << foo << std::endl;
        std::cout << bar << std::endl;
        f1(foo);    // OK
        f1(bar);    // Undefined Behavior
        std::cout << foo << std::endl;
        std::cout << bar << std::endl;
        f2(&foo);   // OK
        f2(&bar);   // Undefined Behavior
        std::cout << foo << std::endl;
        std::cout << bar << std::endl;
    }


真正使用到的情況可能是需要用到的 Library 沒有把 const 相關的部份寫好（not const-correct），
所以需要自己填補這部份，
此時可能還會附上註解說明 Library 的問題，
並看看之後是要改好用到的 Library 或是尋找替到方案。


static_cast
------------------------------

沒有執行期間的檢查，
編譯期間就會檢查是否能轉換型別。


使用情境：

* 初始化
* 靜態 downcast（base class 轉成 derived class）
* lvalue 轉 xvalue
* 忽略值
* 把 implicit 轉換轉回去
* 靜態 upcast（derived class 轉成 base class）
* enum 和數值間轉換
* enum 和 enum 間轉換
* 靜態 member 指標 upcast
* void* 轉成其他各種型別


.. code-block:: cpp

    #include <vector>
    #include <iostream>

    struct Base {
        int m = 0;
        void hello() const {
            std::cout << "Hello world, this is Base!" << std::endl;
        }
    };

    struct Derived : Base {
        void hello() const {
            std::cout << "Hello world, this is Derived!" << std::endl;
        }
    };

    enum class E { ONE = 1, TWO, THREE };
    enum EU { ONE = 1, TWO, THREE };

    int main()
    {
        // 1: initializing conversion
        int n = static_cast<int>(3.14);
        std::cout << "n = " << n << std::endl;  // 3
        std::vector<int> v = static_cast<std::vector<int>>(10);
        std::cout << "v.size() = " << v.size() << std::endl;    // 10

        // 2: static downcast
        Derived d;
        Base& br = d;       // upcast via implicit conversion
        br.hello();         // Base
        Derived& another_d = static_cast<Derived&>(br); // downcast
        another_d.hello();  // Derived

        // 3: lvalue to xvalue
        std::vector<int> v2 = static_cast<std::vector<int>&&>(v);
        std::cout << "after move, v.size() = " << v.size() << std::endl;    // 0

        // 4: discarded-value expression
        static_cast<void>(v2.size());

        // 5. inverse of implicit conversion
        void* nv = &n;
        int* ni = static_cast<int*>(nv);
        std::cout << "*ni = " << *ni << std::endl;

        // 6. array-to-pointer followed by upcast
        Derived a[10];
        Base* dp = static_cast<Base*>(a);

        // 7. scoped enum to int or float
        E e = E::ONE;
        int one = static_cast<int>(e);
        std::cout << one << std::endl;

        // 8. int to enum, enum to another enum
        E e2 = static_cast<E>(one);
        EU eu = static_cast<EU>(e2);

        // 9. pointer to member upcast
        int Derived::*pm = &Derived::m;
        std::cout << br.*static_cast<int Base::*>(pm) << std::endl;

        // 10. void* to any type
        void* voidp = &e;
        std::vector<int>* p = static_cast<std::vector<int>*>(voidp);
    }


dynamic_cast
------------------------------

dynamic_cast 能轉換成的型別只有 class 的 Reference 或 Pointer。
dynamic_cast 會進行動態的轉換和檢查，
如果想轉換成的型別是 Pointer，轉換失敗時會回傳 nullptr，
如果想轉換成的型別是 Reference，轉換失敗時會噴 Exception。

藉由 dynamic_cast 可以在有關連性的 class 間轉換，
只要一開始資料建立時的型別是要轉換到的 class 的子 class 即可，
缺點是要多了執行期間的檢查，
不能在編譯期間就做完。
（而且要搭配 RTTI 一起使用，不能在編譯時使用 ``-fno-rtti`` ，
但是沒有使用到 Polymorphic Object 的狀況就不需要 RTTI ）


.. code-block:: cpp

    #include <iostream>
    #include <memory>

    struct V {
        virtual void f() {};    // must be polymorphic to use runtime-checked dynamic_cast
    };

    struct A : virtual V {};

    struct B : virtual V {
        B(V* v, A* a) {
            // casts during construction (see the call in the constructor of D below)
            dynamic_cast<B*>(v);    // well-defined: v of type V*, V base of B, results in B*
            dynamic_cast<B*>(a);    // undefined behavior: a has type A*, A not a base of B
        }
    };

    struct D : A, B {
        D() : B((A*)this, this) { }
    };

    struct Base {
        virtual ~Base() {}
    };

    struct Derived: Base {
        virtual void name() {}
    };

    int main()
    {
        D d;        // the most derived object
        A& a = d;   // upcast, dynamic_cast may be used, but unnecessary
        auto new_d = dynamic_cast<D&>(a);   // downcast
        auto new_b = dynamic_cast<B&>(a);   // sidecast


        auto b1 = std::make_unique<Base>();
        if (auto d = dynamic_cast<Derived*>(b1.get())) {
            // Base* -> Derived*
            // Fail
            std::cout << "downcast from b1 to d successful\n";
            d->name(); // safe to call
        }

        auto foo = std::make_unique<Derived>();
        Base* b2 = foo.get();
        if (auto d = dynamic_cast<Derived*>(b2)) {
            // Derived* -> Base* -> Derived*
            // Pass
            std::cout << "downcast from b2 to d successful\n";
            d->name(); // safe to call
        }
    }


reinterpret_cast
------------------------------

reinterpret_cast 不會產生任何一個 CPU 指令，
只是用來告訴編譯器要把一串 bits 視為另一個型別。


.. code-block:: cpp

    #include <cstdint>
    #include <cassert>
    #include <iostream>

    int f() { return 42; }

    int main() {
        int i = 7;

        // pointer to integer and back
        auto v1 = reinterpret_cast<uintptr_t>(&i); // static_cast is an error
        std::cout << "The value of &i is 0x" << std::hex << v1 << '\n';
        auto p1 = reinterpret_cast<int*>(v1);
        assert(p1 == &i);

        // pointer to function to another and back
        auto fp1 = reinterpret_cast<void(*)()>(f);
        // fp1(); undefined behavior
        auto fp2 = reinterpret_cast<int(*)()>(fp1);
        std::cout << std::dec << fp2() << '\n'; // safe

        // type aliasing through pointer
        auto p2 = reinterpret_cast<char*>(&i);
        if (p2[0] == '\x7')
            std::cout << "This system is little-endian\n";
        else
            std::cout << "This system is big-endian\n";

        // type aliasing through reference
        reinterpret_cast<unsigned int&>(i) = 42;
        std::cout << i << '\n';

        const int &const_iref = i;
        //int &iref = reinterpret_cast<int&>(const_iref); // compiler error - can't get rid of const
        // Must use const_cast instead:  int &iref = const_cast<int&>(const_iref);
    }



Polymorphic Objects
========================================

class 內至少包含一個 virtual 函式（包含繼承下來的）就稱為 Polymorphic Objects。
每個 Polymorphic Objects 都會存有額外的資訊（通常會多一個指標），
這些資訊會在呼叫 virutal 函式或 RTTI features（dynamic_cast、typeid）時用上，
用來在執行期間判斷物件被建立時的型別，
而不是 expression 使用時的型別。

對於 Non-Polymorphic Objects，
對於型別的解釋會在編譯時期被決定，
利用 expression 使用時的型別來判斷。

.. code-block:: cpp

    #include <iostream>
    #include <typeinfo>

    struct Base1 {
        // polymorphic type: declares a virtual member
        virtual ~Base1() {}
    };

    struct Derived1: Base1 {
         // polymorphic type: inherits a virtual member
    };

    struct Base2 {
         // non-polymorphic type
    };
    struct Derived2 : Base2 {
         // non-polymorphic type
    };

    int main() {
        Derived1 obj1;  // object1 created with type Derived1
        Derived2 obj2;  // object2 created with type Derived2

        Base1& b1 = obj1;   // b1 refers to the object obj1
        Base2& b2 = obj2;   // b2 refers to the object obj2

        std::cout << "Expression type of b1: " << typeid(decltype(b1)).name() << '\n'   // Base1
                  << "Expression type of b2: " << typeid(decltype(b2)).name() << '\n'   // Base2
                  << "Object type of b1: " << typeid(b1).name() << '\n' // Derived1
                  << "Object type of b2: " << typeid(b2).name() << '\n' // Base2
                  << "size of b1: " << sizeof b1 << '\n'        // 8
                  << "size of b2: " << sizeof b2 << std::endl;  // 1
    }



總結
========================================

* const_cast
    - 控制 cv-qualification，其他轉換都不能移除 const 或 volatile
    - 不會產生額外 CPU instruction
* static_cast
    - 進行 implicit 轉換、反向 implicit 轉換、安全的 Derived 轉 Base、可能不安全的 Base 轉 Derived
    - 可能會產生額外 CPU instruction
* reinterpret_cast
    - 指標間轉換或指標數值間轉換，使用同一塊記憶體
    - 不會產生額外 CPU instruction
* dynamic_cast
    - 在 class 架構內到處轉換，並且會動態檢查轉換是否可行
    - 會產生額外 CPU instruction



參考
========================================

* `cppreference - Explicit Type Conversion <http://en.cppreference.com/w/cpp/language/explicit_cast>`_
* `cppreference - const_cast conversion <http://en.cppreference.com/w/cpp/language/const_cast>`_
* `cppreference - static_cast conversion <http://en.cppreference.com/w/cpp/language/static_cast>`_
* `cppreference - dynamic_cast conversion <http://en.cppreference.com/w/cpp/language/dynamic_cast>`_
* `cppreference - reinterpret_cast conversion <http://en.cppreference.com/w/cpp/language/reinterpret_cast>`_
* `cppreference - Objects <http://en.cppreference.com/w/cpp/language/object>`_
