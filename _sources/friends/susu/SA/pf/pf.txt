/etc/rc.conf
------------
::

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

pf.conf
-------
ruleset
+++++++
ex::

    block in all
    pass out all keep state

原則: 最後一個 match 的 rule 決定是 pass 或 block, 除非 match 含有 quick 關鍵字的 rule.

rule syntax::
    
    action [direction] [log] [quick] [on interface] [af] [proto protocol] \
    [from src_addr [port src_port]] [to dst_addr [port dst_port]] \
    [flags tcp_flags] [state]

- action
    - pass
    - block drop
    - block return
        - TCP RST or ICMP Unreachable
- 2-6
    - direction: Interface generate(out) or Interface recieve(in)
    - log
    - quick(last rule)
    - on interface: this rule is used on which Interface, default is all.
    - af: ipv4, 6
    - proto: tcp/udp
- from sockets to sockets (from src_ip [port src_port] to dst_ip [port dst_port])
    - all: from any to any
    - any: any ip (from or to)
- tcp flags
- state

example::

    tcp_services = "{ ssh, smtp, domain, www, pop3, auth, pop3s }" # port name as port number (/etc/services)
    udp_services = "{ domain }"

    block all
    pass out proto tcp to any port $tcp_services keep state
    #    [ ] [       ] [                       ] [        ]
    pass proto udp to any port $udp_services keep state
    #    [       ] [                       ] [        ]

Macros, List, Table
+++++++++++++++++++
- Macros
    - ext_if = "eth0"
    - usage: $ext_if

- List
    - {140.113.244.24, 140.113.27.32/27}
    - use List in rule 將會展開(把相同 rule 套到 List 每一項)
    - Macro + List: trusted_ip = "{140.113.244.24, 140.113.27.32/27}"

- Table
    - fast lookup than list
    - Macro: nat-to, rdr-to, route-to, reply-to, dup-to
    - table keywords
        - const(can't modify table once table is created)
        - persist(table will be stayed at memory even if no rule use it.)
        - file "$file_path"
    - pfctl -t manipulate table dynamically.

pfctl - control pf rule runtime
-------------------------------
`pfctl command <http://www.freebsd.org/doc/en_US.ISO8859-1/books/handbook/firewalls-pf.html#pfctl>`_
    - pfctl -n/-v
    - pfctl -t manipulate table dynamically.

