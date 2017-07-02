Packet Filter (PF firewall) @ FreeBSD Handbook
==============================================

/etc/rc.conf::

    pf_enable="YES"
    pf_flags=""

    pf_rules="/path/to/pf.conf" # rule configuration
    pflog_enable="YES" # enable log
        pflog_logfile="/var/log/pflog"
        pflog_flags=""
    gateway_enable="YES"        # Enable as LAN gateway
    pfsync_enable="YES" ??

run service once::
    
    service pf start
    service pflog start
    sysctl net.inet.ip.forwarding=1 # forwarding ipv4 packet (gateway_enable)

`pfctl command <http://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/firewalls-pf.html#pfctl>`_
    - pfctl -n/-v

monitor traffic of PF firewall

    `sysutil/pftop`

ALTQ
----
- ALTQ is not available as a loadable kernel module. We should customize kernel.
- driver support needed
- choose scheduler algorithm (CBQ, RED ...)

ruleset
-------
block in all
pass out all keep state

- Macros and list (advise at top of configuration)
tcp_services = "{ ssh, smtp, domain, www, pop3, auth, pop3s }" # port name as port number (/etc/services)
udp_services = "{ domain }"
block all
pass out proto tcp to any port $tcp_services keep state
pass proto udp to any port $udp_services keep state

simple gateway + NAT
++++++++++++++++++++
`interface:network` # 該 interface 的 LAN(CIDR)
`nat on $ext_if from $localnet to any -> ($ext_if)` # use `($ext_if)` if `$ext_if` may be dynamic assigned

Misc
----
kernel configuration??

/etc/rc.d/pf 
    - start / stop / restart / reload / status / check / resync
