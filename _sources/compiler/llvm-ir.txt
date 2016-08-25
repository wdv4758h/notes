========================================
LLVM IR
========================================


Introduction
========================================

概念
------------------------------

LLVM 對 code 的表示有三種，三種格式是等價的

* in-memory compiler IR
* on-disk bitcode representation (suitable for fast loading by a Just-In-Time compiler) (``.bc``)
* human readable assembly language representation (``.ll``)

::

    +--------------------+                  +---------------------+
    |                    |     llvm-dis     |                     |
    |                    | ---------------> |                     |
    | LLVM Bitcode (.bc) |                  | LLVM Assembly (.ll) |
    |                    | <--------------- |                     |
    |                    |     llvm-as      |                     |
    +--------------------+                  +---------------------+


----


簡單列表

* LLVM identifiers
    - global : ``@`` (functions, global variables)
    - local : ``%`` (register names, types)
* Comments
    - ``;`` (直到該行結束)
* Linkage Types
    - private
    - internal
    - available_externally
    - linkonce
    - weak
    - common
    - appending
    - extern_weak
    - linkonce_odr, weak_odr
    - external
* Calling Conventions


編譯參數
------------------------------

* ``-S -emit-llvm`` : 生出 LLVM IR (``FILENAME.ll``)


LLVM IR 範例
------------------------------

Hello World
++++++++++++++++++++

LLVM IR :

.. code-block:: llvm

    @.str = constant [12 x i8] c"Hello World\00"

    declare i32 @puts(i8*)

    define i32 @main() {
        %var = getelementptr [12 x i8], [12 x i8]* @.str, i64 0, i64 0
        call i32 @puts(i8* %var)
        ret i32 0
    }


User Input
++++++++++++++++++++

C :

.. code-block:: c

    #include <stdio.h>

    int main() {
        int value;
        scanf("%d", &value);
        printf("%d\n", value);
        return 0;
    }


LLVM IR :

.. code-block:: llvm

    @.str.0 = constant [3 x i8] c"%d\00"
    @.str.1 = constant [4 x i8] c"%d\0A\00"

    declare i32 @scanf(i8*, ...)
    declare i32 @printf(i8*, ...)

    define i32 @main() {
        %ptr = alloca i32       ; i32*:ptr
        call i32 (i8*, ...) @scanf(i8* getelementptr ([3 x i8], [3 x i8]* @.str.0, i32 0, i32 0),
                                   i32* %ptr)


        %value = load i32, i32* %ptr    ; i32:value = *ptr
        call i32 (i8*, ...) @printf(i8* getelementptr ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0),
                                    i32 %value)
        ret i32 0
    }


Fibonacci
++++++++++++++++++++




SSA (Static single assignment form)
========================================

* `Wikipedia - Static single assignment form <https://en.wikipedia.org/wiki/Static_single_assignment_form>`_
* [Book] `Static Single Assignment Book <http://ssabook.gforge.inria.fr/latest/book.pdf>`_



Φ (Phi) function
------------------------------

::

            +----------+
            | x1 < 3 ? |
            +----------+
               |    |
               |    |
         +-----+    +---+
         |              |
         |              |
         v              v
    +--------+      +--------+
    | x2 = 1 |      | x3 = 2 |
    +--------+      +--------+
         |              |
         |              |
         +-------+------+
                 |
                 v
         +----------------+
         | x4 = Φ(x2, x3) |
         +----------------+


* `LLVM: llvm::PHINode Class Reference <http://llvm.org/doxygen/classllvm_1_1PHINode.html>`_



LLVM IR Type
========================================

First Class Types
------------------------------

Single Value Types
++++++++++++++++++++

Vector Type
~~~~~~~~~~~

SIMD

Syntax ::

    < <# elements> x <elementtype> >

Example ::

    <8 x float>     ; Vector of 8 32-bit floating-point values.


LLVM IR Generated Example
========================================

Sanitizer
------------------------------

C :

.. code-block:: c

    #include <stdio.h>

    int main() {
        int a[4];
        printf("%d\n", a[4]);
        return 0;
    }


