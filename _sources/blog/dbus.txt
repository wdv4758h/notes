:title: D-Bus
:slug: d-bus
:date: 2014-12-27 01:45
:modified: 2014-12-27 01:45
:category: Misc
:tags: linux, d-bus, ipc, kdbus
:author: wdv4758h
:summary:

Basic Linux IPC
========================================

* `Wikipedia - Inter-process communication <https://en.wikipedia.org/wiki/Inter-process_communication>`_

* `[Linux.conf.au 2013] - An Introduction to Linux IPC Facilities <https://www.youtube.com/watch?v=8hxb0kwnzGI>`_
    - `[Linux.conf.au 2013] - An Introduction to Linux IPC Facilities - slide <http://man7.org/conf/lca2013/IPC_Overview-LCA-2013-printable.pdf>`_


* sockets
* FIFOs
* shared memory

.. image:: /images/linux/linux-ipc-communication.png
    :alt: linux-ipc-communication

.. image:: /images/linux/linux-ipc-synchronization.png
    :alt: linux-ipc-synchronization


D-Bus
========================================

D-Bus is a message bus system for inter-process communication (``IPC``)

* `D-Bus <https://wiki.archlinux.org/index.php/D-Bus>`_
* `Wikipedia - D-Bus <http://en.wikipedia.org/wiki/D-Bus>`_
* `Freedesktop - Introduction to D-Bus <http://www.freedesktop.org/wiki/IntroductionToDBus/>`_
* `Linux From Scratch - D-Bus <http://www.linuxfromscratch.org/blfs/view/svn/general/dbus.html>`_
* `D-Bus Specification <http://dbus.freedesktop.org/doc/dbus-specification.html>`_

D-Bus is enabled automatically when using systemd because dbus is a dependency of systemd.

What's D-Bus
------------------------------

* a powerful IPC system
* the closest thing to a standard in this area as can be found on Linux
* provides a nice method-call transaction mechanism
* has fundamental inefficiencies of the user-space implementation
    - well suited to control tasks
        + works well to tell a sound server to change the volume
    - less so for anything that has to carry significant amounts of data
        + one would not want to try to send the actual audio data over the bus
* In D-Bus a call-return message requires ``10 message copies``, ``4 message validations``, ``4 context switches``
* D-Bus has ``no timestamps on messages``
* not available at early boot
* **We need a better implementation** -> ``kdbus``

D-Bus - Architecture
------------------------------

* libdbus
* dbus-daemon
* wrapper libraries based on particular application frameworks

Interesting : ::

    In 2013 the systemd project rewrote libdbus in an effort to simplify the code, but it turned out to significantly increase the performance of D-Bus as well.
    In preliminary benchmarks, BMW found that the systemd D-Bus library increased performance by 360%.


.. image:: /images/linux/dbus-architectural.png
    :alt: linux desktop architecture

kdbus
========================================

* `D-Bus in the kernel [linux.conf.au 2014] <https://www.youtube.com/watch?v=NgR6d54blrU>`_
    - `D-Bus in the Kernel - slide <http://events.linuxfoundation.org/sites/events/files/slides/linuxconjapan2014.pdf>`_

* `ALS: Linux interprocess communication and kdbus (May 30, 2013) <https://lwn.net/Articles/551969/>`_
* `The unveiling of kdbus (Jan 13, 2014) <http://lwn.net/Articles/580194/>`_
    - Linux Kernel only have primitives IPC : sockets, FIFOs, and shared memory
    - kdbus is a **in-kernel implementation of D-Bus**
        + can carry large amounts of data
            * even used for gigabyte-sized message streams
        + have zero-copy message passing
        + worst case : ``2 copy operations``, ``2 validations``, ``2 context switches``
        + all messages carry timestamps
        + full credential information (user ID, process ID, SELinux label, control group information, capabilities, and much more) is passed with each message
        + always available to the system (no need to wait for the D-Bus daemon to be started)
        + Linux security modules can hook into it directly
        + various race conditions have been fixed
        + API has simplified
        + Kdbus is implemented as a ``character device`` in the kernel
        + signal broadcasting mechanism has been rewritten to use Bloom filters to select recipients
        + There is a user-space proxy server that can be used by older code that has not been rewritten to use the new API, so everything should just work on a kdbus-enabled system with no code changes required.
    - the new ``memfd`` syscall was merged into Linux kernel 3.17
        + ``memfd`` is a mechanism similar to Android's ``ashmem`` that allows ``zero-copy`` message passing in KDBUS.
    - Android "ashmem" subsystem
    - Android Binder

* `Kdbus meets linux-kernel (Nov 4, 2014) <http://lwn.net/Articles/619068/>`_
* `D-Bus, FreeDesktop, and lots of madness <http://gentooexperimental.org/~patrick/weblog/archives/2014-11.html#e2014-11-23T09_26_01.txt>`_
    - `Hacker News - D-Bus, FreeDesktop, and lots of madness <https://news.ycombinator.com/item?id=8648437>`_

* `Kdbus Details - Greg Kroah-Hartman <http://www.kroah.com/log/blog/2014/01/15/kdbus-details/>`_
    - Binder vs. kdbus
    - Binder is bound to the CPU, D-Bus (and hence kdbus), is bound to RAM
* `kdbus.txt <https://code.google.com/p/d-bus/source/browse/kdbus.txt>`_
