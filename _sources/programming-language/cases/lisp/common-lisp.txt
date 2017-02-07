========================================
Common Lisp
========================================

Equality
========================================

- http://stackoverflow.com/questions/547436/whats-the-difference-between-eq-eql-equal-and-equalp-in-common-lisp

+----------+---------------------------------------------------------------------------------+
| function | comparison                                                                      |
+==========+=================================================================================+
| =        | value of numbers                                                                |
+----------+---------------------------------------------------------------------------------+
| eq       | memory address                                                                  |
|          |                                                                                 |
|          |                                                                                 |
+----------+---------------------------------------------------------------------------------+
| eql      | memory address, than type & value of numbers                                    |
+----------+---------------------------------------------------------------------------------+
| equal    | structure, values                                                               |
+----------+---------------------------------------------------------------------------------+
| equalp   | like equal, but type insensitive for numbers, case insensitive for char/strings |
+----------+---------------------------------------------------------------------------------+

=
------------------------------

just compares value of **numbers**

.. code-block:: lisp

    (= 4 4.0)
    => T

    (= 6/4 1.5)
    => T

    (= 'r 't)
    => *** - =: R is not a number

    (= 4.0 #c(4.0 0))
    => T

eq
------------------------------

看是不是同個 memory address

eq 因為比的是 memory address，所以一些結果會是 implementation-dependent，
例如 numbers 或 characters 可能會是同個 address

.. code-block:: lisp

    (eq 1 1)
    => T

    (eq 'a 'a)
    => T

    (eq '(1) '(1))
    => NIL

    (eq '(a) '(a))
    => NIL

    (setq x (cons 'a 'b))
    => (A . B)

    (setq y x)
    => (A . B)

    (eq x y)
    => T

    (eq x (cons 'a 'b))
    => NIL

    (eq (cons 'a 'b) (cons 'a 'b))
    => NIL


eql
------------------------------

先看是不是同個 memory address，不是的話再檢查是否為同 type 和 value 的 numbers

(同 type、value 的 number 會不會是同個 memory address 要看實作)

equal
------------------------------

檢查是否為同樣結構、有相同 value 的 objects

.. code-block:: lisp

    (eql (cons 'a 'b) (cons 'a 'b))
    => NIL

    (equal (cons 'a 'b) (cons 'a 'b))
    => T

equalp
------------------------------

類似 equal，但是 numbers 是 type insensitive，chars 或 strings 是 case insensitive

.. code-block:: lisp

    (equal 1 1.0)
    => NIL

    (equalp 1 1.0)
    => T

    (equal "a" "A")
    => NIL

    (equalp "a" "A")
    => T


Books
========================================

* `Practical Common Lisp <http://www.gigamonkeys.com/book/>`_

Reference
========================================

* `Why We Hate Lisp <http://c2.com/cgi/wiki?WhyWeHateLisp>`_
