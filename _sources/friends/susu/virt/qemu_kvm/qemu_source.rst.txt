.. contents:: Table of Contents

Source Code
-----------
- KVM-related QEMU ource code

  - ``kvm-all.c``
  - ``target-arm/kvm.c``

- KVM source code (Linux kernel module)

  - ``virt/kvm/*``
  - ``arch/arm/kvm/*``
  - ``include/linux/kvm_*.h``
  - ``arch/arm/include/asm/kvm_*.h``
  - ``Documentation/virtual/kvm/api.txt``

QEMU interaction with KVM(ioctl)
--------------------------------
KVM 為 linux kernel module, 把功能藉由擴充 ioctl system call 來 pass through 給 userspace 的 QEMU.

QEMU 藉由對 KVM device 作 ioctl, 對 KVM 發出 request.

- KVM current api (ioctl type): ``Documentation/virtual/kvm/api.txt``
- 3 kinds of ioctl

  - System, VM, and VCPU ioctl
  - example, one VM with 2 vcpu

    ::

        # file descriptors
        QEMU    1888 susu    8u      CHR             10,232        0t0      330 /dev/kvm
        QEMU    1888 susu    9u  a_inode                0,9          0     7626 kvm-vm
        QEMU    1888 susu   12u  a_inode                0,9          0     7626 kvm-vcpu
        QEMU    1888 susu   13u  a_inode                0,9          0     7626 kvm-vcpu

- QEMU functions (``kvm_all.c``)
        
  - doing system call to specific fd

    - ``int kvm_device_ioctl(int fd, int type, ...)``

  - three kinds ioctl

    - ``int kvm_ioctl(KVMState *s, int type, ...)``
    - ``int kvm_vm_ioctl(KVMState *s, int type, ...)``
    - ``int kvm_vcpu_ioctl(CPUState *s, int type, ...)``

  - what is ``struct CPUState`` in QEMU
    
      QEMU 會替每一個虛擬 CPU (VCPU) 維護一個 CPUState 的資料結構.

      在引入 KVM 之後, QEMU 在 ``CPU_COMMON`` 這個巨集 (cpu-defs.h) 裡的 CPUState 裡面加了幾個 KVM 需要的欄位.

      ::

         #define CPU_COMMON
             struct KVMState *kvm_state;                                         \
             struct kvm_run *kvm_run;                                            \
             int kvm_fd; // VCPU fd                                              \
             int kvm_vcpu_dirty;

- KVM functions (``virt/kvm/kvm_main.c``)
        
  - system call/KVM api implementation.
  - three kinds ioctl: ``kvm_dev_ioctl``, ``kvm_vm_ioctl``, ``kvm_vcpu_ioctl``
  - architecture dependent system call: ``kvm_arch_vm_ioctl``

QEMU call KVM ioctl trace code
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- kvm_arch_vm_ioctl

  - arch-dependent KVM feature
  - detail::

      int kvm_vm_ioctl(KVMState *s, int type, ...)
      long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg)

      Q: when does kvm_vm_ioctl() calls kvm_arch_vm_ioctl()?
      A: if type is architecture type

      [parameter]
      filp = s.vmid
      ioctl = type
      arg = vargs( ... )
      
      [return value]
      return value = return value, for value != -1
                   = errno, for value == -1

- function prototype

    - ``[qemu][args] int kvm_vm_ioctl(KVMState *s, int type, ...) (in kvm-all.c)``
    - ``[glibc/syscall][argv] int ioctl (int __fd, unsigned long int __request, ...)``
    - ``[kvm] long kvm_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg) (virt/kvm/kvm_main.c)``
    - ``[kvm] long kvm_arch_vm_ioctl(struct file *filp, unsigned int ioctl, unsigned long arg) (arch/arm/kvm/arm.c)``

- real function call

    - ``[qemu] save_s2_pgd( ... ) (in target-arm/kvm.c)`` 
    - ``[qemu] s2_size = kvm_vm_ioctl(s, KVM_ARM_GET_S2_PGD_SIZE);``
    - ``[libc call/syscall] ret = ioctl(s->vmfd, type, arg);``
    - ``[kvm] ret = kvm_vm_ioctl(s->vmfd, type, arg);``
    - ``[kvm] r = kvm_arch_vm_ioctl(filp, ioctl, arg);``
    - ``[kvm] return PTRS_PER_S2_PGD * sizeof(pgd_t);``

QEMU KVM architecture & control flow
------------------------------------
Linux kernel view of VM(QEMU)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- example, one VM with 2 vcpu::

    # QEMU process view
    1888 susu       20   0 1104M  301M 28088 S  0.0  2.5  3:55.18 QEMU -enable-kvm

    # QEMU thread view
    1888 susu       20   0 1104M  301M 28088 S  0.0  2.5  3:55.18 QEMU -enable-kvm
    1891 susu       20   0 1104M  301M 28088 S  0.0  2.5  0:12.45 ├─ QEMU -enable-kvm
    1890 susu       20   0 1104M  301M 28088 S  0.0  2.5  0:30.49 └─ QEMU -enable-kvm

- [guess] QEMU 的 3 thread 應該是 QEMU main thread, 2 個 vcpu 各分一個 thread

Architecture
~~~~~~~~~~~~
:: 

    +----------------------------------------------------------+
    |                                                          |
    |  +-----------+    +--------------------+                 |
    |  |           |    |                    |                 |
    |  |           |    |  +--------------+  |                 |
    |  |           |    |  |              |  |                 |
    |  |           |    |  |   guest OS   <---------+          |
    |  |           |    |  |              |  |      |          |
    |  |           |    |  +--------------+  |      | VM enter |
    |  |           |    |                    |      |          |
    |  |           |    | QEMU --enable-kvm  |      |          |
    |  |   Host    |    |                    |      |          |
    |  |  process  |    |   Host process     |      |          |
    |  |           |    |                    |      |          |
    |  +-------+---+    +---------^------+---+      |          |
    |          |                  |      |          |          |
    |          |  context switch  |      |  syscall |          |
    |          |                  |      |  ioctl() |          |
    |      +---v------------------+----+-v----------++         |
    |      |                           |             |         |
    |      |    Host OS(linux kernel)  |     KVM     |         |
    |      |                           |             |         |
    |      +---------------------------+-------------+         |
    |                                                          |
    +----------------------------------------------------------+

Control Flow
~~~~~~~~~~~~
- ``VMEnter`` & ``VMExit``
- ``int kvm_cpu_exec(CPUArchState *env) in kvm_all.c``

    - 負責 ``VMEnter`` 以及 handling ``VMExit`` 需做的操作.

- flow chart::

    QEMU (user mode)       KVM (kernel mode)        Guest VM (guest mode)

           Issue Guest
     -->                 -------------
    |    Execution ioctl              |
    |                                 |
    |          (1)                    |
    |                                 v
    |
    |                        --> Enter Guest Mode ---------------
    |                       |                                    |
    |                       |                                    |
    |                       |                                    |
    |                       |                                    v
    |                       |              
    |                       |                             Execute natively
    |                       |           
    |                       |                               in Guest Mode
    |                       |              
    |                       |                                    |
    |                       |                                    |
    |                       |                                    |
    |                       |    Handle Exit     <--------------- 
    |                       |
    |                       |        |              
    |                       |        |
    |                       |        |
    |                       |        v 
    |                    Y  |
    |           ------------------- I/O?
    |          |            |
    |          |            |        |
    |          |            |        | N
    |          v            |        |
    |                       |   Y    v
     ----  Handle I/O <----------- Signal
                            |
              (A)           |     Pending?
                            | 
                            |        |
                            |        | N
                            |        |
                            --------- 

address translation
-------------------

- QEMU without virtualization

  ::

    GVA -----------> GPA ------------> HVA -------------> HPA
          Guest OS           QEMU             Host OS
         page table         KVMSlot         page table

  - GVA: Guest Virtual Address
  - GPA: Guest Physical Address
  - HVA: Host Virtual Address
  - HPA: Host Physical Address

- 當使用 Hardware Assisted Virtualization 時, GPA -> HPA 用 HAV 支援的 page table 做轉換??

  - in x86, yes: http://people.cs.nctu.edu.tw/~chenwj/slide/QEMU/KVM-mmu.txt 
  - in arm?

QEMU TCG and KVM mode
---------------------
code 切成 2 個 part，根據 kvm/tcg mode 決定跑哪一份 (``kvm_enabled()/tcg_enabled()``)

note: TCG - Tiny Code Generator, the JIT binary translator in qemu for emulation.

QEMU programming technique/architecture
---------------------------------------
1. qemu mainloop:

    - ``qemu/main-loop.h``, ``main-loop.c``
    - ``qemu_set_fd_handler, qemu_set_fd_handler2``

2. qemu coroutine: http://blog.vmsplice.net/2014/01/coroutines-in-qemu-basics.html

    ::

        qemu_coroutine_create(process_incoming_migration_co);
        qemu_coroutine_enter(co, f);


3. QEMUFile struct

    ::

        qemu_loadvm_state(QEMUFile* f);
        qemu_fclose(QEMUFile* f);

        // 使用 qemu_fopen_ops() 函數註冊此 struct (assign many function pointer)
        qemu_fopen_ops()
            QEMUFile* f
            f = qemu_mallocz(sizeof(QEMUFile))
            assign(opaque, put_buffer, get_buffer, close, rate_limit, set_rate_limit, get_rate_limit) from function parameter.
            f->buf_max_size = IO_BUF_SIZE;
            f->buf = qemu_malloc(sizeof(uint8_t) * f->buf_max_size);

        struct QEMUFile {
            // six function pointer (put_buffer ... etc).
            void *opaque;
            int is_write;             

            int64_t buf_offset; /* start of buffer when writing, end of buffer
                                   when reading */
            int buf_index;            
            int buf_size; /* 0 when writing */ 
            int buf_max_size;
            uint8_t *buf;             
            
            int has_error;            
        };  

4. bdrv

    感覺跟 block device 有關.
    ::

        bdrv_snapshot

        bdrv_read/bdrv_write
        bdrv_aio_readv/bdrv_aio_writev

5. loadvm/savevm

    ::

        # qemu shapshot: http://www.xuebuyuan.com/2192772.html
        A) bdrv_snapshots()
        B) vm_stop()
        C) qemu_savevm_state()
        D) bdrv_snapshot_create()
        E) vm_start()

        qemu_savevm_state()
           A) qemu_savevm_state_begin()
           B) qemu_savevm_state_iterate()
           C) qemu_savevm_state_complete()

6. data structure 

    - ``include/qapi/qmp/qdict.h``

        - 根據 ``DictEntry``, 猜測是 linked list based map.

reference
---------
1. http://people.cs.nctu.edu.tw/~chenwj/slide/QEMU/KVM-introduction-01.txt
2. http://people.cs.nctu.edu.tw/~chenwj/slide/QEMU/KVM-introduction-02.txt
3. http://people.cs.nctu.edu.tw/~chenwj/slide/QEMU/KVM-introduction-03.txt
4. https://www.kernel.org/doc/Documentation/virtual/kvm/api.txt
5. QEMU source code notes: http://chenyufei.info/notes/qemu-src.html
