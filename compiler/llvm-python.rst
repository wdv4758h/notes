========================================
LLVM & Python
========================================

llvmlite
========================================

每個版本的 llvmlite 都會綁定一個版本的 LLVM，
所以需要安裝對應版本的 LLVM 才能順利編譯。

LLVM 的 C++ API 變化很大，
並且持續在每版發生，
造成基於這之上的 Binding 都要不斷地追著新版的 C++ API 跑，
無法穩定。

於是一些 Numba 的開發者們決定開發 llvmlite 作為新的 Binding，
這些開發者大部份也是 llvmpy 的開發者，
因此 llvmlite 解決了 llvmpy 先前碰到的一些問題。

llvmlite 使用 C API，
C API 是設計給外部使用的比較穩定。
IR 部份 llvmlite 則採用純 Python 的 IR builder 來避免多次的 FFI calls
（原先 llvmpy 多次 FFI 的方式很慢），
IR 建完後再傳給 LLVM IR parser 處理，
而 LLVM IR 的文字表示是比較穩定的表示法。


安裝 llvmlite
------------------------------

**事先需確認系統已安裝對應的 LLVM 版本**

.. code-block:: sh

    git clone https://github.com/numba/llvmlite
    cd llvmlite
    python setup.py build
    python runtests.py
    python setup.py install


練習
------------------------------

Example 1
++++++++++++++++++++

.. code-block:: c

    int sum(int a, int b) {
        return a + b;
    }


.. code-block:: python

    from ctypes import CFUNCTYPE, c_int

    import llvmlite.ir as ll
    import llvmlite.binding as llvm


    ########################################
    # 說明
    ########################################

    # 以下將藉由 llvmlite 實作出這個簡單的 C Function：
    #
    #     int sum(int a, int b) {
    #         return a + b;
    #     }

    # 內容修改自
    # http://eli.thegreenplace.net/2015/building-and-using-llvmlite-a-basic-example


    ########################################
    # 建立 LLVM IR
    ########################################

    # 建立 Module 和 Function Prototype
    module = ll.Module()
    func_ty = ll.FunctionType(ll.IntType(32), [ll.IntType(32), ll.IntType(32)])
    func = ll.Function(module, func_ty, name='sum')

    func.args[0].name = 'a'
    func.args[1].name = 'b'


    # 實作 Function
    bb_entry = func.append_basic_block('entry')
    irbuilder = ll.IRBuilder(bb_entry)
    tmp = irbuilder.add(func.args[0], func.args[1])
    ret = irbuilder.ret(tmp)


    # 輸出產生的 LLVM IR
    print('=== LLVM IR')
    print(module)


    ########################################
    # LLVM IR 轉成 Binary
    ########################################

    # Code Generation 相關的初始化
    llvm.initialize()
    llvm.initialize_native_target()
    llvm.initialize_native_asmprinter()


    # 把 LLVM IR 從可讀的文字 (.ll) 轉換成 in-memory 的形式
    # （LLVM 對程式碼有三種等價的表示方式，
    # 分別為 in-memory、bitcode（.bc）、可讀的組語（.ll））
    llvm_module = llvm.parse_assembly(str(module))


    # 取得 Host 的相關資訊
    tm = llvm.Target.from_default_triple().create_target_machine()


    # 利用 MCJIT 把 module 編成 machine code
    # （需先利用 create_mcjit_compiler 建立 Execution Engine）
    with llvm.create_mcjit_compiler(llvm_module, tm) as ee:
        # 確保該 Execution Engine 所擁有的所有 module 都已經處理過，
        # 而且可以拿來執行
        ee.finalize_object()

        # 取得 JIT 後產生的 Function 的 Memory Address
        cfptr = ee.get_pointer_to_function(llvm_module.get_function('sum'))

        # 把 Memory Address 轉換成可以呼叫的 Python Function （利用 CFUNCTYPE）
        cfunc = CFUNCTYPE(c_int, c_int, c_int)(cfptr)

        # 輸出產生的組語
        print('=== Assembly')
        print(tm.emit_assembly(llvm_module))

        # 開始使用 JIT 產生的 Function
        res = cfunc(17, 42)
        print('The result is', res)


Reference
========================================

* `Building and using llvmlite - a basic example <http://eli.thegreenplace.net/2015/building-and-using-llvmlite-a-basic-example>`_
* `Calling back into Python from llvmlite-JITed code <http://eli.thegreenplace.net/2015/calling-back-into-python-from-llvmlite-jited-code/>`_
* `Writing Fibonacci in LLVM with llvmlite <https://ian-bertolacci.github.io/llvm/llvmlite/python/compilers/programming/2016/03/06/LLVMLite_fibonacci.html>`_
* `Pykaleidoscope <https://github.com/eliben/pykaleidoscope>`_
