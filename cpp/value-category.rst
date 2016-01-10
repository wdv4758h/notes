========================================
C++ Value Category
========================================

C++ 的 expression 會用兩種性質來做區分，
一個是 type，
另一個是 value categor。

其中 C++ 的 Value 又會依照兩種性質來區分，
一個是 identity，
另一個是可不可以被 move。

+----------+----------+------+-------------------+
|          | Identity | Move |                   |
+==========+==========+======+===================+
| lvalue   | O        | X    |                   |
+----------+----------+------+-------------------+
| prvalue  | X        | O    |                   |
+----------+----------+------+-------------------+
| xvalue   | O        | O    |                   |
+----------+----------+------+-------------------+
| not used | X        | X    |                   |
+----------+----------+------+-------------------+
| glvalue  | O        | X/O  | lvalue or xvalue  |
+----------+----------+------+-------------------+
| rvalue   | X/O      | O    | prvalue or xvalue |
+----------+----------+------+-------------------+

Reference
========================================

* `cppreference - Value categories <http://en.cppreference.com/w/cpp/language/value_category>`_
* `cppreference - C - Value categories <http://en.cppreference.com/w/c/language/value_category>`_
