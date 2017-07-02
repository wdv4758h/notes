maximum number of open file descriptor per process.

- linux

  tuning::

    ulimit -n [LIMIT]

  get fd info of process::

    lsof -p [pid] # lsof based on procfs

- freebsd

  tuning: https://www.freebsd.org/doc/en/books/handbook/configtuning-kernel-limits.html
  
  get fd info of process::

    procstat -f [pid]
