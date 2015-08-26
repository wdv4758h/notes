========================================
Android's Binder
========================================

Binder is bound to the CPU, D-Bus (and hence kdbus), is bound to RAM.

* Binder
    - 會 block
    - synchronous calling CPU
    - 會直接把 CPU 執行權轉交給 callee (類似 system call 那樣)
    - 過程中幾乎不會有 scheduling 發生
    - 設計和 D-Bus 比起來比較不彈性，use-cases 也較受限，但可以執行非常快，overhead 非常低，適合手機這種 device

* D-Bus
    - 用 RAM 來 queue 住訊息 (會照順序)
    - asynchronous
    - 運作方式為 create-store-forward


Reference
========================================

* `Kdbus Details <http://kroah.com/log/blog/2014/01/15/kdbus-details/>`_
    - Greg Kroah-Hartman 寫的很好的一篇文章，簡單快速地說明 D-Bus 和 Binder 的不同
* `The future that everyone forgot <https://medium.com/@chrisdesalvo/the-future-that-everyone-forgot-d823af31f7c>`_
* `Wikipedia - Inter-process communication <https://en.wikipedia.org/wiki/Inter-process_communication>`_
* `Wikipedia - OpenBinder <https://en.wikipedia.org/wiki/OpenBinder>`_
* `Wikipedia - D-Bus <https://en.wikipedia.org/wiki/D-Bus>`_
* `The unveiling of kdbus <https://lwn.net/Articles/580194/>`_
* `Android Binder <http://elinux.org/Android_Binder>`_

* `Wikipedia - User:ScotXW/kdbus <https://en.wikipedia.org/wiki/User:ScotXW/kdbus#D-Bus_in_the_kernel>`_

* D-Bus with Python
    - `DBusBindings <http://www.freedesktop.org/wiki/Software/DBusBindings/>`_
    - `Arch Packages - python-dbus <https://www.archlinux.org/packages/extra/x86_64/python-dbus/>`_
