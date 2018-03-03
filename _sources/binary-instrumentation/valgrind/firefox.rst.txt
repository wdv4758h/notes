========================================
Valgrind & Firefox
========================================

Run Your Firefox
========================================

.. code-block:: sh

    # --smc-check=all     : 我的程式可能會用到 self-modifying code
    #                       (Firefox 的話會 overwrite dynamically generated code)
    # --trace-children    : 我要追蹤子程式
    # --tool=massif       : 使用 Massif
    # --pages-as-heap=yes : 讓 Massif 在 page level 去 profile 所有 memory allocations
    #                       (而不是只有 heap)
    #                       (heap 佔 Firefox 的 memory 使用量不到一半)
    # --detailed-freq=1000000 : 讓 Massif 每 1,000,000 個 snapshot 做一次 detailed snapshot
    #                           (預設是 10，設成 1,000,000 會比較快，
    #                           但是不管設成多少都會在 memory 使用高峰做 detailed snapshot)
    # -no-remote          : 讓 Firefox 開新的 instance
    $ valgrind --smc-check=all --trace-children=yes --tool=massif --pages-as-heap=yes \
        --detailed-freq=1000000 optg64/dist/bin/firefox -P cad20 -no-remote

----

(以下是撰寫中的 Valgrind wrapper)

.. code-block:: sh

    #!/bin/sh

    # a basic wrapper for valgrind

    PWD=`pwd`

    ####################
    # Valgrind basic
    ####################

    VGPARAMS="--trace-children=yes --log-file=$PWD/valgrind.log.%p"

    ####################
    # Valgrind report
    ####################

    VGPARAMS+=" --error-limit=no"               # 不設 error 上限
    VGPARAMS+=" --error-exitcode=255"           # 有 error 的話把 exitcode 設成 255
    VGPARAMS+=" --default-suppressions=yes"     # 使用預設的 suppression
    #VGPARAMS+=" --suppressions=<filename>"
    VGPARAMS+=" --gen-suppressions=all"         # 對 error 生 suppression

    ####################
    # Valgrind malloc
    ####################

    #--alignment=<number>
    #--redzone-size=<number>

    ####################
    # Valgrind extra
    ####################

    #VGPARAMS+=" --smc-check=all"                # 檢查 self-modifying code

    # http://valgrind.org/docs/manual/manual-core.html#manual-core.pthreads_perf_sched
    VGPARAMS+=" --fair-sched=try"               # 嘗試使用 fair scheduling


    ####################
    # Memcheck tool
    ####################

    MC_VGPLUGIN="--tool=memcheck --leak-check=full --show-reachable=yes"
    MC_VGPLUGIN+=" --track-origins=yes"                # 追蹤 undefined value 來源
    MC_VGPLUGIN+=" --keep-stacktraces=alloc-and-free"  # 同時紀錄 alloc 和 free 的 stack trace

    ####################
    # Callgrind
    ####################

    CL_VGPLUGIN=""

    ####################
    # Cachegrind
    ####################

    CG_VGPLUGIN=""

    ####################
    # Helgrind
    ####################

    HG_VGPLUGIN=""

    ####################
    # DRD
    ####################

    DRD_VGPLUGIN=""

    ####################
    # Massif
    ####################

    MS_VGPLUGIN=""
    MS_VGPLUGIN+=" --pages-as-heap=yes"     # 讓 Massif 在 page level 去 profile 所有 memory allocations
                                            # (而不是只有 heap)

    ####################
    # (exp) SGCheck
    ####################

    SG_VGPLUGIN=""

    ####################
    # (exp) DHAT
    ####################

    DH_VGPLUGIN=""

    ####################

    echo "valgrind args: $*"
    exec valgrind $VGPARAMS $VGPLUGIN $*

    # Todo
    #   generate .valgrindrc


VGDB
========================================

Reference
========================================

* `[2010] Memory profiling Firefox with Massif <https://blog.mozilla.org/nnethercote/2010/12/09/memory-profiling-firefox-with-massif/>`_
* `[2011] Memory profiling Firefox with Massif, part 2 <https://blog.mozilla.org/nnethercote/2011/01/07/memory-profiling-firefox-with-massif-part-2/>`_
