generate tag file ``tags`` at local directory.

- ``ctags --list-languages``, ``ctags --list-kinds``: check ctags support languages/features
- ``ctags -R .``: gen tag file for current directory source (`e.g. ./**/*.c, ./**/*.cpp ...``)
- ``ctags -x -R .``: print to stdout

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

tag format

- ``tag_name<TAB>file_name<TAB>ex_cmd;"<TAB>extension_field``
- excmd

  - search pattern: 不用 line number 去定位 symbol, 用 search pattern 找 symbol
  - line

related works
-------------
clang-ctags

1. use clang compiler to generate ctags/etags DB, only support C/C++.
2. more accurate support C++ by real parser and preprocessor. Other ctags implementation is based on some heuristic methods.
3. only support etags (Emacs) now
