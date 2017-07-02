========================================
crt
========================================

名詞解釋：

+-----+----------------------------------------------+
| PIC | position independent code (-fPIC)            |
+-----+----------------------------------------------+
| PIE | position independent executable (-fPIE -pie) |
+-----+----------------------------------------------+
| crt | C runtime                                    |
+-----+----------------------------------------------+



crtbegin.o

    GCC uses this to find the start of the constructors.

crtbeginS.o

    Used in place of crtbegin.o when generating shared objects/PIEs.

crtbeginT.o

    Used in place of crtbegin.o when generating static executables.

crtend.o

    GCC uses this to find the start of the destructors.

crtendS.o

    Used in place of crtend.o when generating shared objects/PIEs.


Reference
========================================

* `Mini FAQ about the misc libc/gcc crt files <https://dev.gentoo.org/~vapier/crt.txt>`_
