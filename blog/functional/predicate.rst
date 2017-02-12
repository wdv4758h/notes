:title: [FP] predicate
:slug: predicate
:date: 2014-10-28 11:20
:category: Functional
:tags: funcitonal
:author: wdv4758h
:summary: explain of predicate

short :

A **predicate** is a box that takes an argument and returns a **Boolean value**. For example, "x -> x is even".

A **function** is a box that takes an argument and returns a **value**. For example, "x -> x*x"

----

Predicate (謂語) in natural language
========================================

Subject + Predicate : The dog + barks.

The predicate identifies and describes the action of the sentence.

Predicate in Functional
========================================

A predicate is a function that returns the **Boolean value**

In Python
========================================

- `Python - Functional Programming How To <https://docs.python.org/3/howto/functional.html>`_

.. code-block:: python

    '''
    filter(predicate, iter)
    '''

    def is_even(x):
        return (x % 2) == 0

    list(filter(is_even, range(10)))

    # there are more in iterools

In Prolog
========================================

Prolog's BNF

.. code-block:: BNF

    <program> ::= <clause list> <query> | <query>
    <clause list> ::= <clause> | <clause list> <clause>
    <clause> ::= <predicate> . | <predicate> :- <predicate list>.
    <predicate list> ::= <predicate> | <predicate list> , <predicate>
    <predicate> ::= <atom> | <atom> ( <term list> )
    <term list> ::= <term> | <term list> , <term>
    <term> ::= <numeral> | <atom> | <variable> | <structure>
    <structure> ::= <atom> ( <term list> )
    <query> ::= ?- <predicate list>.
    <atom> ::= <small atom> | ' <string> '
    <small atom> ::= <lowercase letter> | <small atom> <character>
    <variable> ::= <uppercase letter> | <variable> <character>
    <lowercase letter> ::= a | b | c | ... | x | y | z
    <uppercase letter> ::= A | B | C | ... | X | Y | Z | _
    <numeral> ::= <digit> | <numeral> <digit>
    <digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <character> ::= <lowercase letter> | <uppercase letter> | <digit> | <special>
    <special> ::= + | - | * | / | \ | ^ | ~ | : | . | ? | | # | $ | &
    <string> ::= <character> | <string> <character>

Prolog has two types of **clause (子句)** : (clause = facts | rules)

- facts

.. code-block:: prolog

    cat(tom).

- rules


.. code-block:: prolog

    animal(tom) :- cat(tom).

Both facts and rules are composed of predicates.

Links
========================================

- `Functional predicate - wikipedia <http://en.wikipedia.org/wiki/Functional_predicate>`_
- `Prolog - wikipedia <http://en.wikipedia.org/wiki/Prolog>`_
