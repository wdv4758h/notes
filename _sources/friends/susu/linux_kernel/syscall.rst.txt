.. image:: syscall_routine.png

syscall table

- source: ``arch/x86/entry/syscalls/`` => ``arch/x86/include/generated/asm`` & ``arch/x86/include/generated/uapi/asm``
- x86_64 

  - systbl: ``__SYSCALL_64(0, sys_read, )``
  - syshdr: ``#define __NR_read 0``

- x86

  - systbl: ``__SYSCALL_I386(0, sys_restart_syscall, )``
  - syshdr: ``#define __NR_restart_syscall 0``

- hdr
  
  - ``unistd_(32, 64, x32).h``
  - ``unistd_64_x32.h, unistd_32_ia32.h``

- tbl: ``syscalls_32.h``, ``syscalls_64.h`` (with X32 ABI) 
- misc

  - ?? syscall number in libc: ``/usr/include/asm/unistd_(32, 64, x32).h``, from ``/usr/include/sys/syscall.h``

syscall_entry

- source: ``arch/x86/entry/``

  - x86_64: common.c, entry_64.S, syscall_64.c, thunk_64.S(thunk macro), calling.h

- fast_path & slow_path

  - do_64_syscall()
  - do_int80_syscall_32()

    - enter_from_user_mode()
    - local_irq_enable()
    - do_syscall_32_irqs_on()

  - do_fast_syscall_32()

    - [x86] IRET(x86 trap), SYSEXIT(intel ia32 SYSENTER), SYSRETL(amd64 SYSCALL)
    - http://wiki.osdev.org/SYSENTER

- trace

  - audit
  - seccomp
  - ftrace 
  
    - ``include/linux/syscalls.h``, ``SYSCALL_METADATA``, ``CONFIG_FTRACE_SYSCALLS``
    - asmlinkage: https://kernelnewbies.org/FAQ/asmlinkage

- Misc

  - swappg
  - enter_from_user_mode
  - context_tracking

syscall define

- source: ``include/linux/syscalls.h``

  - SYSCALL_DEFINE<num>(), <num>: 為 system call 參數數量

----

http://wiki.osdev.org/SYSENTER

SYSENTER/SYSEXIT

- sysenter::

    EIP <= IA32_SYSENTER_EIP
    ESP <= IA32_SYSENTER_ESP
    CS  <= IA32_SYSENTER_CS
    SS  <= IA32_SYSENTER_CS + 8

- sysexit::

    EIP <= EDX
    ESP <= ECX
    CS  <= IA32_SYSENTER_CS + 16
    SS  <= IA32_SYSENTER_CS + 24

SYSCALL/SYSRET

- syscall::

    EIP    => ECX
    EIP    <= STAR[32:0]  (LSTAR in 64bits)

    CS     <= STAR[47:32]
    SS     <= STAR[47:32] + 8
    EFLAGS <= SFMASK

- sysret::

    EIP <= ECX
    CS  <= STAR[63:48]
    SS  <= STAR[63:48] + 8

Ref
---
- http://www.cs.columbia.edu/~jae/4118-LAST/L10-syscall.pdf

- Anatomy of a system call, part 1: https://lwn.net/Articles/604287/
- Anatomy of a system call, part 2: https://lwn.net/Articles/604515/

  - x86_32 syscall invocation via SYSENTER
  - x86_32 syscall invocation via INT 0x80
  - x86 syscall invocation mechanisms
  - x86_32 syscall invocation on x86_64
  - A more complex example: execve and 32-bit compatibility handling
  - x32 ABI support
  - gettimeofday(): vDSO
  - ptrace(): syscall tracing

- osdev: sysenter/syscall: http://wiki.osdev.org/SYSENTER
- Implementing virtual system calls(vDSO syscall): https://lwn.net/Articles/615809/

- Documentation/adding-syscalls.txt: http://lxr.free-electrons.com/source/Documentation/adding-syscalls.txt
- LinuxCon NA 2015 - How to design a Linux kernel interface: http://man7.org/conf/lcna2015/designing_linux_kernel_APIs-LCNA_2015-Kerrisk.pdf

  - 寫 unittest, 放到 kselftest: https://kselftest.wiki.kernel.org/
  - 寫 spec, 放到 man page: https://www.kernel.org/doc/man-pages/patches.html
  - Flags as a system call API design pattern: https://lwn.net/Articles/585415/

- FreeBSD - adding syscalls: https://wiki.freebsd.org/AddingSyscalls
