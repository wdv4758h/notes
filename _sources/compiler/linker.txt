========================================
Linker
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


* `Acronyms relevant to Executable and Linkable Format (ELF) <https://web.archive.org/web/20120922073347/http://www.acsu.buffalo.edu/~charngda/elf.html>`_
* `StackOverflow - What do 'statically linked' and 'dynamically linked' mean? <https://stackoverflow.com/a/311889>`_
* `musl FAQ <https://www.musl-libc.org/faq.html>`_
