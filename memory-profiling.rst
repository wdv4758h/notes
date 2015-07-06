========================================
Memory Profiling
========================================

Introduction
========================================

Tools
------------------------------

* Valgrind
    - Massif - Heap profiling
    - DHAT - Dynamic Heap Analysis Tool (experimental)
* Heaptrack
* Deep Memory Profiler

Current Version
++++++++++++++++++++

+----------+--------+
| Valgrind | 3.10.1 |
+----------+--------+



Valgrind
------------------------------

架構
++++++++++++++++++++

Valgrind 的 command 其實只是個 wrapper，
每個 plugin 都是一個執行檔，
plugin 都放在 ``/usr/lib/valgrind/`` 裡面 (on Arch Linux)，
command 會猜一些環境變數後執行指定的 plugin。

Installation
++++++++++++++++++++++++++++++++++++++++

command：

.. code-block:: sh

    $ pacman -S valgrind    # Arch Linux


files：

.. code-block:: sh

    $ pacman -Ql valgrind   # Arch Linux


Valgrind's files (install on Arch Linux)： ::

    valgrind /usr/
    valgrind /usr/bin/
    valgrind /usr/bin/callgrind_annotate
    valgrind /usr/bin/callgrind_control
    valgrind /usr/bin/cg_annotate
    valgrind /usr/bin/cg_diff
    valgrind /usr/bin/cg_merge
    valgrind /usr/bin/ms_print
    valgrind /usr/bin/valgrind
    valgrind /usr/bin/valgrind-di-server
    valgrind /usr/bin/valgrind-listener
    valgrind /usr/bin/vgdb
    valgrind /usr/include/
    valgrind /usr/include/valgrind/
    valgrind /usr/include/valgrind/callgrind.h
    valgrind /usr/include/valgrind/config.h
    valgrind /usr/include/valgrind/drd.h
    valgrind /usr/include/valgrind/helgrind.h
    valgrind /usr/include/valgrind/libvex.h
    valgrind /usr/include/valgrind/libvex_basictypes.h
    valgrind /usr/include/valgrind/libvex_emnote.h
    valgrind /usr/include/valgrind/libvex_guest_amd64.h
    valgrind /usr/include/valgrind/libvex_guest_arm.h
    valgrind /usr/include/valgrind/libvex_guest_arm64.h
    valgrind /usr/include/valgrind/libvex_guest_mips32.h
    valgrind /usr/include/valgrind/libvex_guest_mips64.h
    valgrind /usr/include/valgrind/libvex_guest_offsets.h
    valgrind /usr/include/valgrind/libvex_guest_ppc32.h
    valgrind /usr/include/valgrind/libvex_guest_ppc64.h
    valgrind /usr/include/valgrind/libvex_guest_s390x.h
    valgrind /usr/include/valgrind/libvex_guest_x86.h
    valgrind /usr/include/valgrind/libvex_ir.h
    valgrind /usr/include/valgrind/libvex_s390x_common.h
    valgrind /usr/include/valgrind/libvex_trc_values.h
    valgrind /usr/include/valgrind/memcheck.h
    valgrind /usr/include/valgrind/pub_tool_addrinfo.h
    valgrind /usr/include/valgrind/pub_tool_aspacehl.h
    valgrind /usr/include/valgrind/pub_tool_aspacemgr.h
    valgrind /usr/include/valgrind/pub_tool_basics.h
    valgrind /usr/include/valgrind/pub_tool_basics_asm.h
    valgrind /usr/include/valgrind/pub_tool_clientstate.h
    valgrind /usr/include/valgrind/pub_tool_clreq.h
    valgrind /usr/include/valgrind/pub_tool_debuginfo.h
    valgrind /usr/include/valgrind/pub_tool_deduppoolalloc.h
    valgrind /usr/include/valgrind/pub_tool_errormgr.h
    valgrind /usr/include/valgrind/pub_tool_execontext.h
    valgrind /usr/include/valgrind/pub_tool_gdbserver.h
    valgrind /usr/include/valgrind/pub_tool_hashtable.h
    valgrind /usr/include/valgrind/pub_tool_libcassert.h
    valgrind /usr/include/valgrind/pub_tool_libcbase.h
    valgrind /usr/include/valgrind/pub_tool_libcfile.h
    valgrind /usr/include/valgrind/pub_tool_libcprint.h
    valgrind /usr/include/valgrind/pub_tool_libcproc.h
    valgrind /usr/include/valgrind/pub_tool_libcsetjmp.h
    valgrind /usr/include/valgrind/pub_tool_libcsignal.h
    valgrind /usr/include/valgrind/pub_tool_machine.h
    valgrind /usr/include/valgrind/pub_tool_mallocfree.h
    valgrind /usr/include/valgrind/pub_tool_options.h
    valgrind /usr/include/valgrind/pub_tool_oset.h
    valgrind /usr/include/valgrind/pub_tool_poolalloc.h
    valgrind /usr/include/valgrind/pub_tool_rangemap.h
    valgrind /usr/include/valgrind/pub_tool_redir.h
    valgrind /usr/include/valgrind/pub_tool_replacemalloc.h
    valgrind /usr/include/valgrind/pub_tool_seqmatch.h
    valgrind /usr/include/valgrind/pub_tool_signals.h
    valgrind /usr/include/valgrind/pub_tool_sparsewa.h
    valgrind /usr/include/valgrind/pub_tool_stacktrace.h
    valgrind /usr/include/valgrind/pub_tool_threadstate.h
    valgrind /usr/include/valgrind/pub_tool_tooliface.h
    valgrind /usr/include/valgrind/pub_tool_vki.h
    valgrind /usr/include/valgrind/pub_tool_vkiscnums.h
    valgrind /usr/include/valgrind/pub_tool_vkiscnums_asm.h
    valgrind /usr/include/valgrind/pub_tool_wordfm.h
    valgrind /usr/include/valgrind/pub_tool_xarray.h
    valgrind /usr/include/valgrind/valgrind.h
    valgrind /usr/include/valgrind/vki/
    valgrind /usr/include/valgrind/vki/vki-amd64-linux.h
    valgrind /usr/include/valgrind/vki/vki-arm-linux.h
    valgrind /usr/include/valgrind/vki/vki-arm64-linux.h
    valgrind /usr/include/valgrind/vki/vki-darwin.h
    valgrind /usr/include/valgrind/vki/vki-linux-drm.h
    valgrind /usr/include/valgrind/vki/vki-linux.h
    valgrind /usr/include/valgrind/vki/vki-mips32-linux.h
    valgrind /usr/include/valgrind/vki/vki-mips64-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-amd64-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-arm-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-arm64-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-mips32-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-mips64-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-ppc32-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-ppc64-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-s390x-linux.h
    valgrind /usr/include/valgrind/vki/vki-posixtypes-x86-linux.h
    valgrind /usr/include/valgrind/vki/vki-ppc32-linux.h
    valgrind /usr/include/valgrind/vki/vki-ppc64-linux.h
    valgrind /usr/include/valgrind/vki/vki-s390x-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-amd64-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-arm-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-arm64-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-darwin.h
    valgrind /usr/include/valgrind/vki/vki-scnums-mips32-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-mips64-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-ppc32-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-ppc64-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-s390x-linux.h
    valgrind /usr/include/valgrind/vki/vki-scnums-x86-linux.h
    valgrind /usr/include/valgrind/vki/vki-x86-linux.h
    valgrind /usr/include/valgrind/vki/vki-xen-domctl.h
    valgrind /usr/include/valgrind/vki/vki-xen-evtchn.h
    valgrind /usr/include/valgrind/vki/vki-xen-gnttab.h
    valgrind /usr/include/valgrind/vki/vki-xen-hvm.h
    valgrind /usr/include/valgrind/vki/vki-xen-memory.h
    valgrind /usr/include/valgrind/vki/vki-xen-mmuext.h
    valgrind /usr/include/valgrind/vki/vki-xen-sysctl.h
    valgrind /usr/include/valgrind/vki/vki-xen-tmem.h
    valgrind /usr/include/valgrind/vki/vki-xen-version.h
    valgrind /usr/include/valgrind/vki/vki-xen-x86.h
    valgrind /usr/include/valgrind/vki/vki-xen.h
    valgrind /usr/lib/
    valgrind /usr/lib/pkgconfig/
    valgrind /usr/lib/pkgconfig/valgrind.pc
    valgrind /usr/lib/valgrind/
    valgrind /usr/lib/valgrind/32bit-core-valgrind-s1.xml
    valgrind /usr/lib/valgrind/32bit-core-valgrind-s2.xml
    valgrind /usr/lib/valgrind/32bit-core.xml
    valgrind /usr/lib/valgrind/32bit-linux-valgrind-s1.xml
    valgrind /usr/lib/valgrind/32bit-linux-valgrind-s2.xml
    valgrind /usr/lib/valgrind/32bit-linux.xml
    valgrind /usr/lib/valgrind/32bit-sse-valgrind-s1.xml
    valgrind /usr/lib/valgrind/32bit-sse-valgrind-s2.xml
    valgrind /usr/lib/valgrind/32bit-sse.xml
    valgrind /usr/lib/valgrind/64bit-avx-valgrind-s1.xml
    valgrind /usr/lib/valgrind/64bit-avx-valgrind-s2.xml
    valgrind /usr/lib/valgrind/64bit-avx.xml
    valgrind /usr/lib/valgrind/64bit-core-valgrind-s1.xml
    valgrind /usr/lib/valgrind/64bit-core-valgrind-s2.xml
    valgrind /usr/lib/valgrind/64bit-core.xml
    valgrind /usr/lib/valgrind/64bit-linux-valgrind-s1.xml
    valgrind /usr/lib/valgrind/64bit-linux-valgrind-s2.xml
    valgrind /usr/lib/valgrind/64bit-linux.xml
    valgrind /usr/lib/valgrind/64bit-sse-valgrind-s1.xml
    valgrind /usr/lib/valgrind/64bit-sse-valgrind-s2.xml
    valgrind /usr/lib/valgrind/64bit-sse.xml
    valgrind /usr/lib/valgrind/amd64-avx-coresse-valgrind.xml
    valgrind /usr/lib/valgrind/amd64-avx-coresse.xml
    valgrind /usr/lib/valgrind/amd64-avx-linux-valgrind.xml
    valgrind /usr/lib/valgrind/amd64-avx-linux.xml
    valgrind /usr/lib/valgrind/amd64-coresse-valgrind.xml
    valgrind /usr/lib/valgrind/amd64-linux-valgrind.xml
    valgrind /usr/lib/valgrind/arm-core-valgrind-s1.xml
    valgrind /usr/lib/valgrind/arm-core-valgrind-s2.xml
    valgrind /usr/lib/valgrind/arm-core.xml
    valgrind /usr/lib/valgrind/arm-vfpv3-valgrind-s1.xml
    valgrind /usr/lib/valgrind/arm-vfpv3-valgrind-s2.xml
    valgrind /usr/lib/valgrind/arm-vfpv3.xml
    valgrind /usr/lib/valgrind/arm-with-vfpv3-valgrind.xml
    valgrind /usr/lib/valgrind/arm-with-vfpv3.xml
    valgrind /usr/lib/valgrind/cachegrind-amd64-linux
    valgrind /usr/lib/valgrind/callgrind-amd64-linux
    valgrind /usr/lib/valgrind/default.supp
    valgrind /usr/lib/valgrind/drd-amd64-linux
    valgrind /usr/lib/valgrind/exp-bbv-amd64-linux
    valgrind /usr/lib/valgrind/exp-dhat-amd64-linux
    valgrind /usr/lib/valgrind/exp-sgcheck-amd64-linux
    valgrind /usr/lib/valgrind/getoff-amd64-linux
    valgrind /usr/lib/valgrind/helgrind-amd64-linux
    valgrind /usr/lib/valgrind/i386-coresse-valgrind.xml
    valgrind /usr/lib/valgrind/i386-linux-valgrind.xml
    valgrind /usr/lib/valgrind/lackey-amd64-linux
    valgrind /usr/lib/valgrind/libcoregrind-amd64-linux.a
    valgrind /usr/lib/valgrind/libmpiwrap-amd64-linux.so
    valgrind /usr/lib/valgrind/libreplacemalloc_toolpreload-amd64-linux.a
    valgrind /usr/lib/valgrind/libvex-amd64-linux.a
    valgrind /usr/lib/valgrind/massif-amd64-linux
    valgrind /usr/lib/valgrind/memcheck-amd64-linux
    valgrind /usr/lib/valgrind/mips-cp0-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips-cp0-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips-cp0.xml
    valgrind /usr/lib/valgrind/mips-cpu-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips-cpu-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips-cpu.xml
    valgrind /usr/lib/valgrind/mips-fpu-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips-fpu-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips-fpu.xml
    valgrind /usr/lib/valgrind/mips-linux-valgrind.xml
    valgrind /usr/lib/valgrind/mips-linux.xml
    valgrind /usr/lib/valgrind/mips64-cp0-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips64-cp0-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips64-cp0.xml
    valgrind /usr/lib/valgrind/mips64-cpu-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips64-cpu-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips64-cpu.xml
    valgrind /usr/lib/valgrind/mips64-fpu-valgrind-s1.xml
    valgrind /usr/lib/valgrind/mips64-fpu-valgrind-s2.xml
    valgrind /usr/lib/valgrind/mips64-fpu.xml
    valgrind /usr/lib/valgrind/mips64-linux-valgrind.xml
    valgrind /usr/lib/valgrind/mips64-linux.xml
    valgrind /usr/lib/valgrind/none-amd64-linux
    valgrind /usr/lib/valgrind/power-altivec-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power-altivec-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power-altivec.xml
    valgrind /usr/lib/valgrind/power-core-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power-core-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power-core.xml
    valgrind /usr/lib/valgrind/power-fpu-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power-fpu-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power-fpu.xml
    valgrind /usr/lib/valgrind/power-linux-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power-linux-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power-linux.xml
    valgrind /usr/lib/valgrind/power64-core-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power64-core-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power64-core.xml
    valgrind /usr/lib/valgrind/power64-linux-valgrind-s1.xml
    valgrind /usr/lib/valgrind/power64-linux-valgrind-s2.xml
    valgrind /usr/lib/valgrind/power64-linux.xml
    valgrind /usr/lib/valgrind/powerpc-altivec32l-valgrind.xml
    valgrind /usr/lib/valgrind/powerpc-altivec32l.xml
    valgrind /usr/lib/valgrind/powerpc-altivec64l-valgrind.xml
    valgrind /usr/lib/valgrind/powerpc-altivec64l.xml
    valgrind /usr/lib/valgrind/s390-acr-valgrind-s1.xml
    valgrind /usr/lib/valgrind/s390-acr-valgrind-s2.xml
    valgrind /usr/lib/valgrind/s390-acr.xml
    valgrind /usr/lib/valgrind/s390-fpr-valgrind-s1.xml
    valgrind /usr/lib/valgrind/s390-fpr-valgrind-s2.xml
    valgrind /usr/lib/valgrind/s390-fpr.xml
    valgrind /usr/lib/valgrind/s390x-core64-valgrind-s1.xml
    valgrind /usr/lib/valgrind/s390x-core64-valgrind-s2.xml
    valgrind /usr/lib/valgrind/s390x-core64.xml
    valgrind /usr/lib/valgrind/s390x-generic-valgrind.xml
    valgrind /usr/lib/valgrind/s390x-generic.xml
    valgrind /usr/lib/valgrind/s390x-linux64-valgrind-s1.xml
    valgrind /usr/lib/valgrind/s390x-linux64-valgrind-s2.xml
    valgrind /usr/lib/valgrind/s390x-linux64.xml
    valgrind /usr/lib/valgrind/vgpreload_core-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_drd-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_exp-dhat-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_exp-sgcheck-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_helgrind-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_massif-amd64-linux.so
    valgrind /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so
    valgrind /usr/share/
    valgrind /usr/share/doc/
    valgrind /usr/share/doc/valgrind/
    valgrind /usr/share/doc/valgrind/html/
    valgrind /usr/share/doc/valgrind/html/FAQ.html
    valgrind /usr/share/doc/valgrind/html/QuickStart.html
    valgrind /usr/share/doc/valgrind/html/bbv-manual.html
    valgrind /usr/share/doc/valgrind/html/cg-manual.html
    valgrind /usr/share/doc/valgrind/html/cl-format.html
    valgrind /usr/share/doc/valgrind/html/cl-manual.html
    valgrind /usr/share/doc/valgrind/html/design-impl.html
    valgrind /usr/share/doc/valgrind/html/dh-manual.html
    valgrind /usr/share/doc/valgrind/html/dist.authors.html
    valgrind /usr/share/doc/valgrind/html/dist.html
    valgrind /usr/share/doc/valgrind/html/dist.news.html
    valgrind /usr/share/doc/valgrind/html/dist.news.old.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-android.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-android_emulator.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-developers.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-mips.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-missing.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-packagers.html
    valgrind /usr/share/doc/valgrind/html/dist.readme-s390.html
    valgrind /usr/share/doc/valgrind/html/dist.readme.html
    valgrind /usr/share/doc/valgrind/html/drd-manual.html
    valgrind /usr/share/doc/valgrind/html/faq.html
    valgrind /usr/share/doc/valgrind/html/hg-manual.html
    valgrind /usr/share/doc/valgrind/html/images/
    valgrind /usr/share/doc/valgrind/html/images/home.png
    valgrind /usr/share/doc/valgrind/html/images/next.png
    valgrind /usr/share/doc/valgrind/html/images/prev.png
    valgrind /usr/share/doc/valgrind/html/images/up.png
    valgrind /usr/share/doc/valgrind/html/index.html
    valgrind /usr/share/doc/valgrind/html/license.gfdl.html
    valgrind /usr/share/doc/valgrind/html/license.gpl.html
    valgrind /usr/share/doc/valgrind/html/licenses.html
    valgrind /usr/share/doc/valgrind/html/lk-manual.html
    valgrind /usr/share/doc/valgrind/html/manual-core-adv.html
    valgrind /usr/share/doc/valgrind/html/manual-core.html
    valgrind /usr/share/doc/valgrind/html/manual-intro.html
    valgrind /usr/share/doc/valgrind/html/manual-writing-tools.html
    valgrind /usr/share/doc/valgrind/html/manual.html
    valgrind /usr/share/doc/valgrind/html/mc-manual.html
    valgrind /usr/share/doc/valgrind/html/ms-manual.html
    valgrind /usr/share/doc/valgrind/html/nl-manual.html
    valgrind /usr/share/doc/valgrind/html/quick-start.html
    valgrind /usr/share/doc/valgrind/html/sg-manual.html
    valgrind /usr/share/doc/valgrind/html/tech-docs.html
    valgrind /usr/share/doc/valgrind/html/vg_basic.css
    valgrind /usr/share/doc/valgrind/valgrind_manual.pdf
    valgrind /usr/share/doc/valgrind/valgrind_manual.ps
    valgrind /usr/share/man/
    valgrind /usr/share/man/man1/
    valgrind /usr/share/man/man1/callgrind_annotate.1.gz
    valgrind /usr/share/man/man1/callgrind_control.1.gz
    valgrind /usr/share/man/man1/cg_annotate.1.gz
    valgrind /usr/share/man/man1/cg_diff.1.gz
    valgrind /usr/share/man/man1/cg_merge.1.gz
    valgrind /usr/share/man/man1/ms_print.1.gz
    valgrind /usr/share/man/man1/valgrind-listener.1.gz
    valgrind /usr/share/man/man1/valgrind.1.gz
    valgrind /usr/share/man/man1/vgdb.1.gz


