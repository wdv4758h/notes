- system calls: clone(), unshare(), setns()
- /proc/ files


Mount Namespace
---------------
different mount point in different namespace

UTS Namespace
-------------
nodename(hostname) and domainname (NIS domainname?)

system call

- uname()
- sethostname()/gethostname()
- setdomainname()/getdomainname()

IPC Namespace
-------------
allow unshare IPCs and have a private set of IPC objects (sem, shm, msg) inside namespace

PID Namespace
-------------
- two PIDs: outside and inside namespace
- nested namespace => PID for each layer of the PID namespace hieraechy

Network Namespace
-----------------
Each network namespace has its own network devices, IP addresses, IP routing tables, /proc/net directory, port numbers, and so on.
