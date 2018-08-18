==============================================
動態語言實做 (Dynamic Language Implementation)
==============================================


.. contents:: 目錄


動態語言特性介紹
========================================



Virtual Machine 種類
========================================

Stack
------------------------------

Register
------------------------------


Parser
========================================



Bytecode 設計
========================================



Garbage Collection
========================================



JIT 優化
========================================



實例研究
========================================

JavaScript - V8
------------------------------


JavaScript - SpiderMonkey
------------------------------


Python - PyPy
------------------------------


Lua - LuaJIT
------------------------------



參考
========================================

* `Virtual Machines Summer School 2016 <http://soft-dev.org/events/vmss16/>`_
* `Programming Language Implementation Summer School 2017 <https://pliss2017.github.io/index.html>`_
* `Virtual Machine Meetup <https://vmmeetup.github.io/>`_
* `Managed Languages & Runtimes 2016 <http://pppj16.inf.usi.ch/>`_
* `Managed Languages & Runtimes 2017 <http://d3s.mff.cuni.cz/conferences/manlang17/>`_
* `Idioms of Dynamic Languages <http://willcrichton.net/notes/idioms-of-dynamic-languages/>`_
    - 討論動態語言的特性，為什麼會覺得動態語言比較容易上手，以及靜態語言如何達到類似的彈性
    - Dynamic heterogeneous data structures
        + Subtype polymorphism
        + Any types
        + Trait polymorphism
        + Sum types
            * named vs. anonymous
            * declared vs. inferred
            * matched vs. casted
    - Ad-hoc interfaces
        + Subtype polymorphism
        + Trait polymorphism
        + Compile-time metaprogramming
    - Reflection
    - Exceptions
    - Partial programs
