*********************************
Auto Build
*********************************

.. toctree::


.. highlight:: shell


Working Flow
============

Create a raw image file
--------------------------------------------------------

- 1.1GB is the min requirement

::

    $ truncate -s 1124M bsdcloudinit.raw

Link it with ``mdconfig(8)``
-----------------------------

::

    $ sudo mdconfig -a -f bsdcloudinit.raw
    md0

Install OS via ``bsdinstall``
------------------------------

``bsdinstall`` provide scripting to automate the whole procedure.

1. Prepare environment variables

    #. We only want *kernel* and *base*::

        $ export DISTRIBUTIONS='kernel.txz base.txz'

    #. Where ``bsdinstall`` can fetch distribution files::

        $ export BSDINSTALL_DISTSITE="ftp://ftp.tw.freebsd.org/pub/FreeBSD/releases/amd64/`uname -r`/"

    #. After fetching, where to store distribution files.
       And we can reuse it, ``bsdinstall`` do fetching only when checksum failed or do not exist::

        $ export BSDINSTALL_DISTDIR="/tmp/dist"

    #. Partition table.
       The default schema is ``GPT``, and we set auto to use entire *md0*::

        $ export PARTITIONS="md0 { auto freebsd-ufs / }"

    #. For post-installation,
       ``bsdinstall`` will mount our ``md0`` at ``$BSDINSTALL_CHROOT``,
       ``chroot`` to it,
       and run post-install script provided by us::

        $ export BSDINSTALL_CHROOT=/any/path/you/want

    #. Other helpful vars, set it if you want.
        - ``BSDINSTALL_LOG``
        - ``BSDINSTALL_TMPETC``
        - ``BSDINSTALL_TMPBOOT``


2. Fetch distribution files::

    $ sudo -E bsdinstall distfetch

3. Partition::

    $ sudo -E bsdinstall scriptedpart $PARTITIONS

4. Install OS::

    $ cat post_install.sh
    #!/bin/sh

    # preamble part

    #!/bin/sh

    INSTALLER='/root/installer.sh'

    # network
    echo 'nameserver 8.8.8.8' > /etc/resolv.conf
    ping -c 3 google.com

    # change fstab
    sed -i '' "s/md0p2/vtbd0p2/" /etc/fstab

    # get our installer
    fetch --no-verify-peer https://raw.github.com/pellaeon/bsd-cloudinit-installer/master/installer.sh

    sh -e $INSTALLER
    $ sudo -E bsdinstall script post_install.sh


Push image to OpenStack
-----------------------



Related Resource
----------------------------------------------------------------------

- man pc-sysinstall
