========================================
MPI
========================================

SSH Key Setup
========================================

.. code-block:: sh

    $ ssh-keygen -t rsa -b 4096 -C "username@mail.com"

    # method 1
    $ scp ~/.ssh/id_rsa.pub HOSTNAME:~/.ssh/
    $ ssh HOSTNAME
    $ cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys

    # method 2
    $ ssh-copy-id -i ~/.ssh/id_rsa.pub HOSTNAME


Hosts File
========================================

.. code-block:: sh

    $ cat ~/hostfile
    10.10.0.173 slots=4
    10.10.0.174 slots=4
    10.10.0.175 slots=4
    10.10.0.176 slots=4


.. code-block:: sh

    $ mpirun -np 16 --hostfile ~/hostfile hostname
    master
    slave1
    slave2
    slave2
    master
    slave1
    slave2
    master
    slave1
    master
    slave2
    slave1
    slave3
    slave3
    slave3
    slave3
    $ mpirun -np 16 --hostfile ~/hostfile uptime
     07:19:03 up 22 days, 0 min, 15 users,  load average: 2.09, 2.03, 2.02
     07:19:03 up 22 days, 0 min, 15 users,  load average: 2.09, 2.03, 2.02
     07:19:03 up 22 days, 0 min, 15 users,  load average: 2.09, 2.03, 2.02
     07:19:03 up 22 days, 0 min,  1 user,  load average: 2.08, 2.03, 2.01
     07:19:02 up 22 days, 0 min,  2 users,  load average: 2.00, 2.01, 2.05
     07:19:03 up 22 days, 0 min,  1 user,  load average: 2.08, 2.03, 2.01
     07:19:03 up 22 days, 0 min, 15 users,  load average: 2.09, 2.03, 2.02
     07:19:03 up 22 days, 0 min,  1 user,  load average: 2.08, 2.03, 2.01
     07:19:03 up 22 days, 0 min,  1 user,  load average: 2.08, 2.03, 2.01
     07:19:02 up 22 days, 0 min,  2 users,  load average: 2.00, 2.01, 2.05
     07:19:02 up 22 days, 0 min,  2 users,  load average: 2.00, 2.01, 2.05
     07:19:02 up 22 days, 0 min,  2 users,  load average: 2.00, 2.01, 2.05
     07:19:03 up 22 days, 0 min,  4 users,  load average: 2.00, 2.01, 2.01
     07:19:03 up 22 days, 0 min,  4 users,  load average: 2.00, 2.01, 2.01
     07:19:03 up 22 days, 0 min,  4 users,  load average: 2.00, 2.01, 2.01
     07:19:03 up 22 days, 0 min,  4 users,  load average: 2.00, 2.01, 2.01
    $ mpirun -np 16 --hostfile ~/hostfile ~/hello.out
    Hello world from processor master, rank 1 out of 16 processors
    Hello world from processor slave1, rank 6 out of 16 processors
    Hello world from processor slave2, rank 9 out of 16 processors
    Hello world from processor slave3, rank 15 out of 16 processors
    Hello world from processor slave1, rank 5 out of 16 processors
    Hello world from processor slave2, rank 8 out of 16 processors
    Hello world from processor master, rank 0 out of 16 processors
    Hello world from processor slave3, rank 13 out of 16 processors
    Hello world from processor slave3, rank 14 out of 16 processors
    Hello world from processor slave3, rank 12 out of 16 processors
    Hello world from processor slave2, rank 10 out of 16 processors
    Hello world from processor slave1, rank 4 out of 16 processors
    Hello world from processor master, rank 3 out of 16 processors
    Hello world from processor slave2, rank 11 out of 16 processors
    Hello world from processor slave1, rank 7 out of 16 processors
    Hello world from processor master, rank 2 out of 16 processors


OpenMPI
========================================

Build :

.. code-block:: sh

    $ mpicc -v
    Using built-in specs.
    COLLECT_GCC=/usr/bin/gcc
    COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-unknown-linux-gnu/5.2.0/lto-wrapper
    Target: x86_64-unknown-linux-gnu
    Configured with: /build/gcc-multilib/src/gcc-5.2.0/configure --prefix=/usr --libdir=/usr/lib --libexecdir=/usr/lib --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=https://bugs.archlinux.org/ --enable-languages=c,c++,ada,fortran,go,lto,objc,obj-c++ --enable-shared --enable-threads=posix --enable-libmpx --with-system-zlib --with-isl --enable-__cxa_atexit --disable-libunwind-exceptions --enable-clocale=gnu --disable-libstdcxx-pch --disable-libssp --enable-gnu-unique-object --enable-linker-build-id --enable-lto --enable-plugin --enable-install-libiberty --with-linker-hash-style=gnu --enable-gnu-indirect-function --enable-multilib --disable-werror --enable-checking=release --with-default-libstdcxx-abi=gcc4-compatible
    Thread model: posix
    gcc version 5.2.0 (GCC)
    $ OMPI_CC=clang mpicc -v
    clang version 4.7.0 (tags/RELEASE_370/final)
    Target: x86_64-unknown-linux-gnu
    Thread model: posix
    Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-unknown-linux-gnu/5.2.0
    Found candidate GCC installation: /usr/bin/../lib64/gcc/x86_64-unknown-linux-gnu/5.2.0
    Found candidate GCC installation: /usr/lib/gcc/x86_64-unknown-linux-gnu/5.2.0
    Found candidate GCC installation: /usr/lib64/gcc/x86_64-unknown-linux-gnu/5.2.0
    Selected GCC installation: /usr/bin/../lib64/gcc/x86_64-unknown-linux-gnu/5.2.0
    Candidate multilib: .;@m64
    Candidate multilib: 32;@m32
    Selected multilib: .;@m64



