#include <iostream>

class Base {
public:
    virtual void f() {
        std::cout << "Base    (Virtual)" << std::endl;
    }

    void g() {
        std::cout << "Base    (Non-Virutal)" << std::endl;
    }
};

class Derived : public Base {
public:
    void f() {
        std::cout << "Derived (Virtual)" << std::endl;
    }

    void g() {
        std::cout << "Derived (Non-Virtual)" << std::endl;
    }
};

Base& func(Base& tmp) {

    // call Derived for virtual
    // call Base for non-virtual

    tmp.f();    // virtual
    tmp.g();    // non-virtual

    return tmp;
}

int main() {

    Derived foo;

    std::cout << "===== Derived" << std::endl;

    foo.f();    // Derived
    foo.g();    // Derived

    std::cout << "===== Derived with static_cast<Base>" << std::endl;

    static_cast<Base>(foo).f();     // Base
    static_cast<Base>(foo).g();     // Base

    std::cout << "===== Derived with static_cast<Base&>" << std::endl;

    static_cast<Base&>(foo).f();    // Derived
    static_cast<Base&>(foo).g();    // Base

    std::cout << "===== Derived with func1(Base&)" << std::endl;

    Derived& bar = static_cast<Derived&>(func(foo));

    std::cout << "===== Derived with static_cast<Derived&>(func1(Base&))" << std::endl;

    bar.f();    // Derived
    bar.g();    // Derived

    return 0;
}
