========================================
GTK
========================================


.. contents:: 目錄


介紹
========================================



PyGTK to PyGObject
========================================

:Documentation: https://pygobject.readthedocs.io/en/latest/


GTK 以前有一個 Python binding 叫 PyGTK，
但是後來換成使用更有彈性的 PyGObject，
PyGObject 可以處理各種用 GObject 實做的 library，
包含 GTK+、GStreamer、GIO 等等，
對於 binding 的產生和更新方便許多。


要轉換可以嘗試使用簡單地相容層：

.. code-block:: python

    from gi import pygtkcompat

    pygtkcompat.enable()
    pygtkcompat.enable_gtk(version='3.0')


或是使用 ``pygi-convert.sh``


* `Johns Blog - End of an Era: PyGTK <http://johnstowers.co.nz/2011/04/03/end-of-an-era-pygtk/>`_
* `Migrating from GTK+ 2.x to GTK+ 3 <https://developer.gnome.org/gtk3/3.2/gtk-migrating-2-to-3.html>`_
* `GNOME Wiki - PyGObject Introspection Porting <https://wiki.gnome.org/Projects/PyGObject/IntrospectionPorting>`_



參考
========================================
