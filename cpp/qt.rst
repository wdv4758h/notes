========================================
Qt
========================================


QVariant 實作
========================================


在 C++ 中變數的 type 需要在 compile time 時知道，
但是有些情況是只能在 runtime 才能知道 type 的，
例如從 database 取出一個值，
此時無法在 compile time 知道拿到的 type，
所以會需要一個方式來儲存所有的 type。

QVariant 目前佔 16 bytes，
主要為一個 union 內包含 ``primitive types (int, float, ...) + QObject pointer + void pointer (for non-QObject & non-primitive type)`` 取最大的為 8 bytes，其他還有 30 bits 的 type info，2 bit 的 flags，
8 bytes + 30 bits + 2 bits = 16 bytes
(詳細 code 在 ``qtbase/src/corelib/kernel/qvariant.h`` 裡的 ``struct Private``) 。


Related Work
------------------------------

* `Rust Any <https://doc.rust-lang.org/std/any/>`_
* `Boost - Any <http://www.boost.org/doc/libs/release/doc/html/any.html>`_
* `Boost - Variant <http://www.boost.org/doc/libs/release/doc/html/variant.html>`_
* `The Boost C++ Libraries - Boost.Any <http://theboostcpplibraries.com/boost.any>`_
* `The Boost C++ Libraries - Boost.Variant <http://theboostcpplibraries.com/boost.variant>`_
* [2014] `Type erasure — Part IV <https://akrzemi1.wordpress.com/2014/01/13/type-erasure-part-iv/>`_
* [2008] `Type Inference vs. Static/Dynamic Typing <http://herbsutter.com/2008/06/20/type-inference-vs-staticdynamic-typing/>`_

Reference
------------------------------

* `QVariant Internals <https://wiki.qt.io/QVariant_Internals>`_
* `Implementing QVariant/QMetaType features with template tricks <https://steveire.wordpress.com/2011/03/16/implementing-qvariantqmetatype-features-with-template-tricks/>`_
* [GitHub] `qtbase - src/corelib/kernel/qvariant.cpp <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qvariant.cpp>`_
* [GitHub] `qtbase - src/corelib/kernel/qvariant.h <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qvariant.h>`_
* [GitHub] `qtbase - src/corelib/kernel/qvariant_p.h <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qvariant_p.h>`_
* [GitHub] `qtbase - src/corelib/kernel/qmetatype.h <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qmetatype.h>`_
* [GitHub] `qtbase - src/corelib/kernel/qmetatype_p.h <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qmetatype_p.h>`_
* [GitHub] `qtbase - src/corelib/kernel/qmetatype.cpp <https://github.com/qtproject/qtbase/blob/dev/src/corelib/kernel/qmetatype.cpp>`_



Reference
========================================

* `Arch Wiki - Qt <https://wiki.archlinux.org/index.php/Qt>`_
* `Category: Qt Internals <https://wiki.qt.io/Category:QtInternals>`_
