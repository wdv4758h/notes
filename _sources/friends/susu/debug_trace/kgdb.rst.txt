Linux Kernel KGDB
=================

- `KGDB official site <https://kgdb.wiki.kernel.org/index.php/Main_Page>`_
- `upstream documentation <https://www.kernel.org/pub/linux/kernel/people/jwessel/kdb/>`_
- kgdboc use note

  - `KGDB Tutorial <http://blog.scottt.tw/2010/01/kgdb-tutorial.html>`_
  - `用 kGDB 调试 Linux 内核 <http://tinylab.org/kgdb-debugging-kernel/>`_

- 2014 LinuxCon: https://www.kernel.org/pub/linux/kernel/people/jwessel/dbg_webinar/State_Of_kernel_debugging_LinuxCon2014.pdf


kgdb over USB need EHCI debug port?

- EHCI debug port

  - https://www.codeproject.com/Articles/132313/How-to-Debug-the-Windows-OS-using-USB
  - https://www.coreboot.org/EHCI_Debug_Port
  - http://composter.com.ua/documents/USB-2.0-Debug-Port(John-Keys).pdf
  - `EHCI debugging on the BeagleBone Black <https://libreboot.org/docs/misc/bbb_ehci.html>`_

Architecture
------------

- ARM64 add KGDB support at Linux 3.15

  - `kernelnewbies <https://kernelnewbies.org/Linux_3.15-DriversArch#head-28e77442feb44ba7f49d53344c7ba7bd3bfa361a>`_
  - `KGDB: Add basic KGDB support <https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=bcf5763b0d58d20e288ac52f96cbd7788e262cac>`_
  - `KGDB: Add step debugging support <https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=44679a4f142b69ae0c68ed815a48bbd164827281>`_
