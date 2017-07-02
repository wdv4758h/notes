Scope of Variables
===============================================================================

Global Scope
    * ``module``
    * ``baremodule``
    * REPL

    會建立新的 global scope


Soft Local Scope
    繼承 parent scope, 但 ``local`` keyword 建立新變數

    * ``for``
    * ``while``
    * comprehensions
    * ``try``
    * ``let``


Hard Local Scope
    繼承 parent scope, 但 assignement or ``local`` keyword 建立新變數

    * function
    * ``struct``
    * ``macro``


No new scope
    * ``begin``
    * ``if``
