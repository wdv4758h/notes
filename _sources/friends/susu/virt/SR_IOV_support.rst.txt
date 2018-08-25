To support SR-IOV, we need:

1. PCI-Express support on motherboard? I heard that some motherboard only support it in some PCI-E slots.
2. NIC support SR-IOV. for intel's NIC, seeing http://www.intel.com/support/network/adapter/pro100/sb/CS-031492.htm
3. hypervisor support SR-IOV functionality. (Xen/kvm/VMware vSphere/Hyper-V)

   - for example, in kvm, we need 2 kernel module(vfio-pci/intel-iommu) and NIC driver

4. guest OS support virtual function driver. (Windows/Linux/FreeBSD)

reference: 

- http://www.intel.com/support/network/adapter/pro100/sb/CS-031492.htm
