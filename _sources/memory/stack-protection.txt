========================================
Stack Protection
========================================

* Canary (randomly chosen integer)
    - 在 Stack 的 return pointer 前放上一個 random number，在回傳前檢查這個數字是否有被改到，若有被改到就代表值被蓋掉了

* libsafe

Reference
========================================

* `Wikipedia - Buffer overflow protection <https://en.wikipedia.org/wiki/Buffer_overflow_protection>`_
* `Wikipedia - Stack-based memory allocation <https://en.wikipedia.org/wiki/Stack-based_memory_allocation>`_
* `Wikipedia - Stack buffer overflow <https://en.wikipedia.org/wiki/Stack_buffer_overflow>`_
* `[2014] Strong" stack protection for GCC <https://lwn.net/Articles/584225/>`_
* `[2014] Libsafe: Protecting Critical Elements of Stacks <http://www.researchgate.net/publication/2393717_Libsafe_Protecting_Critical_Elements_of_Stacks>`_
* `[1989] StackGuard: Automatic Adaptive Detection and Prevention of Buffer-Overflow Attacks <https://www.usenix.org/legacy/publications/library/proceedings/sec98/full_papers/cowan/cowan.pdf>`_
* `Memory Exploits & Defenses <http://cs.unc.edu/~fabian/courses/CS600.624/slides/exploits.pdf>`_
* `Lock IT Down: Use Libsafe to secure Linux from buffer overflows <http://www.techrepublic.com/article/lock-it-down-use-libsafe-to-secure-linux-from-buffer-overflows/>`_
