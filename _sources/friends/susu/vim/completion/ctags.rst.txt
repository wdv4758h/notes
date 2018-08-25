Ctags note
==========

ctags CLI options
-----------------

generate tag file ``tags`` at local directory.

Basic Usage

- ``ctags --list-languages``, ``ctags --list-kinds``: check ctags support languages/features
- ``ctags -R .``: Generate tag file for current directory source (e.g. find all files in `./**/*.c, ./**/*.cpp ...``)
- ``ctags -x -R .``: Generate tag file content but print content to the stdout instead of file.

More

- ``-a``: append
- ``-h <list>``: header file(include file) file extension list
- ``-I <id_list>``: special id? e.g. C Macro

- ``-f/-o <tag_file>``: 
- ``-L <source_file>``: ? 

- ``-e``: etags mode (Emacs)
- ``-B/-F``: backward/forward
- ``-u``: unsorted
- ``-V``: verbose
- ``-n/-N``: ``--excmd=number/--excmd=pattern``

- ``--file-scope=<yes|no>``: single-file scope?
- ``--if0``: c #ifdef 0

- ``--excmd``, ``--format``

ctags tag file format
---------------------

- ``tag_name<TAB>file_name<TAB>ex_cmd;"<TAB>extension_field``
- excmd

  - search pattern: 不用 line number 去定位 symbol, 用 search pattern 找 symbol
  - line

related works
-------------

- tags(e.g. ctags) stored in the database instead of plain file.

  - https://github.com/xuhdev/tags2db
  - CodeLite: http://www.wikiwand.com/en/CodeLite

- clang-ctags

  1. use clang compiler to generate ctags/etags DB, only support C/C++.
  2. more accurate support C++ by real parser and preprocessor. Other ctags implementation is based on some heuristic methods.
  3. only support etags (Emacs) now
