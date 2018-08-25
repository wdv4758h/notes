- Realtime Java

  - spec: JSR 001 => JSR 282
  - terminology: 

    - RTSJ: Real-Time Specification for Java

  - common implementations

    - Sun Java SE Real-Time Systems => Oracle JRockit JVM
    - IBM WebSphere Real Time
    - PTC Perc from PTC Inc
    - JamaicaVM from aicas

  - features

    - threading model (e.g. Priority Inheritance)
    - garbage collections (GC)
    - 2.0 support direct device access and deterministic GC

----

2015, The Next Generation of the RT Spec for Java: https://www.aicas.com/cms/sites/default/files/rtsj-next-gen-jtres-2015.pdf

- Major RTSJ 2.0 Improvements

  - Task Control: CPU affinity + improved scheduling
  - Raw Memory: Typed device access + Factory based
  - New Scope Types: Pinnable Memory + Stacked Memory
  - ActiveEvents

    - Unify API for Timer, Happening, & Signal
    - Happening object
    - User defined Clocks

  - Stateful Events: Object & long + POSIX Realtime Signal
  - ISR Support

- Time UML State Machine
- New Raw Memory Architecture
  
  - Factory: RawMemory & RawMemoryFactory
  - Interfaces for each access type: RawInt, RawShort, RawByte, RawFloat, etc.
  - Concrete class for: Memory Mapped & I/O Mapped & Generic Mapping devices.
  - Example: IOBusController => ``MemoryRawByte command, flag; MemoryRawShort addr; MemoryRawInt data;``
  - DMA support

    - direct byte buffer: get address to pass to DMA controller
    - could be use to implement I/O Channels

  - Additional barrier types
    
    - JEP 188: Java Memory Model Update: 好像還沒什麼資料

Reference
---------

- wiki - Realtime Java: https://en.wikipedia.org/wiki/Real_time_Java
- RTSJ 2.0 from aicas: https://www.aicas.com/cms/rtsj
- 2015, The Next Generation of the RT Spec for Java: https://www.aicas.com/cms/sites/default/files/rtsj-next-gen-jtres-2015.pdf

Related
-------
- POSIX.4 Real-time Extensions (e.g. POSIX Realtime Signal)

  - SUSv2: http://pubs.opengroup.org/onlinepubs/7908799/xsh/realtime.html
  - 1993, REAL-TIME POSIX: AN OVERVIEW: http://www.ctr.unican.es/publications/mgh-1993a.pdf
