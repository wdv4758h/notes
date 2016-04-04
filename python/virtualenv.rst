========================================
virtualenv
========================================

利用 CPython 3 的 venv 來建立 CPython 2.7 的 virtualenv
=======================================================

需求

* CPython 3 (with venv support)
* CPython 2.7

.. code-block:: sh

    $ python -m venv venv3
    $ source venv3/bin/activate
    $ pip install virtualenv
    $ virtualenv -p /usr/bin/python2.7 venv2
    $ source venv2/bin/activate


升級 virtualenv
========================================

.. code-block:: sh

    $ find $VENVPATH -type l -delete
    $ virtualenv $VENVPATH


輔助 - virtualenvwrapper
========================================

* `virtualenvwrapper <https://bitbucket.org/dhellmann/virtualenvwrapper>`_
* `virtualenvwrapper - documentation <https://virtualenvwrapper.readthedocs.org/en/latest/>`_
