
- note of paper: I/O Paravirtualization at the Device File Boundary
- link: http://www.ruf.rice.edu/~mobile/publications/amirisani2014asplos.pdf

- outline

  - Abstract
  - 1. Introduction
  - 2. Background
  
    - 2.1 I/O Stack
    - 2.2 I/O Paravirtualization
    - 2.3 Memory Virtualization

  - 3. Paradice Design

    - 3.1 Architectural Design Choices

      - Choice 1: device files as the paravirtualization boundary
      - Choice 2: device and driver sandboxing and strict runtime checks of driver memory operations for fault isolation.
      - Choice 3: hypervisor-enforced access permissions for device data isolation.

    - 3.2 Key Benefits of Paradice Design

      - 3.2.1 One Paravirtual Driver, Many I/O Devices (framework?)
      - 3.2.2 Compatibility between Different OSes
      - 3.2.3 Concurrent Device Access by Multiple Guests

  - 4. Isolation between Guest VMs

    - 4.1 Fault Isolation
    - 4.2 Device Data Isolation

  - 5. Implementation
  
    - 5.1 Paradice Architecture Details
    - 5.2 Hypervisor-Assisted Memory Operations
    - 5.3 Isolation between Guest VMs

  - 6. Evaluation

    - 6.1 Performance
    
      - 6.1.1 Overhead Characterization
      - 6.1.2 Ethernet Card for netmap
      - 6.1.3 GPU for Graphics
      - 6.1.4 GPU for Computation
      - 6.1.5 Mouse

  - 7. Related Work

    - 7.1 I/O Virtualization
    - 7.2 other related work

  - 8. Limitations of Current Design
  - 9. Conclusions

Contents note
-------------
3.1 Architectural Design Choices
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- Choice 1: device files as the paravirtualization boundary

  frontend driver in guest VM, opening virtual device(``devfs``).
  backend driver in hypervisor.
  frontend and backend driver redirect virtual device file operation to real device file operation.

- Choice 2: device and driver sandboxing and strict runtime checks of driver memory operations for fault isolation.

  sandboxing device and its driver in seperate VM, called driver VM.
  device assignment (intel vt-d)
