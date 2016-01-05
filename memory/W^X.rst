========================================
W^X (Write XOR Execute)
========================================

W^X 是一個安全性的 feature，
一種記憶體的保護手段，
可以把 process 的 address space 的各個 page 標上「可執行」或「可寫入」，
但是不會有「可執行且可寫入」，
藉此可以減輕一些 buffer overflow 的攻擊，
讓攻擊者只能造成程式 crush，
而不會執行到有害的程式碼。

Reference
========================================

* `Wikipedia - W^X <https://en.wikipedia.org/wiki/W%5EX>`_
* `Wikipedia - Exec Shield <https://en.wikipedia.org/wiki/Exec_Shield>`_
* `Wikipedia - NX bit <https://en.wikipedia.org/wiki/NX_bit>`_

* kernels
    - OpenBSD 3.3
    - PaX (patch for Linux kernel)
    - Exec Shield (patch for Linux kernel)
    - NetBSD 4

* keyword
    - linker
    - trampolines
