2 phase commit in database
==========================

PostgreSQL
----------
- `pgsql wiki - 2PC on FDW <https://wiki.postgresql.org/wiki/2PC_on_FDW#Internal>`_

  - Cluster-wide atomic commit: guarantees distributed transaction did either commit or rollback on all foreign servers.

- `pgsql 9.3 - Prepare Transaction <https://www.postgresql.org/docs/9.3/static/sql-prepare-transaction.html>`_

  - prepares the current transaction for 2PC.
  - It's intended for use by external transaction manager, some of which are covered by standards(such as X/Open XA).
  - `wikipedia - X/Open XA <https://en.wikipedia.org/wiki/X/Open_XA>`_

    - spec for distributed transaction processing (DTP)
    - XA-compliant resource manager
    - `XA transaction for MySQL (available in InnoDB) <https://dev.mysql.com/doc/refman/5.7/en/xa.html>`_

- 3rd party extension: `Master-less Distributed Queue with PG Paxos <https://www.citusdata.com/blog/2016/04/13/masterless-distributed-queue/>`_
- `Postgres-XC (eXtensible Cluster) <https://wiki.postgresql.org/wiki/Postgres-XC>`_

  - Postgres-XC is a multi-master write-scalable PostgreSQL cluster based on shared-nothing architecture

More
~~~~
- `the 2PC performance improvements in PG10 <https://git.postgresql.org/gitweb/?p=postgresql.git;a=commit;h=978b2f65aa1262eb4ecbf8b3785cb1b9cf4db78e>`_

  - skip two phase state files in normal path
  - 2PC state info is written only to WAL at PREPARE. 
    Prepared transactions that live past one bufmgr checkpoint cycle, will be written to disk.
  - Measured performance gains of 50-100% for short 2PC transactions.

- The Transaction System (src/backend/access/transam/README)

  - PostgreSQL's transaction system is a three-layer system.
    
    - bottom layer: implements low-level transactions and subtransactions.
    - top layer: rests the mainloop's control code, which in turn implements user-visible transactions and savepoints.
    - middle layer: ``StartTransactionCommand, CommitTransactionCommand, AbortCurrentTransaction``

- terminology

  - WAL-log => xlog

More
----
- Java Transaction API 

  - JSR 907, Java EE spec?
  - enable distributed transaction to be done across multiple XA resources
  - implementations: EJB(Enterprise JavaBeans), JNDI, Narayana ... etc.
    
    - RHEL JBoss EAP application use Narayana.

  - https://en.wikipedia.org/wiki/Java_Transaction_API
  - https://access.redhat.com/documentation/en-us/red_hat_jboss_enterprise_application_platform/7.0/html/development_guide/java_transaction_api_jta
