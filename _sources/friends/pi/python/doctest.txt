===========
``doctest``
===========
Python Function 的 Doc String 可以寫 Testing Code：

.. code:: python

    def foo(x):
        '''
        >>> assert foo(2) == 4
        >>> assert foo(3) == 9
        '''
        return x ** 2

    import doctest
    doctest.testmod()

或是使用 ``$ python -m doctest <filename>`` 測試

若 Function 會有 stdout，也需加在 Doctest 中：

.. code:: python

    def tag(text):
        '''
        >>> tag('Hey')
        [Hey]
        '''
        print('[{}]'.format(text))
