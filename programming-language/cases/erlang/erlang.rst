========================================
Erlang
========================================


初步聽了 Erlang 的介紹，
感覺受 Prolog 影響很深 (當初的實作據說就是 Prolog 寫的)。
變數需要大寫，
小寫的都是 atom，
atom 會直接放到 atom table (太大會爆掉)，
常用 pattern matching，
另外有 Erlang 的 if 是 Guard (需要包含所有可能，不然就是最後寫 true 的 condition)。

沒有變數，
只能 initialize 新 constant，
不能 assign，
所以沒有 data race 問題，
mutiprocesses 下是用 actor model 和 message passing 溝通。

目前常用的實作為 BEAM，
Erlang 可以編成 BEAM bytecode 再丟到 VM 上執行，
BEAM 包含 copying generational GC。


.. contents:: 目錄


安裝
========================================

Arch Linux 上有兩個版本可以裝，
一個是 ``erlang`` 一個是 ``erlang-nox`` ，
其中的 ``erlang-nox`` 被標為 ``headless`` ，
裡面少了 ``erlang/lib/wx-1.5/priv/`` 內的東西，
但是其他部份的 wx 程式碼依然存在。


.. code-block:: sh

    $ sudo pacman -S erlang-nox


安裝完後會得到 ``erl`` 指令可以打開直譯器


基本練習
========================================

Erlang 的程式碼是用 ``.erl`` 作為副檔名。


Hello World
------------------------------

hello.erl:

.. code-block:: erlang

    -module(hello).
    -export([hello_world/0]).

    hello_world() -> io:fwrite("hello, world\n").


.. code-block:: sh

    $ erl
    Erlang/OTP 19 [erts-8.2] [source] [64-bit] [smp:8:8] [async-threads:10] [hipe] [kernel-poll:false]

    Eshell V8.2  (abort with ^G)
    1> c(hello).                % 編譯，產生 hello.beam
    {ok,hello}
    2> hello:hello_world().     % 呼叫，只有一個冒號
    hello, world
    ok
    3>


不開 Interactive Shell（REPL）：

.. code-block:: sh

    $ erl -compile hello.erl    # 編譯，產生 hello.beam
    $ erl -noshell -s hello hello_world -s init stop    # 執行



Fibonacci
------------------------------

這次以 escript 的形式讀 stdin 來計算 Fibonacci 後輸出到 stdout。

.. code-block:: erlang

    #!/usr/bin/env escript

    fib(0) -> 0;
    fib(1) -> 1;
    fib(N) when N > 0 -> fib(N-1) + fib(N-2).

    main(_) ->
        %% reads the number
        {ok, [N]} = io:fread("fib> ", "~d"),
        %% call fib
        io:fwrite("result: ~B~n", [fib(N)]).


.. code-block:: sh

    $ chmod +x fib.erl
    $ ./fib.erl
    fib> 10
    result: 55


增加讀入 CLI 參數的能力：

.. code-block:: erlang

    #!/usr/bin/env escript

    fib(0) -> 0;
    fib(1) -> 1;
    fib(N) when N > 0 -> fib(N-1) + fib(N-2).

    main([String]) ->
        %% convert string to number
        N = list_to_integer(String),
        %% call fib
        io:fwrite("result: ~B~n", [fib(N)]);

    main(_) ->
        %% reads the number
        {ok, [N]} = io:fread("fib> ", "~d"),
        %% call fib
        io:fwrite("result: ~B~n", [fib(N)]).


.. code-block:: sh

    $ ./fib.erl 10
    result: 55


增加清理參數的能力，
並在輸入字串不能正常轉成整數時顯示使用說明：

.. code-block:: erlang

    #!/usr/bin/env escript
    %% -*- erlang -*-
    %%! -smp enable -sname fib -mnesia debug verbose

    fib(0) -> 0;
    fib(1) -> 1;
    fib(N) when N > 0 -> fib(N-1) + fib(N-2).

    % from CLI argument
    main([String]) ->
        try
            %% clean spaces and newlines
            S = re:replace(String, "(^\\s+)|(\\s+$)", "", [global,{return,list}]),
            %% convert string to number
            N = list_to_integer(string:strip(S)),
            %% call fib
            io:fwrite("result: ~B~n", [fib(N)])
        catch
            _:_ ->
                usage()
        end;

    % from custom prompt
    main(_) ->
        %% reads the number
        String = io:get_line("fib> "),
        main([String]).

    usage() ->
        io:format("usage: fibonacci integer\n"),
        halt(1).



escript - Erlang Scripting
========================================

* `escript <http://erlang.org/doc/man/escript.html>`_





