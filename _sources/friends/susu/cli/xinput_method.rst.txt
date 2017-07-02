Environment variable and command
--------------------------------
::

    export XIM=hime
    export XIM_PROGRAM=/usr/bin/hime
    export XIM_ARGS=
    export XMODIFIERS="@im=hime"
    export GTK_IM_MODULE=hime
    export QT_IM_MODULE=hime
    export QT4_IM_MODULE=hime
    export CLUTTER_IM_MODULE=hime
    hime &


xinitrc/xsession/xprofile
-------------------------
x initialization script

- xinitrc: after initialization, exec Window Manager or Desktop Environment? (ex. ``cinnamon-session``).
- xprofile: sourced by Display Manager, see below.

http://newtoypia.blogspot.tw/2012/06/xinitrc-xsession-xprofile.html

xprofile
++++++++
``~/.xprofile`` and ``/etc/xprofile``

Xprofile is of particular use for autostarting programs with a session, started from a Display manager

example

    * GDM - ``/etc/gdm/Xsession``
    * KDM - ``/usr/share/config/kdm/Xsession``
    * LightDM - ``/etc/lightdm/Xsession``
    * LXDM - ``/etc/lxdm/Xsession``

Xsession is a shell script which source the xprofile and ... etc.

https://wiki.archlinux.org/index.php/xprofile

im-config tool
--------------
im-config package installs a hook script ``/etc/X11/Xsession.d/70im-config_launch``.

When X starts, it sources this file as a POSIX shell code.
source config file ``~/.xinputrc`` and ``/etc/X11/xinit/xinputrc``.

im-config command: modify xinputrc

    - user: ``~/.xinputrc``
    - root: ``~/etc/X11/xinit/xinputrc``

The essential contents of generated files are:

     run_im <input method name>

     When these files are sourced, the run_im shell function instructs  to
     source the initialization code for the corresponding input method. This
     initialization code is defined in the <2 digits  number>_<input  method
     name>.rc file in /usr/share/im-config/data.

``/etc/X11/Xsession.d/70im-config_launch``, exports following variables to X programs::

    - $XMODIFIERS
    - $GTK_IM_MODULE
    - $QT_IM_MODULE
    - $QT4_IM_MODULE
    - $CLUTTER_IM_MODULE.

http://manpages.ubuntu.com/manpages/raring/en/man8/im-config.8.html
