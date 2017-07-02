Linux system call audit
-----------------------
Linux kernel option: system-call auditing support.

recording the system call unlike ptrace solution, you can record system call of all process.

archlinux userspace tool is in community/audit, but 3.16.7.8-1-MANJARO turn off kernel option of audit support.

more about:

- http://security.stackexchange.com/questions/8485/monitoring-system-calls-in-a-reliable-and-secure-way/8519#8519
- http://people.redhat.com/sgrubb/audit
- https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Security_Guide/chap-system_auditing.html
