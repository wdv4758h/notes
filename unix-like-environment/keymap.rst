xmodmap
========================================

``~/.Xmodmap``

Control & CapsLock 互換
------------------------------

.. code-block:: 

    keycode      37 = Control_L
    keycode      66 = Caps_Lock

    clear   Lock
    clear   Control
    keysym  Control_L   = Caps_Lock
    keysym  Caps_Lock   = Control_L
    add     Lock        = Caps_Lock
    add     Control     = Control_L

Reverse Scrolling
------------------------------

.. code-block:: 

    ! Reverse Scrolling

    pointer = 1 2 3 5 4 7 6 8 9 10 11 12
