Vim In-build Completion
-----------------------

- <C-P> / <C-N>: keyword completion

- <C-X> prefix completions

  - <C-X> + key
  - 可參考這篇介紹: http://www.openfoundry.org/en/tech-column/2215

- <C-X> prefix completions (key)

  - <C-o>: call omnifunc
  - <C-u>: call completefunc
  - <C-]>: tag file

  - <C-l>: line completion
  - <C-i>: keyword completion (also search include file)
  - <C-n>: keyword completion (single file)

  - <C-d>: definition and macro
  - <C-f>: filename
  - <C-k>: dictionary file
  - <C-t>: Thesaurus completion, like dictionary.

  - <C-v>: vim command
  - <C-e>: ?
  - <C-p>: ?
  - <C-y>: ?

Async Completion Support
------------------------

- deoplete plugin

  - need neovim or vim8
  - ...

C/C++ Completions
-----------------

對於 C/C++ 語言的補完, 後端產生 symbol 跟程式碼位置的工具,
主要為兩個小工具 ctags 跟 cscope, 以及真正的編譯器 clang.

關於 cscope 跟 ctags 的使用筆記, 可以參考 `cscope <./cscope.rst>`_ 跟 `ctags <./ctags>`_

其他部份則補充在這.

- OmniCppComplete (project)

  - a cpp completion engine using Vim Omni completion.
  - This project has 2 backends.

    1. ctags
    2. ClangComplete

Other completion solution without vim
-------------------------------------

- synth (project)

  - C/C++ Semantic syntax highlighting and hyperlinking with libclang.
  - https://github.com/oberon00/synth
  - demo: http://oberon00.github.io/synth
  - Syntax highlighting + Go to definition
  - Code completion?