Valgrind - Massif
========================================

Massif 是一個 heap profiler，
利用定期對程式的 heap 做 snapshots 來做 profiling，
分析 heap 的使用量，以及多少的記憶體是為了 book-keeping 或是 alignment 而花費掉的，
也可以測量 stack 的使用量 (預設沒開)，
最後產生出 graph 來呈現 heap 在各個時間點的使用量，
並且包含程式的哪部份用了最多的 memory allocations，
圖的呈現可以是 text 或是 HTML，
但是 Massif 會讓程式慢大約 20 倍。

編譯你的程式的時候當然最好使用 ``-g`` 來加上 debug info 再來執行，
這樣可以取得更多資訊。


使用參數：

* ``--tool=massif`` : 選擇使用 massif



Valgrind - DHAT
========================================

DHAT 是用來檢查程式如何使用 heap 的工具，
會紀錄 allocate 的記憶體、每個記憶體存取 (找哪一塊記憶體) 等等。


使用參數：

* ``--tool=exp-dhat`` : 選擇使用 massif


實際專案測試
========================================


Reference
========================================

* `Wikipedia - Valgrind <https://en.wikipedia.org/wiki/Valgrind>`_
* `Valgrind - Massif: a heap profiler <http://valgrind.org/docs/manual/ms-manual.html>`_
* `Chromium - Deep Memory Profiler <https://www.chromium.org/developers/deep-memory-profiler>`_

Android
------------------------------

* `Android - Investigating Your RAM Usage <https://developer.android.com/tools/debugging/debugging-memory.html>`_
* `Memory Analysis for Android Applications <http://android-developers.blogspot.tw/2011/03/memory-analysis-for-android.html>`_
