Xvfb use case
-------------

Xvfb 開 X server 在 ``$DISPLAY=0`` 上 ::

    Xvfb :0 -screen 0 1024x768x16
    Xvfb <display> -screen <screen> <screen resolution>x<color depth>

把 X program 開在 Xvfb 上 ::

    # set environment variable
    fish) set -x DISPLAY :0
    # run program
    # e.g.
    fish) qemu-system ...

開 x11vnc 讓 vnc 可以存取 Xvfb 的螢幕 ::

    x11vnc -display :0 -localhost

client 開 ssh tunnel 到 server 的 x11vnc port ::

    ssh -p <ssh_port> -L 5900:localhost:5900 -l <ssh_user> <ssh_host>
    # ssh -p <ssh_port> -L <local_port>:<host>:<host_port> -l <ssh_user> <ssh_host>
    # localhost:<local_port> => <host>:<host_port>
    
client 開 vnc client ::

    gvncviewer localhost:0
    # 0 means 5900 port in gvncviewer

advanced
~~~~~~~~

using ssh tunnel over ssh proxy.

::

    client -> proxy -> server

    ssh -L <client_bind_port>:<server_bind_host>:<server_bind_port> -o ProxyCommand='ssh -W <server_host>:<server_port> -p <proxy_port> <proxy_host>' -l <server_user> <server_host>
    # <server_host> is based on proxy's view
