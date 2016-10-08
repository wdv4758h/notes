#include <iostream>

template<class T>
class Base {
public:
    virtual void f() {
        std::cout << "Base    (Virtual)" << std::endl;
    }

    void g() {
        std::cout << "Base    (Non-Virutal)" << std::endl;
    }

    void h() {
        // simulated dynamic binding
        // use this instead of virtual function to avoid the cost of dynamic polymorphism
        // no virtual table is needed for this function
        static_cast<T*>(this)->g();
    }
};

class Derived : public Base<Derived> {  // CRTP (curiously recurring template pattern) (F-bound polymorphism)
public:
    void f() {
        std::cout << "Derived (Virtual)" << std::endl;
    }

    void g() {
        std::cout << "Derived (Non-Virtual)" << std::endl;
    }
};

template<class T>
T& func(T& tmp) {

    // call Derived for virtual
    // call Base for non-virtual

    tmp.f();    // virtual
    tmp.g();    // non-virtual
    tmp.h();    // non-virtual

    return tmp;
}

int main() {

    Derived foo;

    std::cout << "===== Derived" << std::endl;

    foo.f();    // Derived
    foo.g();    // Derived
    foo.h();    // Derived

    std::cout << "===== Derived with static_cast<Derived::Base>" << std::endl;

    static_cast<Derived::Base>(foo).f();     // Base
    static_cast<Derived::Base>(foo).g();     // Base
    static_cast<Derived::Base>(foo).h();     // Derived

    std::cout << "===== Derived with static_cast<Derived::Base&>" << std::endl;

    static_cast<Derived::Base&>(foo).f();    // Derived
    static_cast<Derived::Base&>(foo).g();    // Base
    static_cast<Derived::Base&>(foo).h();    // Derived

    std::cout << "===== Derived with func1(T&)" << std::endl;

    Derived& bar = func(foo);

    std::cout << "===== Derived with T func1(T&)" << std::endl;

    bar.f();    // Derived
    bar.g();    // Derived
    bar.h();    // Derived

    return 0;
}
