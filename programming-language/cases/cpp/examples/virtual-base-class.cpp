#include <iostream>

class MyClass {
public:
    MyClass();
    MyClass(int n);                         // default ctor
    MyClass(MyClass&);                      // copy ctor (@_@)
    MyClass(const MyClass&);                // copy ctor (const)
    MyClass(MyClass&&);                     // move ctor
    MyClass& operator=(MyClass&);           // copy assignment (@_@)
    MyClass& operator=(const MyClass&);     // copy assignment (const)
    MyClass& operator=(MyClass&&);          // move assignment
    MyClass& operator=(int);                // literal assignment
    ~MyClass();                             // dtor

    int data = 42;
    const int origin = 42;
};

MyClass::MyClass() {
    std::cout << "[default ctor] MyClass() "
              << "[" << this << "] "
              << this->data << std::endl;
}

MyClass::~MyClass() {
    std::cout << "[dtor        ] ~MyClass() "
              << "[" << this << "] " << this->origin << " | " << this->data
              << std::endl;
}

class A : public MyClass {};
class B : public MyClass {};
class C : public MyClass {};
class D : public A, public B, public C {
public:
    void func() {
        A::data = 1;
        B::data = 2;
        C::data = 3;
        std::cout << A::data << " "
                  << B::data << " "
                  << C::data << " "
                  << std::endl;
    }
};

class VA : virtual public MyClass {};
class VB : public virtual MyClass {};
class VC : public MyClass {};
class VD : VA, VB, VC {
public:
    void func() {
        VA::data = 1;
        VB::data = 2;
        VC::data = 3;
        std::cout << VA::data << " "
                  << VB::data << " "
                  << VC::data << " "
                  << std::endl;
    }
};


int main() {
    std::cout << "=== non-virtual base" << std::endl;
    {
        auto x = D {};
        x.func();
    }
    std::cout << "=== tow virtual base and one non-virtual base" << std::endl;
    {
        auto y = VD {};
        y.func();
    }
    return 0;
}
