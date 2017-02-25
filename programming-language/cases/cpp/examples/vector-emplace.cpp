#include <iostream>
#include <vector>

using namespace std;

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

MyClass::MyClass(const MyClass& other)
    : data(other.data), origin(other.origin) {
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

vector<MyClass> double_values (const vector<MyClass>& v)
{
    std::cout << "=== start double ===" << '\n';
    vector<MyClass> new_values;
    new_values.reserve(v.size());
    for (auto itr = v.begin(), end_itr = v.end(); itr != end_itr; ++itr )
    {
        new_values.emplace_back(2 * itr->data);
    }
    std::cout << "=== end double ===" << '\n';
    return new_values;
}

int main()
{
    vector<MyClass> v;
    std::cout << "=== start initial ===" << '\n';
    for ( int i = 0; i < 10; i++ )
    {
        v.emplace_back(i);  // vector will keep resizing
    }

    for (auto& i: v) {
        std::cout << i.data << " ";
    }
    std::cout << '\n';

    std::cout << "=== end initial  ===" << '\n';
    std::cout << "=== call double ===" << '\n';
    v = double_values(v);
    std::cout << "=== end ===" << '\n';
}
