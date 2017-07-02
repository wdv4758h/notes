Preemptive Scheduler and Timer Interrupt
========================================

- presequite

   - CPU, machine execution cycle (計算機概論:CPU arch or 計算機組織)

- after reading

   - preemptive scheduling should be based on CPU feature - Interrupt, or other special CPU features
   - CPU execution using machine execution cycle and interrupt
   - User code and Kernel code interacts by interrupt.

     - User code => interrupt => Kernel code
     - Kernel code => reset process context (Registers) => switch to User code (to single process)

- real world system

   - Context Switch: Yield(sched_yield()), IO Blocking(read()/write())
   - Timer Interrupt: irq0 handler => scheduler (http://www.makelinux.net/books/lkd2/ch10lev1sec5)
   - Scheduler: Linux CFS
   - Time Slice: HZ, tick, jiffies

Data
----

- Context Switch 

  - Yield
  - IO Blocking
  - Termination
  - [Only Preemptive] Interrupt

- Context Switch 

  - Yield: e.g. sched_yield() syscall in Linux/FreeBSD, POSIX:2001
  - IO Blocking: e.g. file IO syscall like read()/write() in Linux/FreeBSD, POSIX:2001
  - Termination
  - [Only Preemptive] Interrupt

Ref
---
- [Theory] State Transition of Preemptive/Non-Preemptive Scheduling

  - https://www.cs.princeton.edu/courses/archive/fall09/cos318/lectures/ThreadImplementation.pdf P.9/10

- tick, HZ, jiffies: http://adrianhuang.blogspot.tw/2007/10/linux-kernel-hz-tick-and-jiffies.html
- nice value in linux CFS: http://lxr.free-electrons.com/source/Documentation/scheduler/sched-nice-design.txt?v=4.3
  
  - other document in linux scheduler: http://lxr.free-electrons.com/source/Documentation/scheduler/?v=4.3
