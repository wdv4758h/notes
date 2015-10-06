========================================
AddressSanitizer Algorithm
========================================

把程式使用的 memory 每 8 bytes 對應到 1 byte 的 shadow memory

::

                                  +---+---+---+---+---+---+---+---+
                    shadow memory |   |   |   |   |   |   |   |   | (bit)
                                  +---+---+---+---+---+---+---+---+


                    unpoisoned      0   0   0   0   0   0   0   0   (值為零)

    前 k bytes 是 poisoned                        k                 (值為 k)
    (後 8-k bytes 是 unpoisoned)

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

