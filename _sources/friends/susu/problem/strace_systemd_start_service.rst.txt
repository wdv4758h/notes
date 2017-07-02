``strace`` can't find how ``systemd`` start service ``virlogd``.

command is this: ``strace -f -o vlog.strace systemctl start virtlogd``.

I also tries verboses output of strace, there are 3 level::

    strace -vf -o vlog.strace.v systemctl start virtlogd
    strace -e verbose=all -vf -o vlog.strace.ve systemctl start virtlogd
    strace -s 10000 -e verbose=all -vf -o vlog.strace.ves1w systemctl start virtlogd

find 1 possibility of this -> systemd call dbus

https://www.freedesktop.org/wiki/Software/systemd/dbus/

