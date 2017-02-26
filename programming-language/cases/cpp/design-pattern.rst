========================================
Design Pattern
========================================


.. contents:: 目錄


Creational
========================================

Abstract Factory
------------------------------

Abstract Factory 實際上就是 Factories 的 Factory，
把多個相關的 Factory 包起來形成 Factory。

藉由 Abstract Factory 可以把多個相關的 Factory 抽象化，
依照需求來製造出不同群要使用的類別，
但是使用者只要透過統一的界面來操作即可，
不需要知道底下在使用的類別究竟是哪一個。


Rust 範例：

.. code-block:: rust

    // Rust

    ////////////////////////////////////////

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
        virtual void descripten();
        ~Door() {}
    };

    class DoorFittingExpert {
    public:
        virtual void descripten();
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
        void descripten() override { std::cout << "A wooden door!" << '\n'; }
        ~WoodenDoor() {}
    };

    class IronDoor : public Door {
    public:
        void descripten() override { std::cout << "A iron door!" << '\n'; }
        ~IronDoor() {}
    };

    ////////////////////////////////////////

    class Carpenter : public DoorFittingExpert {
    public:
        void descripten() override { std::cout << "I can only fit wooden door!" << '\n'; }
        ~Carpenter() {}
    };

    class Welder : public DoorFittingExpert {
    public:
        void descripten() override { std::cout << "I can only fit iron door!" << '\n'; }
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
            door.descripten();
            expert.descripten();
        }
        {
            auto factory = IronDoorFactory();
            auto door = factory.new_door();
            auto expert = factory.new_expert();
            door.descripten();
            expert.descripten();
        }
        {
            auto factory = WoodenDoorFactory();
            auto door   = factory.new_door();
            auto expert = factory.new_expert();
            auto pdoor   = static_cast<Door*>             (&door);
            auto pexpert = static_cast<DoorFittingExpert*>(&expert);
            pdoor->descripten();
            pexpert->descripten();
        }
        {
            auto factory = IronDoorFactory();
            auto door   = factory.new_door();
            auto expert = factory.new_expert();
            auto pdoor   = static_cast<Door*>             (&door);
            auto pexpert = static_cast<DoorFittingExpert*>(&expert);
            pdoor->descripten();
            pexpert->descripten();
        }
        return 0;
    }


Python 範例：

.. code-block:: python

    # TODO


Builder
------------------------------

Factory Method
------------------------------

Prototype
------------------------------

Singleton
------------------------------


Structural
========================================

Adapter
------------------------------

Bridge
------------------------------

Composite
------------------------------

Decorator
------------------------------

Facade
------------------------------

Flyweight
------------------------------

Proxy
------------------------------



Behavioral
========================================

Chain of Responsibility
------------------------------

Command
------------------------------

Interpreter
------------------------------

Iterator
------------------------------

Mediator
------------------------------

Memento
------------------------------

Observer
------------------------------

State
------------------------------

Strategy
------------------------------

Template Method
------------------------------

Visitor
------------------------------



Concurrency
========================================



Architectural
========================================



參考
========================================

* [GitHub] `Design Patterns for Humans™ - An ultra-simplified explanation <https://github.com/kamranahmedse/design-patterns-for-humans>`_
* [GitHub] `python-patterns - A collection of design patterns/idioms in Python <https://github.com/faif/python-patterns>`_
* `Design Patterns & Refactoring <https://sourcemaking.com/>`_
* `Category Pattern <http://wiki.c2.com/?CategoryPattern>`_
* `Anti Patterns Catalog <http://wiki.c2.com/?AntiPatternsCatalog>`_
