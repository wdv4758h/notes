========================================
Vimscript
========================================


.. contents:: 目錄


簡單範例
========================================

+-------------------------------------+-------------------------------------------+
| Vimscript                           | Python                                    |
+=====================================+===========================================+
| .. code-block:: vim                 | .. code-block:: python                    |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|     " String                        |      # String                             |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|     len(str)                        |      len(str)                             |
|     strlen(str)                     |                                           |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|     split("a b c")                  |      "a b c".split()                      |
|     split("a.b.c", '.')             |      "a.b.c".split('.')                   |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|     join(['a', 'b'], ',')           |      ','.join(['a', 'b'])                 |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|     tolower('Hello')                |      'Hello'.lower()                      |
|     toupper('Hello')                |      'Hello'.upper()                      |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|     " case-sensitive                |      # case-sensitive                     |
|     data ==# 'Hello'                |      data == 'Hello'                      |
|                                     |                                           |
|     " case-insensitive              |      # case-insensitive                   |
|     data ==? 'Hello'                |      data.lower() == 'Hello'.lower()      |
|                                     |                                           |
|     " depends on :set ignorecase    |                                           |
|     data == 'Hello'                 |                                           |
|                                     |                                           |
|     """"""""""                      |      ##########                           |
|                                     |                                           |
|                                     |                                           |
|                                     |                                           |
+-------------------------------------+-------------------------------------------+



Tools
========================================

* [GitHub] `vimdoc - Helpfile generation for vim <https://github.com/google/vimdoc>`_
    - 為 Vimscript 提供 docstring
* [GitHub] `Vroom - Launch vim tests <https://github.com/google/vroom>`_
    - 為 Vimscript 提供 testing 的方式



參考
========================================

* `A Simpler Vim Statusline <http://www.blaenkdenum.com/posts/a-simpler-vim-statusline/>`_
* `A Good Vimrc <http://dougblack.io/words/a-good-vimrc.html>`_
* `Vim script cheatsheet <http://ricostacruz.com/cheatsheets/vimscript.html>`_
* `Learn Vimscript the Hard Way <http://learnvimscriptthehardway.stevelosh.com/>`_
