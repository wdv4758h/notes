from paper `"Optimizing the TLB Shootdown Algorithm with Page Access Tracking" <https://www.usenix.org/system/files/conference/atc17/atc17-amit.pdf>`_
> Ch6 Related Work > Hardware Solutions.

they(Hardware TLB shootdown) require intrusive microarchitecture changes,
which CPU vendors are apparently reluctant to introduce,
presumably due to a history of TLB bugs.

TLB Bugs
--------
- 2007, AMD's B2 Phenom TLB bugs

  - software workaround: AMD release Linux Kernel patch to emulate access/dirty bit by software.
  - 2008, AMD B3 Phenom fix TLB bugs
  - https://en.wikipedia.org/wiki/AMD_Phenom#Background
  - `AMD's B3 Stepping Phenom Previewed, TLB Hardware Fix Tested <http://www.anandtech.com/show/2477/2>`_
  - `AMD Family 10h revision B2 Erratum 298 and L2 Eviction Bug Workaround <http://www.realworldtech.com/forum/?threadid=82064&curpostid=82079>`_
  - `linux workaround patch (archive) <https://archive.is/uq9L>`_

- `Intel explains the Core 2 CPU errata <https://www.theinquirer.net/inquirer/news/1031406/intel-explains-core-cpu-errata>`_
- ARM ERRATA 720789

  - problems: TLBIASIDIS and TLBIMVAIS operations can broadcast a faulty ASID
  - `software workaround: replace ASID TLB flushing with all-ASID TLB flushing <https://patchwork.kernel.org/patch/1316331/>`_
  - affect: some ARMv7 Cortex-A9 cpu?
  
    - `NVIDIA Tegra T25 (A9 ~r1p1) <https://patchwork.ozlabs.org/patch/134388/#312574>`_

- 2016, Qualcomm Falkor v1 CPU TLB bugs

  - `ARM64: Falkor erratum 1003 <https://lkml.org/lkml/2016/12/29/267>`_
