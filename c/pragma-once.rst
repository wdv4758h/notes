========================================
pragma once
========================================

``#pragma once`` 是 C 和 C++ 語言裡避免多次 include 的方式，
用途跟 ``#include guards`` 一樣，
但是更簡單、方便，
雖然不是語言標準，
但是大部分的編譯器都支援。

Use
------------------------------

#include guards
++++++++++++++++++++

.. code-block:: c

    #ifndef XXX_H
    #define XXX_H

    struct foo {
        int member;
    };

    #endif


#pragma once
++++++++++++++++++++

.. code-block:: c

    #pragma once

    struct foo {
        int member;
    };


Reference
========================================

* `Wikipedia - pragma once <https://en.wikipedia.org/wiki/Pragma_once>`_
* `Wikipedia - #include guard <https://en.wikipedia.org/wiki/Include_guard>`_
