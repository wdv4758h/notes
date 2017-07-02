libcgroup/libcg
---------------

- cgroup: https://wiki.archlinux.org/index.php/Cgroups
- libcg: http://libcg.sourceforge.net
- cgroup virtual file system: http://lwn.net/Articles/236038

commands::

  ## tools part1

  cgcreate:   create control group
  cgdelete:   delete control group
  cgexec:     execute program in cgroups
  cgclassify: attach running program in cgroups

  /proc/<pid>/cgroups: view cgroup of process

  ## examples
  # user susu

  ## create cgroup
  
  # create cgroup "test_group" for controller cpu,memory
  $ sudo cgcreate -a susu -g cpu,memory:test_group
  # create subgroup "test_group/test1"
  $ cgcreate -a susu -g cpu,memory:test_group/test1

  ## execute program with cgroup

  # execute bash with cgroup "test_group/test1" for controller cpu,memory
  $ cgexec -g cpu,memory:test_group/test1 bash
  $ cat /proc/self/cgroups

  ## attach running program with cgroup

  # attach running process (pid=27872) with cgroup "test_group/test1" for controller cpu,memory
  $ cgclassify -g cpu,memory:test_group/test1 27872
  $ cat /proc/27872/cgroups

  ## tools part2

  lscgroup: list all cgroups
  cgget: get cgroups resource limit
  cgset: set cgroups resource limit

  $ lscgroup
  $ cgget -g cpu test_group/test1
  $ cgset cpu.shares=512 test_group/test1

resources::

  /sys/fs/cgroups: control resource by cgroup

  memory.limit_in_bytes
  cpu.shares # default 1024
  cpuset.cpus
  cpuset.mems

simple example::
    
  # prepare, create cgroup
  $ sudo cgcreate -a susu -g cpu,cpuset:test_group
  $ cgcreate -a susu -g cpuset:test_group/test1
  $ cgcreate -a susu -g cpu:test_group/test2
  $ cgcreate -a susu -g cpu:test_group/test3
  
  # run program, use three shell
  # shell 1, 2
  $ yes >> /dev/null
  $ yes >> /dev/null

  # shell 3
  $ ps auxww | grep -e "yes\|PID"
  USER       PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
  susu     10796  100  0.0   9208   836 pts/11   R+   02:42  13:03 yes
  susu     10797  100  0.0   9208   748 pts/12   R+   02:42   6:09 yes

  # cpuset
    # prepare, set test_group from root cgroup (default)
  $ cat /sys/fs/cgroup/cpuset/cpuset.cpus
  0-3
  $ cat /sys/fs/cgroup/cpuset/cpuset.mems
  0
  $ cgset -r cpuset.cpus=0-3 test_group 
  $ cgset -r cpuset.mems=0   test_group 
  $ cgget -g cpuset test_group 

    # only use cpu 3 
  $ cgset -r cpuset.cpus=3 test_group/test1
  $ cgset -r cpuset.mems=0 test_group/test1
  $ cgclassify -g cpuset:test_group/test1 10796
  $ cgclassify -g cpuset:test_group/test1 10797

    # htop
    # two process only use cpu3
      PID USER ... CPU% ... Command
    10796 susu     50.0     yes
    10797 susu     50.0     yes

  # cpu.shares (default 1024)
  $ cgclassify -g cpu:test_group/test2 10796
  $ cgclassify -g cpu:test_group/test3 10797
  $ cgget -g cpu test_group/test3
  $ cgset -r cpu.shares=512 test_group/test3
    # htop
    # cpu.shares 1024:512
      PID USER ... CPU% ... Command
    10796 susu     66.0     yes
    10797 susu     33.5     yes
    
  $ cgset -r cpu.shares=256 test_group/test3
    # htop
    # cpu.shares 1024:256
      PID USER ... CPU% ... Command
    10796 susu     80.6     yes
    10797 susu     19.5     yes
    
- trouble shooting

  1. cpuset.cpus 無法調整 (write error: permission denied)
       
     每個新的 cgroup(subgroup 則繼承 parent) 的 cpuset.cpus 為空

     child group 需要等 parent 的 cpuset.cpus 設定好才可設定, 並且 child 的 cpuset.cpus 必須包含於 parent 的 cpuset.cpus

  2. 無法 assign cgroup cpuset 到 process 上 (Error changing group of pid XXX: No space left on device)
       
     cpuset.cpus / cpuset.mems 都不可為空, 需要設定初始值才行

     初始值可以參考 cgroup root. e.g. ``cat /sys/fs/cgroup/cpuset/cpuset.mems``

     http://www.richardhsu.me/posts/2014/12/08/cgroups-and-no-space.html

  3. ps 的 CPU% 似乎不準 (尚未解決)

Misc
----

- [resource control] rcon: https://github.com/matsumoto-r/rcon

  - attach running process !!

- [sandbox] MBox: https://pdos.csail.mit.edu/archive/mbox

  - chroot
  - cheat program for modifying host file system
  - intersept system call by ptrace and seccomp/BPF
