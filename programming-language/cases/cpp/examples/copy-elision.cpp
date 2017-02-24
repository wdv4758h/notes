#include <iostream>
#include <memory>

class MyClass {
public:
    constexpr MyClass(){};
    MyClass(int n);                         // default ctor
    MyClass(MyClass&);                      // copy ctor (@_@)
    MyClass(const MyClass&);                // copy ctor (const)
    MyClass(MyClass&&);                     // move ctor
    MyClass& operator=(MyClass&);           // copy assignment (@_@)
    MyClass& operator=(const MyClass&);     // copy assignment (const)
    MyClass& operator=(MyClass&&);          // move assignment
    ~MyClass();                             // dtor

    int data = 42;
    const int origin = 42;
};

MyClass::MyClass(int n) : data(n), origin(n) {
    std::cout << "[default ctor] MyClass() "
              << "[" << this << "] "
              << this->data << std::endl;
}

MyClass::MyClass(MyClass&) {
    std::cout << "[copy ctor   ] MyClass(MyClass&)" << std::endl;
}

MyClass::MyClass(const MyClass&) {
    std::cout << "[copy ctor c ] MyClass(const MyClass&)" << std::endl;
}

MyClass::MyClass(MyClass&&) {
    std::cout << "[move ctor   ] MyClass(MyClass&&)" << std::endl;
}

MyClass& MyClass::operator=(MyClass&) {
    std::cout << "[copy assign ] operator=(MyClass&)" << std::endl;
    return *this;
}

MyClass& MyClass::operator=(const MyClass&) {
    std::cout << "[copy assign ] operator=(const MyClass&)" << std::endl;
    return *this;
}

MyClass& MyClass::operator=(MyClass&&) {
    std::cout << "[move assign ] operator=(MyClass&&)" << std::endl;
    return *this;
}

MyClass::~MyClass() {
    std::cout << "[dtor        ] ~MyClass() "
              << "[" << this << "] " << this->origin << " | " << this->data
              << std::endl;
}


////////////////////////////////////////

MyClass f() { return MyClass { 42 }; }

MyClass g() {
    // copy elision when initializing from a temporary, spec in C++17
    MyClass x = MyClass { 42 };
    return x;   // NRVO or move, not guaranteed in C++17
}

void h(MyClass foo) {
    std::cout << foo.data << '\n';
}

int main() {
    {   // copy elision
        // prvalue of same type, spec in C++17
        // result: default -> dtor
        auto x = MyClass ( MyClass ( MyClass ( 42 ) ) );
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // prvalue of same type, spec in C++17
        // result: default -> dtor
        auto x = MyClass { MyClass { MyClass { 42 } } };
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // prvalue and return type is same type, spec in C++17
        // result: default -> dtor
        auto x = f();
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // result: default -> dtor
        auto x = g();
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // prvalue and return type is same type, spec in C++17
        // result: default -> dtor
        auto x = new MyClass(f());
        delete x;
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // prvalue and return type is same type, spec in C++17
        // result: default -> dtor
        auto x = new MyClass{f()};
        delete x;
    }
    std::cout << "=====" << '\n';
    {   // copy elision
        // result: default -> dtor
        h(g());
    }

    return 0;
}
