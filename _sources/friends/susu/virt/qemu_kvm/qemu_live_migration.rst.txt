Quick
-----
- source code version

  - linux 3.12
  - qemu 2.0

source code
-----------

qemu
~~~~
- ``migration.c``
- ``target-arm/kvm.c``
- ``kvm-all.c``

live migration
--------------
basic
~~~~~
1. 5 kind of migration: tcp socket, unix socket, fd, exec, rdma.
2. outgoing is source and incoming is destination.
3. ``qmp_migrate()``

   - 確認連線
   - iteration 轉移資料, 直到某個瓶頸.
   - stop VM and 完全轉移
   - dest VM 啟動
    
source
~~~~~~
確認連線::

    // Migration source (outgoing)
    - qmp_migrate()
      - {protocol}_start_outgoing_migration()
        - {protocol}_wait_for_connect()   
          - migrate_fd_connect()

    // Migration destination (incoming)
    - {protocol}_start_incoming_migration()
      - {protocol}_accept_incoming_migration()
        - process_incoming_migration()

主流程::

    - migrate_fd_connect()
      - migration_thread()
        - qemu_savevm_state_begin()
        - migrate_set_state(MIG_STATE_ACTIVE)
        - loop
          - qemu_savevm_state_iterate()
        - loop exit
          - qemu_savevm_state_complete()
          - vm_stop_force_state(RUN_STATE_FINISH_MIGRATE)
        - runstate_set(RUN_STATE_POSTMIGRATE);

details
~~~~~~~
1. qemu_savevm

   - savevm_handlers is static QTAIL.

resource
~~~~~~~~
- `qemu-kvm-1.1.0源代码中关于迁移的代码分析 <http://www.cnblogs.com/lcchuguo/p/4065309.html>`_

雜七雜八資料
~~~~~~~~~~~~
code trace 過程留下的資料, 沒整理好, 刪了有點可惜所以才留下來.

1. qmp_migrate()
   
    - start_outgoing_migration()

        - get current MigrationState, get MigrationParams from function parameter, initial MigrationState.

            - ``MigrationState* migrate_init(MigrationParams* );``

        - start outgoing migration.

outgoing and incoming migration
"""""""""""""""""""""""""""""""
- qemu_start_incoming_migration() => 根據 URI, 決定 {unix, tcp, ...}_start_incoming_migration()
- `migration-{unix,tcp, ...}`

    - 估計是確定連線成功, source 跟 destination qemu 都成功啟動 migration function.
    - {}_start_outgoing_migration => migrate_fd_connect
    - {}_start_incoming_migration => process_incoming_migration

code trace::

    void migrate_fd_connect(MigrationState *s)
        qemu_thread_create(&s->thread, migration_thread, s, QEMU_THREAD_JOINABLE);

    static void *migration_thread(void *opaque)
        qemu_savevm_state_begin(s->file, &s->params);
        migrate_set_state(s, MIG_STATE_SETUP, MIG_STATE_ACTIVE);

        while (s->state == MIG_STATE_ACTIVE) {
            pending_size = qemu_savevm_state_pending(s->file, max_size);
            if (pending_size && pending_size >= max_size) {
                qemu_savevm_state_iterate(s->file);
            else {
                ret = vm_stop_force_state(RUN_STATE_FINISH_MIGRATE);
                qemu_savevm_state_complete(s->file);
            }
            ret = vm_stop_force_state(RUN_STATE_FINISH_MIGRATE);
        }

        if (s->state == MIG_STATE_COMPLETED) { 
            // migration complete
            runstate_set(RUN_STATE_POSTMIGRATE);
        } else { 
            // migration failed
            if (old_vm_running) {
                vm_start();
            }
        }
        qemu_bh_schedule(s->cleanup_bh);

code trace of ``migration-unix.c``::

    void unix_start_outgoing_migration(MigrationState *s, const char *path, Error **errp)
        unix_nonblocking_connect(path, unix_wait_for_connect, s, errp);
    static void unix_wait_for_connect(int fd, void *opaque)
        // wait for connect and passing connected fd to MigrationState.   
        migrate_fd_connect(s); // MigrationState* s
            
    void unix_start_incoming_migration(const char *path, Error **errp)
        unix_listen(path, NULL, 0, errp);
        qemu_set_fd_handler2(s, NULL, unix_accept_incoming_migration, NULL, (void *)(intptr_t)s);

    static void unix_accept_incoming_migration(void *opaque)
        // accept unix socket
        qemu_set_fd_handler2(s, NULL, NULL, NULL, NULL);
        // open unix socket
        process_incoming_migration(f);

::

    void process_incoming_migration(QEMUFile *f);
        static void process_incoming_migration_co(void *opaque)
    void qemu_start_incoming_migration(const char *uri, Error **errp);

    void tcp_start_incoming_migration(const char *host_port, Error **errp);
    void exec_start_incoming_migration(const char *host_port, Error **errp);

    void tcp_start_outgoing_migration(MigrationState *s, const char *host_port, Error **errp);
    void exec_start_outgoing_migration(MigrationState *s, const char *host_port, Error **errp);
         {unix, fd, rdma} version

    uint64_t migrate_max_downtime(void);
    void do_info_migrate_print(Monitor *mon, const QObject *data);
    void do_info_migrate(Monitor *mon, QObject **ret_data);

    void migrate_fd_error(MigrationState *s);
    void migrate_fd_connect(MigrationState *s);
    int migrate_fd_close(MigrationState *s);

    # migration state
    void add_migration_state_change_notifier(Notifier *notify);
    void remove_migration_state_change_notifier(Notifier *notify);
    bool migration_in_setup(MigrationState *);
    bool migration_has_finished(MigrationState *);
    bool migration_has_failed(MigrationState *);
    MigrationState *migrate_get_current(void);

    extern SaveVMHandlers *savevm_ram_handlers;
    void init_savevm_ram_handlers(void);
