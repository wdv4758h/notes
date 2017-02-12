Device IO
---------
cpu 跟 Device 進行 IO, 常見的手法有 2 種,

一種是 memory mapped IO, 把 buffer 對應到某段 memory space 上, 對 memory 的讀寫同步到對 device 的讀寫.

另一種是 port mapped IO, 把 buffer 對應到某段 IO space 上, cpu 會使用特殊(非 memory 讀寫的 instruction)的 instruction 去讀寫 IO space, 並同步到 device 的讀寫. 特殊的 instruction 如 x86 的 in/out instruction.

IO space
--------
- IBM PC, XT, AT, PS/2 的規範: http://bochs.sourceforge.net/techspec/PORTS.LST

  - IBM 最早的 PC, 從 1981 開始, 到 1987 IBM PS/2 出現.

- http://www.wikiwand.com/en/Input/output_base_address

IO map on linux
---------------
``lspci -vv`` 可以列出本機所有 pci device 的資訊, 裏面的 Region 即為該 device 此時 memory/port mapped IO 的狀態.

以下是某筆電 VGA controller 的資訊::

    00:02.0 VGA compatible controller: Intel Corporation Haswell-ULT Integrated Graphics Controller (rev 0b) (prog-if 00 [VGA controller])
        DeviceName:  Onboard IGD
        Subsystem: Dell Device 05de
        Control: I/O+ Mem+ BusMaster+ SpecCycle- MemWINV- VGASnoop- ParErr- Stepping- SERR- FastB2B- DisINTx+
        Status: Cap+ 66MHz- UDF- FastB2B+ ParErr- DEVSEL=fast >TAbort- <TAbort- <MAbort- >SERR- <PERR- INTx-
        Latency: 0
        Interrupt: pin A routed to IRQ 64
        Region 0: Memory at f6400000 (64-bit, non-prefetchable) [size=4M]
        Region 2: Memory at d0000000 (64-bit, prefetchable) [size=256M]
        Region 4: I/O ports at f000 [size=64]
        Expansion ROM at <unassigned> [disabled]
        Capabilities: <access denied>
        Kernel driver in use: i915

Region 0/2 為 memory mapped IO, mapping 到 memory space 的 f6400000 ~ f6401000 (4M) 跟 d0000000 ~ d0040000(256M).
Region 4 為 port mapped IO, mapping 到 IO space 的 f000 ~ f03F (64B).

x86(32bits) in/out instruction
------------------------------
``OUT`` instruction format 的連結: http://x86.renejeschke.de/html/file_module_x86_id_222.html

從 ``OUT`` instruction, 基本上可以看出 IO space 應該是 16bits(65536) 的大小, 該 instruction 能讓 cpu 一次 IO 一個 register 的值 (最多 32 bits)
