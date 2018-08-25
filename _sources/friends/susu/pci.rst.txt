Conventional PCI
----------------

`Conventional PCI wiki <https://en.wikipedia.org/wiki/Conventional_PCI>`_

- Auto Configuration
- Interrupt
- PCI bus transaction

Auto Configuration
~~~~~~~~~~~~~~~~~~
- Each device can request up to 6 areas of memory space or IO port space,
  via config space register.

- PCI Latency Timers for PCI Bus Mastering.
  
  - PCI device that can operate in bus-master mode is required to implement a timer, called Latency Timer.
  - This does not apply to PCI Express?

Interrupt
~~~~~~~~~
- PCI 4 interrupt line (INT#A, #B, #C, #D)

  - The position of interrupt lines rotate between slots.

- mapping PCI interrupt line onto system interrupt lines

  - through PCI Host Bridge
  - is implementation-defined

- MSI(Message Signaled Interrupt)

  - devices signals by performing a memory write, rather than asserting line.
  - 減緩缺乏 interrupt line 的問題.
  - It also resolves the routing problem, because the memory write is not unpredictably modified between device and host.

- PCI-E doesn't have physical interrupt lines. It uses MSI exclusively.

note
~~~~

- level-triggered / edge-triggered interrupt

  - edge triggered interrupts are easy to miss.
  - PCI interrupt lines is level-triggered.

- in-band / out-of-band interrupt

  - in-band can resolve some synchronization problems, that can occur with posted-write and out-of-band interrupt lines.

PCI-E
-----

`PCI Express wiki <https://en.wikipedia.org/wiki/PCI_Express>`_

- Architecture

  - Interconnect
  - Lane
  - Serial bus

- Hardware protocol summary

  - Physical layer
  - Data link layer
  - Transaction layer

Architecture
~~~~~~~~~~~~

PCIe Bus Topology:

.. image:: image/pci/pcie_topology.png
   :scale: 70%

PCI Bus Topology:

.. image:: image/pci/pci_topology.png
   :scale: 70%

- Shared parallel bus architecture: PCI host and all devices share a common set of (address, data and control lines). 
- p2p topology

  - PCI-E is based on p2p topology, with separate serial links connecting every device to the root complex
  - the older PCI clocking scheme limits bus clock to slowest peripheral on the bus.

- in terms of bus protocol, PCI-E communication is encapsulated in packets.
- PCI requests and interrupts

  - PCI requests: configuration, I/O or memory read/write
  - interrupts: INTx, MSI or MSI-X

Reference
---------

- `PCI config space wiki <https://en.wikipedia.org/wiki/PCI_configuration_space>`_
- `osdev - PCI <http://wiki.osdev.org/PCI>`_
- 2004, `PCI Local Bus 3.0 Spec <https://www.xilinx.com/Attachment/PCI_SPEV_V3_0.pdf>`_

- 2010, `PCI-E 3.0 spec <http://composter.com.ua/documents/PCI_Express_Base_Specification_Revision_3.0.pdf>`_
- https://www.mindshare.com/files/resources/MindShare_Intro_to_PCIe.pdf

