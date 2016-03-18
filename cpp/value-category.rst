========================================
C++ Value Category
========================================

History
========================================

* 196x - CPL - Christopher Strachey

    lvalue, rvalue

* 1966 - BCPL

* 1978 - (K&R) C - Dennis Ritchie

    lvalue, not lvalue

* 1986 - early C++ - Bjarne Stroustrup

    lvalue, rvalue


C++
========================================

C++ 的 expression 會用兩種性質來做區分，
一個是 type，
另一個是 value category。

其中 C++ 的 Value 又會依照兩種性質來區分，
一個是 identity，
另一個是可不可以被 move。

* has identity: i.e. an address, a pointer, the user can determine whether two copies are identical, etc.
* can be moved from: i.e. we are allowed to leave to source of a "copy" in some indeterminate, but valid state

+----------+----------+------+----+-------------------+
|          | Identity | Move |    |                   |
+==========+==========+======+====+===================+
| lvalue   | O        | X    | iM |                   |
+----------+----------+------+----+-------------------+
| prvalue  | X        | O    | Im |                   |
+----------+----------+------+----+-------------------+
| xvalue   | O        | O    | im |                   |
+----------+----------+------+----+-------------------+
| not used | X        | X    | IM |                   |
+----------+----------+------+----+-------------------+
| glvalue  | O        | X/O  | i  | lvalue or xvalue  |
+----------+----------+------+----+-------------------+
| rvalue   | X/O      | O    | m  | prvalue or xvalue |
+----------+----------+------+----+-------------------+

::

    　lvalue   xvalue    prvalue

        \        /\        /
     iM  \      /  \      / Im
          \    / im \    /
           \  /      \  /
            \/ i      \/ m

          glvalue   rvalue

::

    　   std::move
        +---------+
        |         |
        |         v
      lvalue   xvalue    prvalue

        \        /\        /
     iM  \      /  \      / Im
          \    / im \    /
           \  /      \  /
            \/ i      \/ m

          glvalue   rvalue


* prvalues are the implicit moves
* xvalues are the explicit moves


Reference
========================================

* `cppreference - Value categories <http://en.cppreference.com/w/cpp/language/value_category>`_
* `cppreference - C - Value categories <http://en.cppreference.com/w/c/language/value_category>`_
* `Bjarne Stroustrup - "New" Value Terminology <http://www.stroustrup.com/terminology.pdf>`_