Show Flags :

.. code-block:: sh

    # Show the flags necessary to compile MPI C applications
    $ mpicc --showme:compile
    -pthread
    # Show the flags necessary to link MPI C applications
    $ mpicc --showme:link
    -pthread -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags -L/usr/lib/openmpi -lmpi
    $ mpicc hello.c --showme
    gcc hello.c -pthread -Wl,-rpath -Wl,/usr/lib/openmpi -Wl,--enable-new-dtags -L/usr/lib/openmpi -lmpi



Makefile for use your compiler directly (not using OpenMPI wrapper compilers) :

.. code-block:: make

    MPI_COMPILE_FLAGS = $(shell mpicc --showme:compile)
    MPI_LINK_FLAGS = $(shell mpicc --showme:link)

    my_app: my_app.c
            $(CC) $(MPI_COMPILE_FLAGS) my_app.c $(MPI_LINK_FLAGS) -o my_app


Information :

.. code-block:: sh

    $ ompi_info

::

    　               Package: Open MPI builduser@anatol Distribution
                    Open MPI: 1.10.1
      Open MPI repo revision: v1.10.0-178-gb80f802
       Open MPI release date: Nov 03, 2015
                    Open RTE: 1.10.1
      Open RTE repo revision: v1.10.0-178-gb80f802
       Open RTE release date: Nov 03, 2015
                        OPAL: 1.10.1
          OPAL repo revision: v1.10.0-178-gb80f802
           OPAL release date: Nov 03, 2015
                     MPI API: 3.0.0
                Ident string: 1.10.1
                      Prefix: /usr
     Configured architecture: x86_64-unknown-linux-gnu
              Configure host: anatol
               Configured by: builduser
               Configured on: Wed Nov  4 10:38:20 PST 2015
              Configure host: anatol
                    Built by: builduser
                    Built on: Wed Nov  4 11:01:25 PST 2015
                  Built host: anatol
                  C bindings: yes
                C++ bindings: yes
                 Fort mpif.h: yes (all)
                Fort use mpi: yes (full: ignore TKR)
           Fort use mpi size: deprecated-ompi-info-value
            Fort use mpi_f08: yes
     Fort mpi_f08 compliance: The mpi_f08 module is available, but due to limitations in the /usr/bin/gfortran compiler, does not support the following: array subsections, direct passthru (where possible) to underlying Open MPI's C functionality
      Fort mpi_f08 subarrays: no
               Java bindings: no
      Wrapper compiler rpath: runpath
                  C compiler: gcc
         C compiler absolute: /usr/bin/gcc
      C compiler family name: GNU
          C compiler version: 5.2.0
                C++ compiler: g++
       C++ compiler absolute: /usr/bin/g++
               Fort compiler: /usr/bin/gfortran
           Fort compiler abs:
             Fort ignore TKR: yes (!GCC$ ATTRIBUTES NO_ARG_CHECK ::)
       Fort 08 assumed shape: yes
          Fort optional args: yes
              Fort INTERFACE: yes
        Fort ISO_FORTRAN_ENV: yes
           Fort STORAGE_SIZE: yes
          Fort BIND(C) (all): yes
          Fort ISO_C_BINDING: yes
     Fort SUBROUTINE BIND(C): yes
           Fort TYPE,BIND(C): yes
     Fort T,BIND(C,name="a"): yes
                Fort PRIVATE: yes
              Fort PROTECTED: yes
               Fort ABSTRACT: yes
           Fort ASYNCHRONOUS: yes
              Fort PROCEDURE: yes
               Fort C_FUNLOC: yes
     Fort f08 using wrappers: yes
             Fort MPI_SIZEOF: yes
                 C profiling: yes
               C++ profiling: yes
       Fort mpif.h profiling: yes
      Fort use mpi profiling: yes
       Fort use mpi_f08 prof: yes
              C++ exceptions: no
              Thread support: posix (MPI_THREAD_MULTIPLE: no, OPAL support: yes, OMPI progress: no, ORTE progress: yes, Event lib: yes)
               Sparse Groups: no
      Internal debug support: no
      MPI interface warnings: yes
         MPI parameter check: runtime
    Memory profiling support: no
    Memory debugging support: no
                  dl support: yes
       Heterogeneous support: no
     mpirun default --prefix: no
             MPI I/O support: yes
           MPI_WTIME support: gettimeofday
         Symbol vis. support: yes
       Host topology support: yes
              MPI extensions:
       FT Checkpoint support: no (checkpoint thread: no)
       C/R Enabled Debugging: no
         VampirTrace support: yes
      MPI_MAX_PROCESSOR_NAME: 256
        MPI_MAX_ERROR_STRING: 256
         MPI_MAX_OBJECT_NAME: 64
            MPI_MAX_INFO_KEY: 36
            MPI_MAX_INFO_VAL: 256
           MPI_MAX_PORT_NAME: 1024
      MPI_MAX_DATAREP_STRING: 128
               MCA backtrace: execinfo (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                MCA compress: gzip (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                MCA compress: bzip (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA crs: none (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA db: print (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                      MCA db: hash (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                      MCA dl: dlopen (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA event: libevent2021 (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA hwloc: external (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA if: linux_ipv6 (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA if: posix_ipv4 (MCA v2.0.0, API v2.0.0, Component v1.10.1)
             MCA installdirs: env (MCA v2.0.0, API v2.0.0, Component v1.10.1)
             MCA installdirs: config (MCA v2.0.0, API v2.0.0, Component v1.10.1)
              MCA memchecker: valgrind (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA memory: linux (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA pstat: linux (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA sec: basic (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA shmem: posix (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA shmem: sysv (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA shmem: mmap (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA timer: linux (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA dfs: app (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                     MCA dfs: test (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                     MCA dfs: orted (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                  MCA errmgr: default_app (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                  MCA errmgr: default_tool (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                  MCA errmgr: default_hnp (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                  MCA errmgr: default_orted (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA ess: env (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA ess: hnp (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA ess: singleton (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA ess: tool (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                   MCA filem: raw (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                 MCA grpcomm: bad (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA iof: orted (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA iof: mr_hnp (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA iof: hnp (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA iof: tool (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA iof: mr_orted (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA odls: default (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA oob: tcp (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA plm: isolated (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA plm: rsh (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA ras: simulator (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA ras: loadleveler (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: rank_file (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: resilient (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: mindist (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: ppr (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: seq (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: round_robin (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA rmaps: staged (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA rml: oob (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA routed: direct (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA routed: binomial (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA routed: radix (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA routed: debruijn (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA state: app (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: staged_hnp (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: tool (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: orted (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: novm (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: dvm (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: hnp (MCA v2.0.0, API v1.0.0, Component v1.10.1)
                   MCA state: staged_orted (MCA v2.0.0, API v1.0.0, Component v1.10.1)
               MCA allocator: bucket (MCA v2.0.0, API v2.0.0, Component v1.10.1)
               MCA allocator: basic (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA bcol: ptpcoll (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA bcol: basesmuma (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA bml: r2 (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA btl: sm (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA btl: vader (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA btl: tcp (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA btl: self (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: basic (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: libnbc (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: tuned (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: inter (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: sm (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: hierarch (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: self (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA coll: ml (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA dpm: orte (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA fbtl: posix (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA fcoll: static (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA fcoll: two_phase (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA fcoll: individual (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA fcoll: dynamic (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA fcoll: ylib (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA fs: ufs (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA io: romio (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                      MCA io: ompio (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA mpool: sm (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                   MCA mpool: grdma (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA osc: sm (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA osc: pt2pt (MCA v2.0.0, API v3.0.0, Component v1.10.1)
                     MCA pml: v (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA pml: bfo (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA pml: ob1 (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA pml: cm (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA pubsub: orte (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                  MCA rcache: vma (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                     MCA rte: orte (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA sbgp: basesmsocket (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA sbgp: p2p (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA sbgp: basesmuma (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                MCA sharedfp: lockedfile (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                MCA sharedfp: individual (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                MCA sharedfp: sm (MCA v2.0.0, API v2.0.0, Component v1.10.1)
                    MCA topo: basic (MCA v2.0.0, API v2.1.0, Component v1.10.1)
               MCA vprotocol: pessimist (MCA v2.0.0, API v2.0.0, Component v1.10.1)


More Information :

.. code-block:: sh

    $ ompi_info --all --parsable
    ...



MPI
========================================

Parallel For
------------------------------


Reference
========================================

* `MPI Tutorial <http://mpitutorial.com/tutorials/>`_
* `Wikipedia - Open MPI <https://en.wikipedia.org/wiki/Open_MPI>`_
* `Wikipedia - MPICH <https://en.wikipedia.org/wiki/MPICH>`_
* `Wikipedia - Message Passing Interface <https://en.wikipedia.org/wiki/Message_Passing_Interface>`_
* `Open MPI - FAQ - Compiling MPI applications - How do I override the flags specified by Open MPI's wrapper compilers? (v1.1 series and beyond) <http://www.open-mpi.org/faq/?category=mpi-apps#override-wrappers-after-v1.0>`_
* `Open MPI - FAQ - Running MPI jobs <https://www.open-mpi.org/faq/?category=running>`_
