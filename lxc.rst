========================================
Linux Containers (LXC)
========================================

Ubuntu (Elementary OS) ::

    /usr/share/lxc/
    ├── config
    │   ├── centos.common.conf
    │   ├── centos.userns.conf
    │   ├── common.seccomp
    │   ├── debian.common.conf
    │   ├── debian.userns.conf
    │   ├── fedora.common.conf
    │   ├── fedora.userns.conf
    │   ├── gentoo.common.conf
    │   ├── gentoo.moresecure.conf
    │   ├── gentoo.userns.conf
    │   ├── oracle.common.conf
    │   ├── oracle.userns.conf
    │   ├── plamo.common.conf
    │   ├── plamo.userns.conf
    │   ├── ubuntu-cloud.common.conf
    │   ├── ubuntu-cloud.lucid.conf
    │   ├── ubuntu-cloud.userns.conf
    │   ├── ubuntu.common.conf
    │   ├── ubuntu.lucid.conf
    │   └── ubuntu.userns.conf
    ├── hooks
    │   ├── clonehostname
    │   ├── mountecryptfsroot
    │   ├── squid-deb-proxy-client
    │   └── ubuntu-cloud-prep
    ├── lxc.functions
    └── selinux
        ├── lxc.if
        └── lxc.te

Arch Linux ::

    /usr/share/lxc/
    ├── config
    │   ├── archlinux.common.conf
    │   ├── archlinux.userns.conf
    │   ├── centos.common.conf
    │   ├── centos.userns.conf
    │   ├── common.conf
    │   ├── common.conf.d
    │   │   └── README
    │   ├── common.seccomp
    │   ├── debian.common.conf
    │   ├── debian.userns.conf
    │   ├── fedora.common.conf
    │   ├── fedora.userns.conf
    │   ├── gentoo.common.conf
    │   ├── gentoo.moresecure.conf
    │   ├── gentoo.userns.conf
    │   ├── nesting.conf
    │   ├── opensuse.common.conf
    │   ├── opensuse.userns.conf
    │   ├── openwrt.common.conf
    │   ├── oracle.common.conf
    │   ├── oracle.userns.conf
    │   ├── plamo.common.conf
    │   ├── plamo.userns.conf
    │   ├── ubuntu-cloud.common.conf
    │   ├── ubuntu-cloud.lucid.conf
    │   ├── ubuntu-cloud.userns.conf
    │   ├── ubuntu.common.conf
    │   ├── ubuntu.lucid.conf
    │   ├── ubuntu.userns.conf
    │   └── userns.conf
    ├── hooks
    │   ├── clonehostname
    │   ├── mountecryptfsroot
    │   ├── squid-deb-proxy-client
    │   └── ubuntu-cloud-prep
    ├── lxc.functions
    ├── lxc-patch.py
    ├── selinux
    │   ├── lxc.if
    │   └── lxc.te
    └── templates
        ├── lxc-alpine
        ├── lxc-altlinux
        ├── lxc-archlinux
        ├── lxc-busybox
        ├── lxc-centos
        ├── lxc-cirros
        ├── lxc-debian
        ├── lxc-download
        ├── lxc-fedora
        ├── lxc-gentoo
        ├── lxc-openmandriva
        ├── lxc-opensuse
        ├── lxc-oracle
        ├── lxc-plamo
        ├── lxc-sshd
        ├── lxc-ubuntu
        └── lxc-ubuntu-cloud

* `Wikipedia - LXC <https://en.wikipedia.org/wiki/LXC>`_
