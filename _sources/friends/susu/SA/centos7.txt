- installation
    - GUI 界面應該很好理解

first usage
-----------
network
+++++++
- setting files
    - /etc/sysconfig/network-scripts/ifcfg-<INTERFACE_NAME>
        - device name, ip addr/netmask/gateway, mac addr
    - /etc/sysconfig/network
        - ipv4 or ipv6
    - /etc/resolv.conf
        - DNS server
    - /etc/hosts

- tool
    - ifup|ifdown <DEVICE>
    - ifcfg
    - ip

user management
+++++++++++++++
- tool
    - useradd/userdel/usermod
    - passwd
        - 讓 user 自己改密碼.

- simple example::

    useradd <username>
    passwd <username>
    # type meanless passwd, and talk to user
