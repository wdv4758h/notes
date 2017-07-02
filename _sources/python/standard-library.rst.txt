========================================
Standard Library
========================================

textwrap - 更多字串處理
========================================

.. code-block:: python

    >>> import textwrap

    # 每行最多多少字（預設 70）
    >>> textwrap.wrap('XD'*200)
    ['XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD',
     'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD',
     'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD',
     'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD',
     'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD',
     'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD']

    # '\n'.join(wrap(text, ...))
    >>> textwrap.fill('XD'*200)
    'XDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD\nXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD\nXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD\nXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD\nXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD\nXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXDXD'

    # 縮減
    >>> textwrap.shorten('XD '*200, width=12)
    'XD XD [...]'
    >>> textwrap.shorten('XD '*200, width=12, placeholder='口卡口卡～吃光光')
    'XD口卡口卡～吃光光'

    # 除去每行開頭多餘的空白
    >>> s = '''
            我是 docstring!
                <- spaces QQ
            '''
    >>> s
    '\n    我是 docstring!\n        <- spaces QQ\n    '
    >>> print(s)

        我是 docstring!
            <- spaces QQ

    >>> textwrap.dedent(s)
    '\n我是 docstring!\n    <- spaces QQ\n'
    >>> print(textwrap.dedent(s))

    我是 docstring!
        <- spaces QQ


    # 每行加上 prefix
    >>> s = '1\n2\n3\n4'
    >>> textwrap.indent(s, '> ')
    '> 1\n> 2\n> 3\n> 4'
    >>> print(textwrap.indent(s, '> '))
    > 1
    > 2
    > 3
    > 4
    >>> print(textwrap.indent(s, '> ', lambda x: x == '1\n'))
    > 1
    2
    3
    4

    # textwrap 裡的 TextWrapper 還有許多屬性可以設定，
    # 例如是否把 Tabs 展開成空白、是否可以把很長的字分開等等



unicodedata - Unicode Database 查詢
========================================

.. code-block:: python

    >>> import unicodedata

    # 轉數值
    >>> unicodedata.numeric('一')
    1.0
    >>> unicodedata.numeric('壹')
    1.0
    >>> unicodedata.numeric('玖')
    9.0

    # 查名稱
    >>> unicodedata.name('》')
    'RIGHT DOUBLE ANGLE BRACKET'

    # 查字
    >>> unicodedata.lookup('RIGHT DOUBLE ANGLE BRACKET')
    '》'
