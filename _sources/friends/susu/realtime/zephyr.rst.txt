- Zephyr Project Overview: http://events.linuxfoundation.org/sites/events/files/slides/Zephyr%20Overview%20-%20OpenIOT%20Summit%202016.pdf

Overview
--------

- Architecture overview

  - OS on MCUs for wearable/IoT devices. minimize cost of silicon
  - only kernel mode!, no userspace and dynamic runtimes.
  - two modes: nanokernel and microkernel
  - memory and resources are typically statically allocated
  - cross architecture

- Driver Framework and HAL
- IoT Tech: Connectivity
- Integrated Security

Features
--------

- Zephyr Kernel - Key Features

  - Multithread service

    - fiber: priority-based, non-preemptive
    - task: priority-based, preemptive

  - Interrupt service: both compile/run-time registeration of "interrupt handlers".
  - Inter-thread sync/data passing service

    - sync: binary semaphores, counting semaphores, and mutex semaphores (condvar?)
    - data passing: message queues, enhanced message queues, and byte streams (socket?)

- Library-Based RTOS ("Kernel-less")

  - One executable, single address space
  - No loader is required to dynamically load application at runtime

    - system call => function call
    - No context switches are required whencalling an operating system call

  - Lack of security through hardware memory separation (virtual memory)

    - Bugs in one part of the system can affect the whole system.
    - On small microcontrollers on which only one application is executed this disadvantage is acceptable.

Nanokernel and Microkernel
--------------------------

- Zephyr Nanokernel

  - memory footprint 2KB
  - simple multi-thread requirements: 
  
    - such as a set of interrupt handler and a single bg task.

  - cooperatively scheduled: 
    
    - run until yield and call a blocking API.
    - Next highest priority fiber is then run.

  - example

    - embedded sensor hubs
    - environmental sensors
    - simple LED wearables
    - store inventory tags

- Zephyr Microkernel

  - suitable for system 
    
    - heftier memory: 50 ~ 900 KB
    - multiple communication devices(like Wi-Fi + Bluetooth Low Energy)
    - multiple data process tasks

  - example

    - smart watches
    - IoT wireless gateways

supplement
----------
- `ARM - CMSIS <http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php>`_
- Zephyr

  - `Zephyr community tools(mailing list, gerrit, wiki ... etc) <https://www.zephyrproject.org/content/community-tools>`_
  - `Zephyr development model <https://wiki.zephyrproject.org/view/Development_Model>`_

- `sensor hub <https://www.wikiwand.com/en/Sensor_hub>`_

  - a MCU help to integrate data from different sensors and process them
  - offload jobs from CPU (聽起來目的跟 DMA controller 一樣): perf improvement or save power consumption.
  - examples
  
    - Intel Integrated Sensor Hub (ISH), Apple M10, Android Sensor Hub
    - Atmel AVR UC3L, Snapdragon Sensor Core

- HAL for MCU: http://home.agh.edu.pl/~lkrzak/hal/hal_idea.pdf
- adafruit(company)

  - https://learn.adafruit.com/wifi-pixie-cyberwig-wearable-visualization/software
  - https://github.com/adafruit
