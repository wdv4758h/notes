#include <iostream>

class Base {
public:
    void func() { std::cout << "Base\n"; }
};

class Derived1 : public Base {
public:
    virtual void func() { printf("Derived1\n"); }
};

class Derived2 : public Derived1 {
public:
    void func() { printf("Derived2\n"); }    // already virtual since Derived1
};

int main() {
    auto derived1 = Derived1 {};
    auto derived2 = Derived2 {};
    auto d1b    = static_cast<Base&>    (derived1);
    auto d2d1   = static_cast<Derived1&>(derived2);
    auto pd1b   = static_cast<Base*>    (&derived1);
    auto pd2d1  = static_cast<Derived1*>(&derived2);

    d1b.func();     // Base
    d2d1.func();    // Derived1
    pd1b->func();   // Base
    pd2d1->func();  // Derived2
}
