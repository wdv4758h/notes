========================================
ELF (Executable and Linkable Format)
========================================


.. contents:: 目錄


ELF Object Files
========================================

Relocatable file
------------------------------

此種 object file 是 relocatable 的，
可以和其他 relocatable files 產生出 executable binary 或 shared object file

.. code-block:: sh

    gcc -Wall -c test.c -o test.o   # use -c to avoid linking


Shared object file
------------------------------

用於讓 dynamic linker 結合其他 executable object file 來讓程式可以正確執行

.. code-block:: sh

    gcc -c -Wall -Werror -fPIC shared.c     # -fPIC for position-independent code
    gcc -shared -o libshared.so shared.o


Executable file
------------------------------

.. code-block:: sh

    gcc -Wall test.c -o test



ELF Header
========================================



readelf
========================================

.. code-block:: sh

    readelf -h /bin/ls  # -f for file header


result :

::

    ELF Header:
      Magic:   7f 45 4c 46 02 01 01 09 00 00 00 00 00 00 00 00
      Class:                             ELF64
      Data:                              2's complement, little endian
      Version:                           1 (current)
      OS/ABI:                            UNIX - FreeBSD
      ABI Version:                       0
      Type:                              EXEC (Executable file)
      Machine:                           Advanced Micro Devices X86-64
      Version:                           0x1
      Entry point address:               0x401dc0
      Start of program headers:          64 (bytes into file)
      Start of section headers:          31000 (bytes into file)
      Flags:                             0x0
      Size of this header:               64 (bytes)
      Size of program headers:           56 (bytes)
      Number of program headers:         8
      Size of section headers:           64 (bytes)
      Number of section headers:         28
      Section header string table index: 27



objdump
========================================

可以印出指定 section 的內容

.. code-block:: sh

    objdump -j .data -s /bin/ls


result:

::

    /bin/ls:     file format elf64-x86-64-freebsd

    Contents of section .data:
     607440 39634000 00000000 00000000 00000000  9c@.............
     607450 18706000 00000000 00000000 00000000  .p`.............
     607460 50000000 00000000 00000000 00000000  P...............
     607470 80746000 00000000 00000000 00000000  .t`.............
     607480 2e000000 ffffffff 02000000 ffffffff  ................
     607490 ffffffff ffffffff                    ........



ELF View
========================================

assembler 或 linker 處理過後，可以被 CPU 執行的檔案是處於 linking view 的

loader 把程式載到 memory 後，object file 會是 execution view



相關資源
========================================

* `ELF101 <https://code.google.com/p/corkami/wiki/ELF101>`_
* `Executable and Linkable Format - Wikipedia <http://en.wikipedia.org/wiki/Executable_and_Linkable_Format>`_
* `Linux ELF Object File Format (and ELF Header Structure) Basics <http://www.thegeekstuff.com/2012/07/elf-object-file-format/>`_
* ELF（Executable and Linking Format）格式教學文件
    - `#1: ELF 簡介 <http://www.jollen.org/blog/2006/11/executable_linking_format_elf_1.html>`_
    - `#2: ELF header 與範例規 <http://www.jollen.org/blog/2006/11/executable_linking_format_elf_2html.html>`_
    - `#3: 第一個範例：loader v0.1（讀 ELF 檔頭） <http://www.jollen.org/blog/2006/11/executable_linking_format_elf_3.html>`_
    - `#4: 第一個範例：loader v0.2（ELF Identification） <http://www.jollen.org/blog/2006/11/executable_linking_format_elf_4.html>`_
    - `#5: 讀 ELF Section（說明） <http://www.jollen.org/blog/2006/11/elfexecutable_and_linking_form.html>`_
    - `#6: 讀 ELF Section（程式列表） <http://www.jollen.org/blog/2006/12/executable_linking_format_elf_6.html>`_
    - `#7: 讀 ELF 的 Section Name（透過 strtab） <http://www.jollen.org/blog/2006/12/elfexecutable_and_linking_form.html>`_
    - `#8: loader v0.5 與結果輸出（改善與小討論） <http://www.jollen.org/blog/2006/12/_elfexecutable_and_linking_for.html>`_
* jserv - 深入淺出 Hello World
* `ELF - 陳鍾誠 <http://ccckmit.wikidot.com/lk:elf>`_
* `ELF 之 Program Loading 教學文件, #2: Program Header Table <http://www.jollen.org/blog/2007/03/elf_program_loading_2_pht.html>`_
* `ELF 之 Program Loading 教學文件, #1: Segment 的觀念 <http://www.jollen.org/blog/2007/03/>`_



* `Wikipedia - Position Independent Code <http://en.wikipedia.org/wiki/Position-independent_code>`_

* `The missing link: explaining ELF static linking, semanticall <http://dominic-mulligan.co.uk/wp-content/uploads/2011/08/oopsla-elf-linking-2016.pdf>`_
