#include <iostream>

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

    void func(MyClass& i, MyClass& j);

    int data = 42;
};

MyClass::MyClass(int n) : data(n) {
    std::cout << "[default ctor] MyClass() "
              << "[" << this << "] "
              << this->data << std::endl;
}

MyClass::MyClass(MyClass& rhs) {
    std::cout << "[copy ctor   ] MyClass(MyClass&)" << std::endl;
    this->data = rhs.data;
    this->data = rhs.data;
}

MyClass::MyClass(const MyClass& rhs) {
    std::cout << "[copy ctor c ] MyClass(const MyClass&)" << std::endl;
    this->data = rhs.data;
    this->data = rhs.data;
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
              << "[" << this << "] " << this->data
              << std::endl;
}


////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, MyClass const& m) {
    return os << m.data;
}

void MyClass::func(MyClass& i, MyClass& j)
{
    std::cout << "=====" << '\n';
    // ok: by-reference capture default
    [&]     { std::cout << i << " " << j << '\n'; }();

    std::cout << "=====" << '\n';
    // ok: by-copy capture default
    [=]     { std::cout << i << " " << j << '\n'; }();

    std::cout << "=====" << '\n';
    // ok: by-reference capture, except i is captured by copy
    [&, i]  { std::cout << i << " " << j << '\n'; }();

    std::cout << "=====" << '\n';
    // ok: by-copy capture, except i is captured by reference
    [=, &i] { std::cout << i << " " << j << '\n'; }();

    std::cout << "=====" << '\n';
    // error: '&' cannot precede a capture when the capture default is '&'
    //        (by-reference capture when by-reference is the default)
    // [&, &i]{ std::cout << i << " " << j << '\n'; };

    std::cout << "=====" << '\n';
    // error: 'this' cannot be explicitly captured when the capture default is '='
    //        (this when = is the default)
    // [=, this]{ std::cout << i << '\n' };

    std::cout << "=====" << '\n';
    // ok: captures the enclosing MyClass by copy (C++17)
    [=, *this]  { std::cout << i << " " << j << " " << this->data << '\n'; }();

    std::cout << "=====" << '\n';
    // ok: captures the enclosing MyClass by copy (C++17)
    [&, *this]  { std::cout << i << " " << j << " " << this->data << '\n'; }();

    std::cout << "=====" << '\n';
    // ok: captures the enclosing MyClass by reference
    [&, this]   { std::cout << i << " " << j << " " << this->data << '\n'; }();

    std::cout << "=====" << '\n';
    // error: i repeated
    // [i, i]{ std::cout << i << '\n' };

    std::cout << "=====" << '\n';
    // error: "this" repeated (C++17)
    // [this, *this]{ std::cout << this->data << '\n' };
}

int main() {
    auto x = MyClass { 42 };
    auto a = MyClass { 1 };
    auto b = MyClass { 2 };
    x.func(a, b);
    return 0;
}
