Packet Filter (PF firewall) @ OpenBSD PF Manual
==============================================
The pf.conf file has five parts:

- Macros: User-defined variables that can hold IP addresses, interface names, etc.

- Tables: A structure used to hold lists of IP addresses.

- Options: Various options to control how PF works.

- Queueing: Provides bandwidth control and packet prioritization.

- Filter Rules: Allows the selective filtering or blocking of packets as they pass through any of the interfaces.
  Filter rules can be given parameters to specify network address translation (NAT) and packet redirection.

Contents
--------
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

rules
-----
原則: 最後一個 match 的 rule 決定是 pass or block, 除非 match quick 的 rule.

- action
    - pass
    - block drop
    - block return
        - TCP RST or ICMP Unreachable
- direction(interface generate(out)/recieve(in)), log, quick(last rule), af(ipv4, 6), proto
- from sockets to sockets (from src_ip [port src_port] to dst_ip [port dst_port])
    - all: from any to any
    - any: any ip (from or to)
- tcp flags
- state
