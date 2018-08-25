********
Cloudant
********

.. toctree::


CouchDB is the database for hackers.
The philosophy of design is totally different from Mongo.

CouchDB let application built/stored inside database (via design document).
And hackers can make a customized query server to create magical data service!


REST API
===========

The REST api is stateless.
Thus, there is *no cursor*.


/_all_docs
----------

sorted key list


GET
^^^^

params:

+ startkey
+ endkey
+ include_doc=(true|false) *false*
+ descending=(true|false) *false*
+ limit=N
+ skip=N


Replication
============

CouchDB developes a well-defined replication protocol.

+ Only sync on differ, including change history, deleted docs.
+ compression through transfer

Master To Master
----------------

CouchDB can just setup replicator on both end to achieve this.

Single Replication
------------------

For the snapshot of database

``_local`` doc
----------------

The doc recorded in ``_local`` won't be sent through replication.

API
^^^^

::

    METHOD /database/_local/id


Alternative
^^^^^^^^^^^^^

If we want to use including method, we can use ``docs_id`` in replication doc::

    doc_ids (optional)  Array of document IDs to be synchronized


Replicator Database
--------------------

The field ``_replication_state`` always is ``triggered``,
if this replication is set to ``continue``.


Idea
------

We can build a application understanding this protocol to

#. make a backup service


Revision
=========

limits
-------

CouchDB can track document's revsion up to 1000 (default limit, configurable)

.. code-block:: shell

    $ curl "http://{server}/{db}/_revs_limit"
    1000

Get revisions list
-------------------

.. code-block:: shell

    $ curl "http://{server}/{db}/{doc}?revs=true"

    $ curl "http://{server}/{db}/{doc}?revs_info=true"


Secondary index
===============

MapReduce
---------

+ Unable to join between documents

Map Function
^^^^^^^^^^^^^

``map() -> (key, val)``

+ build-in MapReduce fnuctions was written in Erlang -> faster

reduce function can be group by ``key``
    + ``pi?group=true``
    + ``api?group_level=N``

multiple ``emit``

    .. code-block:: javascript


        function(doc)
        {
            emit(doc.id, 1);
            emit(doc.other, 2);
        }


GET
    :reduce: ``true|false``
    :group:  ``true|false``
    :stale:  ``ok`` -> optional skip index building
    :group_level:
        key in [k1, k2, k3]

        ``group_level=1`` -> group by [k1]

        ``group_level=2`` -> group by [k1, k2]


Reduce Function
^^^^^^^^^^^^^^^
if rereduce is False::

    reduce(
        [ 
            [key1, id1],
            [key2, id2],
            [key3, id3]
        ],
        [ value1, value2, value3 ],
        false,
    ) 


e.g::

    reduce(
        [ 
            [
                [
                    id,
                    val,
                ],
                id1],
            [
                [
                    id,
                    val,
                ]
                , id2],
            [
                [
                    id,
                    val,
                ]
                , id3]
        ],
        [ value1, value2, value3 ],
        false,
    ) 


View Group
-----------

One design doc can contain multiple view.
Thus, there is a view group.

Each view group consume one Query Server(one process),



Chainable MapReduce
^^^^^^^^^^^^^^^^^^^

Add ``dbcopy`` field in design document

+ cloudant *only* feature

TOOD
    `ref <http://examples.cloudant.com/sales/_design/sales/index.html>`_


CouchApp
==========

This is the killer feature of CouchDB.

Application can live in CouchDB.

The function defined in design documents will be run with *Query Server*.
CouchDB self-shipped a js engine, SpiderMonkey, as default *Query Server*.
We can customized our Query Server, also.

- It contains server-side js engine, earlier than nodejs.

- `Couch Desktop <http://www.freedesktop.org/wiki/Specifications/desktopcouch/>`_

- CouchApp can be distributed via `Replication`_ .

Query Server
-------------

Protocol
^^^^^^^^^^
CouchDB communicate with it via `stdio`.

Time out
^^^^^^^^^

config

