RISC-V
===============================================================================


open ISA

RISC-V foundation

- No licensing fee

- for all computing devices

- make BSD for standard RISC-V

    - from microcontroller to supercomputers


Origin

    ISA research

    x86/ARM too complex

    - clean-state ISA


2014/5 release frozen user spec


Fundation member 都大頭



Background
----------------------------------------------------------------------

- `Reduced`

- load/store arch

    - no complex memory addressing mode

- easy to implement

- Berkeley Risc-I/II influenced SPARC

- MIPS

- ARM -> advance RISC....


ISA
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

- Fifth RISC ISA from Berkeley
- Modular ISA (?)
- <50 hw instructions in base ISA


- design for extension


int
- RV32I

- RV64I

- RV128I


Privilege Levels

    L0-3


Virtual memory

    Page-based for S-mode


diff register for kernel mode and firmware mode


spec on GH


RISC-V book

H/W
----------------------------------------------------------------------

HDLs

- VHDL, verilog...


Free Chips Project


    - Rocket chip
        Parameterized RISC-V SoC generator

    - Rocket Core

github.com/ucb-bar

    - BOOM

    - ...


SiFive H/W

    - GH

    - low cost chips


`HiFive1` $60?


LowRISC

Shakti

PULPino

PicoRV32


Simulation
    - Spike - RISC-V ISA simulator

    - QEMU

    - RISCVEMU

    - gem5



DTrace
===============================================================================

For large system

LLVM IR fat binary

distributed DTrace

DTrace as runtime debugger

    - not like lldb

    - DTrace always on

github.com/cadets/freebsd


Design Principles
----------------------------------------------------------------------

- no overhead `if not in use`

- production ready

    - no panic the kernel


- Protect the kernel at all costs

    - safety first


`Your Grandparents Computers`


Tuning
----------------------------------------------------------------------

- bufsize

- switchrate

- dynvarsize

Default for limited resources


Recent Improvement
----------------------------------------------------------------------

- kernel dev 寫的，所以是可怕的 output

Performance Analysis


D Language Improvement
----------------------------------------------------------------------

Structered like awk


copyoutmbuf - copy out mbuf


Audit Provider
----------------------------------------------------------------------

subsystem for logging

`provider`
    - DTrace code for collecting a set of event


Performance
----------------------------------------------------------------------

- Drop record

- kernel can kill them if load get high


Loom
----------------------------------------------------------------------

base on LLVM

USDT
    userland statically defined tracing


not only one
----------------------------------------------------------------------

eBPF


bcc c like front end

ply python front end

Brendan Gregg 2017


OpenDTrace
----------------------------------------------------------------------

Cross platform

RFD Process

clean room re-implementation (license issue)


mmap
===============================================================================

Process address space
----------------------------------------------------------------------

sysbreak system call
break system call
sbreak system call
sbrk()
brk()
4.2 BSD mmap

Memory sharing
----------------------------------------------------------------------

4.2BSD Memory interface
----------------------------------------------------------------------

mmap()

    allocate memory

mremap()

munmap()

mprotect()

madvise()
    - hint for kernel.

mincore()
    - ?

sbrk()

sstk()



but only sbrk() implemented



OpenBSD 3.3 implement W^X

CHERI project

    - pointer bounds and premissions


mmap() API issue
----------------------------------------------------------------------

- Too many arguments

- no concept of address space onwership

REC: cmmap
----------------------------------------------------------------------

requests object instead of many args


GPU
===============================================================================

HPC

$$$$$$$

- poudrire && pkg

  cutomized, optimzied  pkg

lang/flang



    slurm-wlm
    science/libxc
    math/tblis

    blis


TigerCI

ADF suit


hwpmc
benchmarks/flame...

OpenCL on CPU: lang/pocl
lang/beignet
lang/clover

cltune
clpeak

clblas
clbast

ROCm Radeon Open Compute Project
graphic/drm-next-kmod

HIP (CUDA emulator)
hiptensorflow


Bhyve
===============================================================================

fbuf

fbuf <-> VNC
guest 的畫面從 fbuf 拿出來再塞到 VNC server 裡面
1/30 (30 fps?) require a lot of b/w


ZFS
===============================================================================

Allan Jude

volume manager

all data and metadata checksummed

optional transparent compression

CoW snaphots and clone (writable snapshots)

fs tuning 顆粒度 : per fs

snapshots and clones
----------------------------------------------------------------------

- snapshots can cross fs


- boot env

    - on root fs, snapshots before upgrading, then clone it

    - boot manage allow you to select them

    - be(8) libbe(3)

    - deep


BE as golden images


    `zfs send | xz > ...xz`

    - zfsbootcfg (ZFS nextboot)

encryption
    - GELI

    - ZFS Native
        - optional encryption. not all metadata


Channel Porgram

    - 之前是 blocking 的 command?

    - ZCP
        - in Lua

        - perform bulk operations

        - memory management

Checkpoints

    - undo operation (maybe for upgrading)

Near Futures

    - ZSTD compression

    - ZIL performance improvement

    - DRAID, Distributed parity

ZFSBook.com


Sec
===============================================================================

ROP?
Gadget
JOP


BROP

Malloc hardening

Pledge


RISC-V
===============================================================================

Capsicum
===============================================================================

(fold, jot)

caph_limit_stream()
caph_limit_stdout()

...

cmp(1)

Debugging infra
----------------------------------------------------------------------

- ktrace/kdump

- enotcap


libCasper
----------------------------------------------------------------------

- flow?

    #. cap_init()

    #. cap_service_open()

    #. cap_close()

service
    - system.dns

    - system.grp

    - system.sysctl



Memory Management in FreeBSD 12.0
===============================================================================

Mark
markj@FreeBSD.org

Responsiblities
----------------------------------------------------------------------

- Virtual memory

- tons of systemcall

- Page fault handling

    - page dirty state

    - CoW

- page LRU

    - page queue maintiance

- Kenrel memory allocate

pmap(9) ?



----

Anita
