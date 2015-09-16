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
