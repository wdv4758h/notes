========================================
GPGPU
========================================

nvcc
========================================

gpucc
========================================

Usage :

.. code-block:: sh

    $ clang++ -Wall -Wextra -O3 --cuda-path=/opt/cuda -I/opt/cuda/samples/common/inc -L/opt/cuda/lib64 -lcudart test.cu -o test.out



Open Source GPGPU compiler built on top of LLVM

* Straight-line scalar optimizations
    - Addressing Mode (base + imm)
    - Injured Redundancy
    - Pointer Arithmetic Reassociation
    - Straight-Line Strength Reduction
    - Global Reassociation
* Inferring memory spaces
    - load/store PTX
        + .reg : registers
        + .sreg : special, read-only, platform-specific registers
        + .const : shared, read-only memory
        + .global : global memory, shared by all threads
        + .local : local memory, private to each thread
        + .param : parameters passed to the kernel
        + .shared : memory shared between threads in a block
        + .tex : global texture memory (deprecated)
    - Memory space qualifiers
    - Fixed-point data-flow analysis
* Loop unrolling and function inlining
    - Higher threshold
    - ``#pragma unroll``
    - ``__forceinline_``
* Memory-space alias analysis
* Speculative execution
* Bypassing 64-bit divisions



Reference
========================================

* `Arch Wiki - GPGPU <https://wiki.archlinux.org/index.php/GPGPU>`_
* `gpucc: An Open-Source GPGPU Compiler <http://llvm.org/devmtg/2015-10/slides/Wu-OptimizingLLVMforGPGPU.pdf>`_
* `Compiling CUDA C/C++ with LLVM <http://llvm.org/docs/CompileCudaWithLLVM.html>`_
* `[2015] LLVM Developers' Meeting: Jingyue Wu 「Optimizing LLVM for GPGPU」 <https://www.youtube.com/watch?v=JHfb8z-iSYk>`_
* LLVM - gpucc
    - `r253389 <http://reviews.llvm.org/rL253389>`_ - Clang should now be usable for CUDA compilation out of the box.
    - `r252660 <http://reviews.llvm.org/rL252660>`_ - [Doc] Compile CUDA with LLVM
* `Wikipedia - Parallel Thread Execution <https://en.wikipedia.org/wiki/Parallel_Thread_Execution>`_
    - pseudo-assembly language used in Nvidia's CUDA
    - CUDA -> PTX (translate bye nvcc) -> Binary (compile by graphics driver)
    - `Memory Space Inference for NVPTX Backend <https://docs.google.com/document/d/199HVFMbv1KKyB2dwXmd7bYMPT6RjQu88hekmulLpPZA/>`_
