Libvirt
===============================================================================

Network
----------------------------------------------------------------------

On Arch::

    sudo pacman -Syu ebtables dnsmasq firewalld
    sudo systemctl start firewalld
    sudo systemctl enable firewalld
    sudo systemctl restart libvirtd


* Ref: http://demo102.phpcaiji.com/article/bagdcea-libvirt-failed-to-initialize-a-valid-firewall-backend.html
