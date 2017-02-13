Concurrent
===============================================================================

.. highlight:: erlang

receive
----------------------------------------------------------------------

::

    receive
        Pattern1 -> value;
        Pattern2 -> value
    after Time ->
        value
    end.

.. note::
    ``Time`` is in millionseconds, but can be atom ``infinity``.


Link
----------------------------------------------------------------------

> "I am going to die if my partner dies."

Here is a race condiction::

    link(spawn(...)).

It's possible that the process crash before the link established.
So, please use::

    spawn_link(...).


Trap
----------------------------------------------------------------------

Turn a process into `system process`::

    process_flag(trap_exit, true).

And get exception via ``receive`` expression, e.g.::

    spawn_link(fun() -> timer:sleep(1000), exit(magic) end), receive X -> X end.

    %% will get {'EXIT',<0.134.0>,magic}.

The ``kill`` signal cannot be trapped::

    > process_flag(trap_exit, true).
    false
    > exit(self(), kill).
    ** exception exit: killed

.. note::
    Because the ``kill`` signal cannot be trapped, so the it will be changed to
    ``killed`` when other process receive the message.


Monitor
----------------------------------------------------------------------

It's special type of ``link`` with

* unidirection

* can be stacked

::

    erlang:monitor(process, Pid).

Note the potential race condiction in following code::

    erlang:monitor(process, spawn(fun() -> ok end)).

So here is an atomic function::

    spawn_monitor(fun() -> ok end).

Demonitor::

    erlang:demonitor(Ref).
    erlang:demonitor(Ref, [flush, info]).


Naming Porcess
----------------------------------------------------------------------

* ``register(atom, Pid)``

And just send via atom::

    > atom ! {self(), hello}
    {<pid>, hello}
