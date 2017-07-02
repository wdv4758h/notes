=============
Makefile 筆記
=============
Makefile 可以處理 Task 之間的 Dependency，讓編譯過程自動化

基本語法
--------
::

    RULE1 = gcc
    RULE2 = value1 value2 value3

    target: dependency
    >---command1
    >---command2 && command3
    >---command4 ;\
    >--->---command5

* 這裡 ``>---`` 表示一個 ``tab`` 字元，不能使用空格
* 在指令前加上 ``@`` 可以避免 make 把指令也輸出到畫面上
* ``command4`` 和 ``command5`` 透過 ``\`` 連接在一起，會被解讀成連續的一行

``make target`` 前會自動把所有 dependency 都 ``make`` 完成

變數
----
* Assign

  - ``=``

    + 把舊的值直接覆蓋

  - ``A += B``

    + 把 ``B`` 接在 ``A`` 上

  - ``A ?= B``

    + 若 ``A`` 未曾定義過，給予 ``B`` 做為變數值，否則不動作

  - ``A != B``

    + 把 ``B`` 做為指令執行， ``stdout`` 做為 ``A`` 的值
    + **[GNU make only]** GNU make 沒有這個 operator，改用 ``$(shell B)``

* 變數使用 ``${variable}`` 或 ``$(variable)`` 存取

  - 若用在 target，則 ``$(variable)`` 中的每個值 (以空白分隔) 都被視為 target
  - Dependency 亦同

* ``$@`` 代表目前的 target
* ``$<`` 代表第一個 dependency

* **[GNU make only]** ``%`` 為通用字元，類似 shell 的 ``*``

  - 用 ``$*`` 存取 match 的部份
  - 範例 ::

      .--------------------.
      | %:                 |
      | >---gcc -o $* $*.c |
      '--------------------'
      $ make test
      gcc -o test test.c

其他
----
* [2015/06/11] 如果 target 是 ``main.out`` ，dependency 最好是 ``main.o`` 而不要是 ``main.cpp``

  - 今日遭遇::

      target=main
      $(target).out: $(target).cpp msgpack.hpp
      >---clang++36 -std=c++14 -Wall -Wextra -pedantic -O2 $(target).cpp -○$(target).out

    + ``Makefile`` 裡面寫的明明是 ``clang++36`` ，下了 ``make`` 指令後卻執行了 ``c++ -O2 -pipe -c main.cpp`` ， ``-std=c++14`` flag 消失了
    + 推測是 FreeBSD ``make`` 自動去尋找系統內的 ``c++`` compiler 去編譯 ``main.cpp``
    + ``c++`` 和 ``clang++`` 是 link，但我需要的是 ``/usr/local/bin/clang++36`` 而不是 ``/usr/bin/clang++``
