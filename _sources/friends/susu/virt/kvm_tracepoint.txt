tracepoint, TRACE_EVENT

::

    $ git clone git://git.kernel.org/pub/scm/linux/kernel/git/rostedt/trace-cmd.git trace-cmd
    $ make   # generate ./trace-cmd

    # kvm tracepoint
    $ cat /sys/kernel/debug/tracing/available_events | grep kvm
    include/trace/events/kvm.h
    arch/arm/kvm/trace.h

::
 
    $ sudo ./trace-cmd record -b 20000 -e kvm  # generate trace.dat
    $ ./trace-cmd report 

ref

- kvm usage

  - http://www.linux-kvm.org/page/Tracing
  - http://people.cs.nctu.edu.tw/~chenwj/dokuwiki/doku.php?id=kvm

- [Doc] trace/events.txt: http://lxr.free-electrons.com/source/Documentation/trace/events.txt
- LWN - Using the TRACE_EVENT() macro (Part 1): https://lwn.net/Articles/379903/
