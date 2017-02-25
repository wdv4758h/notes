#include <iostream>
#include <memory>
#include <vector>

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
    MyClass& operator=(int);                // literal assignment
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

MyClass& MyClass::operator=(int) {
    std::cout << "[literal     ] operator=(int)" << std::endl;
    return *this;
}

MyClass::~MyClass() {
    std::cout << "[dtor        ] ~MyClass() "
              << "[" << this << "] " << this->origin << " | " << this->data
              << std::endl;
}


////////////////////////////////////////

template<typename T>
void func(std::vector<MyClass>& v, T&& value) {
    v.emplace_back(std::forward<T>(value));
}

template<typename T>
void func2(std::vector<MyClass>& v, T&& value) {
    v[0] = std::forward<T>(value);
}

int main() {
    std::vector<MyClass> v;
    v.reserve(10);
    std::cout << "=== x" << std::endl;
    auto x = MyClass{3};
    func(v, x);
    func2(v, x);
    std::cout << "=== MyClass" << std::endl;
    func(v, MyClass{2});
    func2(v, MyClass{2});
    std::cout << "=== 1" << std::endl;
    func(v, 1);
    func2(v, 1);
    std::cout << "===" << std::endl;
    return 0;
}
