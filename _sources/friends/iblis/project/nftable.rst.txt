nftable
===============================================================================

::

    git clone git://git.netfilter.org/nftables

    # load sample
    nft -f files/nftables/ipv4-filter

Add
----------------------------------------------------------------------

::

    nft add rule ip filter input ip saddr '!= 1.2.0.0/16' tcp dport 8545 drop
    nft list table filter -a

Ref
----------------------------------------------------------------------

* https://home.regit.org/netfilter-en/nftables-quick-howto/
