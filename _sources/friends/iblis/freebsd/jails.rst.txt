Jails
===============================================================================

``rc.conf``
----------------------------------------------------------------------

::

    jail_enable="YES"

    # and we will need lots of ip for our jails
    ipv4_addrs_em0="192.168.0.10-30/24"
    gateway_enable="YES"

    pf_enable="YES"


``pf.conf``
----------------------------------------------------------------------

Configuring NAT for jails::

    ex_if='em0'
    ex_ip='140.113.72.14'

    jails_net='192.168.0.0/24'

    nat on $ex_if proto { tcp, udp, icmp } from $jails_net to any -> $ex_ip

    pass out all


``jail.conf``
----------------------------------------------------------------------

- All of my jails are under ``/home/jails`` and I assume its name will correspond
  with its dir name. So I configure ``path`` as ``/home/jails/$name``.

- I shared the ``/usr/ports`` to all of my jails via nullfs. But note that I
  mount it as *readonly* filesystem. If we want to make the ports system work
  properly, we will need to change some variable in
  ``/path/to/jail/etc/make.conf``. I will show this config later.

::

    exec.start = "/bin/sh /etc/rc";
    exec.start += "/usr/sbin/tzsetup Asia/Taipei";

    exec.stop = "/bin/sh /etc/rc.shutdown";

    exec.clean;
    mount.devfs;

    path = "/home/jails/$name";

    mount = "/usr/ports $path/usr/ports nullfs ro 0 0";
    mount += "proc /home/jails/$name/proc procfs rw 0 0";

    allow.raw_sockets;

    myjail {
        host.hostname = "myjail.example.org";
        ip4.addr = 192.168.0.10;
    }


Install Jail via ``bsdinstall``
----------------------------------------------------------------------

::

    cd /home/jail/
    sudo mkdir -p /home/jail/myjail/usr/ports
    sudo bsdinstall myjail

Please check out this script, also:
https://github.com/iblis17/env-config/blob/master/bin/newjails


Post-install
----------------------------------------------------------------------


``/home/jail/myjail/etc/make.conf``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

``/usr/ports`` is readonly in the jail.

::

    WRKDIRPREFIX=/tmp/ports
    DISTDIR=/tmp/ports/distfiles


Start and Attach to the jail
----------------------------------------------------------------------

::

    service jail start myjail

    jls

    jexec myjail tcsh
