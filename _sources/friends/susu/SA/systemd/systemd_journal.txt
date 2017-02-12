systemd logging system - journal
--------------------------------
journal(``systemd-journald.service(8)``) will log

  - kmsg
  - syslog
  - stdout/stderr of system service
  - audit

usage

  - ``journalctl --list-boots``: show all boot number, timestamp ... ::

      -3 08717495ff184a14b9c23609573f8e84 Sun 2016-04-29 01:14:03 CST - Sat 2016-04-29 01:15:10 CST
      -2 628f2c6d974748f8997ea30e91319c3f Thu 2016-04-29 01:15:37 CST - Thu 2016-05-08 20:22:29 CST
      -1 f4d1dc95e13e4600b179b8ef0530438e Mon 2016-05-08 03:35:48 CST - Fri 2016-05-13 15:24:38 CST
       0 35a3f2901d5a47a2b50705a37ae62c9d Fri 2016-05-13 16:33:17 CST - Sat 2016-05-18 01:16:20 CST

  - ``journalctl -k``: only dmesg (kernel log)
  - ``journalctl -u <unit|pattern>``: 
  - ``journalctl -k -b -1``: dmesg of previous boot

    - 1/2 for first/second boot, -0/-1 for last/one before last boot

  - ``-p <num>``: only show log level equal and lower than ``<num>``. (log level: 0/"emerg" and 7/"debug")

- used journal files: ``--user``, ``--system``, ``--directory``, and ``--file`` option

  - special groups with permission of all journal files: ``systemd-journal``, ``adm``, ``wheel``

reference
~~~~~~~~~

- ``man journalctl``
- ``man systemd-journald.service``

More
~~~~

- systemd Journal: https://linuxtoy.org/archives/systemd-journal.html?cm_mc_uid=35417870122914266652479&cm_mc_sid_50200000=1468074103
- How To Use Journalctl to View and Manipulate Systemd Logs: https://www.digitalocean.com/community/tutorials/how-to-use-journalctl-to-view-and-manipulate-systemd-logs
