========================================
Rust Videos
========================================

以下為聽 Talks 時紀錄的內容，有些可能有加進自己去搜尋、嘗試後的結果

* `Felix Klock - Rust: A type system you didn't know you wanted - Curry On <https://www.youtube.com/watch?v=Q7lQCgnNWU0>`_
    - `Slide <http://pnkfelix.github.io/curry-on2015.html>`_
    - What ?
        + 新的 **systems** programming language
            * fast; FFI interface; data layout control
            * compete (and interface with) with C/C++
        + Mix in the classic hits of PL
            * user-defined iterators, RAII, objects with vtable method dispatch, generics / F-bounded polymorphism, algebraic data types, affine types, etc
        + Safety
            * Memory-safe, data-race free
            * Fearless concurrency
    - Abstraction without overhead
        .. code-block:: rust

            // Rust

            // sums all the positive values in `v`
            fn sum_pos(v: &Vec<i32>) -> i32 {
                let mut sum = 0;
                for i in v.iter().filter(|i| **i > 0) {
                    sum += *i;
                }
                sum
            }


            // much shorter version
            fn sum_pos(v: &Vec<i32>) -> i32 {
                v.iter().filter(|i| **i > 0).sum()
            }


        .. code-block:: asm

            # Generated x86_64 machine code for Rust's fn sum_pos:
            # rustc -C opt-level=3

            sum_pos::h890463990285d60deaa:
                # stack check can be cloesed by "-C no-stack-check"
                # +--- stack check ---+
                # v                   v
            	cmpq	%fs:112, %rsp
            	ja	.LBB0_2
            	movabsq	$8, %r10
            	movabsq	$0, %r11
            	callq	__morestack
            	retq
                # ^                   ^
                # +--- stack check ---+
            .LBB0_2:
            	pushq	%rbp
            	movq	%rsp, %rbp
            	movq	(%rdi), %rcx
            	movq	8(%rdi), %rax
            	leaq	(%rcx,%rax,4), %rdx
            	xorl	%eax, %eax
            	jmp	.LBB0_3
            .LBB0_5:
            	addl	%esi, %eax
            .LBB0_3:
            	cmpq	%rcx, %rdx
            	je	.LBB0_6
            	movl	(%rcx), %esi
            	addq	$4, %rcx
            	testl	%esi, %esi
            	jle	.LBB0_3
            	jmp	.LBB0_5
            .LBB0_6:
            	popq	%rbp
            	retq

        .. code-block:: cpp

            // C++

            # include <vector>

            int sum_pos(std::vector<int>& v) {
                int sum = 0;
                for (const auto& i : v) {
                    if (i > 0) {
                        sum += i;
                    }
                }
                return sum;
            }

        .. code-block:: asm

            # Generated x86_64 machine code for C++'s int sum_pos:
            # by clang 3.6
            # clang -O3 -std=c++14 -S sum_pos.cpp
            # cat sum_pos.s | c++filt

            sum_pos(std::vector<int, std::allocator<int> >&):
            	movq	(%rdi), %rdx
            	movq	8(%rdi), %rcx
            	xorl	%eax, %eax
            	cmpq	%rcx, %rdx
            	je	.LBB0_9
            # BB#1:                                 # %overflow.checked
            	leaq	-4(%rcx), %rdi
            	subq	%rdx, %rdi
            	shrq	$2, %rdi
            	incq	%rdi
            	xorl	%esi, %esi
            	movabsq	$9223372036854775800, %rax # imm = 0x7FFFFFFFFFFFFFF8
            	andq	%rdi, %rax
            	pxor	%xmm0, %xmm0
            	je	.LBB0_2
            # BB#3:                                 # %vector.body.preheader
            	leaq	(%rdx,%rax,4), %r8
            	addq	$16, %rdx
            	movq	%rdi, %rsi
            	andq	$-8, %rsi
            	pxor	%xmm2, %xmm2
            	pxor	%xmm0, %xmm0
            	pxor	%xmm1, %xmm1
            .LBB0_4:                                # %vector.body
                                                    # =>This Inner Loop Header: Depth=1
            	movdqa	%xmm1, %xmm3
            	movdqa	%xmm0, %xmm4
            	movdqu	-16(%rdx), %xmm5
            	movdqu	(%rdx), %xmm6
            	movdqa	%xmm5, %xmm0
            	pcmpgtd	%xmm2, %xmm0
            	movdqa	%xmm6, %xmm1
            	pcmpgtd	%xmm2, %xmm1
            	pand	%xmm5, %xmm0
            	pand	%xmm6, %xmm1
            	paddd	%xmm4, %xmm0
            	paddd	%xmm3, %xmm1
            	addq	$32, %rdx
            	addq	$-8, %rsi
            	jne	.LBB0_4
            # BB#5:
            	movq	%r8, %rdx
            	movq	%rax, %rsi
            	jmp	.LBB0_6
            .LBB0_2:
            	pxor	%xmm1, %xmm1
            .LBB0_6:                                # %middle.block
            	paddd	%xmm1, %xmm0
            	pshufd	$78, %xmm0, %xmm1       # xmm1 = xmm0[2,3,0,1]
            	paddd	%xmm0, %xmm1
            	pshufd	$-27, %xmm1, %xmm0      # xmm0 = xmm1[1,1,2,3]
            	paddd	%xmm1, %xmm0
            	movd	%xmm0, %eax
            	cmpq	%rsi, %rdi
            	je	.LBB0_9
            	xorl	%esi, %esi
            .LBB0_8:                                # %.lr.ph
                                                    # =>This Inner Loop Header: Depth=1
            	movl	(%rdx), %edi
            	testl	%edi, %edi
            	cmovsl	%esi, %edi
            	addl	%edi, %eax
            	addq	$4, %rdx
            	cmpq	%rdx, %rcx
            	jne	.LBB0_8
            .LBB0_9:                                # %._crit_edge
            	retq

    - Memory safety
        + 例如在利用 iterator 進行操作時，當中不可以更動到原本的 iterator，不然可能會出錯 (例如 realloc)，這種問題在會 Rust 變成 compile-time error
            * 例如在使用 vector.iter() 時，做了 vector.push(XXX)，這就會是錯誤的
    - Slick, Fearless Concurrency
    - Why ?
        + C/C++ impedes ability to compete in the browser market
        + Fast experimentation (and deployment)
    - Servo
        + written in Rust
        + parallel paint
        + parallel layout
        + parallel css selector matching
    - How ?
        + Ownership + Move Semantics (explicit resource control)
        + Borrowing (brings back reference semantics)
        + Lifetimes (encode safety constraints between references)
    - The Family of Types
        + T: base type. Moves, unless bounded by Copy trait
        + &T: shared ref, "read-only" access; copyable
            * programmer (+ compiler) must assumed aliased
            * (i.e. "many readers")
        + &mut T: "mutable" ref, exclusive access; non-copy
            * assured unaliased
            * (i.e. "at most one writer")
    - Method signatures
        + self: consumes receiver
        + &self: accesses receiver
        + &mut self: mutates receiver
    - "Smart" "Pointers"
        + Box<T>: unique reference to T on (malloc/free-style) heap
        + Rc<T>: shared ownership, thread-local
        + Arc<T>: shared ownership, safe across threads
        + (All of above deref to &T)
    - Interactive Compiler
        + `Compiler Explorer - Rust <http://rust.godbolt.org/>`_
        + `Compiler Explorer - C & C++ <http://gcc.godbolt.org/>`_
