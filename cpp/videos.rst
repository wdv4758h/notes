========================================
C++ Videos
========================================

* [2014] `Scott Meyers: Support for Embedded Programming in C++11 and C++14 <https://www.youtube.com/watch?v=J-tA17slViE>`_
    - ``auto``
    - ``constexpr``

* [2014/06] `Scott Meyers: Why C++ Sails When the Vasa Sank <https://events.yandex.ru/lib/talks/1954/>`_
    - 講述 C++ 這一路走來，讓它持續有許多使用者的重要特色，以及近年來如何變得更好
    - 讓舊有的程式碼依然可以編譯，加入新 feature 讓同樣的 code 可以更簡單易懂
        + 20 年前的程式依然可以 compile
    - You don't pay for what you don't use.
        + 編譯時期把不必要的東西去掉 (pay at compile time, not runtime)
    - C : Trust the programmer
    - 和 C 有一定的相似度，所以 C programmer 的一些知識在這邊也同樣用的上
    - C++ 有良好的效能，也適用於只能用較少的硬體和能源但同時也需要效能的情況 (embedded)

* [2012/06] Scott Meyers: Adventures in Perfect Forwarding
    - `Part1 <https://www.facebook.com/video/video.php?v=10151094464083109>`_
    - `Part2 <https://www.facebook.com/video/video.php?v=10151094455928109>`_
    - `PDF <http://www.aristeia.com/TalkNotes/Facebook2012_PerfectForwarding.pdf>`_
    - 這場在 Facebook 的 talk 畫質比較差 ...，錄音還有問題 Orz
    - perfect forwarding 可以避免 temporary object 的產生
    - ``std::forward``
    - type traits : ``std::remove_reference``, ``std::enable_if``
    - ``std::make_shared``
    - moving is not free, it's typically cheap, but it's not always cheap, and it more expensive then binding to a reference
    - perfect forwarding is not perfect, but it's really really good
    - something can't perfect forwarding
        + 0 as null pointer constant
        + Braced initializer lists
        + Integral const static class members lacking a definiton
        + Template names (e.g., std::endl)
        + Non-const lvalue bitfields

* [2013/09] `C++ Seasoning <https://www.youtube.com/watch?v=qH6sSOr-yk8>`_
    - `PDF <https://github.com/sean-parent/sean-parent.github.com/wiki/presentations/2013-09-11-cpp-seasoning/cpp-seasoning.pdf>`_
    - `Sean Parent - Papers and Presentations <https://github.com/sean-parent/sean-parent.github.io/wiki/Papers-and-Presentations>`_
    - no raw loops
    - no raw synchronization primitives
    - no raw pointers
    - use STL or general function in libraries when available
    - <algorithm>
        + rotate
        + stable_partition
        + lower_bound
    - keep the body short
    - Amdahl's law
    - <future>
        + packaged_task
    - make_shared
