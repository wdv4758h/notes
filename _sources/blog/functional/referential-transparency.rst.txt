:title: [FP] Referential Transparency
:slug: referential-transparency
:date: 2014-10-26 11:20
:category: Functional
:tags: funcitonal
:author: wdv4758h
:summary: explain of referential transparency

Short : **no side effect**

----

- `Referential Transparency - wikipedia <http://en.wikipedia.org/wiki/Referential_transparency_%28computer_science%29>`_

Referential Transparency means a expression won't change the behavior of a program

For example :

.. code-block:: c

    // C code

    // this is not referential transparency
    // it's referential opaqueness
    // function will modify the variable outside the function
    void f(int *x) {
        *x += 3;
    }

    // this is referential transparency
    // function won't modify the variable outside the function
    int f(int x) {
        return x+3;
    }

if a function is referential transparency, then it can be optimized by many ways,
ex:

- memoization
- common subexpression elimination
- lazy evaluation
- parallelization

only referentially transparent functions can be memoized (cache the results)

a referentially transparent expression is **deterministic**
(the same results with the same input)
