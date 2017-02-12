- (NUMA) futexes and hash table collisions: http://blog.stgolabs.net/2014/01/futexes-and-hash-table-collisions.html
- process private futex: http://lwn.net/Articles/229668/

source code::

    kernel/futex.c
    kernel/futex-compat.c

    include/linux/futex.h
    include/uapi/linux/futex.h
    include/asm-generic/futex.h

    arch/x86/include/asm/futex.h

headers::

    include/linux/futex.h

        - struct futex_key
        - interface: do_futex()

    include/uapi/linux/futex.h
        
        - macros

    include/asm-generic/futex.h

        - futex_atomic_op_inuser()
        - futex_atomic_cmpxchg_inatomic()
        - use preempt_disable() & pagefault_disable() in uniprocessor system.
        - not implement in SMP

    arch/x86/include/asm/futex.h

        - macro: __futex_atomic_op1, 2
        - futex_atomic_op_inuser()
        - futex_atomic_cmpxchg_inatomic()

          - user_atomic_cmpxchg_inatomic(): arch/x86/include/asm/uaccess.h

            - macro
            - cmpxchgb, w, l, q: 4 size support. in __user_atomic_cmpxchg_inatomic()

- DS::

    __futex_data: hash bucket array
    struct futex_hash_bucket: hash bucket
        {
            ...
            struct plist_head chain; // linked-list of hashmap value (futex_p)
        }

    struct futex_key: hash key
    struct futex_q: hash value.

    - Each key may have multiple value(futex_q structure), one futex_q for each task waiting on this futex.

- entry::

    SYSCALL_DEFINE6(futex)
    do_futex()

    SYSCALL_DEFINE2(set_robust_list)
    SYSCALL_DEFINE3(get_robust_list)

- behavior::

    - futex_key equal: futex_key.both 的三個 member 相同
        
----

Misc

- smp_mb__after_atomic()

  - smp_mb: memory barrier

----

struct::

    union futex_key

        - shared, private, both
        - word(pgoff/address), ptr(inode/mm), offset

    struct futex_q
    struct futex_hash_bucket
    struct futex_pi_state

::

    SYSCALL_DEFINE6(futex)
    static void __init futex_detect_cmpxchg(void)
    static int __init futex_init(void)
