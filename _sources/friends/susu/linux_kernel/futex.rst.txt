- 何謂 "fast" mutex?
- 如何只在 user space 完成 uncontended lock
- 實作多個 wait queues: hash table of wait queue
- 進階功能/issue

  - robust futex: thread exit without release mutex
  - PI futex: thread priority-awared wake-up
  - memory and parallel issue: process private futex, memory page lock
  - bitset conditional wake-up (for rw-lock)
  - requeueing waiters for PI futex (used in condvar boardcast)

- Now what

  - NUMA-optimized futex hash table
  - adaptive futex
  - interruptible futex

----

futex: fast user-space mutex

何謂 "fast" mutex?

- uncontended lock 的時候不需要進入 kernel space, 只有 contended lock 的時候需要.
- 簡單來說的話就是不碰到 wait queue 的時候, 不需要進入 kernel space.

mutex lock 的組成

- uncontended lock

  - lock variable
  - atomic lock acquision
  - lock release

- contended lock

  - waitqueue: sleep and wake up

hash table of many wait queues

- 處理任意數量的 mutex lock: 多個 wait queue, 並且以 lock variable 的 memory address(uaddr) 為 unique hash key 來尋找對應的 wait queue.
- 256 buckets 的 hash table, hash collision 的解法類似使用 linked list 的 chaining.

.. image:: image/dvh-futexes.png

----

- [Userspace] very fast uncontended lock acquisition and release
- futex state => 32 bits userspace variable
- uncontended case: atomic operation to change futex state
- contended case: kernel space sleep and wakeup

----

futex_key, futex_queue, futex_q

- unordered_map: key = uaddr, value = futex_queue

  - hash_futex(uaddr) -> futex_queue
  - futex_queues = vector<futex_q>
  - futex_q = futex_key + tid (task id)

----

advanced: PI and robust futex

- robust lists: 當持有 mutex lock 的 thread 在未釋放 lock 前異常終止. http://lwn.net/Articles/172149/
- priority inheritance (PI) chains: 處理 priority inversion 的問題, wait queue 中要由 high priority 的 thread 搶到 lock. http://lwn.net/Articles/177111/
- note: PI 跟 robust futex 的 state 不只跟 lock variable 有關, 還跟持有 lock 的 owner thread 有關. 需要特殊的 lock construction 才能讓 uncontended lock 依舊處於 userspace.

optimization

- process private futex

  - private futex 只會在一個 virtual address space 裡, 可以用 virtual address 來唯一分辨. 相反的 pshared futex 在不同 process 間有不同 virtual address, 必須要用 physical address 才能唯一分辨
  - 所以, 優化就是用 virtual address 取代 physical address 來做 futex queue 的 key
  - 減少 VMA 上 rw_semaphore (mmap_sem) 的使用, 減少 system-wide 的 contention (address translation 會使得 VMA 進入 read lock.)
  - 也減少了 private futex 的 reference counting 使用 atomic operation 的次數, 因此減少了 SMP 機器上的 cache-line bouncing.
  - http://lwn.net/Articles/229668/

- 使用 get_user_pages_fast() 取代 get_user_pages() -> 減少 mmap_sem 的 dependency

  - pushing the mmap_sem locks down tightly around the slow paths (September 2008)
    
    - removing much of the virtual memory related logic from kernel/futex.c 
  
  - Due to their dependence on user space addresses
  - Holding mmap_sem 會使得 fault logic 變得複雜, 因為 它(mmap_sem?) 必須要在呼叫 get_user() 之前被 release

- Bitset conditional wakeup -> 優化 rwlock 實作

  - FUTEX_WAIT_BITSET, FUTEX_WAKE_BITSET
  - 指定一個 bitmask, 限制有相同 bitset (或是 bitset 的 superset, 透過 FUTEX_BITSET_MATCH_ANY) 的 task 才能被喚醒
  - `Sleeping Read-Write Locks (bitset and rw-lock) <http://locklessinc.com/articles/sleeping_rwlocks/>`_ 

- requeueing waiters from a non-PI futex to a PI futex

  - 因為 PI futex, glibc 的 condvar 在 pthread_cond_broadcast 時會 wake up 所有 waiters.
  - 不能使用到 FUTEX_REQUEUE 的好處, 因為缺乏 PI futexes requeueing 的支援.
  - 壞處: wake-up storm, 無法使高優先度 task 先 acquire lock.
  - FUTEX_CMP_REQUEUE_PI patch
  
    - 使用 condvar 時, 可以有 guaranteed wake-up order 和更少的總 wake-ups 數目.
    - http://static.lwn.net/images/conf/rtlws11/papers/proc/p10.pdf
    - https://www.osadl.org/fileadmin/dam/presentations/RTLWS11/dvhart-requeue-pi.pdf

Now What?

- Man pages
- Adaptive futexes: busy-waiting 跟 sleeping 的效能取捨. 目前的 Adaptive futexes 作法是, thread acquire lock 會一直 busy-waiting 到該 thread 被 context switch. 請見 `Adaptive spinning futexes`_
- Interruptible futexes: Futex operations restart themselves in the event of a signal, or return ECANCELED to user space. (FUTEX_INTERRUPTIBLE)
- Scalability enhancements: NUMA-optimized futex hash tables. 

  - 2014 的 patch `futexes and hash table collisions`_
  
    - aligned hash bucket (``____cacheline_aligned_in_smp`` for ``struct futex_hash_bucket``) 
    - large NUMA-aware table: 增加 bucket 數為 256 * ncpu (round up 到 2 的指數)
    - ...

- Futex test suite

.. _`Adaptive spinning futexes`: https://lwn.net/Articles/387246/
.. _`futexes and hash table collisions`: http://blog.stgolabs.net/2014/01/futexes-and-hash-table-collisions.html

More
----
mmap_sem, get_user_pages(), get_user_pages_fast()

- https://lwn.net/Articles/548098/
- https://lwn.net/Articles/591978/
- https://chengyihe.wordpress.com/2015/12/28/kernel-mm-task-mm-mmap_sem/

- ``mmap_sem`` is rwlock of ``mm_struct``, operation to ``mm_struct`` members will trigger the lock.

Reference
---------
- 2009, A futex overview and update: https://lwn.net/Articles/360699/
- 2010, Futex Cheat Sheet: http://locklessinc.com/articles/futex_cheat_sheet/
- 2014, Linux futex 浅析: http://blog.sina.com.cn/s/blog_e59371cc0102v29b.html

- Priority Spin Locks: http://locklessinc.com/articles/priority_locks/
- Linux pi_futex 浅析: https://yq.aliyun.com/articles/6044

Questions?
----------
- multiple key 共用 list 造成的 performance loss 是否嚴重? (很像 hash table 的 seperate chaining)

TODO or more
------------
- 完成 futex tutorial
- private futex 跟 memory management(mmap_sem) 的關係
- linux/futex.c source code overview

interesting

- FreeBSD linux compatibility layer - futex operator and flags: https://wiki.freebsd.org/linux-kernel#futex_operators_and_flags
- MUSL libc
- 關於在 Linux 下, 多個無關的程序 (process) 互斥存取同一片共享記憶體的問題: https://segmentfault.com/a/1190000000630435
