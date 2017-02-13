Ethereum
===============================================================================

Create Private Network
----------------------------------------------------------------------

* Use go-ethereum as client

::

    pkg install net-p2p/go-ethereum

    mkdir ~/.ethapc/

Create custom genesis block::

    cat ~/.ethapc/genesis.json
    {
        "alloc"      : {},
        "coinbase"   : "0x0000000000000000000000000000000000000000",
        "difficulty" : "0x20000",
        "extraData"  : "",
        "gasLimit"   : "0x2fefd8",
        "nonce"      : "0x0000000000000042",
        "mixhash"    : "0x0000000000000000000000000000000000000000000000000000000000000000",
        "parentHash" : "0x0000000000000000000000000000000000000000000000000000000000000000",
        "timestamp"  : "0x00"
    }


Flags
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::

    geth --nodiscover --maxpeers 0 --identity "MyNodeName" --datadir=~/.ethapc --networkid 42

Attach
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
::

    geth  attach ipc:~/.ethapc/geth.ipc
