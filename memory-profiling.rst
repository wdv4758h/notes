========================================
Memory Profiling
========================================

.. contents:: Table of Contents

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

Valgrind 的 command 其實只是個 wrapper (wrapper 的 source code 為 repo 裡的 ``coregrind/launcher-linux.c``)，
每個 plugin 都是一個執行檔，
plugin 都放在 ``/usr/lib/valgrind/`` 裡面 (on Arch Linux)，
command 會猜一些環境變數後執行指定的 plugin。

Valgrind 內部有 VEX IR，
會先把要跑的 binary 轉成內部的 VEX IR，
在這之上做處理，
底下再用 Virtual Machine 轉回去 Host Machine 的指令集來執行。

Valgrind 的每個 plugin 都是依照 Valgrind 提供的 framework 來撰寫，
最後整個 link 成執行檔。


執行的大概狀況 (待補資訊)：::

        /usr/bin/valgrind --tool=XXX ./myprogram
    =>  execve /usr/lib/valgrind/XXX-amd64-linux ...
    =>  open myprogram
    =>  load preload /usr/lib/valgrind/vgpreload_XXX-amd64-linux.so
    =>  other tool's stuff


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
圖可以在 terminal 上直接呈現，
但是執行 Massif 會讓程式慢大約 20 倍。

每次 heap 做 allocation 或是 deallocation 的時候 Massif 就會做 snapshot，
預設最多保留 100 個 snapshot，但是可以用 ``--max-snapshots`` 參數來調整，
大部分的 snapshot 為 normal snapshot (只紀錄基本的資訊)，
這種 snapshot 在圖上會用 ``:`` 來表示，
少部份為 detailed snapshot (會包含更多資訊)，
這種 snapshot 在圖上會用 ``@`` 來表示，
最後還有一種叫作 peak snapshot，
peak snapshot 是 detailed snapshot 的一種，
但是是記憶體使用量最高的地方，
這種 snapshot 在圖上會用 ``#`` 來表示。

Massif 預設是紀錄透過 malloc、calloc、realloc、memalign、new、new[] 等等 function 來取得的記憶體，
而不是更低階的 mmap、mremap、brk system call，
也不會紀錄其他區塊的大小 (例如 code、data、BSS segments)，
但是可以用 ``--pages-as-heap=yes`` 參數來把所有的 memory pages 都紀錄起來 (當然包含 stack)


編譯你的程式的時候當然最好使用 ``-g`` 來加上 debug info 再來執行，
這樣可以取得更多資訊。

Massif 的執行結果預設會寫到叫作 ``massif.out.<pid>`` 的檔案，
可以用 ``--massif-out-file`` 參數來更改。


使用參數：

* ``--tool=massif`` : 選擇使用 massif
* ``--stacks=yes`` : 也紀錄 stack 的使用量


生出的結果可以用 ``ms_print`` 指令來觀看，
例如：

