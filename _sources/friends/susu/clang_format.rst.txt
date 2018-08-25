Formatter 可以自動幫程式改好 style format, 可惜沒辦法像 style checker 列出不合 format 的地方, 是不符合哪個 rule.

目前未知 solution
~~~~~~~~~~~~~~~~~

1. function definition 的 return type 會先換行, 才接 function name/parameter

     AlwaysBreakAfterReturnType 設定成 None 或 All 仍然都會換行

2. mozilla rr 裡面的 .clang-format, 有個設定找不到文件 (後來發現是版本差異, clang-format 3.4 有)

     IndentFunctionDeclarationAfterType 

     clang-format 3.4: http://llvm.org/releases/3.4/tools/clang/docs/ClangFormatStyleOptions.html

Command & Usage
~~~~~~~~~~~~~~~
::

    clang-format -style=[llvm|google|mozilla] -dump-config > .clang-format

    clang-format -style=file <c_source> # default style filename = .clang-format
    clang-format -style=file -assume-filename=<clang_format_style_file> <c_source> 

    # inplace modify
    clang-format -i -style=file <c_source>
    # modify and diff
    clang-format -style=file <c_source> > <c_source_format>
    diff <c_source> <c_source_format>
    # for commited git repo, we can use inplace modify and git diff
    clang-format -style=file *.c
    git diff [--stat]

reference
~~~~~~~~~
CLI: http://clang.llvm.org/docs/ClangFormat.html
Style Options: http://clang.llvm.org/docs/ClangFormatStyleOptions.html
