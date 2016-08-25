========================================
Writeing a New Valgrind Tool
========================================

Introduction
========================================

Valgrind 把架構分成 core 和 plugin，
其中 core 負責 low-level infrastructure 讓上面的 plugin 可以容易做 instrumentation，
提供的內容包含 JIT compiler、low-level memory manager、signal handling、scheduler (pthread) 等等。

Simple Plugin
========================================

Valgrind 使用 GNU automake、autoconf

.. code-block:: sh

    # 取得 Valgrind source code
    svn co svn://svn.valgrind.org/valgrind/trunk valgrind
    cd valgrind

    # 為自己的 plugin 取個名字 (和縮寫)
    # 這邊先隨便取為 myplugin (mp)
    mkdir -p myplugin/docs myplugin/tests
    touch myplugin/docs/Makefile.am myplugin/tests/Makefile.am

    cp none/Makefile.am myplugin/
    sed -i 's/none/myplugin/g' myplugin/Makefile.am
    sed -i 's/NONE/MYPLUGIN/g' myplugin/Makefile.am
    sed -i 's/nl_/mp_/g' myplugin/Makefile.am
    sed -i 's/nl-/mp-/g' myplugin/Makefile.am

    #  changing the details lines in nl_pre_clo_init() to something appropriate for the tool.
    #  These fields are used in the startup message, except for bug_reports_to which is used if a tool assertion fails.
    cp none/nl_main.c myplugin/mp_main.c
    sed -i 's/nl_/mp_/g' myplugin/mp_main.c

    sed -i '/memcheck \\/a\		myplugin\\' Makefile.am

    # 更新 configure.ac (configure.in 已經 deprecated，Valgrind 官網的文件還沒更新)
    # 加到 AC_CONFIG_FILES
    sed -i '/coregrind\/Makefile/a\   myplugin\/Makefile\n   myplugin\/tests/Makefile\n   myplugin\/docs/Makefile' configure.ac

    ./autogen.sh
    ./configure --prefix=`pwd`/inst
    make -j8 install    #  putting copies of the tool in myplugin/ and inst/lib/valgrind/

    # Test
    inst/bin/valgrind --tool=myplugin date


Error Recording
========================================

Suppression
========================================

Reference
========================================

* `Valgrind Technical Documentation - Writing a New Valgrind Tool <http://www.valgrind.org/docs/manual/writing-tools.html>`_
