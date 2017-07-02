- http://0pointer.de/blog/projects/systemd-docs.html
- http://0pointer.de/blog/projects/systemd-for-admins-1.html


More Reading
------------

淺析 Linux 初始化 init 系統，第 3 部分: Systemd

https://www.ibm.com/developerworks/cn/linux/1407_liuming_init3/

- Systemd 的簡介和特點
- initscript: 同 SysVinit 和 LSB init scripts 兼容
- 啟動速度加快

  - 比 UpStart 更激進的平行啟動能力.
  - 使用 socket activation, D-Bus activation, autofs 來解除相依性 (即可平行啟動)
  - 按需求啟動 (On Demand / Lazy)

- Linux Cgroup 管理 process 的生命周期

  - 管理 daemon 跟它所有的 subprocess
  - UpStart 使用 strace 追蹤 fork() 跟 exit() syscall
  - Systemd 使用 Cgroup

- mount/umount

  - 相容 /etc/fstab

- 實現事務性依賴關係管理
  
  - e.g. 掛載 NFS 跟 啟動網路存在相依關係

- 能夠對系統進行快照和恢復
- 日誌服務 (journald)

systemd 基本概念

- 單元的概念

  - service
  - socket
  - device
  - mount, automount, swap
  - timer
  - snapshot
  - target

...

More
++++
- 使用 D-BUS 连接桌面应用程序: http://www.ibm.com/developerworks/cn/linux/l-dbus.html
