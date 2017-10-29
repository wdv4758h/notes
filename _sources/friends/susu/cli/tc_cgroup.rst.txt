- 開一個 net_cls controller 的 cgroup, 並設定 net_cls.classid 為 10:1::

    cgcreate -t susu -a susu -g net_cls:net_test
    cd /sys/fs/cgroup/
    echo 0x100001 > net_cls/net_test/net_cls.classid
    # 0x100001 => 0x0010:0x0001 => 10:1
    
- 設定 interface 的 qdisc, class, filter::

    tc qdisc add dev wlp2s0 root handle 10: htb
    tc class add dev wlp2s0 parent 10: classid 10:1 htb rate 1mbit
    tc filter add dev wlp2s0 parent 10: protocol ip prio 10 handle 1: cgroup

    # check
    # tc [qdisc|class|filter] show dev wlp2s0

    # change the upload rate
    tc class add dev wlp2s0 parent 10: classid 10:1 htb rate <rate>
    # rate: 1mbit, 20mbit ... etc

- 把程式跑在 cgroup 裡::

    cgexec -g net_cls:net_test bash

    # child 也會在同個 cgroup, 所以以這個 shell 執行的所有程式的流量總和會被限制.
    # 測試, 使用 speedtest-cli
    pip install speedtest-cli
    speedtest-cli

    # 實際量測程式的 net bandwidth
    nethogs

reference
---------
- https://www.kernel.org/doc/Documentation/cgroup-v1/net_cls.txt
- https://puremonkey2010.blogspot.tw/2015/01/linux-tc-traffic-control.html
- https://github.com/u1240976/mess_note/blob/master/system/cgroup_and_sandbox.rst
- net_cls: https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/6/html/Resource_Management_Guide/sec-net_cls.html

- cgroups net_cls, netfilter x_table: https://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/commit/?id=82a37132f300ea53bdcd812917af5a6329ec80c3

Misc
----
1. 限制单个进程的带宽: http://chenlinux.com/2013/01/06/limit-bandwidth-of-one-process/

   - SMP 以前的系統, ``iptable`` 的 ``owner`` module 即可支援 (Misc 2)
   - trickle 用 libc hijacking 去 delay ``send()``/``recv()`` 來限流 (Misc 3)

2. 以前 ``tc`` + ``iptable`` 有支援對 process 限流, ``iptable`` 有 ``--pid-owner``, ``--sid-owner`` 兩個選項支援.
   但似乎之後 linux kernel 拔掉這個選項了, 原因應該是 ``netfilter`` 身為 network subsystem 要處理到 process subsystem 的部份實在耦合性太大, 很容易有難解的 deadlock 問題.
   也所以現在把 process 的部份分工交給 cgroup 去做管理.

3. trickle paper: http://trickled.sourceforge.net/trickle/trickle.pdf


some data
---------

tc

- control method

  - shaping: 限流, output packet
  - scheduling: priority
  - policing: 限流, input packet
  - dropping: drop

- traffic control 處理對象

  - qdisc: Queueing Discipline
  - class
  - filter

- classless qdisc

  - pfifo, bfifo
  - pfifo_fast
  - red: Random Only Detection
  - sfq: Stochastic Fairness Queueing
  - tbf: Token Bucket Filter

cgroups

- cgroups v1 net_cls
- cgroups v2 io
