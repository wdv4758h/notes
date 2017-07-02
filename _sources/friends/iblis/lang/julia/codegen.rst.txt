Code Generation
===============================================================================

.. highlight:: julia


::

    julia> λ(l) = l ^ 2
    λ (generic function with 1 method)

    julia> code_native(λ, (Float64,))
            .text
    Filename: REPL[3]
            pushq   %rbp
            movq    %rsp, %rbp
    Source line: 1
            vmulsd  %xmm0, %xmm0, %xmm0
            popq    %rbp
            retq
            nopw    (%rax,%rax)

    julia> code_native(λ, (Int,))
            .text
    Filename: REPL[3]
            pushq %rbp
            movq    %rsp, %rbp
    Source line: 1
            imulq   %rdi, %rdi
            movq    %rdi, %rax
            popq    %rbp
            retq
            nopl    (%rax)
