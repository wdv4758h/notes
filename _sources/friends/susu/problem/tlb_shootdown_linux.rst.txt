- [RFC PATCH 2/2] ARMv7: Invalidate the TLB before freeing page tables: http://lists.infradead.org/pipermail/linux-arm-kernel/2011-February/042029.html

  - 看起來似乎是 speculative execution 造成 TLB invalidating 必須要比 freeing page table 來的早, 不然就有機會拿到舊的 TLB entry 來執行.
  - how x86 handle TLB flush: ``include/asm-generic/tlb.h``, ``arch/x86/include/asm/tlb.h``
  - TLB shootdown code is supposed to make this more efficient than 
    having to issue a broadcasted TLB invalidate for every page as we remove each one in sequence?
  - tlb_remove_page(), zap_pte_range(), tlb_end_vma()

- Context switch and TLB: http://www.wowotech.net/process_management/context-switch-tlb.html

  - TLB 如果沒使用 ASID, context switch 時需要 flush local TLB entries
  - 使用 ASID, 有機會在多次 context switch 之後仍然保持 TLB hot. 具體來說會根據 TLB entry 數, process 數跟 per process 的 page 數目有關.
  - 反之, 使用 ASID 在 SMP 系統上, 可能會造成多餘的 TLB false sharing, 引發 TLB shootdown 降低效能.
  - context switch 到 linux kthread, 可以使用 lazy TLB mode 減少 TLB invalidation
  - ARM 的 TLB invalidate 指令似乎支援對 multi-core 使用(shared domain), 就不需要用 IPI 送 TLB invalidate 指令來給多 cpu core 執行.

- linux-patches/tlb-shootdown-measurement: https://github.com/x-y-z/linux-patches/blob/master/tlb-shootdown-measurement/0003-tracing-add-a-reason-for-tracing-tlb-shootdown-initi.patch

- ``arch/arm/include/asm/tlb.h`` 寫說, 有三種方法使用 TLB shootdown 的 code
  
  a. unmap range of vmas: unmap_region(), zap_page_range()
  b. unmap all vmas: exit_mmap()
  c. unmap argument pages: shift_arg_pages()

- ``arch/arm64/include/asm/tlbflush.h``: http://lxr.free-electrons.com/source/arch/arm64/include/asm/tlbflush.h?v=4.8#L28

  - arm64 TLB management code?

unmap_region()::

    - unmap_region()
      - tlb_gather_mmu() => __tlb_reset_range()
      - free_pgtables()
      - tlb_finish_mmu()
        - tlb_flush_mmu()
          - tlb_flush_mmu_tlbonly(): flush tlb entry
            - tlb_flush()
            - mmu_notifier_invalidate_range()
            - __tlb_reset_range()
          - tlb_flush_mmu_free(): free pages

    - [x86] tlb_flush()
    - [x86] flush_tlb_mm_range()
    - [x86] flush_tlb_others() = native_flush_tlb_others() // trace_tlb_flush(TLB_REMOTE_SEND_IPI)
    - smp_call_function_many() + flush_tlb_func

    // mmu_notifier, mmu_notifier_op // implemented in ./drivers/iommu/{intel-svm.c, amd_iommu_v2.c}
