========================================
Computed goto
========================================


Reference
========================================

* `Wikipedia - Threaded code <https://en.wikipedia.org/wiki/Threaded_code>`_
* [2012] `Computed goto for efficient dispatch tables <http://eli.thegreenplace.net/2012/07/12/computed-goto-for-efficient-dispatch-tables>`_
* `GCC - Labels as Values <https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html>`_
* [2010] `Address of Label and Indirect Branches in LLVM IR <http://blog.llvm.org/2010/01/address-of-label-and-indirect-branches.html>`_
* CPython
    - `Python/makeopcodetargets.py <https://github.com/python/cpython/blob/master/Python/makeopcodetargets.py>`_
    - `configure.ac <https://github.com/python/cpython/blob/1fe0fd9feb6a4472a9a1b186502eb9c0b2366326/configure.ac#L4919>`_
        + ``--with-computed-gotos``
    - `Python/ceval.c <https://github.com/python/cpython/blob/aed79b41a1fbcedd4697269e3fdd40af5ee82b14/Python/ceval.c#L829>`_
    - `Python/opcode_targets.h <https://github.com/python/cpython/blob/master/Python/opcode_targets.h>`_
    - CPython 3.1 - `Enabling a configure option named "--with-computed-gotos" <https://github.com/python/cpython/blob/master/Doc/whatsnew/3.1.rst>`_
    - CPython 3.2 - `Computed gotos are now enabled by default on supported compilers <https://github.com/python/cpython/blob/master/Doc/whatsnew/3.2.rst>`_

* papers
    - [2001] `The Behavior of Efficient Virtual Machine Interpreters on Modern Architectures <https://www.cs.tcd.ie/David.Gregg/papers/ertl-europar01.pdf>`_
    - [2005] `Optimizing Indirect Branch Prediction Accuracy in Virtual Machine Interpreters <https://www.cs.tcd.ie/David.Gregg/papers/toplas05.pdf>`_
