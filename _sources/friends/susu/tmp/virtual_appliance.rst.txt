- virtual appliance: pre-configured virtual machine image, ready to run on a hypervisor.

  - 先設定過的 VM image, 能快速佈署在 hypervisor 上.
  - 先安裝好特定軟體, 可能還為此優化過.
  - 使用 embedded OS(ex. JeOS) 減少損耗的效能.

實際範例
--------
1. OpenVPN Access Server Virtual Appliance

2. The JumpBox Virtual Machine & Virtual Appliance Library

   - http://www.jumpbox.com/library
   - ex

     - Nagios, Drupal, Mediawiki, Bugzilla, RoR application
     - support VMware, parallel, virtaulbox, Amazon EC2 Cloud Computing

VA 經常用 JeOS(Just enough Operation System), 讓資料消耗量減少.

Ubuntu, SUSE(Novell), Redhat are all provide JeOS version.

other VA 供應者

- turnkey linux

  - http://www.turnkeylinux.org/all

    - gitlab, jenkin CI, redmine, MoinMoin, django

學理分析
--------
https://vmware-partnerpedia-shared.s3.amazonaws.com/documents/Virtual_Appliance_Whitepaper.pdf

- Virtual appliances: 

  prebuilt software solutions comprising one or more virtual machines that are packaged, updated, maintained and managed as a unit. 

- VM v.s VA

  - virtual machine

    - has 4 key virtualized resources (CPU, RAM, storage and networking).
    - need install OS and run applications.

  - virtual appliance

    - same as above, has 4 key virtualized resources
    - preinstall, preconfigured OS, an application stack that is optimized to provide a specific set of service.

- VA usually use JeOS(Just enough Operation System)

  - Ubuntu, SUSE(Novell), Redhat are all provide JeOS version

- OVF

  portable packaging format for virtual machines.
  It describes how virtual appliances can be packaged in a platform-neutral format to be run on any hypervisor

- OVF v.s. VM Disk

  - OVF

    - complete specification of VM.
    - full list of disk.
    - hardware info: CPU, memory, network.

  - VM Disk

    - only a disk of one VM, not containing CPU/Memory/Network message of VM.
    - one VM can have many disk, more than one.

實際 data
---------
Ubuntu 12.04 JeOS: 55 MB (原 740 MB)
