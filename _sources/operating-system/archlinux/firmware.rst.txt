========================================
Firmware
========================================


.. contents:: 目錄


fwupdate 使用
========================================

.. code-block:: sh

    $ fwupdmgr get-devices
    XPS 13 9350
    │
    ├─Thunderbolt Controller:
    │     Device ID:           0000000000000000000000000000000000000000
    │     Summary:             Unmatched performance for high-speed I/O
    │     Current version:     16.00
    │     Vendor:              Dell (TBT:0x00D4)
    │     GUIDs:               00000000-0000-0000-0000-000000000000
    │                          00000000-0000-0000-0000-000000000000
    │     Device Flags:        • Internal device
    │                          • Updatable
    │                          • Requires AC power
    │                          • Supported on remote server
    │                          • Device stages updates
    │
    ├─SAMSUNG SSD CM871 M.2 2280 128GB:
    │     Device ID:           0000000000000000000000000000000000000000
    │     Summary:             ATA Drive
    │     Current version:     FXT21D1Q
    │     Vendor:              Intel Corporation
    │     GUIDs:               00000000-0000-0000-0000-000000000000
    │                          00000000-0000-0000-0000-000000000000
    │                          00000000-0000-0000-0000-000000000000
    │     Device Flags:        • Internal device
    │                          • Updatable
    │                          • Requires AC power
    │                          • Needs a reboot after installation
    │                          • Device is usable for the duration of the update
    │
    ├─System Firmware:
    │     Device ID:           0000000000000000000000000000000000000000
    │     Current version:     0.1.10.1
    │     Minimum Version:     0.1.10.1
    │     Vendor:              Dell Inc.
    │     GUIDs:               00000000-0000-0000-0000-000000000000
    │     Device Flags:        • Internal device
    │                          • Updatable
    │                          • Requires AC power
    │                          • Supported on remote server
    │                          • Needs a reboot after installation
    │                          • Cryptographic hash verification is available
    │                          • Device is usable for the duration of the update
    │
    ├─TPM 1.2:
    │ │   Device ID:           0000000000000000000000000000000000000000
    │ │   Summary:             Platform TPM device
    │ │   Current version:     5.81.0.0
    │ │   Vendor:              Dell Inc.
    │ │   Update Error:        Updating disabled due to TPM ownership
    │ │   GUID:                00000000-0000-0000-0000-000000000000
    │ │   Device Flags:        • Internal device
    │ │                        • Requires AC power
    │ │                        • Supported on remote server
    │ │
    │ └─TPM 2.0:
    │       Device ID:         0000000000000000000000000000000000000000
    │       Summary:           Alternate mode for platform TPM device
    │       Vendor:            Dell Inc.
    │       Update Error:      mode switch disabled due to TPM ownership
    │       GUID:              00000000-0000-0000-0000-000000000000
    │       Device Flags:      • Internal device
    │                          • Requires AC power
    │                          • Device is locked
    │
    └─Touchpad:
          Device ID:           0000000000000000000000000000000000000000
          Current version:     1.2.2011643
          Bootloader Version:  54.0
          Vendor:              Dell Inc (HIDRAW:0x06CB)
          GUIDs:               00000000-0000-0000-0000-000000000000
                               00000000-0000-0000-0000-000000000000
                               00000000-0000-0000-0000-000000000000
                               00000000-0000-0000-0000-000000000000
          Device Flags:        • Internal device
                               • Updatable

    $ fwupdmgr get-updates
    $ fwupdmgr update



提醒
========================================

fwupd 的 UEFI firmware 更新需要 udisks2



參考
========================================

* `Linux Vendor Firmware Service (LVFS) <https://fwupd.org/>`_
* `fwupd 支援的裝置搜尋 <https://fwupd.org/lvfs/devices/>`_
* `Dell XPS 13 (9350) #Firmware Updates <https://wiki.archlinux.org/index.php/Dell_XPS_13_(9350)#Firmware_Updates>`_
