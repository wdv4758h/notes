========================================
AddressSanitizer Algorithm
========================================

.. contents:: Table of Contents

把程式使用的 memory 每 8 bytes 對應到 1 byte 的 shadow memory

::

                                  +---+---+---+---+---+---+---+---+
                    shadow memory |   |   |   |   |   |   |   |   | (bit)
                                  +---+---+---+---+---+---+---+---+


                    unpoisoned      0   0   0   0   0   0   0   0   (值為零)

    前 k bytes 是 unpoisoned                      k                 (值為 k)
    (後 8-k bytes 是 poisoned)

                   完全 poisoned    1                               (值為負)


假設原本的程式有：

.. code-block:: c

    *ptr = 42;


加上 ASAN Instrumentation 後大概會變成：

.. code-block:: c

    byte *shadow_address = MemToShadow(ptr);
    byte shadow_value = *shadow_address

    if (shadow_value) {
        // poisoned
        if (Check(shadow_value, ptr, kAccessSize)) {
            ReportError(ptr, kAccessSize, kIsWrite);
        }
    }

    ////////////////////////////////////////

    byte* MemToShadow(void *ptr) {
        // address's last 3 bits will change in the 8 bytes
        // but these 8 bytes will share 1 byte shadow
        return ((uintptr_t) ptr >> 3) + 0x7fff8000;
    }

    ////////////////////////////////////////

    bool Check(byte shadow_value, void *ptr, size_t kAccessSize) {
        // pick last 3 bits (& 7)
        // add access size to see whether excess the range
        //
        // 0 - - - - - - - 7 (bytes)
        //      ^       ^
        //      |       |
        //
        //      ptr&7   (ptr&7 + access size - 1)
        //
        return ((uintptr_t) ptr & 7 + kAccessSize - 1) >= shadow_value;
    }


Address
------------------------------

64-bit
++++++++++++++++++++

``Shadow = (Mem >> 3) + 0x7fff8000;``

[0x10007fff8000, 0x7fffffffffff] 	HighMem
[0x02008fff7000, 0x10007fff7fff] 	HighShadow
[0x00008fff7000, 0x02008fff6fff] 	ShadowGap
[0x00007fff8000, 0x00008fff6fff] 	LowShadow
[0x000000000000, 0x00007fff7fff] 	LowMem


32 bit
++++++++++++++++++++

``Shadow = (Mem >> 3) + 0x20000000;``

[0x40000000, 0xffffffff] 	HighMem
[0x28000000, 0x3fffffff] 	HighShadow
[0x24000000, 0x27ffffff] 	ShadowGap
[0x20000000, 0x23ffffff] 	LowShadow
[0x00000000, 0x1fffffff] 	LowMem


mprotect
========================================

設定某段記憶體的權限

.. code-block:: c

    #include <sys/mman.h>

    int mprotect(void *addr, size_t len, int prot);


``prot`` 的值為 ``PROT_NONE`` 或是由其他權限經過 bitwise-or 出來的結果

* PROT_NONE
    - 完全不能被存取
* PROT_READ
    - 可以被讀
* PROT_WRITE
    - 可以被寫
* PROT_EXEC
    - 可以被執行

如果程式的記憶體存取違反這邊的權限的話，
kernel 會送 ``SIGSEGV`` 給程式。


指定某 function 不要加入 Sanitizer 檢查
========================================

程式撰寫上：

.. code-block:: c

    #if defined(__clang__) || defined (__GNUC__)
    # define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))
    #else
    # define ATTRIBUTE_NO_SANITIZE_ADDRESS
    #endif


或是編譯時， ``-fsanitize-blacklist=my_ignores.txt``

``my_ignores.txt`` ::

    # Ignore exactly this function (the names are mangled)
    fun:MyFooBar
    # Ignore MyFooBar(void) if it is in C++:
    fun:_Z8MyFooBarv
    # Ignore all function containing MyFooBar
    fun:*MyFooBar*



Reference
========================================

* `AddressSanitizer - Compile Time Optimizations <https://github.com/google/sanitizers/wiki/AddressSanitizerCompileTimeOptimizations>`_
* `AddressSanitizer - Algorithm <https://github.com/google/sanitizers/wiki/AddressSanitizerAlgorithm>`_
