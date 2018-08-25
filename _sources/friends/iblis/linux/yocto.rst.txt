Yocto
===============================================================================
.. code-highlight: shell

I got an intel edison board and ``yocto`` installed.

Connect to it via serial port::

    $ sudo screen /dev/ttyUSB0 115200


Install python35
----------------------------------------------------------------------

::

    $ wget <python source>
    $ tar xzvf <Python.tar.gz>
    $ cd <Python source dir>

    $ ./configure --prefix=/usr/local
    $ make -j 2  # There are two cpus on this SoC
    $ make test  # optional
    $ make install

Check your pip installed::

    $ pip3 -V
    pip 7.1.2 from /usr/local/lib/python3.5/site-packages (python 3.5)


Install GNU Screen
----------------------------------------------------------------------

::

    $ ./autogen.sh
    $ ./configure --prefix=/usr/local
    $ make -j 2
    $ make install


Run EC
----------------------------------------------------------------------

::

    $ cd /path/to/ec
    $ cd setup


Patch the ``startup.sh``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

.. literalinclude:: yocto/startup.sh.patch
    :language: diff
    :linenos:


Patch the ``ec/main_na.py``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

When the edison in host ap mode, the default gateway gone.
The orignial code bind socket to all interface,
thus cause udp broadcasting failed.

.. literalinclude:: yocto/main_na.py.patch
    :language: diff
    :linenos:


Prepare ``virtualenv``
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::

    $ cd /path/to/ec
    $ pyvenv-3.5 .venv
    $ source .venv/bin/activate


Patch the ``ec/requirements.txt``
**************************************************

.. code-block:: diff
    :linenos:

    --- requirements.txt.orig
    +++ requirements.txt
    @@ -1,5 +1,3 @@
     flask
     sqlalchemy
    ---allow-external mysql-connector-python
    -mysql-connector-python
     sphinx

::

    $ pip install -r ec/requirements.txt


Run it!
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

::

	$ /path/to/ec/startup.sh


Make EC Run at System Started
----------------------------------------------------------------------

::

    $ vi /etc/rc.local
    $ cat /etc/rc.local
    #!/bin/sh

    echo 'Boostrap EC'
    /home/root/easyconnect/setup/startup.sh
    $ chomd +x /etc/rc.local


Then reboot for checking.


Make Yocto in AP Mode
----------------------------------------------------------------------

::

    $ /usr/bin/configure_edison --enableOneTimeSetup --persist


Relax
----------------------------------------------------------------------

Enjoy!
