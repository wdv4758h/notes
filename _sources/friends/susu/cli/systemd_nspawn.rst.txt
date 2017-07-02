systemd-nspawn -bD/var/lib/lxc/arch1/rootfs -n

ip addr add 172.18.1.1/24 dev <if>
ip link set <if> up

ip addr add 172.18.1.2/24 dev <if>
ip link set <if> up
ip route add default via 172.18.1.1

sysctl net.ipv4.ip_forward=1
iptables -t nat -A POSTROUTING -s 172.18.1/24 -d 0.0.0.0/0 -j MASQUERADE
iptables -t nat -nL # show state


# archlinux/manjaro package
1. mirrorlist
2. remove manjaro-system, manjaro-keyring

   # pacman depend on manjaro-keyring::
       
       $ pacman -Qi pacman

       # modify pacman-key to remove dependency
       # before
       $ pacman-key --populate archlinux manjaro 
       # after
       $ pacman-key --populate archlinux

3. pacman.conf

   HoldPkg
   SyncFirst

4. locale
