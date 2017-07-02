========================================
Design Pattern
========================================


.. contents:: 目錄


Creational
========================================

Abstract Factory
------------------------------


Builder
------------------------------

Rust 對於 Builder Pattern 的支援可以直接使用第三方的 `Builder Pattern Derive <https://github.com/colin-kiegel/rust-derive-builder>`_ 。

安裝：

.. code-block:: sh

    $ cargo add derive_builder

使用：

.. code-block:: rust

    #[macro_use]
    extern crate derive_builder;

    #[derive(Default, Builder, Debug)]
    struct Channel {
        token: i32,
        special_info: i32,
        // .. a whole bunch of other fields ..
    }

    fn main() {
        // builder pattern
        let ch = ChannelBuilder::default()
                                .special_info(42u8)
                                .token(19124)
                                .build()
                                .unwrap();
        println!("{:?}", ch);
    }


Factory Method
------------------------------


Object Pool
------------------------------


Prototype
------------------------------


Simple Factory
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


Private Class Data
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


Null Object
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
