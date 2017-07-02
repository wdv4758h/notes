- PERCENT_MEM: based on RES
- VIRT: memory of total program size.
- RES: resident set size, total - in swap/file system
- SHR: size of shared pages

::

    ps -p <pid> -o vsz,rss,trs,drs,%cpu,%mem
