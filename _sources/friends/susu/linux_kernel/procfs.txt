- curious about

  1. kernel space to user space, like dmesg, relayfs

     - system call, devfs, sysfs

  2. htop related, process related info

     - memory map: pmap, procinfo(bsd)
     - file descriptors: lsof

  3. kernel allocate physical memory

     - buddyinfo, slabinfo, vmallocinfo
     - ?: dma, iomem, ioports

  4. interrupt
     
     - interrupts, softirqs

- note

  - memory: /proc/<pid>/maps, smaps

    - android procrank: http://stackoverflow.com/questions/22372960/is-this-explanation-about-vss-rss-pss-uss-accurately
    - RSS = vma size - cache in disk (private + shared page without cache)
    - PSS = (without cache?) private page size + (shared page size / number of process sharing)
      
      - sum is system memory use?

    - * USS = only private page

      - process creation need USS size memory, killing release USS size memory in the current condition.
