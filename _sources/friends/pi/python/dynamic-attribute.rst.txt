=================
Dynamic Attribute
=================
存取一個物件（例如 ``obj`` ）的屬性時，若該屬性的名稱不存在於 ``obj.__dict__`` 中，則會觸發 ``__getattr__()`` 或 ``__setattr__()``

.. code:: python

  class example:
      def __getattr__(self, attr):
          return 42

      def __setattr__(self, attr, value):
          self.__dict__[attr] = value

注意在屬性被加入 ``__dict__`` 以後，就不會再觸發 ``__getattr__``

注意若希望在 class 內用其他變數管理動態的屬性，要在 ``__init__`` 內加入 ``__dict__`` ，而不是用 ``self._data = {}`` ，否則會觸發無窮遞迴
