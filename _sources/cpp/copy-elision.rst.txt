========================================
Copy Elision
========================================


.. contents:: 目錄


介紹
========================================

Copy Elision 介紹的是一種優化，
可以把 copy constructor 和 move constructor 優化掉，
形成 zero-copy 的 pass-by-value，
要注意的是如果 constructor 有副作用的話會造成程式在優化前後行為不同。

Copy Elision 是目前 C++ 內為二被允許可以更改可觀查到的副作用的優化技巧，
另外一項是 Allocation Elision。（C++14）

範例在： `examples/copy-elision.cpp <examples/copy-elision.cpp>`_

其中針對回傳值的優化又稱為 RVO 和 NRVO，
在 `另外一篇 <rvo.rst>`_ 有更多紀錄。



參考
========================================

* `Wikipedia - Copy Elision <https://en.wikipedia.org/wiki/Copy_elision>`_
* `cppreference - Copy Elision <http://en.cppreference.com/w/cpp/language/copy_elision>`_
