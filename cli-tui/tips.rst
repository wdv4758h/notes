========================================
Tips
========================================


.. contents:: 目錄


檢查記憶體速度和種類
========================================

要檢查這種資訊需要存取 SMBIOS 的資訊，
而 ``biosdecode`` 就是負責這工作的 CLI 工具，
而 ``dmidecode`` 則是更進一步轉成可讀的資訊。

安裝：

.. code-block:: sh

    $ sudo pacman -S dmidecode  # biosdecode 也在裡面

使用：

.. code-block:: sh

    $ sudo dmidecode --type 17
    # dmidecode 3.0
    Getting SMBIOS data from sysfs.
    SMBIOS 2.8 present.

    Handle 0x003A, DMI type 17, 40 bytes
    Memory Device
        Array Handle: 0x0039
        Error Information Handle: Not Provided
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 4096 MB
        Form Factor: Chip
        Set: None
        Locator: System Board Memory
        Bank Locator: BANK 0
        Type: LPDDR3
        Type Detail: Synchronous
        Speed: 1867 MHz
        Manufacturer: Elpida
        Serial Number: 12131010
        Asset Tag: 9876543210
        Part Number: EDFA232A2MA-JD-F-R
        Rank: 2
        Configured Clock Speed: 1867 MHz
        Minimum Voltage: Unknown
        Maximum Voltage: Unknown
        Configured Voltage: 1.2 V

    Handle 0x003B, DMI type 17, 40 bytes
    Memory Device
        Array Handle: 0x0039
        Error Information Handle: Not Provided
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 4096 MB
        Form Factor: Chip
        Set: None
        Locator: System Board Memory
        Bank Locator: BANK 1
        Type: LPDDR3
        Type Detail: Synchronous
        Speed: 1867 MHz
        Manufacturer: Elpida
        Serial Number: 12031104
        Asset Tag: 9876543210
        Part Number: EDFA232A2MA-JD-F-R
        Rank: 2
        Configured Clock Speed: 1867 MHz
        Minimum Voltage: Unknown
        Maximum Voltage: Unknown
        Configured Voltage: 1.2 V


另外也可以使用 ``lshw`` ，
安裝：

.. code-block:: sh

    $ sudo pacman -S lshw

使用：

.. code-block:: sh

    $ sudo lshw -short -C memory
    H/W path         Device   Class          Description
    ====================================================
    /0/0                      memory         64KiB BIOS
    /0/38/35                  memory         64KiB L1 cache
    /0/38/36                  memory         512KiB L2 cache
    /0/38/37                  memory         3MiB L3 cache
    /0/34                     memory         64KiB L1 cache
    /0/39                     memory         8GiB System Memory
    /0/39/0                   memory         4GiB Chip LPDDR3 Synchronous 1867 MHz (0.5 ns)
    /0/39/1                   memory         4GiB Chip LPDDR3 Synchronous 1867 MHz (0.5 ns)
    /0/100/1f.2               memory         Memory controller


參考：

* `Linux: Check Ram Speed and Type <https://www.cyberciti.biz/faq/check-ram-speed-linux/>`_