專案輔助工具
========================================

Rebar3
----------------------------------------

* `Rebar3 <https://www.rebar3.org/>`_
* [GitHub] `erlang/rebar3 <https://github.com/erlang/rebar3>`_
* `Rebar3 documentaion <https://www.rebar3.org/docs/commands>`_
* `Hex <https://hex.pm/>`_

安裝：

.. code-block:: sh

    $ wget https://s3.amazonaws.com/rebar3/rebar3
    $ chmod +x rebar3


建立專案：

.. code-block:: sh

    $ rebar3 new
    app (built-in): Complete OTP Application structure.
    cmake (built-in): Standalone Makefile for building C/C++ in c_src
    escript (built-in): Complete escriptized application structure
    lib (built-in): Complete OTP Library application (no processes) structure
    plugin (built-in): Rebar3 plugin project structure
    release (built-in): OTP Release structure for executable programs

    $ rebar3 new release myrelease
    ===> Writing myrelease/apps/myrelease/src/myrelease_app.erl
    ===> Writing myrelease/apps/myrelease/src/myrelease_sup.erl
    ===> Writing myrelease/apps/myrelease/src/myrelease.app.src
    ===> Writing myrelease/rebar.config
    ===> Writing myrelease/config/sys.config
    ===> Writing myrelease/config/vm.args
    ===> Writing myrelease/.gitignore
    ===> Writing myrelease/LICENSE
    ===> Writing myrelease/README.md

    $ tree myrelease/
    myrelease/
    ├── apps
    │   └── myrelease
    │       └── src
    │           ├── myrelease_app.erl
    │           ├── myrelease.app.src
    │           └── myrelease_sup.erl
    ├── config
    │   ├── sys.config
    │   └── vm.args
    ├── LICENSE
    ├── README.md
    └── rebar.config

    4 directories, 8 files

    $ cd myrelease
    $ rebar3 compile
    ===> Verifying dependencies...
    ===> Compiling myrelease

    $ tree _build/
    _build/
    └── default
        └── lib
            └── myrelease
                ├── ebin
                │   ├── myrelease.app
                │   ├── myrelease_app.beam
                │   └── myrelease_sup.beam
                ├── include -> ../../../../apps/myrelease/include
                ├── priv -> ../../../../apps/myrelease/priv
                └── src -> ../../../../apps/myrelease/src

    5 directories, 5 files

    $ rebar3 release
    ===> Verifying dependencies...
    ===> Compiling myrelease
    ===> Starting relx build process ...
    ===> Resolving OTP Applications from directories:
              /tmp/myrelease/_build/default/lib
              /tmp/myrelease/apps
              /usr/lib/erlang/lib
    ===> Resolved myrelease-0.1.0
    ===> Dev mode enabled, release will be symlinked
    ===> release successfully created!

    $ tree _build/default/rel/
    _build/default/rel/
    └── myrelease
        ├── bin
        │   ├── install_upgrade.escript
        │   ├── myrelease
        │   ├── myrelease-0.1.0
        │   ├── nodetool
        │   └── start_clean.boot
        ├── lib
        │   └── myrelease-0.1.0 -> /tmp/myrelease/_build/default/lib/myrelease
        └── releases
            ├── 0.1.0
            │   ├── myrelease.boot
            │   ├── myrelease.rel
            │   ├── myrelease.script
            │   ├── start_clean.boot
            │   ├── sys.config -> /tmp/myrelease/config/sys.config
            │   └── vm.args -> /tmp/myrelease/config/vm.args
            ├── RELEASES
            └── start_erl.data

    6 directories, 13 files

    # 打包
    $ rebar3 as prod tar
    ===> Verifying dependencies...
    ===> Compiling myrelease
    ===> Starting relx build process ...
    ===> Resolving OTP Applications from directories:
              /tmp/myrelease/_build/prod/lib
              /tmp/myrelease/apps
              /usr/lib/erlang/lib
    ===> Resolved myrelease-0.1.0
    ===> Including Erts from /usr/lib/erlang
    ===> release successfully created!
    ===> Starting relx build process ...
    ===> Resolving OTP Applications from directories:
              /tmp/myrelease/_build/prod/lib
              /tmp/myrelease/apps
              /usr/lib/erlang/lib
              /tmp/myrelease/_build/prod/rel
    ===> Resolved myrelease-0.1.0
    ===> tarball /tmp/myrelease/_build/prod/rel/myrelease/myrelease-0.1.0.tar.gz successfully created!


    $ rebar3 shell
    ===> Verifying dependencies...
    ===> Compiling myrelease
    Erlang/OTP 19 [erts-8.2] [source] [64-bit] [smp:8:8] [async-threads:0] [hipe] [kernel-poll:false]

    Eshell V8.2  (abort with ^G)
    1> ===> The rebar3 shell is a development tool; to deploy applications in production, consider using releases (
    http://www.rebar3.org/docs/releases)

    =PROGRESS REPORT==== 5-Feb-2017::16:17:27 ===
              supervisor: {local,sasl_safe_sup}
                 started: [{pid,<0.107.0>},
                           {id,alarm_handler},
                           {mfargs,{alarm_handler,start_link,[]}},
                           {restart_type,permanent},
                           {shutdown,2000},
                           {child_type,worker}]
    ===> Booted myrelease

    =PROGRESS REPORT==== 5-Feb-2017::16:17:27 ===
              supervisor: {local,sasl_sup}
                 started: [{pid,<0.106.0>},
                           {id,sasl_safe_sup},
                           {mfargs,
                               {supervisor,start_link,
                                   [{local,sasl_safe_sup},sasl,safe]}},
                           {restart_type,permanent},
                           {shutdown,infinity},
                           {child_type,supervisor}]
    ===> Booted sasl

    =PROGRESS REPORT==== 5-Feb-2017::16:17:27 ===
              supervisor: {local,sasl_sup}
                 started: [{pid,<0.108.0>},
                           {id,release_handler},
                           {mfargs,{release_handler,start_link,[]}},
                           {restart_type,permanent},
                           {shutdown,2000},
                           {child_type,worker}]

    =PROGRESS REPORT==== 5-Feb-2017::16:17:27 ===
             application: sasl
              started_at: nonode@nohost

    1>



Hex - BEAM VM 生態圈的套件平台
========================================

Hex 是 Erlang 的 BEAM VM 的套件管理工具及平台，
可以共享於 Erlang 和 Elixir 之間，
也有 Erlang Rebar3 的 Plugin 可以使用。


``~/.config/rebar3/rebar.config`` :

.. code-block:: erlang

    {plugins, [rebar3_hex]}.



OTP
========================================


Erlang 與其他程式語言
========================================

ErlPort
------------------------------

:URL: https://github.com/hdima/erlport


py - Distributed Python for the Erlang Ecosystem
------------------------------------------------

:URL: https://github.com/lfex/py



NIF (Natively Implemented Function)
========================================

a shorthand for replacing Erlang code with C


DS (Dirty Scheduler)
========================================


Garbage Collection
========================================

* `Erlang Garbage Collection Details and Why It Matters <https://hamidreza-s.github.io/erlang%20garbage%20collection%20memory%20layout%20soft%20realtime/2015/08/24/erlang-garbage-collection-details-and-why-it-matters.html>`_


書籍
========================================

* `Learn You Some Erlang for Great Good! <http://learnyousomeerlang.com/>`_



Reference
========================================

* `Wikipedia - Erlang (programming language) <https://en.wikipedia.org/wiki/Erlang_%28programming_language%29>`_
* `Wikipedia - Guard (computer science) <https://en.wikipedia.org/wiki/Guard_%28computer_science%29>`_
* `Learn You Some Erlang for Great Good! <http://learnyousomeerlang.com/>`_
* `[2011] ErLLVM: An LLVM back-end for HiPE, the native code compiler of Erlang/OTP Design and Implementation <http://erllvm.softlab.ntua.gr/files/erllvm_pres-20111107.pdf>`_
* `[2012] ErLLVM: An LLVM Backend for Erlang <http://erllvm.softlab.ntua.gr/files/erlang03-sagonas.pdf>`_
    - ErLLVM 是 HiPE 把 backend 換成 LLVM 的版本
* `[2012][Slide] ErLLVM: An LLVM Backend for Erlang <http://erllvm.softlab.ntua.gr/files/ErLLVM.pdf>`_
* `[2012] Hitchhiker's Tour of the BEAM <http://www.erlang-factory.com/upload/presentations/708/HitchhikersTouroftheBEAM.pdf>`_
* `[2014] BEAMJIT: An LLVM based just-in-time compiler for Erlang <http://llvm.org/devmtg/2014-04/PDFs/Talks/drejhammar.pdf>`_
* `[2015] A Tracing JIT Compiler for Erlang using LLVM <http://lup.lub.lu.se/luur/download?func=downloadFile&recordOId=5470892&fileOId=5470933>`_
* `Erlang Dirty Scheduler Overhead - Using DTrace to figure out what calls cost <https://medium.com/@jlouis666/erlang-dirty-scheduler-overhead-6e1219dcc7>`_
