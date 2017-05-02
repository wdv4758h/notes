Oenhan KVM note
===============

Part2 VM RUN
------------

http://www.oenhan.com/kvm-src-2-vm-run

- ioctl 介面

  - 3 介面
  - kvm: create_vm
  - kvm_vm: create_vcpu, set_user_memory_region, create_device
  - kvm_vcpu: run

- ``vl.c`` 的 main()
- ``util/module.c``, ``util/qemu-config.c``
- atexit(), qemu_run_exit_notifier
- kvm_init() (by type_init() + module_call_init(), read module init mechanism for detail )

- cpu_exec_init_all()
- cpudef_init()
- qemu_set_log()
- machine_class->init(current_machine)

  - ``current_machine = MACHINE(object_new(object_class_get_name(OBJECT_CLASS(machine_class))));``
  - ``machine_class`` is from CLI option
  - call pc_init1() 

- pc_init1()

  - pc_cpus_init()
  - pc_memory_init()

module init mechanism
~~~~~~~~~~~~~~~~~~~~~

- module_call_init()
  
  - type: BLOCK, MACHINE, QAPI, QOM. (current / QEMU 2.7) MACHINE 換成 OPT 了.
  - function linked list: ``ModuleTypeList``, image
  - foreach ``ModuleEntry`` e in ``ModuleTypeList``: e->init()

- ``ModuleTypeList`` 註冊

  - module_init() 處理註冊, use ``__attribute__((constructor))`` => 在 main 之前執行.
  - block_init(f) => module_init(f, MODULE_INIT_BLOCK), register_module_init(f, MODULE_INIT_BLOCK)

  - DEFINE_I440FX_MACHINE(), DEFINE_PC_MACHINE()
  
    - pc_init_##suffix(), pc_machine_##suffix##_class_init()
    - pc_machine_init_##suffix()
    - pc_init1(machine)
    - type_register(&pc_machine_type_##suffix)
    - machine_init(pc_machine_init_##suffix)

- ``ModuleEntry``

  - 3 member: init(), next pointer, ``module_init_type``

- example

  - module_call_init(MODULE_INIT_QOM);
  - module_call_init(MODULE_INIT_OPTS);
  - type_init(kvm_type_init）-> kvm_accel_type -> kvm_accel_class_init -> kvm_init

- module_init(MODULE_INIT_MACHINE) 是讓 mc->init = pc_init1.
  然後當 machine_class = find_default_machine() 時, machine_class 的 init 就會執行 pc_init1()

pc_init1()
~~~~~~~~~~

pc_cpus_init() + pc_memory_init()

pc_cpus_init()
""""""""""""""

- cpu_model: builtin_x86_defs
  
  - "SandyBridge", x86 CPUID flags ... etc.

- for loop: pc_new_cpu() => cpu_x86_create() 

  - fill in ``CPUX86State``

- x86_cpu_realizefn() => qemu_init_vcpu() => qemu_kvm_start_vcpu()::

      //创建VPU对于的qemu线程，线程函数是qemu_kvm_cpu_thread_fn
      qemu_thread_create(cpu->thread, thread_name, qemu_kvm_cpu_thread_fn,
                         cpu, QEMU_THREAD_JOINABLE);

      //如果线程没有创建成功，则一直在此处循环阻塞。说明多核vcpu的创建是顺序的
      while (!cpu->created) {
          qemu_cond_wait(&qemu_cpu_cond, &qemu_global_mutex);
      }

- qemu_kvm_cpu_thread_fn(): 真正的 cpu thread 函數.

  - kvm_init_vcpu()
    
    - KVM_CREATE_VCPU
    - KVM_GET_VCPU_MMAP_SIZE get memory mapping of ``env->kvm_run``.
    - kvm_arch_init_vcpu()

  - qemu_kvm_init_cpu_signals(): KVM_SET_SIGNAL_MASK
  - qemu_cond_signal(&qemu_cpu_cond) => kvm_cpu_exec(env) in while loop
  - kvm_cpu_exec(): KVM_RUN

- sources

  - ``hw/i386/pc.c``: pc_cpus_init(), pc_new_cpu()
  - ``target-i386/cpu.c``: x86_cpu_realizefn()
  
    - (register and invoke) TypeInfo x86_cpu_type_info => x86_cpu_common_class_init() => x86_cpu_realizefn()
    - qom or qobject model
    - ``target-i386/cpu-qom.h``: X86_CPU()

      - ``include/qom/object.h``: OBJECT_CHECK()

  - ``cpus.c``: qemu_init_vcpu(), qemu_kvm_start_vcpu(), qemu_kvm_cpu_thread_fn()

pc_memory_init()
""""""""""""""""

Part3 CPU Virtualization
------------------------

http://www.oenhan.com/kvm-src-3-cpu

- cpu virtualization: time-sharing

  - restore state (for context switch): VMCS, VMExit reason ... etc
  - resource isolation: VMX root mode

- VMCS register

  - VM-execution controls: Determines what operations cause VM exits
  - Guest-state and Host-state area: Guest/Host OS state for context switch (save & restore)
  - VM-exit controls: Example: MSR save-load list
  - VM-entry controls: Including injecting events (interrupts, exceptions) on entry

