========================================
A Bug Hunter's Diary
========================================

[未讀完]

----

Instruction Pointer/Program Counter：

+--------+----------+
| 名稱   | 架構     |
+========+==========+
| EIP    | IA-32    |
+--------+----------+
| R15/PC | ARM      |
+--------+----------+
| RIP    | Intel 64 |
+--------+----------+
| R15/PC | ARM      |
+--------+----------+

----

* /GS (Buffer Security Check)
* ASLR
* NX/DEP

----

user-to-kernel interface

* IOCTLs
* System Calls
* File Systems
* Network Stack
* Hook of third-party drivers
