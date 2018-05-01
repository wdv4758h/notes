========================================
Chaos Engineering
========================================


.. contents:: 目錄


介紹
========================================

概念是用程式在自己的系統架構裡搗亂，
例如隨機關掉某些 instance 模擬系統出問題，
藉此來確保系統的容錯性非常高。



參考
========================================

* `Principles of Chaos Engineering <http://principlesofchaos.org/>`_
* [GitHub] `Netflix - Chaos Monkey <https://github.com/Netflix/chaosmonkey>`_
* `FreeBSD failpoints <https://www.freebsd.org/cgi/man.cgi?query=fail>`_
* `From Chaos to Order -- Tools and Techniques for Testing TiDB, A Distributed NewSQL Database <https://pingcap.com/blog/chaos-practice-in-tidb/>`_
    - Use kill -9 to kill the process by force or use kill to kill the process gracefully and then restart it.
    - Send SIGSTOP to hang or SIGCONT to resume the process.
    - Use renice to adjust the process priority or use setpriority for the threads of the process.
    - Max out the CPU.
    - Use iptables or tc to drop or reject the network packages or delay the network packages.
    - Use tc to reorder the network packages and use a proxy to reorder the gRPC requests.
    - Use iperf to take all network throughput.
    - Use libfuse to mount a file system and do the I/O fault injection.
    - Link libfiu to do the I/O fault injection.
    - Use rm -rf forcbily to remove all data.
    - Use echo 0 > file to damage a file.
    - Copy a huge file to create the NoSpace problem.
