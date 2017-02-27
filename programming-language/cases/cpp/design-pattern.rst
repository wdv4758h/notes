========================================
Design Pattern
========================================


.. contents:: 目錄


Creational
========================================

Creational Design Pattern 顧名思義就是與物件建立相關，
可能是提供比較方便的建立方式，
或者是對物件的建立設定一些限制。


Simple Factory
------------------------------

「目標是把物件建立的複雜性抽象化掉，
提供一個簡單的物件建立方式」


Simple Factory 就是一個函式或物件，
可以用來製造另外一個物件，
可以把比較麻煩的物件建立流程包裝起來，
可能是以一般 Function 或 Static Member Function 的形式。


Rust 範例：

.. code-block:: rust

    trait Door {
        fn description(&self);
    }

    ////////////////////////////////////////

    #[derive(Default)]
    struct WoodenDoor;

    #[derive(Default)]
    struct IronDoor;

    impl Door for WoodenDoor {
        fn description(&self) { println!("A wooden door!"); }
    }

    impl Door for IronDoor {
        fn description(&self) { println!("A iron door!"); }
    }

    ////////////////////////////////////////

    fn door_factory(material: &str) -> Option<Box<Door>> {
        match material {
            "wood" => Some(Box::new(WoodenDoor{})),
            "iron" => Some(Box::new(IronDoor{})),
            _ => None,
        }
    }

    fn main() {
        {
            let door = door_factory("wood").unwrap();
            door.description();
        }
        {
            let door = door_factory("iron").unwrap();
            door.description();
        }
    }


C++ 範例：

.. code-block:: cpp

    #include <iostream>
    #include <memory>

    ////////////////////////////////////////

    class Door {
    public:
        virtual void description() {};
        ~Door() {}
    };

    ////////////////////////////////////////

    class WoodenDoor : public Door {
    public:
        void description() { std::cout << "A wooden door!" << std::endl; }
        ~WoodenDoor() {}
    };

    class IronDoor : public Door {
    public:
        void description() { std::cout << "A iron door!" << std::endl; }
        ~IronDoor() {}
    };

    ////////////////////////////////////////

    class DoorFactory {
    public:
        static std::unique_ptr<Door> make_door(std::string material) {
            if (material == "wood") {
                return std::make_unique<WoodenDoor>();
            } else if (material == "iron") {
                return std::make_unique<IronDoor>();
            }
            return std::make_unique<WoodenDoor>();
        }
    };

    int main() {
        {
            auto door = DoorFactory::make_door("wood");
            door->description();
        }
        {
            auto door = DoorFactory::make_door("iron");
            door->description();
        }
        return 0;
    }


Python 範例：

.. code-block:: python

    # TODO


Factory Method
------------------------------

「目標是把物件建立的複雜性交由 class 自己處理，
使用者只要使用提供好的操作界面即可，
專住在真正的行為操作」



Abstract Factory
------------------------------

「工廠們的工廠，
把數個相關或有依賴性的工廠綁在一起」


Abstract Factory 實際上就是 Factories 的 Factory，
把多個相關的 Factory 包起來形成 Factory。

藉由 Abstract Factory 可以把多個相關的 Factory 抽象化，
依照需求來製造出不同群要使用的類別，
但是使用者只要透過統一的界面來操作即可，
不需要知道底下在使用的類別究竟是哪一個。


Rust 範例：

.. code-block:: rust

    trait Door {
        fn description(&self);
    }

    trait DoorFittingExpert {
        fn description(&self);
    }

    trait DoorAbstractFactory<D: Door + Default, E: DoorFittingExpert + Default> {
        fn new_door(&self) -> D { Default::default() }
        fn new_expert(&self) -> E { Default::default() }
    }

    ////////////////////////////////////////

    #[derive(Default)]
    struct WoodenDoor;

    #[derive(Default)]
    struct IronDoor;

    impl Door for WoodenDoor {
        fn description(&self) { println!("A wooden door!"); }
    }

    impl Door for IronDoor {
        fn description(&self) { println!("A iron door!"); }
    }

    ////////////////////////////////////////

    #[derive(Default)]
    struct Carpenter;

    #[derive(Default)]
    struct Welder;

    impl DoorFittingExpert for Carpenter {
        fn description(&self) { println!("I can only fit wooden door!"); }
    }

    impl DoorFittingExpert for Welder {
        fn description(&self) { println!("I can only fit iron door!"); }
    }

    ////////////////////////////////////////

    struct WoodenDoorFactory;
    struct IronDoorFactory;

    impl DoorAbstractFactory<WoodenDoor, Carpenter> for WoodenDoorFactory {}
    impl DoorAbstractFactory<IronDoor, Welder> for IronDoorFactory {}

    fn main() {
        {
            let factory = WoodenDoorFactory{};
            let door = factory.new_door();
            let expert = factory.new_expert();
            door.description();
            expert.description();
        }
        {
            let factory = IronDoorFactory{};
            let door = factory.new_door();
            let expert = factory.new_expert();
            door.description();
            expert.description();
        }
    }


C++ 範例：

