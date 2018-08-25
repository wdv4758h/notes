x11vnc: simple VNC server on X11
--------------------------------

Basic::
    
    x11vnc -storepasswd
    # set password and store in ~/.vnc/passwd
    x11vnc -usepw
    # use ~/.vnc/passwd as VNC server password

example::
    
    # you should login in GUI system before(ex. lock out status).
    x11vnc -display :0 -usepw

    # or you can try to find ``display manager MIT-MAGIC-COOKIE``
    # ex. ubuntu 14.04 lightdm
    # tips: ``ps wwwwaux | grep auth`` may find the path of MIT-MAGIC-COOKIE.
    x11vnc -display :0 -auth /var/run/lightdm/root/:0 -usepw

other options

- ``-once``, ``-forever``: VNC server listen once/forever.
- ``-display :<number>``

other usage

- ``x11vnc -localhost`` + ``ssh tunnel``: see `xvfb.rst <xvfb.rst>`_ for detail.
