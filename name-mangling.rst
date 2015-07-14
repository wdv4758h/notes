========================================
Name Mangling
========================================

name mangling 又稱為 name decoration，
是程式語言中常使用的技術，
用來需要獨一無二名稱的問題。
藉由此種方式 compiler 可以提供更多的資訊給 linker。
這種需求隨著語言允許在不同 namespace 有相同名稱的東西或是不同 signatures (function overloading) 而提高。

C++
========================================

測試範例：

.. code-block:: cpp

    // mangling.cpp

    #include <cstdio>

    namespace mangled
    {
        class test
        {
        public:
            void func1()
            {
                printf("test\n");
            }
        };
    }

    class test
    {
    public:
        void func1()
        {
            printf("test\n");
        }
    };

    int main() {
        mangled::test foo;
        test bar;
        foo.func1();
        bar.func1();
        return 0;
    }


編譯：

.. code-block:: sh

    $ g++ -c mangling.cpp -o mangling.o
    $ objdump -Sr mangling.o    # without demangling
    $ objdump -CSr mangling.o   # with demangling
    $ g++ -S mangling.cpp -o mangling.s
    $ cat mangling.s

可以觀察到 ``mangled::test::func`` 變成了 ``_ZN7mangled4test5func1Ev`` ，
demangling 也可以利用 binutils 裡的 c++filt 來做，
例如：

.. code-block:: sh

    $ c++filt -n _ZN7mangled4test5func1Ev
    mangled::test::func1()
    $ c++filt -n _ZN4test5func1Ev
    test::func1()


GCC 對 C++ 做 name mangling 的一些規則：

* 所有 mangled 符號都由 "_Z" 開頭
* 巢狀名稱的話在 "_Z" 後面加上 "N" 作為開頭
* 接著為一連串 字串長度 + 名稱
* 最後面加上 "E" 作為結尾
* 最後加上 return type
    - int -> i
    - float -> f
    - void -> v


Python
========================================

在 Python 中，用雙底線開頭、零個或一個底線結尾的 class member 會做 name mangling，
可以達到某種程度 private 的效果，在用 ``dir`` 看 attribute 的時候，
可以發現符合這 pattern 的 class member 會被轉成 "_ClassName" + member name，
而在 instance 單純使用原本的 member name 來存取會發現拿不到原本 member 的值 (因為名字不同了)。

.. code-block:: python

    class Test1(object):

        __mangled_var = ":P"
        normal_var    = ":("

        def __mangled_name(self):
            print("I'm mangled     : ", self.__mangled_var)

        def normal_name(self):
            print("I'm not mangled : ", self.normal_var)

        def name(self):
            self.__mangled_name()
            self.normal_name()


    class Test2(Test1):
        __mangled_var = ":O"
        normal_var    = ":|"

    ########################################

    print("=" * 10)

    t1 = Test1()
    print(dir(t1))
    t1.name()
    t1.normal_var     = ":(("
    t1.__mangled_var  = ":PP"
    t1.name()

    print("=" * 10)

    t2 = Test2()
    print(dir(t2))
    t2.name()
    t2.normal_var     = ":(("
    t2.__mangled_var  = ":PP"
    t2.name()

    print("=" * 10)

    ########################################

    ''' Output
    ==========
    ['_Test1__mangled_name', '_Test1__mangled_var', '__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'name', 'normal_name', 'normal_var']
    I'm mangled     :  :P
    I'm not mangled :  :(
    I'm mangled     :  :P
    I'm not mangled :  :((
    ==========
    ['_Test1__mangled_name', '_Test1__mangled_var', '_Test2__mangled_var', '__class__', '__delattr__', '__dict__', '__dir__', '__doc__', '__eq__', '__format__', '__ge__', '__getattribute__', '__gt__', '__hash__', '__init__', '__le__', '__lt__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', 'name', 'normal_name', 'normal_var']
    I'm mangled     :  :P
    I'm not mangled :  :|
    I'm mangled     :  :P
    I'm not mangled :  :((
    ==========
    '''

注意的點：

* Test1 的 class member "__mangled_name" 變成 "_Test1__mangled_name"
* Test1 的 class member "__mangled_var" 變成 "_Test1__mangled_var"
* instance 用 .__mangled_var 無法改到原本的 member，要用 ._Test1__manbled_var 才可以 access 到
* Test2 繼承 Test1 後，用 __mangled_var 宣告新的 member 會跟原本的隔開，不會蓋到、影響到原本 access 的 function


Reference
========================================

* `Wikipedia - Name Mangling <https://en.wikipedia.org/wiki/Name_mangling>`_
