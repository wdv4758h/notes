Finite State Machine
===============================================================================

* elements: 狀態 (State), Event, and Data (狀態轉移時可能帶著其他資訊)

    :Event: 如， State A 收到 Event foo (with Data X) 會轉移到 State B

Simple cat FSM:

.. literalinclude:: ./cat_fsm.erl
   :language: erlang
   :linenos:
