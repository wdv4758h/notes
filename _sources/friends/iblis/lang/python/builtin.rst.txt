Builtin Functions
===============================================================================

.. toctree::

.. highlight:: python


``print``
----------------------------------------------------------------------

::

    >>> print('\v'.join(map(str,range(10))))
    0
     1
      2
       3
        4
         5
          6
           7
            8
             9

    >>> print('\v'.join(map(str, range(10, 20))))
    10
      11
        12
          13
            14
              15
                16
                  17
                    18
                      19

Exception
----------------------------------------------------------------------

Handy ``args``

::

    >>> e = Exception('reason', 'detail')
    >>> e.args
    ('reason', 'detail')


``property`` decorator
----------------------------------------------------------------------

How dose it work? It return a *Descriptor Object*.


:Data Descriptor: An object defines both ``__get__()`` and ``__set__()``

:Non-data Descriptor: An object only defines ``__get__()``


Make read-only data descriptor: make ``__set__`` raise ``AttributeError``.


Attribute Lookup
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

``a.x``

Order:

#. Data descriptor

#. ``a.__dict__['x']``

#. ``type(a).__dict__['x']``

#. Non-data descriptor


Ref:

- http://stackoverflow.com/questions/17330160/how-does-the-property-decorator-work

- https://docs.python.org/3.6/howto/descriptor.html
