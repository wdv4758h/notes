#include <memory>       // smart pointer
#include <iostream>
#include <array>


class MyClass {
public:
    MyClass();      // default ctor
    ~MyClass();     // dtor
};

MyClass::MyClass() {
    std::cout << "[default ctor] MyClass()" << std::endl;
}

MyClass::~MyClass() {
    std::cout << "[dtor        ] ~MyClass()" << std::endl;
}


MyClass func1() {   // allocate on Stack, will be RVO to caller stack
    auto foo = MyClass();
    std::cout << &foo << std::endl;
    return foo;
}

MyClass* func2() {  // need explicit delete, or it will have memory leak
    auto foo = new MyClass();
    std::cout << foo << std::endl;
    return foo;
}

auto func3() {      // unique_ptr, delete object automatically when there is no owner
    auto foo = std::make_unique<MyClass>();     // make_unique is C++14
    std::cout << foo.get() << std::endl;
    return foo;
}

auto func4() {      // shared_ptr, delete object automatically when there is no sharer
    auto foo = std::make_shared<MyClass>();     // make_shared is C++11
    std::cout << foo.get() << std::endl;
    return foo;
}

template<typename T>
void share_with_you(std::shared_ptr<T> ptr) {
    std::cout << "Share Count: " << ptr.use_count() << std::endl;
}


int main() {

    std::cout << "=== Allocate on Stack ===" << std::endl;
    {
        auto foo = func1();
        std::cout << &foo << std::endl;
    }

    std::cout << "=== Allocate on Heap (without explicit delete) ===" << std::endl;
    {
        auto foo = func2();
        std::cout << foo << std::endl;
    }

    std::cout << "=== Allocate on Heap (unique_ptr) ===" << std::endl;
    {
        auto foo = func3();
        std::cout << foo.get() << std::endl;
    }

    std::cout << "=== Allocate on Heap (shared_ptr) ===" << std::endl;
    {
        auto foo = func4();
        std::cout << foo.get() << std::endl;
        std::cout << "Share Count: " << foo.use_count() << std::endl;
        share_with_you(foo);
        std::cout << "Share Count: " << foo.use_count() << std::endl;
    }
    std::cout << "=== Allocate on Heap (return shared_ptr, assign weak_ptr) ===" << std::endl;
    {
        std::weak_ptr<MyClass> foo = func4();   // this will not keep the object
        std::cout << foo.use_count() << std::endl;
        auto ptr = foo.lock();
        if (ptr == nullptr) {   // or foo.expired()
            std::cout << "I don't have object :(" << std::endl;
        }
    }

    std::cout << "=== shared_ptr and array ===" << std::endl;
    {
        std::shared_ptr<MyClass> foo(new MyClass[3],
                                     [](MyClass* ptr){ delete [] ptr; });
    }
    std::cout << "=== shared_ptr and array ===" << std::endl;
    {
        auto foo = std::make_shared<std::array<MyClass, 3>>();
    }

    return 0;
}
