Today, I open my virtualbox guest VM (centos7).

.. image:: image/vbox_hanging/vbox_init.png

when opening it, hanging at 0% process and has 2 window in my GUI.

.. image:: image/vbox_hanging/centos7_hang2.png

.

.. image:: image/vbox_hanging/centos7_hang.png

Then, I views the process tree by htop, to check if I open two guest VM simultaneously to make it hanging.

.. image:: image/vbox_hanging/htop_vbox.png

Obviously, I has just one guest VM, so I try to see what it does.
I use ``strace -p <pid>`` to see the system call this process calling now.(attach this process)

.. image:: image/vbox_hanging/strace_vbox.png

E_AGAIN mean I read the non-blocking socket, and if this socket is blocking and you read it, it will hanging.
So, I try to know what is file descritor 16, 17, 22 is in guest VM process.
I use ``lsof -p <pid>`` to see the file descritors of process.

.. image:: image/vbox_hanging/lsof_vbox.png

and now, I want know how to see the two end of unix socket. Then I can guest why this unix socket doesn't reply any message.

After googling, It seems to impossible because of design in unix socket.

http://serverfault.com/questions/252723/how-to-find-other-end-of-unix-socket-connection/276606#276606

but there are some interesting ideas.

1. find near inode number in unix socket

::
    
    # For unix socket with i-node 492252
    # you can find it
    $ sudo ls -l /proc/*/fd | grep 492252
    # you can try nearly number
    $ sudo ls -l /proc/*/fd | grep 492251
    $ sudo ls -l /proc/*/fd | grep 492253
    # more useful
    $ sudo ls -l /proc/*/fd | grep 49225[0-9]
    $ sudo ls -l /proc/*/fd | grep 49224[0-9]
    # if not enough
    $ sudo ls -l /proc/*/fd | grep 4922[0-9][0-9]

    lrwx------ 1 root root 64 Dec 27 16:31 16 -> socket:[492252]
    lr-x------ 1 root root 64 Dec 27 16:31 18 -> pipe:[492253]
    l-wx------ 1 root root 64 Dec 27 16:31 19 -> pipe:[492253]
    lrwx------ 1 root root 64 Dec 27 16:31 21 -> socket:[492266]
    lrwx------ 1 root root 64 Dec 27 16:31 22 -> socket:[492267]
    lr-x------ 1 root root 64 Dec 27 16:31 28 -> pipe:[492274]
    l-wx------ 1 root root 64 Dec 27 16:31 29 -> pipe:[492274]
    lrwx------ 1 root root 64 Dec 27 16:31 30 -> socket:[492275]
    lr-x------ 1 root root 64 Dec 27 16:31 31 -> pipe:[492278]
    l-wx------ 1 root root 64 Dec 27 16:31 32 -> pipe:[492278]

    # after checking existence, using less and / to search i-node, and find which process use it.
    $ sudo ls -l /proc/*/fd | less
    # search 492253, 492266 ... etc.

2. kernel debugging

see http://stackoverflow.com/questions/11897662/identify-other-end-of-a-unix-domain-socket-connection/11900231#11900231.

Misc
----
- ``strace -c`` is profiling every system call time consuming.

.. image:: image/vbox_hanging/strace_c_vbox.png

- http://www.hokstad.com/5-simple-ways-to-troubleshoot-using-strace
