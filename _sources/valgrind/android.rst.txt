========================================
Valgrind on Android Platform
========================================

自己試過會動的版本 :

+-------------------+-------------------------------------+
| Valgrind          | 721e6a4 (2015-06-16)                |
+-------------------+-------------------------------------+
| Android NDK       | android-ndk-r10e-linux-x86_64.bin   |
+-------------------+-------------------------------------+
| Platform          | Android 21 (ARM)                    |
+-------------------+-------------------------------------+
| Target CPU        | ARMv7                               |
+-------------------+-------------------------------------+
| Toolchain         | GCC 4.9 (ARM, Android EABI)         |
+-------------------+-------------------------------------+
| SoC               | Qualcomm Snapdragon S3 MSM8260      |
+-------------------+-------------------------------------+
| CPU               | Qualcomm 1.5 GHz dual-core Scorpion |
+-------------------+-------------------------------------+
| Android (running) | 4.1.2, 5.1.1                        |
+-------------------+-------------------------------------+

.. code-block:: sh

    $ cat /proc/cpuinfo
    Processor   : ARMv7 Processor rev 4 (v7l)
    processor   : 0
    BogoMIPS    : 13.53

    processor   : 1
    BogoMIPS    : 13.53

    Features    : swp half thumb fastmult vfp edsp neon vfpv3 tls
    CPU implementer : 0x51
    CPU architecture: 7
    CPU variant : 0x0
    CPU part    : 0x02d
    CPU revision    : 4

    Hardware    : fuji
    Revision    : 0000
    Serial      : 0000000000000000
