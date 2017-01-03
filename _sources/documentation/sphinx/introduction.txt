========================================
Sphinx
========================================


.. contents:: 目錄


使用者
========================================

* `使用 Sphinx 的專案們 <http://www.sphinx-doc.org/en/latest/examples.html>`_


Linux kernel
------------------------------

介紹
++++++++++++++++++++

Linux kernel 在 2016 年把文件從原本的 DocBook 轉換到 Sphinx 上，
也因此在 Linux 4.8-rc1 中有超過 20% 的 patch 在文件上，

* `How to write kernel documentation <https://www.kernel.org/doc/html/latest/doc-guide/sphinx.html>`_
* `Kernel documentation with Sphinx, part 1: how we got here <https://lwn.net/Articles/692704/>`_
* `Kernel documentation with Sphinx, part 2: how it works <https://lwn.net/Articles/692705/>`_
* `Kernel documentation update <https://lwn.net/Articles/705224/>`_

* `conf.py 設定檔 <https://github.com/torvalds/linux/blob/master/Documentation/conf.py>`_
* `Makefile.sphinx <https://github.com/torvalds/linux/blob/master/Documentation/Makefile.sphinx>`_
* `Linux kernel Sphinx extensions folder <https://github.com/torvalds/linux/tree/master/Documentation/sphinx>`_


kerneldoc
++++++++++++++++++++

`kerneldoc <https://github.com/torvalds/linux/blob/master/Documentation/sphinx/kerneldoc.py>`_
可以從 Kernel 程式碼內爬出特定格式的註解來生成文件。


rstFlatTable
++++++++++++++++++++

`rstFlatTable <https://github.com/torvalds/linux/blob/master/Documentation/sphinx/rstFlatTable.py>`_
實做 ``rstFlatTable`` directive，
輔助 table 的撰寫。


kernel_include
++++++++++++++++++++

`kernel_include <https://github.com/torvalds/linux/blob/master/Documentation/sphinx/kernel_include.py>`_
實做 ``kernel-include`` directive，
用於取代內建的 include 功能，
讓 include 更適用於 Kernel 的程式碼。


cdomain
++++++++++++++++++++

Sphinx 的 `Domains <http://www.sphinx-doc.org/en/latest/domains.html>`_ 是支援不同程式語言的方式，
雖然 Sphinx 內建就有 C Domain，
但是 Linux kernel 內的
`cdomain <https://github.com/torvalds/linux/blob/master/Documentation/sphinx/cdomain.py>`_
實做了替換 Sphinx 內建的 C Domain 的 Extension，
做了一些客製化。



常見 Sphinx Extensions
========================================



參考
========================================
