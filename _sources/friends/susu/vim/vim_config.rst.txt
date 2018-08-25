::

    ~/.vimrc
    ~/.vim/filetype.vim
    ~/.vim/ftplugin/
    ~/.vim/syntax/

    # Vundle
    # if vimrc setting
    #    call vundle#begin('~/.vim/bundle/')
    # then all plugin install at
    ~/.vim/bundle/$plugin_name/

    # and Vundle set runtimepath='~/.vim/bundle/$plugin_name/'
    # load plugin script at
    ~/.vim/bundle/$plugin_name/**/*.vim


filetype.vim
------------

- file location

    - User-specific primary definitions: 
        - [Unix] ``$HOME/.vim/filetype.vim`` 
        - [Windows] ``$HOME\vimfiles\filetype.vim``
    - System primary definitions
        - ``$VIM/vimfiles/filetype.vim``
    - Vim default ruleset: 
        - ``$VIMRUNTIME/filetype.vim``
    - System fallback definitions:
        - ``$VIM/vimfiles/after/filetype.vim``
    - User-specific fallback definitions: 
        - [Unix] ``$HOME/.vim/after/filetype.vim``
        - [Windows] ``$HOME\vimfiles\after\filetype.vim``

    thus, important environment variable

        - $HOME
        - $VIM
        - $VIMRUNTIME

manual in vim terminal
----------------------
command mode::
    
    " help manual for keyword
    help <keyword>
    " open help in tab instead of split
    tab h <keyword>
    " open user manual index, usr_01.txt manual
    tab h user
    tab h usr_01


vim variables scoping
---------------------
- buffer, window, tabpage (b: w: t:)

  - tabpage: collection of windows

- global (g:)
- script (s:) (``:source``)
- function argument, and local variables(function) (a: l:)
- vim variables: predefined by vim, global. (v:)

- examples

  - ``g:UltiSnipsExpandTrigger="<tab>"``: plugin public setting
  - ``b:current_syntax``: current syntax/ft 
  - ``s:initVariable`` in NERDTree
