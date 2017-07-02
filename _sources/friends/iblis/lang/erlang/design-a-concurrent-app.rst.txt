Designing a Concurrent Application
===============================================================================

Origin: http://learnyousomeerlang.com/designing-a-concurrent-application

- "A reminder app"


Requirement
----------------------------------------------------------------------

Task:

+-------+----------+
| name  | deadline |
+-------+----------+


Operation:

* Cancel event by name.

* Task deadline alert.


Component
----------------------------------------------------------------------

* Task Server

* Client

* Task process


Protocol
----------------------------------------------------------------------

* client monitor server

* server monitor client, also

> client can live without server, and vice versa.