.. code-block:: sh

    $ ms_print massif.out.18904
    --------------------------------------------------------------------------------
    Command:            ./a.out
    Massif arguments:   --time-unit=B
    ms_print arguments: massif.out.18904
    --------------------------------------------------------------------------------


         B
      120^                                    ###################################
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
         |                                    #
       0 +----------------------------------------------------------------------->B
         0                                                                     240

    Number of snapshots: 4
     Detailed snapshots: [2 (peak)]

    --------------------------------------------------------------------------------
      n        time(B)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
      0              0                0                0             0            0
      1            120              120              100            20            0
      2            120              120              100            20            0
    83.33% (100B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
    ->83.33% (100B) 0x400556: main (single-heap-more-char.c:4)

    --------------------------------------------------------------------------------
      n        time(B)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
      3            240                0                0             0            0



.. code-block:: sh

    $ ms_print massif.out.18829
    --------------------------------------------------------------------------------
    Command:            ./a.out
    Massif arguments:   --stacks=yes
    ms_print arguments: massif.out.18868
    --------------------------------------------------------------------------------


        KB
    3.125^         ##
         |         # @
         |         # @
         |      :  # @
         |      :  # @
         |    : : :# @
         |    : : :# @
         |    : : :# @
         |    ::: :# @
         |    ::: :# @
         |    ::: :# @
         |    ::: :# @             : :: ::::  : :   :            ::       ::    @
         |    ::: :# @             : :: : ::  : :   :            ::  : :  ::    @
         |    ::: :# @             : :::: ::: :::@ ::::::  :@ : ::: ::@:::::  : @
         |    :::::# @             :::::: :::::::@::::::::::@:: ::: ::@:::::  : @
         |    :::::# @ :         :::::::: :::::::@::::::::::@::::@::::@::::@  : @
         |  : :::::# @::::::::::::::::::: :::::::@::::::::::@::::@::::@::::@::: @
         | ::::::::# @:::        :::::::: :::::::@::::::::::@::::@::::@::::@::::@
         |:::::::::# @:::        :::::::: :::::::@::::::::::@::::@::::@::::@::::@:
         |:::::::::# @:::        :::::::: :::::::@::::::::::@::::@::::@::::@::::@:
       0 +----------------------------------------------------------------------->ki
         0                                                                   124.6

    Number of snapshots: 92
     Detailed snapshots: [12 (peak), 13, 14, 36, 47, 57, 67, 77, 87]

    --------------------------------------------------------------------------------
      n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
      0              0                0                0             0            0
      1          1,492              472                0             0          472
      2          3,046              584                0             0          584
      3          4,046              752                0             0          752
      4          5,748              592                0             0          592
      5          7,178            2,472                0             0        2,472
      6          8,346              600                0             0          600
      7         10,002            2,048                0             0        2,048
      8         11,537            2,720                0             0        2,720
      9         12,774            1,008                0             0        1,008
     10         14,855            2,448                0             0        2,448
     11         16,354            2,496                0             0        2,496
     12         17,461            3,200                0             0        3,200
    00.00% (0B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.

    ...

    --------------------------------------------------------------------------------
      n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
     78        117,027              280                0             0          280
     79        117,910              280                0             0          280
     80        118,710              744                0             0          744
     81        119,512              400                0             0          400
     82        120,315              704                0             0          704
     83        121,182            1,160              100            20        1,040
     84        121,999              664                0             0          664
     85        122,815              456                0             0          456
     86        123,628              520                0             0          520
     87        124,428            1,440                0             0        1,440
    00.00% (0B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
    ...


.. code-block:: sh

    $ ms_print massif.out.21469
    --------------------------------------------------------------------------------
    Command:            ./a.out
    Massif arguments:   --time-unit=B --pages-as-heap=yes
    ms_print arguments: massif.out.21469
    --------------------------------------------------------------------------------


        MB
    5.996^                                                                       :
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                                                                    ::#:
         |                         :::::::::::::::::::::::::::::::::::::::::::::#:
         |                         ::                                         ::#:
         |                         ::                                         ::#:
         |                         ::                                         ::#:
         |                         ::                                         ::#:
         |                         ::                                         ::#:
         |                         ::                                         ::#:
       0 +----------------------------------------------------------------------->MB
         0                                                                   6.230

    Number of snapshots: 21
     Detailed snapshots: [9, 18 (peak)]

    --------------------------------------------------------------------------------
      n        time(B)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
      0          4,096            4,096            4,096             0            0
      1          8,192            8,192            8,192             0            0
      2        147,456          147,456          147,456             0            0
      3        155,648          155,648          155,648             0            0
      4        159,744          159,744          159,744             0            0
      5        163,840          163,840          163,840             0            0
      6        167,936          167,936          167,936             0            0
      7        176,128          176,128          176,128             0            0
      8        180,224          180,224          180,224             0            0
      9        180,224          180,224          180,224             0            0
    100.00% (180,224B) (page allocation syscalls) mmap/mremap/brk, --alloc-fns, etc.
    ->100.00% (180,224B) 0xFFFFFFFFFFFFFFFF: ???

    --------------------------------------------------------------------------------
      n        time(B)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
     10      2,285,568        2,285,568        2,285,568             0            0
     11      2,293,760        2,293,760        2,293,760             0            0
     12      2,416,640        2,416,640        2,416,640             0            0
     13      2,420,736        2,420,736        2,420,736             0            0
     14      6,230,016        6,230,016        6,230,016             0            0
     15      6,254,592        6,254,592        6,254,592             0            0
     16      6,270,976        6,270,976        6,270,976             0            0
     17      6,275,072        6,275,072        6,275,072             0            0
     18      6,393,856        6,156,288        6,156,288             0            0
    100.00% (6,156,288B) (page allocation syscalls) mmap/mremap/brk, --alloc-fns, etc.
    ->97.07% (5,976,064B) 0x40183A9: mmap (in /usr/lib/ld-2.21.so)
    | ->96.07% (5,914,624B) 0x40065CE: _dl_map_object_from_fd (in /usr/lib/ld-2.21.so)
    | | ->96.07% (5,914,624B) 0x4008544: _dl_map_object (in /usr/lib/ld-2.21.so)
    | |   ->61.88% (3,809,280B) 0x400CA60: openaux (in /usr/lib/ld-2.21.so)
    | |   | ->61.88% (3,809,280B) 0x400EF92: _dl_catch_error (in /usr/lib/ld-2.21.so)
    | |   |   ->61.88% (3,809,280B) 0x400CCC2: _dl_map_object_deps (in /usr/lib/ld-2.21.so)
    | |   |     ->61.88% (3,809,280B) 0x400304C: dl_main (in /usr/lib/ld-2.21.so)
    | |   |       ->61.88% (3,809,280B) 0x401643E: _dl_sysdep_start (in /usr/lib/ld-2.21.so)
    | |   |         ->61.88% (3,809,280B) 0x4004D88: _dl_start (in /usr/lib/ld-2.21.so)
    | |   |           ->61.88% (3,809,280B) 0x4000D86: ??? (in /usr/lib/ld-2.21.so)
    | |   |
    | |   ->34.20% (2,105,344B) 0x4000F63: map_doit (in /usr/lib/ld-2.21.so)
    | |     ->34.20% (2,105,344B) 0x400EF92: _dl_catch_error (in /usr/lib/ld-2.21.so)
    | |       ->34.20% (2,105,344B) 0x4000BCD: do_preload (in /usr/lib/ld-2.21.so)
    | |         ->34.20% (2,105,344B) 0x4003580: dl_main (in /usr/lib/ld-2.21.so)
    | |           ->34.20% (2,105,344B) 0x401643E: _dl_sysdep_start (in /usr/lib/ld-2.21.so)
    | |             ->34.20% (2,105,344B) 0x4004D88: _dl_start (in /usr/lib/ld-2.21.so)
    | |               ->34.20% (2,105,344B) 0x4000D86: ??? (in /usr/lib/ld-2.21.so)
    | |
    | ->01.00% (61,440B) in 1+ places, all below ms_print's threshold (01.00%)
    |
    ->02.93% (180,224B) 0xFFFFFFFFFFFFFFFF: ???

    --------------------------------------------------------------------------------
      n        time(B)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
    --------------------------------------------------------------------------------
     19      6,397,952        6,152,192        6,152,192             0            0
     20      6,533,120        6,287,360        6,287,360             0            0


Valgrind - DHAT
========================================

DHAT 是用來檢查程式如何使用 heap 的工具，
會紀錄 allocate 的記憶體、每個記憶體存取 (找哪一塊記憶體) 等等。


使用參數：

* ``--tool=exp-dhat`` : 選擇使用 massif



code：

.. code-block:: c

    // C

    #include <stdlib.h>

    int main () {
        // allocate a lot of heap memory, and then free without using it
        // and here may pay some heap memory for memory allocator
        char* c = malloc(sizeof(char) * 100);
        c[0] = 'a';
        c[7] = 'z';
        free(c);
        return 0;
    }

Valgrind：

.. code-block:: sh

    $ valgrind --tool=exp-dhat ./single-heap-more-char
    ==2607== DHAT, a dynamic heap analysis tool
    ==2607== NOTE: This is an Experimental-Class Valgrind Tool
    ==2607== Copyright (C) 2010-2013, and GNU GPL'd, by Mozilla Inc
    ==2607== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==2607== Command: ./single-heap-more-char
    ==2607==
    ==2607==
    ==2607== ======== SUMMARY STATISTICS ========
    ==2607==
    ==2607== guest_insns:  127,901
    ==2607==
    ==2607== max_live:     100 in 1 blocks
    ==2607==
    ==2607== tot_alloc:    100 in 1 blocks
    ==2607==
    ==2607== insns per allocated byte: 1,279
    ==2607==
    ==2607==
    ==2607== ======== ORDERED BY decreasing "max-bytes-live": top 10 allocators ========
    ==2607==
    ==2607== -------------------- 1 of 10 --------------------
    ==2607== max-live:    100 in 1 blocks
    ==2607== tot-alloc:   100 in 1 blocks (avg size 100.00)
    ==2607== deaths:      1, at avg age 912 (0.71% of prog lifetime)
    ==2607== acc-ratios:  0.00 rd, 0.02 wr  (0 b-read, 2 b-written)
    ==2607==    at 0x4C280B0: malloc (in /usr/lib/valgrind/vgpreload_exp-dhat-amd64-linux.so)
    ==2607==    by 0x400557: main (single-heap-more-char.c:6)
    ==2607==
    ==2607== Aggregated access counts by offset:
    ==2607==
    ==2607== [   0]  1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0
    ==2607== [  16]  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    ==2607== [  32]  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    ==2607== [  48]  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    ==2607== [  64]  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    ==2607== [  80]  0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    ==2607== [  96]  0 0 0 0
    ==2607==
    ==2607==
    ==2607==
    ==2607== ==============================================================
    ==2607==
    ==2607== Some hints: (see --help for command line option details):
    ==2607==
    ==2607== * summary stats for whole program are at the top of this output
    ==2607==
    ==2607== * --show-top-n=  controls how many alloc points are shown.
    ==2607==                  You probably want to set it much higher than
    ==2607==                  the default value (10)
    ==2607==
    ==2607== * --sort-by=     specifies the sort key for output.
    ==2607==                  See --help for details.
    ==2607==
    ==2607== * Each allocation stack, by default 12 frames, counts as
    ==2607==   a separate alloc point.  This causes the data to be spread out
    ==2607==   over far too many alloc points.  I strongly suggest using
    ==2607==   --num-callers=4 or some such, to reduce the spreading.
    ==2607==


Valgrind for Unix-like command
========================================

.. code-block:: sh

    $ echo "hello" > test.txt
    $ valgrind --tool=exp-dhat cat test.txt
    ==18771== DHAT, a dynamic heap analysis tool
    ==18771== NOTE: This is an Experimental-Class Valgrind Tool
    ==18771== Copyright (C) 2010-2013, and GNU GPL'd, by Mozilla Inc
    ==18771== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==18771== Command: cat test.txt
    ==18771==
    ==18771==
    ==18771== ======== SUMMARY STATISTICS ========
    ==18771==
    ==18771== guest_insns:  173,876
    ==18771==
    ==18771== max_live:     138,829 in 30 blocks
    ==18771==
    ==18771== tot_alloc:    138,834 in 31 blocks
    ==18771==
    ==18771== insns per allocated byte: 1
    ==18771==
    ==18771==
    ==18771== ======== ORDERED BY decreasing "max-bytes-live": top 10 allocators ========
    ==18771==
    ==18771== -------------------- 1 of 10 --------------------
    ==18771== max-live:    135,167 in 1 blocks
    ==18771== tot-alloc:   135,167 in 1 blocks (avg size 135167.00)
    ==18771== deaths:      1, at avg age 2,840 (1.63% of prog lifetime)
    ==18771== acc-ratios:  0.00 rd, 0.00 wr  (6 b-read, 6 b-written)
    ==18771==    at 0x4C280B0: malloc (in /usr/lib/valgrind/vgpreload_exp-dhat-amd64-linux.so)
    ==18771==    by 0x405BE8: ??? (in /usr/bin/cat)
    ==18771==    by 0x402436: ??? (in /usr/bin/cat)
    ==18771==    by 0x4E4E78F: (below main) (in /usr/lib/libc-2.21.so)
    ==18771==
    ...
    ==18771==
    ==18771== -------------------- 4 of 10 --------------------
    ==18771== max-live:    120 in 1 blocks
    ==18771== tot-alloc:   120 in 1 blocks (avg size 120.00)
    ==18771== deaths:      1, at avg age 41,012 (23.58% of prog lifetime)
    ==18771== acc-ratios:  3.33 rd, 0.93 wr  (400 b-read, 112 b-written)
    ==18771==    at 0x4C280B0: malloc (in /usr/lib/valgrind/vgpreload_exp-dhat-amd64-linux.so)
    ==18771==    by 0x4E59202: _nl_load_locale_from_archive (in /usr/lib/libc-2.21.so)
    ==18771==    by 0x4E5867A: _nl_find_locale (in /usr/lib/libc-2.21.so)
    ==18771==    by 0x4E57EEE: setlocale (in /usr/lib/libc-2.21.so)
    ==18771==    by 0x401AAB: ??? (in /usr/bin/cat)
    ==18771==    by 0x4E4E78F: (below main) (in /usr/lib/libc-2.21.so)
    ==18771==
    ==18771== Aggregated access counts by offset:
    ==18771==
    ==18771== [   0]  2 2 2 2 2 2 2 2 26 26 26 26 26 26 26 26
    ==18771== [  16]  3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
    ==18771== [  32]  3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
    ==18771== [  48]  3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
    ==18771== [  64]  0 0 0 0 0 0 0 0 3 3 3 3 3 3 3 3
    ==18771== [  80]  3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
    ==18771== [  96]  3 3 3 3 3 3 3 3 3 3 3 3 3 3 3 3
    ==18771== [ 112]  3 3 3 3 3 3 3 3
    ==18771==
    ...

Valgrind for Scripting Language
========================================

Python：

.. code-block:: python

    # hello.py

    print("Hello")


Valgrind：

.. code-block:: sh

    $ valgrind python hello.py
    ==17971== Memcheck, a memory error detector
    ==17971== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
    ==17971== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==17971== Command: python hello.py
    ==17971==
    ==17971== Invalid read of size 4
    ==17971==    at 0x4EDE88B: _PyObject_Free (obmalloc.c:1346)
    ==17971==    by 0x4EE7C25: tupledealloc (tupleobject.c:249)
    ==17971==    by 0x4EAE73E: code_dealloc (codeobject.c:365)
    ==17971==    by 0x4F5FA21: PyImport_ImportFrozenModuleObject (import.c:1275)
    ==17971==    by 0x4F5FAF9: PyImport_ImportFrozenModule (import.c:1291)
    ==17971==    by 0x4F6CE4D: import_init.isra.8 (pythonrun.c:283)
    ==17971==    by 0x4F6DA2E: _Py_InitializeEx_Private (pythonrun.c:449)
    ==17971==    by 0x4F82103: Py_Main (main.c:654)
    ==17971==    by 0x108C05: main (in /usr/bin/python3.4)
    ==17971==  Address 0x6030020 is 336 bytes inside a block of size 1,285 free'd
    ==17971==    at 0x4C2B200: free (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==17971==    by 0x4EAE6BE: code_dealloc (codeobject.c:364)
    ==17971==    by 0x4F5FA21: PyImport_ImportFrozenModuleObject (import.c:1275)
    ==17971==    by 0x4F5FAF9: PyImport_ImportFrozenModule (import.c:1291)
    ==17971==    by 0x4F6CE4D: import_init.isra.8 (pythonrun.c:283)
    ==17971==    by 0x4F6DA2E: _Py_InitializeEx_Private (pythonrun.c:449)
    ==17971==    by 0x4F82103: Py_Main (main.c:654)
    ==17971==    by 0x108C05: main (in /usr/bin/python3.4)
    ...
    ==17971==
    ==17971==
    ==17971== HEAP SUMMARY:
    ==17971==     in use at exit: 434,136 bytes in 341 blocks
    ==17971==   total heap usage: 7,684 allocs, 7,343 frees, 3,394,810 bytes allocated
    ==17971==
    ==17971== LEAK SUMMARY:
    ==17971==    definitely lost: 0 bytes in 0 blocks
    ==17971==    indirectly lost: 0 bytes in 0 blocks
    ==17971==      possibly lost: 2,888 bytes in 5 blocks
    ==17971==    still reachable: 431,248 bytes in 336 blocks
    ==17971==         suppressed: 0 bytes in 0 blocks
    ==17971== Rerun with --leak-check=full to see details of leaked memory
    ==17971==
    ==17971== For counts of detected and suppressed errors, rerun with: -v
    ==17971== Use --track-origins=yes to see where uninitialised values come from
    ==17971== ERROR SUMMARY: 631 errors from 56 contexts (suppressed: 0 from 0)


.. code-block:: sh

    $ valgrind --tool=exp-dhat python hello.py
    ==18016== DHAT, a dynamic heap analysis tool
    ==18016== NOTE: This is an Experimental-Class Valgrind Tool
    ==18016== Copyright (C) 2010-2013, and GNU GPL'd, by Mozilla Inc
    ==18016== Using Valgrind-3.10.1 and LibVEX; rerun with -h for copyright info
    ==18016== Command: python hello.py
    ==18016==
    ==18016==
    ==18016== ======== SUMMARY STATISTICS ========
    ==18016==
    ==18016== guest_insns:  55,485,582
    ==18016==
    ==18016== max_live:     1,165,986 in 3,409 blocks
    ==18016==
    ==18016== tot_alloc:    3,020,163 in 7,049 blocks
    ==18016==
    ==18016== insns per allocated byte: 18
    ==18016==
    ==18016==
    ==18016== ======== ORDERED BY decreasing "max-bytes-live": top 10 allocators ========
    ==18016==
    ==18016== -------------------- 1 of 10 --------------------
    ==18016== max-live:    196,640 in 1 blocks
    ==18016== tot-alloc:   196,640 in 1 blocks (avg size 196640.00)
    ==18016== deaths:      none (none of these blocks were freed)
    ==18016== acc-ratios:  1.23 rd, 1.27 wr  (242,840 b-read, 251,368 b-written)
    ==18016==    at 0x4C280B0: malloc (in /usr/lib/valgrind/vgpreload_exp-dhat-amd64-linux.so)
    ==18016==    by 0x4EC776A: new_keys_object (dictobject.c:342)
    ==18016==    by 0x4EC9394: dictresize (dictobject.c:928)
    ==18016==    by 0x4EC9881: insertdict (dictobject.c:831)
    ==18016==    by 0x4F18614: PyUnicode_InternInPlace (unicodeobject.c:15074)
    ==18016==    by 0x4F5B8A9: r_object (marshal.c:1097)
    ==18016==    by 0x4F5BCFC: r_object (marshal.c:1313)
    ==18016==    by 0x4F5B27E: r_object (marshal.c:1123)
    ==18016==    by 0x4F5BC38: r_object (marshal.c:1283)
    ==18016==    by 0x4F5B27E: r_object (marshal.c:1123)
    ==18016==    by 0x4F5BC38: r_object (marshal.c:1283)
    ==18016==    by 0x4F5C22D: read_object (marshal.c:1381)
    ...
    ==18016==
    ==18016== Aggregated access counts by offset:
    ==18016==
    ==18016== [   0]  1799 1799 1799 1799 1799 1799 1799 1799 561 561 561 561 561 561 561 561
    ==18016== [  16]  6082 6082 6082 6082 6082 6082 6082 6082 13139 13139 13139 13139 13139 13139 13139 13139
    ==18016== [  32]  7513 7513 7513 7513 7512 7512 7512 7512 1667 1667 1667 1667 1667 1667 1667 1667
    ==18016== [  48]  211 211 211 211 211 211 211 211 693 693 693 693 693 693 693 693
    ==18016== [  64]  1111 1111 1111 1111 1111 1111 1111 1111 1431 1431 1431 1431 1431 1431 1431 1431
    ==18016== [  80]  106 106 106 106 106 106 106 106 383 383 383 383 383 383 383 383
    ...


實際專案測試
========================================


Running Valgrind on Android
========================================

Related Topics
========================================

* Valgrind 在 Linux 上的 launcher 會去讀 ``/proc/self/exe``，而 Linux 的 ``/proc/self/`` 會自動依照存取的 process 來 link 到 /proc/$(pid)/
    - Linux fs/proc/base.c
    - man pid_namespaces


Reference
========================================

* `Wikipedia - Valgrind <https://en.wikipedia.org/wiki/Valgrind>`_
* `Wikipedia - Shadow memory <https://en.wikipedia.org/wiki/Shadow_memory>`_
* `Valgrind - Massif: a heap profiler <http://valgrind.org/docs/manual/ms-manual.html>`_
* `Chromium - Deep Memory Profiler <https://www.chromium.org/developers/deep-memory-profiler>`_
* `Using and understanding the Valgrind core <http://valgrind.org/docs/manual/manual-core.html>`_
* `The Design and Implementation of Valgrind <http://valgrind.org/docs/manual/mc-tech-docs.html>`_
* `Valgrind Research Papers <http://www.valgrind.org/docs/pubs.html>`_
* [2003] Valgrind: A Program Supervision Framework
* `[2007] Valgrind: A Framework for Heavyweight Dynamic Binary Instrumentation <http://valgrind.org/docs/valgrind2007.pdf>`_
* [2008] Optimizing Binary Code Produced by Valgrind

Android
------------------------------

* `Valgrind - README.android <http://valgrind.org/docs/manual/dist.readme-android.html>`_
* `Android - Investigating Your RAM Usage <https://developer.android.com/tools/debugging/debugging-memory.html>`_
* `Memory Analysis for Android Applications <http://android-developers.blogspot.tw/2011/03/memory-analysis-for-android.html>`_
