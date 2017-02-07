========================================
Sandbox
========================================

* `Wikipedia - Sandbox (computer security) <http://en.wikipedia.org/wiki/Sandbox_%28computer_security%29>`_

seccomp
========================================

* `Wikipedia - seccomp <http://en.wikipedia.org/wiki/Seccomp>`_
* Linux kernel's feature since version 2.6.12
* seccomp-bpf : system call filter
* used by
    - OpenSSH
    - vsftpd
    - Chrome/Chromium
    - LXD
    - Firefox
    - Firefox OS

PyPy's sandboxing
========================================

* `PyPy's sandboxing features <http://pypy.readthedocs.org/en/latest/sandbox.html>`_

NaCl
========================================

* `Wikipedia - Google Native Client <http://en.wikipedia.org/wiki/Google_Native_Client>`_
* 在 sandbox 裡安全地執行 Intel x86、ARM、MIPS 的子集
* 接近原生速度
* Software Fault Isolation (SFI) model
    - 限制可以執行的 code (Control Flow Integrity → CFI)
    - 限制哪些資料可以被存取 (Data Integrity)
    - 限制 I/O 介面
* 被用於 ZeroVM
    - `Wikipedia - ZeroVM <http://en.wikipedia.org/wiki/ZeroVM>`_
* `Native Client - Google Chrome <https://developer.chrome.com/native-client>`_
    - `Sandbox Internals <https://developer.chrome.com/native-client/reference/sandbox_internals>`_
    - `PNaCl Bitcode Reference Manual <https://developer.chrome.com/native-client/reference/pnacl-bitcode-abi>`_
* `Native Client - Frequently Asked Questions <https://developer.chrome.com/native-client/faq>`_
* Native Client:A Sandbox for Portable, Untrusted x86 Native Code
    - `Google - Publication Data <http://research.google.com/pubs/pub34913.html>`_
    - `Slide <https://www.utdallas.edu/~zxl111930/spring2012/lec18.pdf>`_
* `LLVM on the Web Using Portable Native Client to run Clang/LLVM in the Browser <https://fosdem.org/2015/schedule/event/llvm_pnacl/>`_
    - `Slide <http://llvm.org/devmtg/2015-02/slides/brad-pnacl.pdf>`_