Build :

.. code-block:: sh

    $ clang -fsanitize=address -S -emit-llvm test.c


LLVM IR :

.. code-block:: llvm

    ; ModuleID = 'test.c'
    target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
    target triple = "x86_64-unknown-linux-gnu"

    @.str = internal unnamed_addr constant { [4 x i8], [60 x i8] } { [4 x i8] c"%d\0A\00", [60 x i8] zeroinitializer }, align 32
    @llvm.global_ctors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 1, void ()* @asan.module_ctor }]
    @__asan_option_detect_stack_use_after_return = external global i32
    @__asan_gen_ = private unnamed_addr constant [12 x i8] c"1 32 16 1 a\00", align 1
    @__asan_gen_.1 = private constant [7 x i8] c"test.c\00", align 1
    @__asan_gen_.2 = private unnamed_addr constant [17 x i8] c"<string literal>\00", align 1
    @__asan_gen_.3 = private unnamed_addr constant [7 x i8] c"test.c\00", align 1
    @__asan_gen_.4 = private unnamed_addr constant { [7 x i8]*, i32, i32 } { [7 x i8]* @__asan_gen_.3, i32 5, i32 12 }
    @0 = internal global [1 x { i64, i64, i64, i64, i64, i64, i64 }] [{ i64, i64, i64, i64, i64, i64, i64 } { i64 ptrtoint ({ [4 x i8], [60 x i8] }* @.str to i64), i64 4, i64 64, i64 ptrtoint ([17 x i8]* @__asan_gen_.2 to i64), i64 ptrtoint ([7 x i8]* @__asan_gen_.1 to i64), i64 0, i64 ptrtoint ({ [7 x i8]*, i32, i32 }* @__asan_gen_.4 to i64) }]
    @llvm.global_dtors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 1, void ()* @asan.module_dtor }]

    ; Function Attrs: nounwind sanitize_address uwtable
    define i32 @main(i32 %argc, i8** %argv) #0 {
    %1 = alloca i32, align 4
    %2 = alloca i32, align 4
    %3 = alloca i8**, align 8
    %4 = load i32, i32* @__asan_option_detect_stack_use_after_return
    %5 = icmp ne i32 %4, 0
    br i1 %5, label %6, label %8

    ; <label>:6                                       ; preds = %0
    %7 = call i64 @__asan_stack_malloc_0(i64 64)
    br label %8

    ; <label>:8                                       ; preds = %0, %6
    %9 = phi i64 [ 0, %0 ], [ %7, %6 ]
    %10 = icmp eq i64 %9, 0
    br i1 %10, label %11, label %13

    ; <label>:11                                      ; preds = %8
    %MyAlloca = alloca i8, i64 64, align 32
    %12 = ptrtoint i8* %MyAlloca to i64
    br label %13

    ; <label>:13                                      ; preds = %8, %11
    %14 = phi i64 [ %9, %8 ], [ %12, %11 ]
    %15 = add i64 %14, 32
    %16 = inttoptr i64 %15 to [4 x i32]*
    %17 = inttoptr i64 %14 to i64*
    store i64 1102416563, i64* %17
    %18 = add i64 %14, 8
    %19 = inttoptr i64 %18 to i64*
    store i64 ptrtoint ([12 x i8]* @__asan_gen_ to i64), i64* %19
    %20 = add i64 %14, 16
    %21 = inttoptr i64 %20 to i64*
    store i64 ptrtoint (i32 (i32, i8**)* @main to i64), i64* %21
    %22 = lshr i64 %14, 3
    %23 = add i64 %22, 2147450880
    %24 = add i64 %23, 0
    %25 = inttoptr i64 %24 to i64*
    store i64 -868350299093208591, i64* %25
    store i32 0, i32* %1
    store i32 %argc, i32* %2, align 4
    store i8** %argv, i8*** %3, align 8
    %26 = getelementptr inbounds [4 x i32], [4 x i32]* %16, i32 0, i64 4
    %27 = ptrtoint i32* %26 to i64
    %28 = lshr i64 %27, 3
    %29 = add i64 %28, 2147450880
    %30 = inttoptr i64 %29 to i8*
    %31 = load i8, i8* %30
    %32 = icmp ne i8 %31, 0
    br i1 %32, label %33, label %39, !prof !3

    ; <label>:33                                      ; preds = %13
    %34 = and i64 %27, 7
    %35 = add i64 %34, 3
    %36 = trunc i64 %35 to i8
    %37 = icmp sge i8 %36, %31
    br i1 %37, label %38, label %39

    ; <label>:38                                      ; preds = %33
    call void @__asan_report_load4(i64 %27)
    call void asm sideeffect "", ""()
    unreachable

    ; <label>:39                                      ; preds = %33, %13
    %40 = load i32, i32* %26, align 4
    %41 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ({ [4 x i8], [60 x i8] }, { [4 x i8], [60 x i8] }* @.str, i32 0, i32 0, i32 0), i32 %40)
    store i64 1172321806, i64* %17
    %42 = icmp ne i64 %9, 0
    br i1 %42, label %43, label %50

    ; <label>:43                                      ; preds = %39
    %44 = add i64 %23, 0
    %45 = inttoptr i64 %44 to i64*
    store i64 -723401728380766731, i64* %45
    %46 = add i64 %9, 56
    %47 = inttoptr i64 %46 to i64*
    %48 = load i64, i64* %47
    %49 = inttoptr i64 %48 to i8*
    store i8 0, i8* %49
    br label %53

    ; <label>:50                                      ; preds = %39
    %51 = add i64 %23, 0
    %52 = inttoptr i64 %51 to i64*
    store i64 0, i64* %52
    br label %53

    ; <label>:53                                      ; preds = %50, %43
    ret i32 0
    }

    declare i32 @printf(i8*, ...) #1

    define internal void @asan.module_ctor() {
    call void @__asan_init_v5()
    call void @__asan_register_globals(i64 ptrtoint ([1 x { i64, i64, i64, i64, i64, i64, i64 }]* @0 to i64), i64 1)
    ret void
    }

    declare void @__asan_init_v5()

    declare void @__asan_report_load_n(i64, i64)

    declare void @__asan_loadN(i64, i64)

    declare void @__asan_report_load1(i64)

    declare void @__asan_load1(i64)

    declare void @__asan_report_load2(i64)

    declare void @__asan_load2(i64)

    declare void @__asan_report_load4(i64)

    declare void @__asan_load4(i64)

    declare void @__asan_report_load8(i64)

    declare void @__asan_load8(i64)

    declare void @__asan_report_load16(i64)

    declare void @__asan_load16(i64)

    declare void @__asan_report_store_n(i64, i64)

    declare void @__asan_storeN(i64, i64)

    declare void @__asan_report_store1(i64)

    declare void @__asan_store1(i64)

    declare void @__asan_report_store2(i64)

    declare void @__asan_store2(i64)

    declare void @__asan_report_store4(i64)

    declare void @__asan_store4(i64)

    declare void @__asan_report_store8(i64)

    declare void @__asan_store8(i64)

    declare void @__asan_report_store16(i64)

    declare void @__asan_store16(i64)

    declare void @__asan_report_exp_load_n(i64, i64, i32)

    declare void @__asan_exp_loadN(i64, i64, i32)

    declare void @__asan_report_exp_load1(i64, i32)

    declare void @__asan_exp_load1(i64, i32)

    declare void @__asan_report_exp_load2(i64, i32)

    declare void @__asan_exp_load2(i64, i32)

    declare void @__asan_report_exp_load4(i64, i32)

    declare void @__asan_exp_load4(i64, i32)

    declare void @__asan_report_exp_load8(i64, i32)

    declare void @__asan_exp_load8(i64, i32)

    declare void @__asan_report_exp_load16(i64, i32)

    declare void @__asan_exp_load16(i64, i32)

    declare void @__asan_report_exp_store_n(i64, i64, i32)

    declare void @__asan_exp_storeN(i64, i64, i32)

    declare void @__asan_report_exp_store1(i64, i32)

    declare void @__asan_exp_store1(i64, i32)

    declare void @__asan_report_exp_store2(i64, i32)

    declare void @__asan_exp_store2(i64, i32)

    declare void @__asan_report_exp_store4(i64, i32)

    declare void @__asan_exp_store4(i64, i32)

    declare void @__asan_report_exp_store8(i64, i32)

    declare void @__asan_exp_store8(i64, i32)

    declare void @__asan_report_exp_store16(i64, i32)

    declare void @__asan_exp_store16(i64, i32)

    declare i8* @__asan_memmove(i8*, i8*, i64)

    declare i8* @__asan_memcpy(i8*, i8*, i64)

    declare i8* @__asan_memset(i8*, i32, i64)

    declare void @__asan_handle_no_return()

    declare void @__sanitizer_ptr_cmp(i64, i64)

    declare void @__sanitizer_ptr_sub(i64, i64)

    declare i64 @__asan_stack_malloc_0(i64)

    declare void @__asan_stack_free_0(i64, i64)

    declare i64 @__asan_stack_malloc_1(i64)

    declare void @__asan_stack_free_1(i64, i64)

    declare i64 @__asan_stack_malloc_2(i64)

    declare void @__asan_stack_free_2(i64, i64)

    declare i64 @__asan_stack_malloc_3(i64)

    declare void @__asan_stack_free_3(i64, i64)

    declare i64 @__asan_stack_malloc_4(i64)

    declare void @__asan_stack_free_4(i64, i64)

    declare i64 @__asan_stack_malloc_5(i64)

    declare void @__asan_stack_free_5(i64, i64)

    declare i64 @__asan_stack_malloc_6(i64)

    declare void @__asan_stack_free_6(i64, i64)

    declare i64 @__asan_stack_malloc_7(i64)

    declare void @__asan_stack_free_7(i64, i64)

    declare i64 @__asan_stack_malloc_8(i64)

    declare void @__asan_stack_free_8(i64, i64)

    declare i64 @__asan_stack_malloc_9(i64)

    declare void @__asan_stack_free_9(i64, i64)

    declare i64 @__asan_stack_malloc_10(i64)

    declare void @__asan_stack_free_10(i64, i64)

    declare void @__asan_poison_stack_memory(i64, i64)

    declare void @__asan_unpoison_stack_memory(i64, i64)

    declare void @__asan_alloca_poison(i64, i64)

    declare void @__asan_allocas_unpoison(i64, i64)

    declare void @__asan_before_dynamic_init(i64)

    declare void @__asan_after_dynamic_init()

    declare void @__asan_register_globals(i64, i64)

    declare void @__asan_unregister_globals(i64, i64)

    define internal void @asan.module_dtor() {
    call void @__asan_unregister_globals(i64 ptrtoint ([1 x { i64, i64, i64, i64, i64, i64, i64 }]* @0 to i64), i64 1)
    ret void
    }

    attributes #0 = { nounwind sanitize_address uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
    attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

    !llvm.asan.globals = !{!0}
    !llvm.ident = !{!2}

    !0 = !{[4 x i8]* getelementptr inbounds ({ [4 x i8], [60 x i8] }, { [4 x i8], [60 x i8] }* @.str, i32 0, i32 0), !1, !"<string literal>", i1 false, i1 false}
    !1 = !{!"test.c", i32 5, i32 12}
    !2 = !{!"clang version 3.7.0 (tags/RELEASE_370/final)"}
    !3 = !{!"branch_weights", i32 1, i32 100000}


Reference
========================================

* `LLVM Language Reference Manual <http://llvm.org/docs/LangRef.html>`_
* `Implementing a JIT Compiled Language with Haskell and LLVM <http://www.stephendiehl.com/llvm/>`_
* `The Architecture of Open Source Applications: LLVM <http://www.aosabook.org/en/llvm.html>`_
