========================================
Linker
========================================


.. contents:: 目錄


介紹
========================================

現今成熟的 Open Source Linker :

* `GNU ld <https://sourceware.org/git/gitweb.cgi?p=binutils-gdb.git;a=tree;f=ld;hb=HEAD>`_

    Linux kernel

* `Google gold <https://sourceware.org/git/gitweb.cgi?p=binutils-gdb.git;a=tree;f=gold;hb=HEAD>`_

    Linux kernel

* `Apple ld64 <http://www.opensource.apple.com/source/ld64/>`_

    Mac OS X, iOS

* `MCLinker <https://github.com/mclinker/mclinker>`_

    BSD, Android

----

system linkers 非常複雜，而其中 ELF linkers 又超級複雜，
有很多沒寫在文件上的行為和特定 target 才有的行為。
雖然很多研究都證明 linker 可以對程式進行很大程度的效能優化，
但是現今實作依然甚少從中獲益。



History
========================================



靜態連結
========================================



動態連結
========================================



Linker Script
========================================

* `ld - Linker Scripts <https://sourceware.org/binutils/docs/ld/Scripts.html>`_
* `GNU ld 的 linker script 簡介 <https://www.slideshare.net/zzz00072/gnu-ldlinker-script>`_
* `Linker Script 初探 - GNU Linker LD 手冊略讀 <http://wen00072.github.io/blog/2014/03/14/study-on-the-linker-script/>`_
* `OSDev - Linker Scripts <http://wiki.osdev.org/Linker_Scripts>`_
* Linux kernel 的 vmlinuz.lds
* ``/usr/lib/ldscripts/``
* `MCLinker - script parser <https://github.com/mclinker/mclinker/blob/master/lib/Script/ScriptParser.yy>`_
* LLD
    - `lld/ELF/LinkerScript.h <https://github.com/llvm-mirror/lld/blob/master/ELF/LinkerScript.h>`_
    - `lld/ELF/LinkerScript.cpp <https://github.com/llvm-mirror/lld/blob/master/ELF/LinkerScript.cpp>`_


* Bringing link-time optimization to the embedded world: (Thin)LTO with Linker Scripts
    - `Slides <https://llvm.org/devmtg/2017-10/slides/LTOLinkerScriptsEdlerVonKoch.pdf>`_
    - `Video <https://www.youtube.com/watch?v=hhaPAKUt35E>`_
    - examples
        + Tightly Coupled Memories (TCM)
        + RAM / ROM placement
        + Compressio
    - original LTO might miss source object file name, and cause linker script generate bad binary
    - add IR symbol table
    - feed IR symbol table and Linker script together
    - ThinLTO be enhanced to support path-based rules in linker scripts



LLD Linker
========================================

目前使用 LLD 作為系統 Linker 的系統：

* CloudABI
* Fuchsia
* FreeBSD
    - https://github.com/freebsd/freebsd/commit/0691a52b0f6d2925df0254b8e73cf3e02abc162e

有支援 LLD 的專案：

* Chromium
* Clang/LLVM


其他：

* FreeBSD 正常式使用 LLD 作為系統預設的 Linker


參考：

* [2016] `LLD status update and performance chart - Rui Ueyama <http://lists.llvm.org/pipermail/llvm-dev/2016-December/107981.html>`_
* `The ELF linker symbol table design has been ported to the COFF linker in LLD <https://reviews.llvm.org/rL289280>`_
* `Identical code folding (ICF) in LLD has been parallelised <https://reviews.llvm.org/rL288373>`_
* [2016] `New LLD linker for ELF <http://llvm.org/devmtg/2016-03/Presentations/EuroLLVM%202016-%20New%20LLD%20linker%20for%20ELF.pdf>`_
* [2016] `LLD: A new linker for FreeBSD <https://www.bsdcan.org/2016/schedule/events/656.en.html>`_



Binary Format
========================================

ELF
------------------------------

COFF
------------------------------



Linker Architecture
========================================



Linker 優化技術 (Optimization Technology)
=========================================

Identical Code Folding
------------------------------



參數
========================================

--as-needed
------------------------------



Reference
========================================

* `Gentoo Wiki - Gold <https://wiki.gentoo.org/wiki/Gold>`_
* [2013] `The Theory, History and Future of System Linkers <http://www.hellogcc.org/wp-content/uploads/2013/11/hellogcc2013_5.pptx>`_
* [2008] `A New ELF Linker <http://research.google.com/pubs/pub34417.html>`_
* [2002] `Linkers and Loaders <https://www.linuxjournal.com/article/6463>`_
* [2014][Book] `Advanced C and C++ Compiling <http://www.amazon.com/Advanced-C-Compiling-Milan-Stevanovic/dp/1430266678/>`_
* [1999][Book] `Linkers and Loaders <http://www.amazon.com/Linkers-Kaufmann-Software-Engineering-Programming/dp/1558604960/>`_
* `Wikipedia - Linker (computing) <https://en.wikipedia.org/wiki/Linker_%28computing%29#Linkage_editor>`_
* `Wikipedia - gold (linker) <https://en.wikipedia.org/wiki/Gold_%28linker%29>`_


* [2006] `Optimizing Linker Load Times <https://lwn.net/Articles/192624/>`_
* [2016] `The Missing Link: Explaining ELF Static Linking, Semantically <http://dl.acm.org/citation.cfm?doid=2983990.2983996>`_


* `Acronyms relevant to Executable and Linkable Format (ELF) <https://web.archive.org/web/20120922073347/http://www.acsu.buffalo.edu/~charngda/elf.html>`_
* `StackOverflow - What do 'statically linked' and 'dynamically linked' mean? <https://stackoverflow.com/a/311889>`_
* `musl FAQ <https://www.musl-libc.org/faq.html>`_

* `Project:Quality Assurance/As-needed <https://wiki.gentoo.org/wiki/Project:Quality_Assurance/As-needed>`_