.. code-block:: cpp

    #include <iostream>

    ////////////////////////////////////////

    class Door {
    public:
        virtual void description();
        ~Door() {}
    };

    class DoorFittingExpert {
    public:
        virtual void description();
        ~DoorFittingExpert() {}
    };

    template<typename Door, typename Expert>
    class DoorAbstractFactory {
    public:
        Door new_door() { return Door {}; }
        Expert new_expert() { return Expert {}; }
    };

    ////////////////////////////////////////

    class WoodenDoor : public Door {
    public:
        void description() override { std::cout << "A wooden door!" << '\n'; }
        ~WoodenDoor() {}
    };

    class IronDoor : public Door {
    public:
        void description() override { std::cout << "A iron door!" << '\n'; }
        ~IronDoor() {}
    };

    ////////////////////////////////////////

    class Carpenter : public DoorFittingExpert {
    public:
        void description() override { std::cout << "I can only fit wooden door!" << '\n'; }
        ~Carpenter() {}
    };

    class Welder : public DoorFittingExpert {
    public:
        void description() override { std::cout << "I can only fit iron door!" << '\n'; }
        ~Welder() {}
    };

    ////////////////////////////////////////

    using WoodenDoorFactory = DoorAbstractFactory<WoodenDoor, Carpenter>;
    using IronDoorFactory = DoorAbstractFactory<IronDoor, Welder>;


    int main() {
        {
            auto factory = WoodenDoorFactory();
            auto door = factory.new_door();
            auto expert = factory.new_expert();
            door.description();
            expert.description();
        }
        {
            auto factory = IronDoorFactory();
            auto door = factory.new_door();
            auto expert = factory.new_expert();
            door.description();
            expert.description();
        }
        {
            auto factory = WoodenDoorFactory();
            auto door   = factory.new_door();
            auto expert = factory.new_expert();
            auto pdoor   = static_cast<Door*>             (&door);
            auto pexpert = static_cast<DoorFittingExpert*>(&expert);
            pdoor->description();
            pexpert->description();
        }
        {
            auto factory = IronDoorFactory();
            auto door   = factory.new_door();
            auto expert = factory.new_expert();
            auto pdoor   = static_cast<Door*>             (&door);
            auto pexpert = static_cast<DoorFittingExpert*>(&expert);
            pdoor->description();
            pexpert->description();
        }
        return 0;
    }


Python 範例：

.. code-block:: python

    # TODO


Builder
------------------------------

「目標是提供客製化物件的方式，
但是又要避免讓物件建立複雜化，
所以提供額外的特製 method 來操作」


使用上看起來會是建立一個基本的物件後，
再利用 method 來調整相關屬性。


Rust 範例：

.. code-block:: rust

    let matches = App::new("MyApp")
                      .version("1.0")
                      .author("Kevin K. <kbknapp@gmail.com>")
                      .about("Does awesome things")
                      .args_from_usage("-c, --config=[FILE] 'Sets a custom config file'
                                       <output> 'Sets an optional output file'
                                       -d... 'Turn debugging information on'")
                      .subcommand(SubCommand::with_name("test")
                                             .about("does testing things")
                                             .arg_from_usage("-l, --list 'lists test values'"))
                      .get_matches();


實際使用案例：

* `clap-rs <https://github.com/kbknapp/clap-rs/blob/master/examples/01a_quick_example.rs>`_


Prototype
------------------------------

「目標是複製另外一個物件來建立物件」


Singleton
------------------------------

「目標是確保某個 class 只會有一個 instance 存在」



Structural
========================================

Adapter
------------------------------

「目標是包裝現有的物件來讓他符合另外一個界面」


Bridge
------------------------------

「目標是把實做細節拆分到另外的物件身上」


Composite
------------------------------

「目標是讓操作多個物件跟操作單一個物件一樣方便」


Decorator
------------------------------

「藉由額外的包裝來動態地改變物件的行為，提供一個擴充過的界面」


Facade
------------------------------

「目標是為複雜的系統提供比較簡單的包裝以便於操作」


Flyweight
------------------------------

「目標是藉由共享相似的物件來減少計算的使用和計算的消耗」


Proxy
------------------------------

「目標是藉由包裝來做額外的控制，提供外觀相似但內部有額外邏輯的界面」



Behavioral
========================================

Chain of Responsibility
------------------------------

「把一連串可能可以處理的物件串起來，依序嘗試操作，直到找到可行的方案」


Command
------------------------------

「目標是把物件的操作包裝起來，
以便讓使用者可以不用知道太多訊息，
讓內部邏輯跟操作可以完全分開」


Command 要做的是把物件的操作包裝起來，
藉此可以把 client 和處理的 reciver 分開，
讓使用者可以透過統一的界面來執行需要的行為，
也可以拿來實做 transaction 的系統。



Interpreter
------------------------------

「」


Iterator
------------------------------

「目標是在不用知道資料結構細節的狀況下，遍歷容器內的所有物件」


Mediator
------------------------------

「」


Memento
------------------------------

「」


Observer
------------------------------

「」


State
------------------------------

「」


Strategy
------------------------------

「」


Template Method
------------------------------

「」


Visitor
------------------------------

「」



Concurrency
========================================



Architectural
========================================



參考
========================================

* [GitHub] `Design Patterns for Humans™ - An ultra-simplified explanation <https://github.com/kamranahmedse/design-patterns-for-humans>`_
* [GitHub] `python-patterns - A collection of design patterns/idioms in Python <https://github.com/faif/python-patterns>`_
* [GitHub] `Rust Design Patterns <https://github.com/rust-unofficial/patterns>`_
* [GitHub] `Design Patterns implemented in Java <https://github.com/iluwatar/java-design-patterns>`_
* [GitHub] `Design Patterns PHP <https://github.com/domnikl/DesignPatternsPHP>`_
* [GitHub] `Design Patterns implemented in Swift 3.0 <https://github.com/ochococo/Design-Patterns-In-Swift>`_
* `Design Patterns & Refactoring <https://sourcemaking.com/>`_
* `Category Pattern <http://wiki.c2.com/?CategoryPattern>`_
* `Anti Patterns Catalog <http://wiki.c2.com/?AntiPatternsCatalog>`_
