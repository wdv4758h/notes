ref: http://www.sbf5.com/~cduan/technical/vi/vi-2.shtml

- Text Processing Commands

  - ``: [ range ] command [ args ... ]``
  - range

    - single line: ``1``, ``100``
    - range: ``3,100``, ``4,$`` (to end), ``+2,$-3`` (current+2 ~ end-3)
    - special: ``%`` (all), ``.`` (current)

  - command

    - ``p`` for print
    - ``s`` for substitude, like sed
    - ``d`` for delete

  - more complex command

    - ``g``: global action: more advance in above command(``p``, ``d``)
    - ``!``: All purpose filter: Unix shell command

usage & example::

    # print 1 ~ 3 line
    :1,3p
    # delete 2 ~ 8 line
    :2,8d
    
    # substitude => :[range]s/pattern/replacement[/flags...]
    # hello => world in all file
    :%s/hello/world/

    # global action => :[range]g/pattern/command
    # use like grep
    :%g/re/p
    # grep and delete
    :%g/re/d

    # All-Purpose Filter => :range!command
    :.! ls
    :%! grep "a"
    :3,8! sort

    :r ! ls
    # sudo trick
    :w ! sudo tee %
    :w ! sudo tee filename
    :%! sudo tee filename
