========================================
Virtual Machine
========================================


.. contents:: 目錄


參考
========================================

* `CrosVM - Chrome OS Virtual Machine Monitor <https://chromium.googlesource.com/chromiumos/platform/crosvm/>`_
    - by Google
    - based on ``rust-vmm``
    - Virtual Machine Monitor (VMM) that runs on top of KVM
* `Firecracker <https://github.com/firecracker-microvm/firecracker>`_
    - by Amazon
    - based on ``rust-vmm``
    - Virtual Machine Monitor (VMM) that runs on top of KVM
    - `Secure and Fast microVM for Serverless Computing <https://aws.amazon.com/tw/blogs/opensource/firecracker-open-source-secure-fast-microvm-serverless/>`_
    - 專門為 Severless Computing 設計，提供小、快、安全的虛擬化技術
* `Cloud Hypervisor <https://github.com/intel/cloud-hypervisor>`_
    - by Intel
    - based on ``rust-vmm``
    - Virtual Machine Monitor (VMM) that runs on top of KVM

* [2019/03] `Building the virtualization stack of the future with rust-vmm <https://opensource.com/article/19/3/rust-virtual-machine>`_
* [2019][FOSDEM] `rust-vmm - shared virtualization crates <https://archive.fosdem.org/2019/schedule/event/vai_rust_vmm/>`_
* `rust-vmm - Community <https://github.com/rust-vmm/community>`_
    - "rust-vmm is an open-source project that empowers the community to build custom Virtual Machine Monitors (VMMs) and hypervisors."
    - "The rust-vmm project is organized as a shared effort, shared ownership open-source project that includes (so far) contributors from Alibaba, AWS, Cloud Base, Crowdstrike, Intel, Google, Red Hat as well as individual contributors."

* `kvm-ioctls - safe wrapper over KVM API <https://github.com/rust-vmm/kvm-ioctls>`_
