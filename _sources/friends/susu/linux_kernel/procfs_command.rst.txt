- pmap
- lsof
- timer interrupt frequency

  - ``cat /proc/interrupts | grep timer; and sleep 1; and cat /proc/interrupts | grep timer``

- vmstat (``man vmstat``)

  - vmstat [delay] [count]
  - delay: repeat distance
  - count: repeat times
  - -a: active/inactive memory
  - -S [unit]: unit is k, K, m, M
  - -t: print timestamp
  - -w: width, enlarges print message field width
  - other branch

    - -f: fork time after boot
    - -s: many statistic data: boot time, context switch ... etc.
    - -m: slab info
    - -p [partition]: partition info

  ::

      procs -----------memory---------- ---swap-- -----io---- -system-- ------cpu-----
       r  b   swpd   fee   buff  cache   si   so    bi    bo   in   cs us sy id wa st
       1  0      0 541376 430476 4166868    0    0    22    94  309  286 20  7 72  1  0

  - proc: r/b: number of running/IO blocking(waiting) process
  - memory:

    - swpd
    - free
    - buff, cache
    - inactive, active

  - si/so: swap in/out per sec
  - bi/bo: write/read disk block per sec
  - in/cs: interrupt/context switch per sec
  - CPU
    
    - us: Time spent running non-kernel code. (user time, including nice time)
    - sy: Time spent running kernel code. (system time)
    - id: Time spent idle, This includes IO-wait time.
    - wa: Time spent waiting for IO, included in idle.
    - st: Time stolen from a virtual machine. Prior to Linux 2.6.11, unknown.

  - ``getstat()`` in ``/proc/sysinfo.c``::

      non-nice user cpu ticks  |  cpu_use
      nice user cpu ticks      |  cpu_nic 
      system cpu ticks         |  cpu_sys 
      idle cpu ticks           |  cpu_idl
      IO-wait cpu ticks        |  cpu_iow 
      IRQ cpu ticks            |  cpu_xxx 
      softirq cpu ticks        |  cpu_yyy 
      stolen cpu ticks         |  cpu_zzz
      pages paged in           |  pgpgin 
      pages paged out          |  pgpgout 
      pages swapped in         |  pswpin 
      pages swapped out        |  pswpout
      interrupts               |  intr 
      CPU context switches     |  ctxt
                               |  running
                               |  blocked
      boot time                |  btime 
      forks                    |  processes
  
  - ``vmstat -s``::

      total memory
        used memory
        active memory, inactive memory
        free memory
        buffer memory
        swap cache
      total swap
        used swap, free swap

