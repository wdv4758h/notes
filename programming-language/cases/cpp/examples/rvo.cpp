// clang++ -std=c++14 -Wall -Wextra

#include <iostream>

class MyClass {
public:
    MyClass(int n);                         // default ctor
    MyClass(MyClass&);                      // copy ctor (@_@)
    MyClass(const MyClass&);                // copy ctor (const)
    MyClass(MyClass&&);                     // move ctor
    MyClass& operator=(MyClass&);           // copy assignment (@_@)
    MyClass& operator=(const MyClass&);     // copy assignment (const)
    MyClass& operator=(MyClass&&);          // move assignment
    ~MyClass();                             // dtor
    MyClass operator+(const MyClass&) const;    // operator+
    MyClass& operator+=(const MyClass&);        // operator+=

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

MyClass MyClass::operator+(const MyClass& rhs) const {
    std::cout << "[operator add] operator+(const MyClass&) const "
              << "[" << this << "] " << this->data
              << " + "
              << "[" << &rhs << "] " << rhs.data << std::endl;
    MyClass tmp(this->data + rhs.data);
    return tmp;
}

MyClass& MyClass::operator+=(const MyClass& rhs) {
    std::cout << "[operator add] operator+=(const MyClass&) "
              << "[" << this << "] " << this->data
              << " + "
              << "[" << &rhs << "] " << rhs.data << std::endl;
    this->data += rhs.data;
    return *this;
}

auto f1(int n) {
    std::cout << "===== f1 start =====" << std::endl;
    if (n < 1) {
        ////////////////////////////////////////
        // version 1, NRVO
        //
        // auto tmp = MyClass(n);
        //
        ////////////////////////////////////////
        // version 2, NRVO for const local

        const  auto tmp = MyClass(n);

        ////////////////////////////////////////
        std::cout << "===== f1 end   =====" << std::endl;
        return tmp;
    } else {
        ////////////////////////////////////////
        // version 1, default ctor
        //
        // auto tmp = MyClass(n) + f1(n-1);   // will call "default ctor" here, and "dtor" later
        //
        ////////////////////////////////////////
        // version 2, NRVO

        auto tmp = MyClass(n);
        tmp += f1(n-1);

        ////////////////////////////////////////
        std::cout << "===== f1 end   =====" << std::endl;
        return tmp;
    }
}

auto f2(int n) {
    std::cout << "===== f2 start =====" << std::endl;
    auto tmp = f1(n);
    // auto tmp2 = tmp + tmp;   // will call "default ctor" here, and "dtor" later
    tmp += tmp;
    std::cout << "===== f2 end   =====" << std::endl;
    return tmp;
}

int main(int argc, char *argv[]) {

    auto x = f2(5);
    std::cout << "[" << &x << "]" << std::endl;
    std::cout << x.data << std::endl;

    return 0;
}
