- 2.2 device number: http://tldp.org/HOWTO/Partition/devices.html
  
  - major number 決定由哪個 driver 使用 device
  - device number list: http://lxr.free-electrons.com/source/Documentation/devices.txt

    - major 8 應該是 SCSI+SATA 硬碟, 平常的 /dev/sdX 應該都屬於 major 8

  - ``ls -l /dev/`` 可以看到 devfs 中各 device 的 device number
  - 列出 char/block device, 根據 major number 排序: ``ls -l /dev/** | grep -e "^[cb]" | sort -n -k5,5``

    - major 189(/dev/bus/usb/) 資料夾下的檔案/資料夾跟 ``lsusb`` 列出的訊息一致

- ``pmap -d <PID>`` 列出的 device 就是 device number