.. code-block:: shell

    # to show
    $ curl -X GET deb/_config/couchdb
    {
        "uuid": "47a043497fb27ffd481a25671220b2c5",
        "max_document_size": "67108864",
        "database_dir": "/srv/cloudant/db",
        "file_compression": "snappy",
        "geo_index_dir": "/srv/cloudant/geo_index",
        "attachment_stream_buffer_size": "4096",
        "max_dbs_open": "500",
        "delayed_commits": "false",
        "view_index_dir": "/srv/cloudant/view_index",
        "os_process_timeout": "5000"
    }

    # change config
    $ curl -X PUT deb/_config/couchdb/os_process_timeout -d '10000'


Show Function
-------------


List Function
-------------


Update Function
----------------

``updatefuc(doc, req)``


Cloudant Search
===============

+ build on Apache Lucene
+ text searching
+ text analyzer
+ ad-hoc query
    + primary index
    + secondary index
+ can create index on inside text

Query Syntax
-------------

`Lucene query syntax ref <https://lucene.apache.org/core/5_2_0/queryparser/org/apache/lucene/queryparser/classic/package-summary.html#package_description>`_


Index Function
--------------

``index('field', doc.field, {options: val})``


Cloudant Query
===============

+ JSON query syntax
+ store in design doc
    + primary index (out-of-box)
    + type ``json``: store json index in ``view.map``
    + search index -> type ``text``
    + lang (query server) ``query``


Security
=========

Auth
-----

``local.ini``
^^^^^^^^^^^^^^

Assume we have the following admin section with unencrypted password.

::

    [admin]

    admin = password
    foo = bar
    ...

And restart the cloudant/couchdb, it will auto generate encrypted password for you.

Couchdb:

.. code-block:: shell

        $ sudo service couchdb restart

Cloudant on debian:

.. code-block:: shell

        $ sudo sv restart /etc/service/cloudant


Comparison
===========

The following table compare some method in design document.


+------------+---------------------------+---------------------------+---------------------------+
| item       | Secondary Index           | Cloudant Search           | Cloudant Query            |
+------------+---------------------------+---------------------------+---------------------------+
| Require to | V                         | V                         | X                         |
| build      |                           |                           |                           |
| index      |                           |                           |                           |
+------------+---------------------------+---------------------------+---------------------------+
| Senario    | - Map                     | - Search engine           | - Ad-hoc query            |
|            |    - doc filtering        |    - keyword search       | - module mango            |
|            |    - doc reshaping        |    - tokenlizer           |    - provide mongo-like   |
|            |    - multiple ``emit()``  |    - fuzzy search         |      query syntax         |
|            | - Reduce                  |    - regex                | - SQL-like                |
|            |    - ``sum``              |    - numeric value        |    - need to define       |
|            |    - ``stat``             |       - range base        |      schema first         |
|            |    - ``count``            |                           |                           |
|            |    - grouping             |                           |                           |
|            |    - complex key          |                           |                           |
|            |    - *for reporting*      |                           |                           |
|            | - Query Server            |                           |                           |
|            |    - embeded AP           |                           |                           |
|            |    - special protocol     |                           |                           |
|            |    - highly customized    |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
|            |                           |                           |                           |
+------------+---------------------------+---------------------------+---------------------------+

Attachment
===========

All data (whatever readable or unreadable) store in the database B-tree.

An attachment should be store under a document.


API
----

e.g.: We have a doc ``user``

.. code-block:: shell

    $ curl -X GET http://{server}/{db}/{user}

.. code-block:: javascript

    {
        "id": "user",
        ...
        "_attachments": {
            "filename": {
                "content_type": "...",
                ... // meta datas
            }
        }
    }


Create
^^^^^^^

Via ``PUT`` to ::

    http://{server}/{db}/{user}/{filename}


Cluster
=========

API
----

GET /_up
^^^^^^^^^^

GET /_haproxy
^^^^^^^^^^^^^^^

GET /_haproxy_health_check
^^^^^^^^^^^^^^^^^^^^^^^^^^^^


Idea
======

Create ecosystem
------------------

#. CouchApp + ``http://codepen.io``
    clone app from codepen!

#. CouchApp + ``deck.js``


Visual tool for schema discover


Survey
=======

Mongo cluster
