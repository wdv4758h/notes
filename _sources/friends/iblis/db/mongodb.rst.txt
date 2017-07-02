*******
MongoDB
*******

.. toctree::


.. highlight:: javascript

Overview
=========

MongoDB require driver to communicate with server and transfer bson.

BSON document
--------------

Additional type info


Database
---------

Same as *database* in RDBMS


Collection
-----------

It's analogous to *table*.
All the docs in a collection should share similar schema.


CRUD
======

Query
-------

.. _SQL-like: http://docs.mongodb.org/manual/reference/sql-comparison/


MongoDB is quite suitable for making ad-hoc/dynamic query.

We provide large amount of (`SQL-like`_) selectors.


Syntax
^^^^^^^

+ Collection
+ Query Criteria
+ Modifier, e.g.: ``sort``, ``limit``
+ Projection: The fields will be returned

e.g.::

    db.users.find({   // criteria
        'age': {
            '$gt': 18,
        }
    }, {   // projection
        'name': true,
        'age': true,
    })

    { "_id" : ObjectId("55addab1166d94c5f8952452"), "name" : "foo", "age" : 18 }
    { "_id" : ObjectId("55addade166d94c5f8952453"), "name" : "bar", "age" : 20 }


Selector
^^^^^^^^^

.. _$text: `Text Search`_


+ Comparison: ``$eq``, ``$gt``, ... etc.
+ Logical: ``$or``, ``$and``, ... etc.
+ Element: ``$exists``, ``$type``
+ Evaluation: ``$regex``, `$text`_, ``$where``, ... etc.
+ Geospatial: ``$near``, ... etc.
+ Array: ``$all``, ``$size``, ... etc.
+ Comment: ``$comment``.
+ Projection: ``$``, ``$slice``.



Projection
^^^^^^^^^^^^

+ Inclusion Model::

    db.users.find({   // criteria
        'age': {
            '$gt': 18,
        }
    }, {   // include projection
        'name': true,
        'age': true,
    })

    { "_id" : ObjectId("55addab1166d94c5f8952452"), "name" : "foo", "age" : 18 }
    { "_id" : ObjectId("55addade166d94c5f8952453"), "name" : "bar", "age" : 20 }

+ Exclusion Model::

    db.users.find({   // criteria
        'age': {
            '$gt': 18,
        }
    }, {   // exclude projection
        'age': false,
    })

    { "_id" : ObjectId("55addab1166d94c5f8952452"), "name" : "foo", "status" : "A" }
    { "_id" : ObjectId("55addade166d94c5f8952453"), "name" : "bar", "status" : "B" }


Modifier
^^^^^^^^^

+ ``limits``
+ ``skips``
+ ``sort``, this require all doc loaded in mem


Text Search
^^^^^^^^^^^^^

.. _langs: http://docs.mongodb.org/manual/reference/text-search-languages/#text-search-languages


Currently supported `langs`_


Behavior
^^^^^^^^^

+ Each query run in *single* collection
+ Without ``sort``, the order returned is undefined


Cursor
^^^^^^^

The ``find()`` will return a *cursor*.

Iteration
    1. Using ``cursor.next()``
    #. ``cursor.toArray()``
    #. ``cursor.forEach(callback_function)``

Isolation problem
    Same document maybe return more than on time.
    We using snapshot mode to handle it.

Max Doc Size
^^^^^^^^^^^^^

16 MB

16+ MB -> GridFS, required driver

Update
--------

- MongoDB natively support in-place update. Change the fields we want.
-
