// clang++ -std=c++14 -Wall -Wextra ctor-dtor.cpp

#include <iostream>

class MyClass {
public:
    MyClass();                              // default ctor
    MyClass(MyClass&);                      // copy ctor (@_@)
    MyClass(const MyClass&);                // copy ctor (const)
    MyClass(MyClass&&);                     // move ctor
    MyClass& operator=(MyClass&);           // copy assignment (@_@)
    MyClass& operator=(const MyClass&);     // copy assignment (const)
    MyClass& operator=(MyClass&&);          // move assignment
    ~MyClass();                             // dtor
};

MyClass::MyClass() {
    std::cout << "[default ctor] MyClass()" << std::endl;
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
    std::cout << "[dtor        ] ~MyClass()" << std::endl;
}


void line(const char* data = "") {
    static unsigned int counter = 0;
    std::cout << std::endl << "========== Case " << ++counter << " | " << data << std::endl;
}


int main(int argc, char *argv[]) {

    ////////////////////////////////////////

    line("nothing");

    {
        MyClass x;
    }

    line("prvalue");

    {
        MyClass x = MyClass();
    }

    line("prvalue");

    {
        const MyClass x = MyClass();
    }

    line("prvalue");

    {
        auto x = MyClass();
    }

    line("prvalue");

    {
        const auto x = MyClass();
    }

    ////////////////////////////////////////

    line("lvalue");

    {
        const auto x = MyClass();
        MyClass y(x);
    }

    line("lvalue");

    {
        const auto x = MyClass();
        const MyClass y(x);
    }

    line("lvalue");

    {
        const auto x = MyClass();
        auto y(x);
    }

    line("lvalue");

    {
        const auto x = MyClass();
        const auto y(x);
    }

    line("lvalue, move const won't effect");

    {
        const auto x = MyClass();
        auto y(std::move(x));
    }

    line("lvalue, move const won't effect");

    {
        const auto x = MyClass();
        const auto y(std::move(x));
    }

    line("prvalue");

    {
        const auto y((MyClass()));
    }

    ////////////////////////////////////////

    line("lvalue");

    {
        auto x = MyClass();
        MyClass y(x);
    }

    line("lvalue");

    {
        auto x = MyClass();
        const MyClass y(x);
    }

    line("lvalue");

    {
        auto x = MyClass();
        auto y(x);
    }

    line("lvalue");

    {
        auto x = MyClass();
        const auto y(x);
    }

    line("lvalue to xvalue");

    {
        auto x = MyClass();
        auto y(std::move(x));
    }

    line("lvalue to xvalue");

    {
        auto x = MyClass();
        const auto y(std::move(x));
    }

    line("prvalue");

    {
        auto y((MyClass()));
    }

    line("lvalue to xvalue");

    {
        auto x = MyClass();
        const auto y = std::move(x);
    }

    line("lvalue");

    {
        auto x = MyClass();
        const auto y = x;
    }

    ////////////////////////////////////////

    line("lvalue");

    {
        auto x = MyClass();
        auto y = MyClass();
        x = y;
    }

    line("prvalue");

    {
        auto x = MyClass();
        x = MyClass();
    }

    line("lvalue to xvalue");

    {
        auto x = MyClass();
        auto y = MyClass();
        y = std::move(x);
    }

    ////////////////////////////////////////

    line("lvalue");

    {
        const auto x = MyClass();
        auto y = MyClass();
        y = x;
    }

    line("lvalue, move const won't effect");

    {
        const auto x = MyClass();
        auto y = MyClass();
        y = std::move(x);
    }

    ////////////////////////////////////////

    return 0;
}
