Tuning
===============================================================================

Tuning Power
----------------------------------------------------------------------

Ref: https://wiki.freebsd.org/TuningPowerConsumption

Terms
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

:P-states: performance states

:T-states: throttling

:S-states: sleeping

:G-states: global

:C-states: CPU


P-states
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Make CPU work in different freq.

:Intel: EIST (Enhanced Intel SpeedStep Technology)

:AMD: CnQ (Cool’n’Quiet)

By convention, P0 denote the highest freq, and the second one is P1, and so on.

e.g: we have a CPU which highest freq is 3.0Hz. Now, we make it work in 50% of
P-states. The freq of CPU will become 1.5Hz.

.. image:: ./img/p-states_and_t-states.jpg

(the source of image: https://cdn0-techbang.pixcdn.tw/system/images/156313/original/3bd6486853a3f91922ee4dbd8f5e502b.jpg)


T-States
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Change the working time.


S-States
----------------------------------------------------------------------

:S1: power on suspend. CPU is off; the RAM is still on.

:S2: CPU is off; the RAM is still on. It has lower power consumption then S1.

:S3: suspend to RAM. Most of hardware are off; few power one RAM.

:S4: suspend to Disk. Dump memory state to disk and poweroff.
     The power consumption is same as poweroff (S5).

:S5: poweroff
