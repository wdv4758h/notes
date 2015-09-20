========================================
LLVM - compiler-rt
========================================

.. contents:: Table of Contents

* instrument SQLite

* ``grep 'FIXME' -r llvm/``
    - Python 3 (and LLDB)

Clang on x86_64 -> Clang on x86_64 with ASAN lib for ARM -> Zygote with ASAN for Android/ARM

Introduction
========================================

* `compiler-rt 官網 <http://compiler-rt.llvm.org/>`_
* `LLVM - compiler-rt <http://llvm.org/svn/llvm-project/compiler-rt/trunk/>`_
* `[GitHub] llvm-mirror/compiler-rt <https://github.com/llvm-mirror/compiler-rt>`_
* /usr/lib/clang/3.6.2/lib/linux/libclang_rt.asan-x86_64.a


Build From Source
========================================

.. code-block:: sh

    # http://clang.llvm.org/get_started.html

    svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

    cd llvm/tools
    svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
    cd ../..

    cd llvm/projects
    svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
    cd ../..

    mkdir build
    cd build
    cmake -G "Unix Makefiles" ../llvm
    make -j8
    make install


如果系統已經有 ``llvm-config`` 的話可以使用以下方式只編 ``compiler-rt`` 的部份：

.. code-block:: sh

    # if you have llvm-config

    git clone https://github.com/llvm-mirror/compiler-rt/
    mkdir build
    cd build
    cmake ../compiler-rt -DLLVM_CONFIG_PATH=`which llvm-config`
    make


Clang On ARM
========================================


Cross Compile Android Program To ARM
========================================

Build For Android/ARM
========================================

* `Cross-compilation using Clang <http://clang.llvm.org/docs/CrossCompilation.html>`_
* `How To Cross-Compile Clang/LLVM using Clang/LLVM <http://llvm.org/docs/HowToCrossCompileLLVM.html>`_
* `[LLVMdev] compiler-rt for ARM-Linux with CMake? <https://groups.google.com/forum/#!topic/llvm-dev/xZL64aZMoAU>`_

* http://falstaff.agner.ch/2015/03/03/cross-compile-linux-for-arm-using-llvmclang-on-arch-linux/


.. code-block:: sh

    LD='arm-none-eabi-ld' CC='clang' CXX='clang++' cmake -G Ninja ../llvm-arm \
        -DCMAKE_LINKER=`which arm-none-eabi-ld` \
        -DCMAKE_CXX_LINK_EXECUTABLE='<CMAKE_LINKER> <FLAGS> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>' \
        -DCMAKE_CROSSCOMPILING=True \
        -DCMAKE_INSTALL_PREFIX=/opt \
        -DLLVM_TABLEGEN=`which llvm-tblgen` \
        -DCLANG_TABLEGEN=`which clang-tblgen` \
        -DLLVM_DEFAULT_TARGET_TRIPLE=arm-linux-gnueabihf \
        -DLLVM_TARGET_ARCH=ARM \
        -DLLVM_TARGETS_TO_BUILD=ARM \
        -DCMAKE_CXX_FLAGS='-target armv7a-linux-gnueabihf -mcpu=cortex-a9 -I/usr/arm-none-eabi/include/c++/5.2.0/arm-none-eabi/ -I/usr/arm-none-eabi/include/ -mfloat-abi=hard -ccc-gcc-name arm-linux-gnueabihf-gcc' \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_C_COMPILER=`which arm-none-eabi-clang` \
        -DCMAKE_CXX_COMPILER=`which arm-none-eabi-clang++` \
        -DLLVM_ENABLE_ASSERTIONS=ON
        #-DLLVM_EXTERNAL_COMPILER_RT_SOURCE_DIR=../compiler-rt


Standalone
========================================

* https://llvm.org/bugs/show_bug.cgi?id=18331


Languages
========================================

* `[2013] Introducing the Go Race Detector <http://blog.golang.org/race-detector>`_
* `[2014] The Go Race Detector <https://github.com/robertknight/talks/blob/master/golang-race-detector/race.slide>`_


Addr2Line
========================================

* `Support inline functions symbolization in Addr2Line symbolizer. <https://github.com/llvm-mirror/compiler-rt/commit/a1f6419d4f1ae39600c6669564ca179aa18b0d99>`_


Reference
========================================

* `CppCon 2014: Kostya Serebryany "Sanitize your C++ code" <https://isocpp.org/blog/2015/05/cppcon-2014-sanitize-your-cpp-code-kostya-serebryany>`_
* `CppCon 2015: Beyond Sanitizers <https://cppcon2015.sched.org/event/cab93ab408d0aacbc4c0894c44cfd9cf>`_
* `GCC Undefined Behavior Sanitizer – ubsan <http://developerblog.redhat.com/2014/10/16/gcc-undefined-behavior-sanitizer-ubsan/>`_
* `The Chromium Projects - AddressSanitizer (ASan) <https://www.chromium.org/developers/testing/addresssanitizer>`_
* `The LLVM gold plugin <http://llvm.org/docs/GoldPlugin.html>`_
* `lld - The LLVM Linker <http://lld.llvm.org/>`_
* `LLVM 研究 - 3.4.2 <https://cgcheng.hackpad.com/ep/pad/static/lPbY7K0tYcB>`_
* search : ``site:llvmweekly.org`` ``compiler-rt`` ``sanitizer``


LLVM Weekly
========================================

* [2014-01-31][r200546_] Compiler-rt's CMake files will now compile the library for ARM. Give it a go and see what breaks. r200546.
* [2014-01-21][r199729_] In compiler-rt, support was added for intercepting and sanitizing arguments passed to printf functions in AddressSanitizer and ThreadSanitizer.
* [2014-01-16][r199377_] AddressSanitizer in compiler-rt gained the ability to start in 'deactivated' mode. It can later be activated when __asan_init is called in an instrumented library.


.. _r200546: http://reviews.llvm.org/rL200546
.. _r199729: http://reviews.llvm.org/rL199729
.. _r199377: http://reviews.llvm.org/rL199377


Installation
========================================

::

    [  2%] Built target LLVMSupport
    [  3%] Built target LLVMTableGen
    [  4%] Built target obj.llvm-tblgen
    [  4%] Built target llvm-tblgen
    [  4%] Built target intrinsics_gen
    [  5%] Built target LLVMCore
    [  5%] Built target LLVMIRReader
    [ 10%] Built target LLVMCodeGen
    [ 11%] Built target LLVMSelectionDAG
    [ 11%] Built target LLVMAsmPrinter
    [ 11%] Built target LLVMMIRParser
    [ 11%] Built target LLVMBitReader
    [ 11%] Built target LLVMBitWriter
    [ 12%] Built target LLVMTransformUtils
    [ 12%] Built target LLVMInstrumentation
    [ 14%] Built target LLVMInstCombine
    [ 15%] Built target LLVMScalarOpts
    [ 16%] Built target LLVMipo
    [ 16%] Built target LLVMVectorize
    [ 16%] Built target LLVMHello_exports
    [ 16%] Built target LLVMHello
    [ 17%] Built target LLVMObjCARCOpts
    [ 17%] Built target LLVMLinker
    [ 20%] Built target LLVMAnalysis
    [ 20%] Built target LLVMLTO
    [ 22%] Built target LLVMMC
    [ 22%] Built target LLVMMCParser
    [ 22%] Built target LLVMMCDisassembler
    [ 22%] Built target LLVMObject
    [ 22%] Built target LLVMOption
    [ 23%] Built target LLVMDebugInfoDWARF
    [ 24%] Built target LLVMDebugInfoPDB
    [ 24%] Built target LLVMExecutionEngine
    [ 24%] Built target LLVMInterpreter
    [ 24%] Built target LLVMMCJIT
    [ 24%] Built target LLVMOrcJIT
    [ 24%] Built target LLVMRuntimeDyld
    [ 24%] Built target LLVMTarget
    [ 24%] Built target AArch64CommonTableGen
    [ 25%] Built target LLVMAArch64CodeGen
    [ 25%] Built target LLVMAArch64Info
    [ 25%] Built target LLVMAArch64AsmParser
    [ 27%] Built target LLVMAArch64Disassembler
    [ 27%] Built target LLVMAArch64AsmPrinter
    [ 27%] Built target LLVMAArch64Desc
    [ 27%] Built target LLVMAArch64Utils
    [ 28%] Built target AMDGPUCommonTableGen
    [ 29%] Built target LLVMAMDGPUCodeGen
    [ 29%] Built target LLVMAMDGPUAsmParser
    [ 29%] Built target LLVMAMDGPUAsmPrinter
    [ 29%] Built target LLVMAMDGPUInfo
    [ 29%] Built target LLVMAMDGPUDesc
    [ 29%] Built target LLVMAMDGPUUtils
    [ 29%] Built target ARMCommonTableGen
    [ 30%] Built target LLVMARMCodeGen
    [ 30%] Built target LLVMARMInfo
    [ 30%] Built target LLVMARMAsmParser
    [ 30%] Built target LLVMARMDisassembler
    [ 30%] Built target LLVMARMAsmPrinter
    [ 31%] Built target LLVMARMDesc
    [ 31%] Built target BPFCommonTableGen
    [ 31%] Built target LLVMBPFCodeGen
    [ 32%] Built target LLVMBPFAsmPrinter
    [ 32%] Built target LLVMBPFInfo
    [ 32%] Built target LLVMBPFDesc
    [ 32%] Built target LLVMCppBackendCodeGen
    [ 32%] Built target LLVMCppBackendInfo
    [ 34%] Built target HexagonCommonTableGen
    [ 35%] Built target LLVMHexagonCodeGen
    [ 35%] Built target LLVMHexagonInfo
    [ 35%] Built target LLVMHexagonDesc
    [ 35%] Built target LLVMHexagonDisassembler
    [ 35%] Built target MipsCommonTableGen
    [ 36%] Built target LLVMMipsCodeGen
    [ 36%] Built target LLVMMipsAsmPrinter
    [ 36%] Built target LLVMMipsDisassembler
    [ 36%] Built target LLVMMipsInfo
    [ 36%] Built target LLVMMipsDesc
    [ 36%] Built target LLVMMipsAsmParser
    [ 37%] Built target MSP430CommonTableGen
    [ 38%] Built target LLVMMSP430CodeGen
    [ 38%] Built target LLVMMSP430AsmPrinter
    [ 38%] Built target LLVMMSP430Info
    [ 38%] Built target LLVMMSP430Desc
    [ 40%] Built target NVPTXCommonTableGen
    [ 41%] Built target LLVMNVPTXCodeGen
    [ 41%] Built target LLVMNVPTXInfo
    [ 41%] Built target LLVMNVPTXAsmPrinter
    [ 41%] Built target LLVMNVPTXDesc
    [ 42%] Built target PowerPCCommonTableGen
    [ 42%] Built target LLVMPowerPCCodeGen
    [ 42%] Built target LLVMPowerPCAsmParser
    [ 43%] Built target LLVMPowerPCDisassembler
    [ 44%] Built target LLVMPowerPCAsmPrinter
    [ 44%] Built target LLVMPowerPCInfo
    [ 44%] Built target LLVMPowerPCDesc
    [ 45%] Built target SparcCommonTableGen
    [ 47%] Built target LLVMSparcCodeGen
    [ 47%] Built target LLVMSparcInfo
    [ 47%] Built target LLVMSparcDesc
    [ 47%] Built target LLVMSparcAsmPrinter
    [ 47%] Built target LLVMSparcAsmParser
    [ 47%] Built target LLVMSparcDisassembler
    [ 48%] Built target SystemZCommonTableGen
    [ 48%] Built target LLVMSystemZCodeGen
    [ 49%] Built target LLVMSystemZAsmParser
    [ 49%] Built target LLVMSystemZDisassembler
    [ 49%] Built target LLVMSystemZAsmPrinter
    [ 49%] Built target LLVMSystemZInfo
    [ 49%] Built target LLVMSystemZDesc
    [ 49%] Built target X86CommonTableGen
    [ 50%] Built target LLVMX86CodeGen
    [ 50%] Built target LLVMX86AsmParser
    [ 50%] Built target LLVMX86Disassembler
    [ 50%] Built target LLVMX86AsmPrinter
    [ 50%] Built target LLVMX86Desc
    [ 50%] Built target LLVMX86Info
    [ 50%] Built target LLVMX86Utils
    [ 51%] Built target XCoreCommonTableGen
    [ 52%] Built target LLVMXCoreCodeGen
    [ 52%] Built target LLVMXCoreDisassembler
    [ 52%] Built target LLVMXCoreAsmPrinter
    [ 52%] Built target LLVMXCoreInfo
    [ 52%] Built target LLVMXCoreDesc
    [ 52%] Built target LLVMAsmParser
    [ 52%] Built target LLVMLineEditor
    [ 52%] Built target LLVMProfileData
    [ 52%] Built target LLVMPasses
    [ 52%] Built target LibOptionsTableGen
    [ 52%] Built target LLVMLibDriver
    [ 52%] Built target FileCheck
    [ 52%] Built target llvm-PerfectShuffle
    [ 52%] Built target count
    [ 52%] Built target not
    [ 52%] Built target yaml-bench
    [ 52%] Built target gtest
    [ 52%] Built target gtest_main
    [ 54%] Built target RTSanitizerCommon.x86_64
    [ 54%] Built target RTSanitizerCommonLibc.x86_64
    [ 54%] Built target RTInterception.x86_64
    [ 54%] Built target clang_rt.dd-x86_64
    [ 54%] Built target RTDD.x86_64
    [ 54%] Built target clang_rt.dyndd-dynamic-x86_64
    [ 54%] Built target dd
    [ 54%] Built target compiler-rt-headers
    [ 54%] Built target cfi_blacklist
    [ 54%] Built target cfi
    [ 54%] Built target RTLSanCommon.x86_64
    [ 54%] Built target clang_rt.lsan-x86_64
    [ 54%] Built target lsan
    [ 54%] Built target RTUbsan.x86_64
    [ 54%] Built target RTUbsan_standalone.x86_64
    [ 54%] Built target clang_rt.ubsan_standalone-x86_64
    [ 54%] Built target clang_rt.ubsan_standalone-x86_64-symbols
    [ 55%] Built target RTUbsan_cxx.i386
    [ 55%] Built target clang_rt.ubsan_standalone_cxx-i386
    [ 55%] Built target RTUbsan_cxx.x86_64
    [ 55%] Built target clang_rt.ubsan_standalone_cxx-x86_64
    [ 55%] Built target clang_rt.ubsan_standalone_cxx-x86_64-symbols
    [ 55%] Built target RTUbsan_standalone.i386
    [ 56%] Built target RTSanitizerCommon.i386
    [ 56%] Built target RTSanitizerCommonLibc.i386
    [ 56%] Built target RTUbsan.i386
    [ 56%] Built target clang_rt.ubsan_standalone-i386
    [ 56%] Built target ubsan
    [ 56%] Built target RTAsan_preinit.x86_64
    [ 57%] Built target RTAsan.x86_64
    [ 57%] Built target clang_rt.asan-x86_64
    [ 57%] Built target RTAsan_cxx.x86_64
    [ 57%] Built target clang_rt.asan_cxx-x86_64
    [ 57%] Built target RTAsan_dynamic_version_script_dummy.i386
    [ 58%] Built target RTInterception.i386
    [ 58%] Built target RTLSanCommon.i386
    [ 60%] Built target RTAsan_dynamic.i386
    [ 60%] Built target clang_rt.asan-dynamic-i386
    [ 60%] Built target clang_rt.asan_cxx-x86_64-symbols
    [ 60%] Built target RTAsan_cxx.i386
    [ 60%] Built target clang_rt.asan_cxx-i386
    [ 60%] Built target RTAsan.i386
    [ 60%] Built target RTAsan_preinit.i386
    [ 60%] Built target clang_rt.asan-i386
    [ 60%] Built target clang_rt.asan-preinit-i386
    [ 60%] Built target clang_rt.asan-x86_64-symbols
    [ 60%] Built target clang_rt.asan-preinit-x86_64
    [ 60%] Built target asan_blacklist
    [ 60%] Built target RTAsan_dynamic_version_script_dummy.x86_64
    [ 60%] Built target RTAsan_dynamic.x86_64
    [ 60%] Built target clang_rt.asan-dynamic-x86_64
    [ 60%] Built target asan
    [ 64%] Built target clang_rt.builtins-x86_64
    [ 69%] Built target clang_rt.builtins-i386
    [ 69%] Built target builtins
    [ 69%] Built target dfsan_abilist
    [ 69%] Built target clang_rt.dfsan-x86_64
    [ 69%] Built target clang_rt.dfsan-x86_64-symbols
    [ 69%] Built target dfsan
    [ 69%] Built target msan_blacklist
    [ 69%] Built target clang_rt.msan_cxx-x86_64
    [ 69%] Built target clang_rt.msan_cxx-x86_64-symbols
    [ 69%] Built target clang_rt.msan-x86_64
    [ 69%] Built target clang_rt.msan-x86_64-symbols
    [ 69%] Built target msan
    [ 70%] Built target clang_rt.profile-i386
    [ 70%] Built target clang_rt.profile-x86_64
    [ 70%] Built target profile
    [ 70%] Built target clang_rt.tsan_cxx-x86_64
    [ 70%] Built target clang_rt.tsan_cxx-x86_64-symbols
    [ 71%] Built target clang_rt.tsan-x86_64
    [ 71%] Built target clang_rt.tsan-x86_64-symbols
    [ 71%] Built target tsan
    [ 71%] Built target compiler-rt
    [ 71%] Built target RTSanitizerCommonNoLibc.i386
    [ 71%] Built target RTSanitizerCommonNoLibc.x86_64
    [ 71%] Built target RTSanitizerCommon.test.i386
    [ 71%] Built target RTSanitizerCommon.test.nolibc.x86_64
    [ 71%] Built target RTSanitizerCommon.test.x86_64
    [ 71%] Built target clang_rt.asan-dynamic-x86_64-version-list
    [ 71%] Built target RTAsanTest.i386-inline
    [ 71%] Built target RTAsanTest.i386-with-calls
    [ 71%] Built target RTAsanTest.x86_64-inline
    [ 71%] Built target RTAsanTest.x86_64-with-calls
    [ 71%] Built target clang_rt.safestack-i386
    [ 71%] Built target clang_rt.safestack-x86_64
    [ 71%] Built target LTO_exports
    [ 71%] Built target LTO
    [ 71%] Built target obj.clang-tblgen
    [ 71%] Built target clang-tblgen
    [ 74%] Built target clang-headers
    [ 74%] Built target ClangAttrPCHWrite
    [ 74%] Built target ClangAttrClasses
    [ 74%] Built target ClangAttrImpl
    [ 74%] Built target ClangAttrDump
    [ 74%] Built target ClangAttrVisitor
    [ 74%] Built target ClangStmtNodes
    [ 74%] Built target ClangDeclNodes
    [ 74%] Built target ClangCommentNodes
    [ 74%] Built target ClangCommentHTMLTags
    [ 74%] Built target ClangCommentHTMLTagsProperties
    [ 74%] Built target ClangCommentHTMLNamedCharacterReferences
    [ 75%] Built target ClangCommentCommandInfo
    [ 75%] Built target ClangCommentCommandList
    [ 75%] Built target ClangDiagnosticAnalysis
    [ 75%] Built target ClangDiagnosticAST
    [ 75%] Built target ClangDiagnosticComment
    [ 75%] Built target ClangDiagnosticCommon
    [ 75%] Built target ClangDiagnosticDriver
    [ 75%] Built target ClangDiagnosticFrontend
    [ 75%] Built target ClangDiagnosticLex
    [ 75%] Built target ClangDiagnosticParse
    [ 75%] Built target ClangDiagnosticSema
    [ 76%] Built target ClangDiagnosticSerialization
    [ 76%] Built target ClangDiagnosticGroups
    [ 76%] Built target ClangDiagnosticIndexName
    [ 76%] Built target ClangAttrList
    [ 76%] Built target ClangAttrHasAttributeImpl
    [ 76%] Built target ClangARMNeon
    [ 76%] Built target ClangAttrParserStringSwitches
    [ 76%] Built target ClangAttrTemplateInstantiate
    [ 76%] Built target ClangAttrParsedAttrList
    [ 76%] Built target ClangAttrParsedAttrKinds
    [ 76%] Built target ClangAttrSpellingListIndex
    [ 76%] Built target ClangAttrParsedAttrImpl
    [ 76%] Built target ClangAttrPCHRead
    [ 77%] Built target clangBasic
    [ 78%] Built target clangLex
    [ 78%] Built target clangParse
    [ 80%] Built target clangAST
    [ 80%] Built target clangASTMatchers
    [ 80%] Built target clangDynamicASTMatchers
    [ 81%] Built target clangSema
    [ 82%] Built target clangCodeGen
    [ 83%] Built target clangAnalysis
    [ 83%] Built target clangEdit
    [ 83%] Built target clangRewrite
    [ 84%] Built target clangARCMigrate
    [ 84%] Built target ClangDriverOptions
    [ 85%] Built target clangDriver
    [ 85%] Built target clangSerialization
    [ 87%] Built target clangFrontend
    [ 88%] Built target clangRewriteFrontend
    [ 88%] Built target clangFrontendTool
    [ 88%] Built target clangTooling
    [ 88%] Built target clangToolingCore
    [ 88%] Built target clangIndex
    [ 89%] Built target clangStaticAnalyzerCore
    [ 89%] Built target ClangSACheckers
    [ 91%] Built target clangStaticAnalyzerCheckers
    [ 92%] Built target clangStaticAnalyzerFrontend
    [ 92%] Built target clangFormat
    [ 94%] Built target diagtool
    [ 94%] Built target clang
    [ 94%] Built target clang-format
    [ 94%] Built target libclang_exports
    [ 94%] Built target libclang
    [ 94%] Built target c-index-test
    [ 94%] Built target arcmt-test
    [ 94%] Built target c-arcmt-test
    [ 94%] Built target clang-check
    [ 94%] Built target llvm-dis
    [ 94%] Built target opt
    [ 94%] Built target llvm-mcmarkup
    [ 94%] Built target macho-dump
    [ 95%] Built target llvm-cov
    [ 95%] Built target llvm-lto
    [ 95%] Built target llvm-stress
    [ 95%] Built target bugpoint
    [ 95%] Built target llvm-mc
    [ 96%] Built target lli
    [ 96%] Built target lli-child-target
    [ 96%] Built target llvm-size
    [ 96%] Built target llvm-readobj
    [ 96%] Built target llvm-bcanalyzer
    [ 96%] Built target llvm-dwarfdump
    [ 96%] Built target llvm-config
    [ 96%] Built target llvm-pdbdump
    [ 96%] Built target BugpointPasses_exports
    [ 96%] Built target BugpointPasses
    [ 96%] Built target llvm-diff
    [ 96%] Built target llc
    [ 96%] Built target llvm-cxxdump
    [ 96%] Built target llvm-profdata
    [ 96%] Built target verify-uselistorder
    [ 97%] Built target llvm-objdump
    [ 97%] Built target llvm-symbolizer
    [ 97%] Built target llvm-go
    [ 97%] Built target llvm-extract
    [ 97%] Built target llvm-nm
    [ 98%] Built target llvm-split
    [ 98%] Built target llvm-dsymutil
    [100%] Built target yaml2obj
    [100%] Built target llvm-c-test
    [100%] Built target llvm-as
    [100%] Built target llvm-link
    [100%] Built target obj2yaml
    [100%] Built target llvm-ar
    [100%] Built target llvm-lib
    [100%] Built target llvm-ranlib
    [100%] Built target llvm-rtdyld
    Install the project...
    -- Install configuration: ""
    -- Installing: /usr/local/include/llvm
    -- Installing: /usr/local/include/llvm/AsmParser
    -- Installing: /usr/local/include/llvm/AsmParser/SlotMapping.h
    -- Installing: /usr/local/include/llvm/AsmParser/Parser.h
    -- Installing: /usr/local/include/llvm/CodeGen
    -- Installing: /usr/local/include/llvm/CodeGen/MachineLoopInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/SchedulerRegistry.h
    -- Installing: /usr/local/include/llvm/CodeGen/ResourcePriorityQueue.h
    -- Installing: /usr/local/include/llvm/CodeGen/CalcSpillWeights.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineMemOperand.h
    -- Installing: /usr/local/include/llvm/CodeGen/FaultMaps.h
    -- Installing: /usr/local/include/llvm/CodeGen/ParallelCG.h
    -- Installing: /usr/local/include/llvm/CodeGen/FunctionLoweringInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/TargetLoweringObjectFileImpl.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineFunctionInitializer.h
    -- Installing: /usr/local/include/llvm/CodeGen/SlotIndexes.h
    -- Installing: /usr/local/include/llvm/CodeGen/ValueTypes.h
    -- Installing: /usr/local/include/llvm/CodeGen/ScheduleHazardRecognizer.h
    -- Installing: /usr/local/include/llvm/CodeGen/EdgeBundles.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineFunctionAnalysis.h
    -- Installing: /usr/local/include/llvm/CodeGen/SelectionDAGISel.h
    -- Installing: /usr/local/include/llvm/CodeGen/GCStrategy.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineSSAUpdater.h
    -- Installing: /usr/local/include/llvm/CodeGen/MIRYamlMapping.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineValueType.h
    -- Installing: /usr/local/include/llvm/CodeGen/LatencyPriorityQueue.h
    -- Installing: /usr/local/include/llvm/CodeGen/GCs.h
    -- Installing: /usr/local/include/llvm/CodeGen/RegAllocPBQP.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveVariables.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineInstr.h
    -- Installing: /usr/local/include/llvm/CodeGen/FastISel.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineBasicBlock.h
    -- Installing: /usr/local/include/llvm/CodeGen/ValueTypes.td
    -- Installing: /usr/local/include/llvm/CodeGen/Passes.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineDominators.h
    -- Installing: /usr/local/include/llvm/CodeGen/IntrinsicLowering.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineJumpTableInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveIntervalUnion.h
    -- Installing: /usr/local/include/llvm/CodeGen/RegisterScavenging.h
    -- Installing: /usr/local/include/llvm/CodeGen/StackProtector.h
    -- Installing: /usr/local/include/llvm/CodeGen/MIRParser
    -- Installing: /usr/local/include/llvm/CodeGen/MIRParser/MIRParser.h
    -- Installing: /usr/local/include/llvm/CodeGen/DwarfStringPoolEntry.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveRegMatrix.h
    -- Installing: /usr/local/include/llvm/CodeGen/AtomicExpandUtils.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachinePassRegistry.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachinePostDominators.h
    -- Installing: /usr/local/include/llvm/CodeGen/RegisterPressure.h
    -- Installing: /usr/local/include/llvm/CodeGen/AsmPrinter.h
    -- Installing: /usr/local/include/llvm/CodeGen/GCMetadataPrinter.h
    -- Installing: /usr/local/include/llvm/CodeGen/DAGCombine.h
    -- Installing: /usr/local/include/llvm/CodeGen/Analysis.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineFrameInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachORelocation.h
    -- Installing: /usr/local/include/llvm/CodeGen/LivePhysRegs.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveStackAnalysis.h
    -- Installing: /usr/local/include/llvm/CodeGen/LexicalScopes.h
    -- Installing: /usr/local/include/llvm/CodeGen/DFAPacketizer.h
    -- Installing: /usr/local/include/llvm/CodeGen/LinkAllAsmWriterComponents.h
    -- Installing: /usr/local/include/llvm/CodeGen/StackMaps.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineModuleInfoImpls.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP/Solution.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP/Graph.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP/CostAllocator.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP/Math.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQP/ReductionRules.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineCombinerPattern.h
    -- Installing: /usr/local/include/llvm/CodeGen/RegisterClassInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/PseudoSourceValue.h
    -- Installing: /usr/local/include/llvm/CodeGen/ScoreboardHazardRecognizer.h
    -- Installing: /usr/local/include/llvm/CodeGen/CommandFlags.h
    -- Installing: /usr/local/include/llvm/CodeGen/RuntimeLibcalls.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineScheduler.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineModuleInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/ISDOpcodes.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineRegisterInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/DIEValue.def
    -- Installing: /usr/local/include/llvm/CodeGen/WinEHFuncInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineInstrBuilder.h
    -- Installing: /usr/local/include/llvm/CodeGen/SelectionDAG.h
    -- Installing: /usr/local/include/llvm/CodeGen/BasicTTIImpl.h
    -- Installing: /usr/local/include/llvm/CodeGen/RegAllocRegistry.h
    -- Installing: /usr/local/include/llvm/CodeGen/CallingConvLower.h
    -- Installing: /usr/local/include/llvm/CodeGen/TargetSchedule.h
    -- Installing: /usr/local/include/llvm/CodeGen/DIE.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveInterval.h
    -- Installing: /usr/local/include/llvm/CodeGen/PBQPRAConstraint.h
    -- Installing: /usr/local/include/llvm/CodeGen/ScheduleDAGInstrs.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineFunction.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineConstantPool.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineBlockFrequencyInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/ScheduleDFS.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineOperand.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineTraceMetrics.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineInstrBundle.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveRangeEdit.h
    -- Installing: /usr/local/include/llvm/CodeGen/VirtRegMap.h
    -- Installing: /usr/local/include/llvm/CodeGen/ScheduleDAG.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineRegionInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineBranchProbabilityInfo.h
    -- Installing: /usr/local/include/llvm/CodeGen/LiveIntervalAnalysis.h
    -- Installing: /usr/local/include/llvm/CodeGen/GCMetadata.h
    -- Installing: /usr/local/include/llvm/CodeGen/LinkAllCodegenComponents.h
    -- Installing: /usr/local/include/llvm/CodeGen/SelectionDAGNodes.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineFunctionPass.h
    -- Installing: /usr/local/include/llvm/CodeGen/MachineDominanceFrontier.h
    -- Installing: /usr/local/include/llvm/Analysis
    -- Installing: /usr/local/include/llvm/Analysis/CFGPrinter.h
    -- Installing: /usr/local/include/llvm/Analysis/BasicAliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/AliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/DomPrinter.h
    -- Installing: /usr/local/include/llvm/Analysis/SparsePropagation.h
    -- Installing: /usr/local/include/llvm/Analysis/BranchProbabilityInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/AssumptionCache.h
    -- Installing: /usr/local/include/llvm/Analysis/PostDominators.h
    -- Installing: /usr/local/include/llvm/Analysis/RegionIterator.h
    -- Installing: /usr/local/include/llvm/Analysis/Interval.h
    -- Installing: /usr/local/include/llvm/Analysis/ScalarEvolutionExpander.h
    -- Installing: /usr/local/include/llvm/Analysis/TypeBasedAliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/IVUsers.h
    -- Installing: /usr/local/include/llvm/Analysis/CallGraph.h
    -- Installing: /usr/local/include/llvm/Analysis/VectorUtils.h
    -- Installing: /usr/local/include/llvm/Analysis/AliasSetTracker.h
    -- Installing: /usr/local/include/llvm/Analysis/IntervalPartition.h
    -- Installing: /usr/local/include/llvm/Analysis/LazyValueInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/IntervalIterator.h
    -- Installing: /usr/local/include/llvm/Analysis/OrderedBasicBlock.h
    -- Installing: /usr/local/include/llvm/Analysis/ObjCARCAliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/TargetTransformInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/CodeMetrics.h
    -- Installing: /usr/local/include/llvm/Analysis/Passes.h
    -- Installing: /usr/local/include/llvm/Analysis/IteratedDominanceFrontier.h
    -- Installing: /usr/local/include/llvm/Analysis/TargetLibraryInfo.def
    -- Installing: /usr/local/include/llvm/Analysis/CallPrinter.h
    -- Installing: /usr/local/include/llvm/Analysis/BlockFrequencyInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/RegionInfoImpl.h
    -- Installing: /usr/local/include/llvm/Analysis/TargetTransformInfoImpl.h
    -- Installing: /usr/local/include/llvm/Analysis/LoopPass.h
    -- Installing: /usr/local/include/llvm/Analysis/DemandedBits.h
    -- Installing: /usr/local/include/llvm/Analysis/MemoryDependenceAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/InstructionSimplify.h
    -- Installing: /usr/local/include/llvm/Analysis/CaptureTracking.h
    -- Installing: /usr/local/include/llvm/Analysis/DOTGraphTraitsPass.h
    -- Installing: /usr/local/include/llvm/Analysis/DominanceFrontier.h
    -- Installing: /usr/local/include/llvm/Analysis/LibCallSemantics.h
    -- Installing: /usr/local/include/llvm/Analysis/LoopAccessAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/RegionPass.h
    -- Installing: /usr/local/include/llvm/Analysis/ScalarEvolutionExpressions.h
    -- Installing: /usr/local/include/llvm/Analysis/CFG.h
    -- Installing: /usr/local/include/llvm/Analysis/RegionPrinter.h
    -- Installing: /usr/local/include/llvm/Analysis/CGSCCPassManager.h
    -- Installing: /usr/local/include/llvm/Analysis/MemoryLocation.h
    -- Installing: /usr/local/include/llvm/Analysis/ScopedNoAliasAA.h
    -- Installing: /usr/local/include/llvm/Analysis/CallGraphSCCPass.h
    -- Installing: /usr/local/include/llvm/Analysis/Loads.h
    -- Installing: /usr/local/include/llvm/Analysis/ScalarEvolution.h
    -- Installing: /usr/local/include/llvm/Analysis/ObjCARCAnalysisUtils.h
    -- Installing: /usr/local/include/llvm/Analysis/ValueTracking.h
    -- Installing: /usr/local/include/llvm/Analysis/InlineCost.h
    -- Installing: /usr/local/include/llvm/Analysis/Lint.h
    -- Installing: /usr/local/include/llvm/Analysis/ScalarEvolutionAliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/LoopInfoImpl.h
    -- Installing: /usr/local/include/llvm/Analysis/TargetLibraryInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/PtrUseVisitor.h
    -- Installing: /usr/local/include/llvm/Analysis/TargetFolder.h
    -- Installing: /usr/local/include/llvm/Analysis/Trace.h
    -- Installing: /usr/local/include/llvm/Analysis/LoopInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/DominanceFrontierImpl.h
    -- Installing: /usr/local/include/llvm/Analysis/DependenceAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/ScalarEvolutionNormalization.h
    -- Installing: /usr/local/include/llvm/Analysis/BlockFrequencyInfoImpl.h
    -- Installing: /usr/local/include/llvm/Analysis/RegionInfo.h
    -- Installing: /usr/local/include/llvm/Analysis/GlobalsModRef.h
    -- Installing: /usr/local/include/llvm/Analysis/CFLAliasAnalysis.h
    -- Installing: /usr/local/include/llvm/Analysis/LoopIterator.h
    -- Installing: /usr/local/include/llvm/Analysis/ConstantFolding.h
    -- Installing: /usr/local/include/llvm/Analysis/LazyCallGraph.h
    -- Installing: /usr/local/include/llvm/Analysis/ObjCARCInstKind.h
    -- Installing: /usr/local/include/llvm/Analysis/MemoryBuiltins.h
    -- Installing: /usr/local/include/llvm/Analysis/PHITransAddr.h
    -- Installing: /usr/local/include/llvm/Config
    -- Installing: /usr/local/include/llvm/LinkAllPasses.h
    -- Installing: /usr/local/include/llvm/Bitcode
    -- Installing: /usr/local/include/llvm/Bitcode/BitcodeWriterPass.h
    -- Installing: /usr/local/include/llvm/Bitcode/ReaderWriter.h
    -- Installing: /usr/local/include/llvm/Bitcode/BitstreamReader.h
    -- Installing: /usr/local/include/llvm/Bitcode/LLVMBitCodes.h
    -- Installing: /usr/local/include/llvm/Bitcode/BitstreamWriter.h
    -- Installing: /usr/local/include/llvm/Bitcode/BitCodes.h
    -- Installing: /usr/local/include/llvm/Passes
    -- Installing: /usr/local/include/llvm/Passes/PassBuilder.h
    -- Installing: /usr/local/include/llvm/IR
    -- Installing: /usr/local/include/llvm/IR/Mangler.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsAArch64.td
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsWebAssembly.td
    -- Installing: /usr/local/include/llvm/IR/IRBuilder.h
    -- Installing: /usr/local/include/llvm/IR/ValueMap.h
    -- Installing: /usr/local/include/llvm/IR/DebugLoc.h
    -- Installing: /usr/local/include/llvm/IR/LLVMContext.h
    -- Installing: /usr/local/include/llvm/IR/GetElementPtrTypeIterator.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsPowerPC.td
    -- Installing: /usr/local/include/llvm/IR/DIBuilder.h
    -- Installing: /usr/local/include/llvm/IR/PassManagerInternal.h
    -- Installing: /usr/local/include/llvm/IR/ValueHandle.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsAMDGPU.td
    -- Installing: /usr/local/include/llvm/IR/Statepoint.h
    -- Installing: /usr/local/include/llvm/IR/AssemblyAnnotationWriter.h
    -- Installing: /usr/local/include/llvm/IR/Constant.h
    -- Installing: /usr/local/include/llvm/IR/LegacyPassManager.h
    -- Installing: /usr/local/include/llvm/IR/BasicBlock.h
    -- Installing: /usr/local/include/llvm/IR/MetadataTracking.h
    -- Installing: /usr/local/include/llvm/IR/GlobalObject.h
    -- Installing: /usr/local/include/llvm/IR/InlineAsm.h
    -- Installing: /usr/local/include/llvm/IR/Constants.h
    -- Installing: /usr/local/include/llvm/IR/GlobalVariable.h
    -- Installing: /usr/local/include/llvm/IR/TypeFinder.h
    -- Installing: /usr/local/include/llvm/IR/Metadata.def
    -- Installing: /usr/local/include/llvm/IR/TypeBuilder.h
    -- Installing: /usr/local/include/llvm/IR/Instructions.h
    -- Installing: /usr/local/include/llvm/IR/CallSite.h
    -- Installing: /usr/local/include/llvm/IR/Instruction.def
    -- Installing: /usr/local/include/llvm/IR/IRPrintingPasses.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsARM.td
    -- Installing: /usr/local/include/llvm/IR/GlobalValue.h
    -- Installing: /usr/local/include/llvm/IR/Operator.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsX86.td
    -- Installing: /usr/local/include/llvm/IR/Value.h
    -- Installing: /usr/local/include/llvm/IR/User.h
    -- Installing: /usr/local/include/llvm/IR/Intrinsics.td
    -- Installing: /usr/local/include/llvm/IR/SymbolTableListTraits.h
    -- Installing: /usr/local/include/llvm/IR/Use.h
    -- Installing: /usr/local/include/llvm/IR/Metadata.h
    -- Installing: /usr/local/include/llvm/IR/GlobalAlias.h
    -- Installing: /usr/local/include/llvm/IR/DataLayout.h
    -- Installing: /usr/local/include/llvm/IR/PatternMatch.h
    -- Installing: /usr/local/include/llvm/IR/Instruction.h
    -- Installing: /usr/local/include/llvm/IR/CFG.h
    -- Installing: /usr/local/include/llvm/IR/DerivedTypes.h
    -- Installing: /usr/local/include/llvm/IR/Function.h
    -- Installing: /usr/local/include/llvm/IR/TrackingMDRef.h
    -- Installing: /usr/local/include/llvm/IR/Comdat.h
    -- Installing: /usr/local/include/llvm/IR/DebugInfoFlags.def
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsHexagon.td
    -- Installing: /usr/local/include/llvm/IR/PassManager.h
    -- Installing: /usr/local/include/llvm/IR/DebugInfoMetadata.h
    -- Installing: /usr/local/include/llvm/IR/CallingConv.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsSystemZ.td
    -- Installing: /usr/local/include/llvm/IR/Attributes.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicInst.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsMips.td
    -- Installing: /usr/local/include/llvm/IR/DebugInfo.h
    -- Installing: /usr/local/include/llvm/IR/DiagnosticInfo.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsNVVM.td
    -- Installing: /usr/local/include/llvm/IR/ValueSymbolTable.h
    -- Installing: /usr/local/include/llvm/IR/Argument.h
    -- Installing: /usr/local/include/llvm/IR/Type.h
    -- Installing: /usr/local/include/llvm/IR/UseListOrder.h
    -- Installing: /usr/local/include/llvm/IR/PredIteratorCache.h
    -- Installing: /usr/local/include/llvm/IR/LegacyPassManagers.h
    -- Installing: /usr/local/include/llvm/IR/Value.def
    -- Installing: /usr/local/include/llvm/IR/OperandTraits.h
    -- Installing: /usr/local/include/llvm/IR/Intrinsics.h
    -- Installing: /usr/local/include/llvm/IR/InstrTypes.h
    -- Installing: /usr/local/include/llvm/IR/ConstantFolder.h
    -- Installing: /usr/local/include/llvm/IR/MDBuilder.h
    -- Installing: /usr/local/include/llvm/IR/DiagnosticPrinter.h
    -- Installing: /usr/local/include/llvm/IR/ModuleSlotTracker.h
    -- Installing: /usr/local/include/llvm/IR/InstIterator.h
    -- Installing: /usr/local/include/llvm/IR/Verifier.h
    -- Installing: /usr/local/include/llvm/IR/InstVisitor.h
    -- Installing: /usr/local/include/llvm/IR/Module.h
    -- Installing: /usr/local/include/llvm/IR/Dominators.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsXCore.td
    -- Installing: /usr/local/include/llvm/IR/AutoUpgrade.h
    -- Installing: /usr/local/include/llvm/IR/ConstantRange.h
    -- Installing: /usr/local/include/llvm/IR/IntrinsicsBPF.td
    -- Installing: /usr/local/include/llvm/IR/LegacyPassNameParser.h
    -- Installing: /usr/local/include/llvm/IR/GVMaterializer.h
    -- Installing: /usr/local/include/llvm/IR/NoFolder.h
    -- Installing: /usr/local/include/llvm/PassRegistry.h
    -- Installing: /usr/local/include/llvm/LTO
    -- Installing: /usr/local/include/llvm/LTO/LTOModule.h
    -- Installing: /usr/local/include/llvm/LTO/LTOCodeGenerator.h
    -- Installing: /usr/local/include/llvm/DebugInfo
    -- Installing: /usr/local/include/llvm/DebugInfo/DIContext.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeBaseClass.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeUDT.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDB.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolPublicSymbol.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypePointer.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbol.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBSourceFile.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeFunctionArg.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolExe.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBSession.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIARawSymbol.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIAEnumSourceFiles.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIADataStream.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIAEnumDebugStreams.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIALineNumber.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIASourceFile.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIAEnumSymbols.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIASession.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIAEnumLineNumbers.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/DIA/DIASupport.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolThunk.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/ConcreteSymbolEnumerator.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeFunctionSig.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBContext.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBEnumChildren.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymDumper.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolBlock.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolCompilandDetails.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeTypedef.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolAnnotation.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeCustom.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolCompilandEnv.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolLabel.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBDataStream.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeDimension.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeEnum.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeVTable.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBRawSymbol.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/IPDBLineNumber.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBExtras.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolFuncDebugStart.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeArray.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBTypes.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeVTableShape.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeFriend.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolFunc.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolCompiland.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolCustom.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeManaged.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolFuncDebugEnd.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolUsingNamespace.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolData.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolTypeBuiltin.h
    -- Installing: /usr/local/include/llvm/DebugInfo/PDB/PDBSymbolUnknown.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugRangeList.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFCompileUnit.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugLine.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFUnit.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugAranges.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFFormValue.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugFrame.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugInfoEntry.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugArangeSet.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugLoc.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFTypeUnit.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFSection.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFAbbreviationDeclaration.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFRelocMap.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFAcceleratorTable.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFContext.h
    -- Installing: /usr/local/include/llvm/DebugInfo/DWARF/DWARFDebugAbbrev.h
    -- Installing: /usr/local/include/llvm/InitializePasses.h
    -- Installing: /usr/local/include/llvm/Option
    -- Installing: /usr/local/include/llvm/Option/OptSpecifier.h
    -- Installing: /usr/local/include/llvm/Option/ArgList.h
    -- Installing: /usr/local/include/llvm/Option/OptParser.td
    -- Installing: /usr/local/include/llvm/Option/OptTable.h
    -- Installing: /usr/local/include/llvm/Option/Arg.h
    -- Installing: /usr/local/include/llvm/Option/Option.h
    -- Installing: /usr/local/include/llvm/Object
    -- Installing: /usr/local/include/llvm/Object/ELFYAML.h
    -- Installing: /usr/local/include/llvm/Object/Binary.h
    -- Installing: /usr/local/include/llvm/Object/ELFObjectFile.h
    -- Installing: /usr/local/include/llvm/Object/COFF.h
    -- Installing: /usr/local/include/llvm/Object/COFFImportFile.h
    -- Installing: /usr/local/include/llvm/Object/Error.h
    -- Installing: /usr/local/include/llvm/Object/SymbolSize.h
    -- Installing: /usr/local/include/llvm/Object/MachOUniversal.h
    -- Installing: /usr/local/include/llvm/Object/MachO.h
    -- Installing: /usr/local/include/llvm/Object/StackMapParser.h
    -- Installing: /usr/local/include/llvm/Object/SymbolicFile.h
    -- Installing: /usr/local/include/llvm/Object/RelocVisitor.h
    -- Installing: /usr/local/include/llvm/Object/ELFTypes.h
    -- Installing: /usr/local/include/llvm/Object/ArchiveWriter.h
    -- Installing: /usr/local/include/llvm/Object/Archive.h
    -- Installing: /usr/local/include/llvm/Object/ObjectFile.h
    -- Installing: /usr/local/include/llvm/Object/ELF.h
    -- Installing: /usr/local/include/llvm/Object/IRObjectFile.h
    -- Installing: /usr/local/include/llvm/Object/COFFYAML.h
    -- Installing: /usr/local/include/llvm/ProfileData
    -- Installing: /usr/local/include/llvm/ProfileData/InstrProfWriter.h
    -- Installing: /usr/local/include/llvm/ProfileData/SampleProf.h
    -- Installing: /usr/local/include/llvm/ProfileData/CoverageMappingReader.h
    -- Installing: /usr/local/include/llvm/ProfileData/InstrProfReader.h
    -- Installing: /usr/local/include/llvm/ProfileData/CoverageMapping.h
    -- Installing: /usr/local/include/llvm/ProfileData/CoverageMappingWriter.h
    -- Installing: /usr/local/include/llvm/ProfileData/SampleProfWriter.h
    -- Installing: /usr/local/include/llvm/ProfileData/InstrProf.h
    -- Installing: /usr/local/include/llvm/ProfileData/SampleProfReader.h
    -- Installing: /usr/local/include/llvm/Target
    -- Installing: /usr/local/include/llvm/Target/TargetCallingConv.h
    -- Installing: /usr/local/include/llvm/Target/TargetInstrInfo.h
    -- Installing: /usr/local/include/llvm/Target/TargetLowering.h
    -- Installing: /usr/local/include/llvm/Target/TargetSelectionDAGInfo.h
    -- Installing: /usr/local/include/llvm/Target/TargetSchedule.td
    -- Installing: /usr/local/include/llvm/Target/TargetIntrinsicInfo.h
    -- Installing: /usr/local/include/llvm/Target/Target.td
    -- Installing: /usr/local/include/llvm/Target/TargetFrameLowering.h
    -- Installing: /usr/local/include/llvm/Target/TargetRecip.h
    -- Installing: /usr/local/include/llvm/Target/TargetSubtargetInfo.h
    -- Installing: /usr/local/include/llvm/Target/CostTable.h
    -- Installing: /usr/local/include/llvm/Target/TargetItinerary.td
    -- Installing: /usr/local/include/llvm/Target/TargetCallingConv.td
    -- Installing: /usr/local/include/llvm/Target/TargetSelectionDAG.td
    -- Installing: /usr/local/include/llvm/Target/TargetLoweringObjectFile.h
    -- Installing: /usr/local/include/llvm/Target/TargetOptions.h
    -- Installing: /usr/local/include/llvm/Target/TargetRegisterInfo.h
    -- Installing: /usr/local/include/llvm/Target/TargetMachine.h
    -- Installing: /usr/local/include/llvm/Target/TargetOpcodes.h
    -- Installing: /usr/local/include/llvm/ADT
    -- Installing: /usr/local/include/llvm/ADT/Optional.h
    -- Installing: /usr/local/include/llvm/ADT/PriorityQueue.h
    -- Installing: /usr/local/include/llvm/ADT/MapVector.h
    -- Installing: /usr/local/include/llvm/ADT/SetOperations.h
    -- Installing: /usr/local/include/llvm/ADT/SmallString.h
    -- Installing: /usr/local/include/llvm/ADT/SmallPtrSet.h
    -- Installing: /usr/local/include/llvm/ADT/GraphTraits.h
    -- Installing: /usr/local/include/llvm/ADT/StringSwitch.h
    -- Installing: /usr/local/include/llvm/ADT/PointerUnion.h
    -- Installing: /usr/local/include/llvm/ADT/APSInt.h
    -- Installing: /usr/local/include/llvm/ADT/IntrusiveRefCntPtr.h
    -- Installing: /usr/local/include/llvm/ADT/StringRef.h
    -- Installing: /usr/local/include/llvm/ADT/DenseMapInfo.h
    -- Installing: /usr/local/include/llvm/ADT/SmallBitVector.h
    -- Installing: /usr/local/include/llvm/ADT/DenseSet.h
    -- Installing: /usr/local/include/llvm/ADT/STLExtras.h
    -- Installing: /usr/local/include/llvm/ADT/DAGDeltaAlgorithm.h
    -- Installing: /usr/local/include/llvm/ADT/PointerIntPair.h
    -- Installing: /usr/local/include/llvm/ADT/SCCIterator.h
    -- Installing: /usr/local/include/llvm/ADT/FoldingSet.h
    -- Installing: /usr/local/include/llvm/ADT/StringExtras.h
    -- Installing: /usr/local/include/llvm/ADT/PackedVector.h
    -- Installing: /usr/local/include/llvm/ADT/edit_distance.h
    -- Installing: /usr/local/include/llvm/ADT/EquivalenceClasses.h
    -- Installing: /usr/local/include/llvm/ADT/APFloat.h
    -- Installing: /usr/local/include/llvm/ADT/iterator_range.h
    -- Installing: /usr/local/include/llvm/ADT/ImmutableSet.h
    -- Installing: /usr/local/include/llvm/ADT/None.h
    -- Installing: /usr/local/include/llvm/ADT/SparseMultiSet.h
    -- Installing: /usr/local/include/llvm/ADT/DenseMap.h
    -- Installing: /usr/local/include/llvm/ADT/BitVector.h
    -- Installing: /usr/local/include/llvm/ADT/IntervalMap.h
    -- Installing: /usr/local/include/llvm/ADT/UniqueVector.h
    -- Installing: /usr/local/include/llvm/ADT/TinyPtrVector.h
    -- Installing: /usr/local/include/llvm/ADT/VariadicFunction.h
    -- Installing: /usr/local/include/llvm/ADT/StringMap.h
    -- Installing: /usr/local/include/llvm/ADT/StringSet.h
    -- Installing: /usr/local/include/llvm/ADT/ImmutableList.h
    -- Installing: /usr/local/include/llvm/ADT/Twine.h
    -- Installing: /usr/local/include/llvm/ADT/ScopedHashTable.h
    -- Installing: /usr/local/include/llvm/ADT/SmallVector.h
    -- Installing: /usr/local/include/llvm/ADT/SparseBitVector.h
    -- Installing: /usr/local/include/llvm/ADT/APInt.h
    -- Installing: /usr/local/include/llvm/ADT/SmallSet.h
    -- Installing: /usr/local/include/llvm/ADT/PostOrderIterator.h
    -- Installing: /usr/local/include/llvm/ADT/Triple.h
    -- Installing: /usr/local/include/llvm/ADT/iterator.h
    -- Installing: /usr/local/include/llvm/ADT/SparseSet.h
    -- Installing: /usr/local/include/llvm/ADT/ilist.h
    -- Installing: /usr/local/include/llvm/ADT/ArrayRef.h
    -- Installing: /usr/local/include/llvm/ADT/EpochTracker.h
    -- Installing: /usr/local/include/llvm/ADT/ilist_node.h
    -- Installing: /usr/local/include/llvm/ADT/IndexedMap.h
    -- Installing: /usr/local/include/llvm/ADT/SetVector.h
    -- Installing: /usr/local/include/llvm/ADT/DepthFirstIterator.h
    -- Installing: /usr/local/include/llvm/ADT/ImmutableMap.h
    -- Installing: /usr/local/include/llvm/ADT/Hashing.h
    -- Installing: /usr/local/include/llvm/ADT/IntEqClasses.h
    -- Installing: /usr/local/include/llvm/ADT/Statistic.h
    -- Installing: /usr/local/include/llvm/ADT/DeltaAlgorithm.h
    -- Installing: /usr/local/include/llvm/PassAnalysisSupport.h
    -- Installing: /usr/local/include/llvm/TableGen
    -- Installing: /usr/local/include/llvm/TableGen/SetTheory.h
    -- Installing: /usr/local/include/llvm/TableGen/Error.h
    -- Installing: /usr/local/include/llvm/TableGen/Record.h
    -- Installing: /usr/local/include/llvm/TableGen/StringMatcher.h
    -- Installing: /usr/local/include/llvm/TableGen/TableGenBackend.h
    -- Installing: /usr/local/include/llvm/TableGen/StringToOffsetTable.h
    -- Installing: /usr/local/include/llvm/TableGen/Main.h
    -- Installing: /usr/local/include/llvm/LibDriver
    -- Installing: /usr/local/include/llvm/LibDriver/LibDriver.h
    -- Installing: /usr/local/include/llvm/Support
    -- Installing: /usr/local/include/llvm/Support/Registry.h
    -- Installing: /usr/local/include/llvm/Support/TrailingObjects.h
    -- Installing: /usr/local/include/llvm/Support/GCOV.h
    -- Installing: /usr/local/include/llvm/Support/Allocator.h
    -- Installing: /usr/local/include/llvm/Support/RecyclingAllocator.h
    -- Installing: /usr/local/include/llvm/Support/StreamingMemoryObject.h
    -- Installing: /usr/local/include/llvm/Support/FileSystem.h
    -- Installing: /usr/local/include/llvm/Support/Endian.h
    -- Installing: /usr/local/include/llvm/Support/Dwarf.def
    -- Installing: /usr/local/include/llvm/Support/DOTGraphTraits.h
    -- Installing: /usr/local/include/llvm/Support/PointerLikeTypeTraits.h
    -- Installing: /usr/local/include/llvm/Support/RandomNumberGenerator.h
    -- Installing: /usr/local/include/llvm/Support/CBindingWrapping.h
    -- Installing: /usr/local/include/llvm/Support/Casting.h
    -- Installing: /usr/local/include/llvm/Support/Path.h
    -- Installing: /usr/local/include/llvm/Support/COM.h
    -- Installing: /usr/local/include/llvm/Support/LEB128.h
    -- Installing: /usr/local/include/llvm/Support/Process.h
    -- Installing: /usr/local/include/llvm/Support/Program.h
    -- Installing: /usr/local/include/llvm/Support/ConvertUTF.h
    -- Installing: /usr/local/include/llvm/Support/COFF.h
    -- Installing: /usr/local/include/llvm/Support/Mutex.h
    -- Installing: /usr/local/include/llvm/Support/type_traits.h
    -- Installing: /usr/local/include/llvm/Support/Format.h
    -- Installing: /usr/local/include/llvm/Support/Recycler.h
    -- Installing: /usr/local/include/llvm/Support/TargetRegistry.h
    -- Installing: /usr/local/include/llvm/Support/Atomic.h
    -- Installing: /usr/local/include/llvm/Support/MipsABIFlags.h
    -- Installing: /usr/local/include/llvm/Support/Host.h
    -- Installing: /usr/local/include/llvm/Support/MutexGuard.h
    -- Installing: /usr/local/include/llvm/Support/Dwarf.h
    -- Installing: /usr/local/include/llvm/Support/RegistryParser.h
    -- Installing: /usr/local/include/llvm/Support/FormattedStream.h
    -- Installing: /usr/local/include/llvm/Support/SystemUtils.h
    -- Installing: /usr/local/include/llvm/Support/ARMBuildAttributes.h
    -- Installing: /usr/local/include/llvm/Support/PluginLoader.h
    -- Installing: /usr/local/include/llvm/Support/DataExtractor.h
    -- Installing: /usr/local/include/llvm/Support/TargetParser.h
    -- Installing: /usr/local/include/llvm/Support/Memory.h
    -- Installing: /usr/local/include/llvm/Support/MachO.h
    -- Installing: /usr/local/include/llvm/Support/BlockFrequency.h
    -- Installing: /usr/local/include/llvm/Support/Win64EH.h
    -- Installing: /usr/local/include/llvm/Support/OnDiskHashTable.h
    -- Installing: /usr/local/include/llvm/Support/ThreadLocal.h
    -- Installing: /usr/local/include/llvm/Support/AIXDataTypesFix.h
    -- Installing: /usr/local/include/llvm/Support/ArrayRecycler.h
    -- Installing: /usr/local/include/llvm/Support/ErrorOr.h
    -- Installing: /usr/local/include/llvm/Support/WindowsError.h
    -- Installing: /usr/local/include/llvm/Support/DynamicLibrary.h
    -- Installing: /usr/local/include/llvm/Support/CodeGen.h
    -- Installing: /usr/local/include/llvm/Support/PrettyStackTrace.h
    -- Installing: /usr/local/include/llvm/Support/Debug.h
    -- Installing: /usr/local/include/llvm/Support/raw_ostream.h
    -- Installing: /usr/local/include/llvm/Support/Capacity.h
    -- Installing: /usr/local/include/llvm/Support/ARMWinEH.h
    -- Installing: /usr/local/include/llvm/Support/MD5.h
    -- Installing: /usr/local/include/llvm/Support/SpecialCaseList.h
    -- Installing: /usr/local/include/llvm/Support/UnicodeCharRanges.h
    -- Installing: /usr/local/include/llvm/Support/SourceMgr.h
    -- Installing: /usr/local/include/llvm/Support/raw_os_ostream.h
    -- Installing: /usr/local/include/llvm/Support/SaveAndRestore.h
    -- Installing: /usr/local/include/llvm/Support/Valgrind.h
    -- Installing: /usr/local/include/llvm/Support/LICENSE.TXT
    -- Installing: /usr/local/include/llvm/Support/StringPool.h
    -- Installing: /usr/local/include/llvm/Support/JamCRC.h
    -- Installing: /usr/local/include/llvm/Support/TargetSelect.h
    -- Installing: /usr/local/include/llvm/Support/ARMEHABI.h
    -- Installing: /usr/local/include/llvm/Support/Compiler.h
    -- Installing: /usr/local/include/llvm/Support/LineIterator.h
    -- Installing: /usr/local/include/llvm/Support/thread.h
    -- Installing: /usr/local/include/llvm/Support/LockFileManager.h
    -- Installing: /usr/local/include/llvm/Support/RWMutex.h
    -- Installing: /usr/local/include/llvm/Support/YAMLTraits.h
    -- Installing: /usr/local/include/llvm/Support/Regex.h
    -- Installing: /usr/local/include/llvm/Support/UniqueLock.h
    -- Installing: /usr/local/include/llvm/Support/Compression.h
    -- Installing: /usr/local/include/llvm/Support/Unicode.h
    -- Installing: /usr/local/include/llvm/Support/GenericDomTree.h
    -- Installing: /usr/local/include/llvm/Support/ToolOutputFile.h
    -- Installing: /usr/local/include/llvm/Support/DataStream.h
    -- Installing: /usr/local/include/llvm/Support/Signals.h
    -- Installing: /usr/local/include/llvm/Support/EndianStream.h
    -- Installing: /usr/local/include/llvm/Support/Timer.h
    -- Installing: /usr/local/include/llvm/Support/Solaris.h
    -- Installing: /usr/local/include/llvm/Support/Errc.h
    -- Installing: /usr/local/include/llvm/Support/circular_raw_ostream.h
    -- Installing: /usr/local/include/llvm/Support/AlignOf.h
    -- Installing: /usr/local/include/llvm/Support/Threading.h
    -- Installing: /usr/local/include/llvm/Support/ErrorHandling.h
    -- Installing: /usr/local/include/llvm/Support/BranchProbability.h
    -- Installing: /usr/local/include/llvm/Support/GraphWriter.h
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/Mips.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/PowerPC.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/x86_64.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/Hexagon.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/SystemZ.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/AArch64.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/PowerPC64.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/ARM.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/i386.def
    -- Installing: /usr/local/include/llvm/Support/ELFRelocs/Sparc.def
    -- Installing: /usr/local/include/llvm/Support/MemoryObject.h
    -- Installing: /usr/local/include/llvm/Support/MemoryBuffer.h
    -- Installing: /usr/local/include/llvm/Support/SMLoc.h
    -- Installing: /usr/local/include/llvm/Support/MathExtras.h
    -- Installing: /usr/local/include/llvm/Support/CrashRecoveryContext.h
    -- Installing: /usr/local/include/llvm/Support/ELF.h
    -- Installing: /usr/local/include/llvm/Support/StringSaver.h
    -- Installing: /usr/local/include/llvm/Support/Errno.h
    -- Installing: /usr/local/include/llvm/Support/SwapByteOrder.h
    -- Installing: /usr/local/include/llvm/Support/ManagedStatic.h
    -- Installing: /usr/local/include/llvm/Support/YAMLParser.h
    -- Installing: /usr/local/include/llvm/Support/FileUtilities.h
    -- Installing: /usr/local/include/llvm/Support/Watchdog.h
    -- Installing: /usr/local/include/llvm/Support/Options.h
    -- Installing: /usr/local/include/llvm/Support/GenericDomTreeConstruction.h
    -- Installing: /usr/local/include/llvm/Support/Locale.h
    -- Installing: /usr/local/include/llvm/Support/ScaledNumber.h
    -- Installing: /usr/local/include/llvm/Support/FileOutputBuffer.h
    -- Installing: /usr/local/include/llvm/Support/CommandLine.h
    -- Installing: /usr/local/include/llvm/Support/ARMTargetParser.def
    -- Installing: /usr/local/include/llvm/Support/TimeValue.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine
    -- Installing: /usr/local/include/llvm/ExecutionEngine/OrcMCJITReplacement.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/JITSymbolFlags.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/SectionMemoryManager.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Interpreter.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/ExecutionUtils.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/IndirectionUtils.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/JITSymbol.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/LogicalDylib.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/IRCompileLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/LambdaResolver.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/ObjectTransformLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/LazyEmittingLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/NullResolver.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/IRTransformLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/ObjectLinkingLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/OrcTargetSupport.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/GlobalMappingLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/CompileOnDemandLayer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/Orc/CompileUtils.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/MCJIT.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/ExecutionEngine.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/ObjectCache.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/RTDyldMemoryManager.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/JITEventListener.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/GenericValue.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/OProfileWrapper.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/RuntimeDyld.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/ObjectMemoryBuffer.h
    -- Installing: /usr/local/include/llvm/ExecutionEngine/RuntimeDyldChecker.h
    -- Installing: /usr/local/include/llvm/LinkAllIR.h
    -- Installing: /usr/local/include/llvm/LineEditor
    -- Installing: /usr/local/include/llvm/LineEditor/LineEditor.h
    -- Installing: /usr/local/include/llvm/MC
    -- Installing: /usr/local/include/llvm/MC/MCLinkerOptimizationHint.h
    -- Installing: /usr/local/include/llvm/MC/MCSubtargetInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCRegisterInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCDirectives.h
    -- Installing: /usr/local/include/llvm/MC/MCObjectFileInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCInstrDesc.h
    -- Installing: /usr/local/include/llvm/MC/MCExpr.h
    -- Installing: /usr/local/include/llvm/MC/MCFixup.h
    -- Installing: /usr/local/include/llvm/MC/MCDisassembler.h
    -- Installing: /usr/local/include/llvm/MC/SectionKind.h
    -- Installing: /usr/local/include/llvm/MC/MCCodeEmitter.h
    -- Installing: /usr/local/include/llvm/MC/MachineLocation.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmInfoELF.h
    -- Installing: /usr/local/include/llvm/MC/MCMachObjectWriter.h
    -- Installing: /usr/local/include/llvm/MC/MCSectionCOFF.h
    -- Installing: /usr/local/include/llvm/MC/MCTargetAsmParser.h
    -- Installing: /usr/local/include/llvm/MC/MCSymbolELF.h
    -- Installing: /usr/local/include/llvm/MC/MCRelocationInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmInfoCOFF.h
    -- Installing: /usr/local/include/llvm/MC/SubtargetFeature.h
    -- Installing: /usr/local/include/llvm/MC/MCValue.h
    -- Installing: /usr/local/include/llvm/MC/MCDwarf.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmBackend.h
    -- Installing: /usr/local/include/llvm/MC/MCStreamer.h
    -- Installing: /usr/local/include/llvm/MC/MCObjectWriter.h
    -- Installing: /usr/local/include/llvm/MC/MCSymbolCOFF.h
    -- Installing: /usr/local/include/llvm/MC/MCFixedLenDisassembler.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmLayout.h
    -- Installing: /usr/local/include/llvm/MC/MCInst.h
    -- Installing: /usr/local/include/llvm/MC/MCAnalysis
    -- Installing: /usr/local/include/llvm/MC/StringTableBuilder.h
    -- Installing: /usr/local/include/llvm/MC/MCSectionELF.h
    -- Installing: /usr/local/include/llvm/MC/MCSchedule.h
    -- Installing: /usr/local/include/llvm/MC/MCELFObjectWriter.h
    -- Installing: /usr/local/include/llvm/MC/MCContext.h
    -- Installing: /usr/local/include/llvm/MC/ConstantPools.h
    -- Installing: /usr/local/include/llvm/MC/MCInstPrinter.h
    -- Installing: /usr/local/include/llvm/MC/MCObjectStreamer.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCInstrAnalysis.h
    -- Installing: /usr/local/include/llvm/MC/MCLabel.h
    -- Installing: /usr/local/include/llvm/MC/MCSymbolMachO.h
    -- Installing: /usr/local/include/llvm/MC/YAML.h
    -- Installing: /usr/local/include/llvm/MC/MCAsmInfoDarwin.h
    -- Installing: /usr/local/include/llvm/MC/MCSectionMachO.h
    -- Installing: /usr/local/include/llvm/MC/MCWinCOFFStreamer.h
    -- Installing: /usr/local/include/llvm/MC/MCInstBuilder.h
    -- Installing: /usr/local/include/llvm/MC/MCInstrInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCWinCOFFObjectWriter.h
    -- Installing: /usr/local/include/llvm/MC/MCExternalSymbolizer.h
    -- Installing: /usr/local/include/llvm/MC/MCSymbol.h
    -- Installing: /usr/local/include/llvm/MC/MCSymbolizer.h
    -- Installing: /usr/local/include/llvm/MC/MCSection.h
    -- Installing: /usr/local/include/llvm/MC/MCWinEH.h
    -- Installing: /usr/local/include/llvm/MC/MCInstrItineraries.h
    -- Installing: /usr/local/include/llvm/MC/MCWin64EH.h
    -- Installing: /usr/local/include/llvm/MC/MCFixupKindInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCCodeGenInfo.h
    -- Installing: /usr/local/include/llvm/MC/MCTargetOptionsCommandFlags.h
    -- Installing: /usr/local/include/llvm/MC/MCAssembler.h
    -- Installing: /usr/local/include/llvm/MC/MCParser
    -- Installing: /usr/local/include/llvm/MC/MCParser/MCParsedAsmOperand.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/MCAsmParserExtension.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/AsmLexer.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/MCAsmParserUtils.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/AsmCond.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/MCAsmParser.h
    -- Installing: /usr/local/include/llvm/MC/MCParser/MCAsmLexer.h
    -- Installing: /usr/local/include/llvm/MC/MCTargetOptions.h
    -- Installing: /usr/local/include/llvm/MC/MCELFStreamer.h
    -- Installing: /usr/local/include/llvm/PassInfo.h
    -- Installing: /usr/local/include/llvm/IRReader
    -- Installing: /usr/local/include/llvm/IRReader/IRReader.h
    -- Installing: /usr/local/include/llvm/Pass.h
    -- Installing: /usr/local/include/llvm/Transforms
    -- Installing: /usr/local/include/llvm/Transforms/IPO.h
    -- Installing: /usr/local/include/llvm/Transforms/Vectorize.h
    -- Installing: /usr/local/include/llvm/Transforms/ObjCARC.h
    -- Installing: /usr/local/include/llvm/Transforms/IPO
    -- Installing: /usr/local/include/llvm/Transforms/IPO/PassManagerBuilder.h
    -- Installing: /usr/local/include/llvm/Transforms/IPO/InlinerPass.h
    -- Installing: /usr/local/include/llvm/Transforms/IPO/LowerBitSets.h
    -- Installing: /usr/local/include/llvm/Transforms/InstCombine
    -- Installing: /usr/local/include/llvm/Transforms/InstCombine/InstCombine.h
    -- Installing: /usr/local/include/llvm/Transforms/InstCombine/InstCombineWorklist.h
    -- Installing: /usr/local/include/llvm/Transforms/Instrumentation.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SSAUpdater.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/ValueMapper.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SimplifyIndVar.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/PromoteMemToReg.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SSAUpdaterImpl.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/IntegerDivision.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/BasicBlockUtils.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/GlobalStatus.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/Cloning.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/ModuleUtils.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SplitModule.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/CtorUtils.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/BuildLibCalls.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/UnrollLoop.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/CodeExtractor.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/ASanStackFrameLayout.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SymbolRewriter.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/SimplifyLibCalls.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/Local.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/LoopUtils.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/UnifyFunctionExitNodes.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/BypassSlowDivision.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/CmpInstAnalysis.h
    -- Installing: /usr/local/include/llvm/Transforms/Utils/LoopVersioning.h
    -- Installing: /usr/local/include/llvm/Transforms/Scalar
    -- Installing: /usr/local/include/llvm/Transforms/Scalar/EarlyCSE.h
    -- Installing: /usr/local/include/llvm/Transforms/Scalar/SimplifyCFG.h
    -- Installing: /usr/local/include/llvm/Transforms/Scalar/SROA.h
    -- Installing: /usr/local/include/llvm/Transforms/Scalar/LowerExpectIntrinsic.h
    -- Installing: /usr/local/include/llvm/Transforms/Scalar.h
    -- Installing: /usr/local/include/llvm/PassSupport.h
    -- Installing: /usr/local/include/llvm/Linker
    -- Installing: /usr/local/include/llvm/Linker/Linker.h
    -- Installing: /usr/local/include/llvm-c
    -- Installing: /usr/local/include/llvm-c/Analysis.h
    -- Installing: /usr/local/include/llvm-c/BitWriter.h
    -- Installing: /usr/local/include/llvm-c/ExecutionEngine.h
    -- Installing: /usr/local/include/llvm-c/Object.h
    -- Installing: /usr/local/include/llvm-c/BitReader.h
    -- Installing: /usr/local/include/llvm-c/Linker.h
    -- Installing: /usr/local/include/llvm-c/Core.h
    -- Installing: /usr/local/include/llvm-c/LinkTimeOptimizer.h
    -- Installing: /usr/local/include/llvm-c/Target.h
    -- Installing: /usr/local/include/llvm-c/Support.h
    -- Installing: /usr/local/include/llvm-c/lto.h
    -- Installing: /usr/local/include/llvm-c/TargetMachine.h
    -- Installing: /usr/local/include/llvm-c/IRReader.h
    -- Installing: /usr/local/include/llvm-c/Transforms
    -- Installing: /usr/local/include/llvm-c/Transforms/PassManagerBuilder.h
    -- Installing: /usr/local/include/llvm-c/Transforms/IPO.h
    -- Installing: /usr/local/include/llvm-c/Transforms/Vectorize.h
    -- Installing: /usr/local/include/llvm-c/Transforms/Scalar.h
    -- Installing: /usr/local/include/llvm-c/Initialization.h
    -- Installing: /usr/local/include/llvm-c/Disassembler.h
    -- Installing: /usr/local/include/llvm
    -- Installing: /usr/local/include/llvm/Config
    -- Installing: /usr/local/include/llvm/Config/Disassemblers.def
    -- Installing: /usr/local/include/llvm/Config/Targets.def
    -- Installing: /usr/local/include/llvm/Config/AsmPrinters.def
    -- Installing: /usr/local/include/llvm/Config/AsmParsers.def
    -- Installing: /usr/local/include/llvm/Config/llvm-config.h
    -- Installing: /usr/local/include/llvm/IR
    -- Installing: /usr/local/include/llvm/IR/Intrinsics.gen
    -- Installing: /usr/local/include/llvm/Support
    -- Installing: /usr/local/include/llvm/Support/DataTypes.h
    -- Installing: /usr/local/lib/libLLVMSupport.a
    -- Installing: /usr/local/lib/libLLVMTableGen.a
    -- Installing: /usr/local/bin/llvm-tblgen
    -- Installing: /usr/local/lib/libLLVMCore.a
    -- Installing: /usr/local/lib/libLLVMIRReader.a
    -- Installing: /usr/local/lib/libLLVMCodeGen.a
    -- Installing: /usr/local/lib/libLLVMSelectionDAG.a
    -- Installing: /usr/local/lib/libLLVMAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMMIRParser.a
    -- Installing: /usr/local/lib/libLLVMBitReader.a
    -- Installing: /usr/local/lib/libLLVMBitWriter.a
    -- Installing: /usr/local/lib/libLLVMTransformUtils.a
    -- Installing: /usr/local/lib/libLLVMInstrumentation.a
    -- Installing: /usr/local/lib/libLLVMInstCombine.a
    -- Installing: /usr/local/lib/libLLVMScalarOpts.a
    -- Installing: /usr/local/lib/libLLVMipo.a
    -- Installing: /usr/local/lib/libLLVMVectorize.a
    -- Installing: /usr/local/lib/LLVMHello.so
    -- Installing: /usr/local/lib/libLLVMObjCARCOpts.a
    -- Installing: /usr/local/lib/libLLVMLinker.a
    -- Installing: /usr/local/lib/libLLVMAnalysis.a
    -- Installing: /usr/local/lib/libLLVMLTO.a
    -- Installing: /usr/local/lib/libLLVMMC.a
    -- Installing: /usr/local/lib/libLLVMMCParser.a
    -- Installing: /usr/local/lib/libLLVMMCDisassembler.a
    -- Installing: /usr/local/lib/libLLVMObject.a
    -- Installing: /usr/local/lib/libLLVMOption.a
    -- Installing: /usr/local/lib/libLLVMDebugInfoDWARF.a
    -- Installing: /usr/local/lib/libLLVMDebugInfoPDB.a
    -- Installing: /usr/local/lib/libLLVMExecutionEngine.a
    -- Installing: /usr/local/lib/libLLVMInterpreter.a
    -- Installing: /usr/local/lib/libLLVMMCJIT.a
    -- Installing: /usr/local/lib/libLLVMOrcJIT.a
    -- Installing: /usr/local/lib/libLLVMRuntimeDyld.a
    -- Installing: /usr/local/lib/libLLVMTarget.a
    -- Installing: /usr/local/lib/libLLVMAArch64CodeGen.a
    -- Installing: /usr/local/lib/libLLVMAArch64Info.a
    -- Installing: /usr/local/lib/libLLVMAArch64AsmParser.a
    -- Installing: /usr/local/lib/libLLVMAArch64Disassembler.a
    -- Installing: /usr/local/lib/libLLVMAArch64AsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMAArch64Desc.a
    -- Installing: /usr/local/lib/libLLVMAArch64Utils.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUCodeGen.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUAsmParser.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUInfo.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUDesc.a
    -- Installing: /usr/local/lib/libLLVMAMDGPUUtils.a
    -- Installing: /usr/local/lib/libLLVMARMCodeGen.a
    -- Installing: /usr/local/lib/libLLVMARMInfo.a
    -- Installing: /usr/local/lib/libLLVMARMAsmParser.a
    -- Installing: /usr/local/lib/libLLVMARMDisassembler.a
    -- Installing: /usr/local/lib/libLLVMARMAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMARMDesc.a
    -- Installing: /usr/local/lib/libLLVMBPFCodeGen.a
    -- Installing: /usr/local/lib/libLLVMBPFAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMBPFInfo.a
    -- Installing: /usr/local/lib/libLLVMBPFDesc.a
    -- Installing: /usr/local/lib/libLLVMCppBackendCodeGen.a
    -- Installing: /usr/local/lib/libLLVMCppBackendInfo.a
    -- Installing: /usr/local/lib/libLLVMHexagonCodeGen.a
    -- Installing: /usr/local/lib/libLLVMHexagonInfo.a
    -- Installing: /usr/local/lib/libLLVMHexagonDesc.a
    -- Installing: /usr/local/lib/libLLVMHexagonDisassembler.a
    -- Installing: /usr/local/lib/libLLVMMipsCodeGen.a
    -- Installing: /usr/local/lib/libLLVMMipsAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMMipsDisassembler.a
    -- Installing: /usr/local/lib/libLLVMMipsInfo.a
    -- Installing: /usr/local/lib/libLLVMMipsDesc.a
    -- Installing: /usr/local/lib/libLLVMMipsAsmParser.a
    -- Installing: /usr/local/lib/libLLVMMSP430CodeGen.a
    -- Installing: /usr/local/lib/libLLVMMSP430AsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMMSP430Info.a
    -- Installing: /usr/local/lib/libLLVMMSP430Desc.a
    -- Installing: /usr/local/lib/libLLVMNVPTXCodeGen.a
    -- Installing: /usr/local/lib/libLLVMNVPTXInfo.a
    -- Installing: /usr/local/lib/libLLVMNVPTXAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMNVPTXDesc.a
    -- Installing: /usr/local/lib/libLLVMPowerPCCodeGen.a
    -- Installing: /usr/local/lib/libLLVMPowerPCAsmParser.a
    -- Installing: /usr/local/lib/libLLVMPowerPCDisassembler.a
    -- Installing: /usr/local/lib/libLLVMPowerPCAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMPowerPCInfo.a
    -- Installing: /usr/local/lib/libLLVMPowerPCDesc.a
    -- Installing: /usr/local/lib/libLLVMSparcCodeGen.a
    -- Installing: /usr/local/lib/libLLVMSparcInfo.a
    -- Installing: /usr/local/lib/libLLVMSparcDesc.a
    -- Installing: /usr/local/lib/libLLVMSparcAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMSparcAsmParser.a
    -- Installing: /usr/local/lib/libLLVMSparcDisassembler.a
    -- Installing: /usr/local/lib/libLLVMSystemZCodeGen.a
    -- Installing: /usr/local/lib/libLLVMSystemZAsmParser.a
    -- Installing: /usr/local/lib/libLLVMSystemZDisassembler.a
    -- Installing: /usr/local/lib/libLLVMSystemZAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMSystemZInfo.a
    -- Installing: /usr/local/lib/libLLVMSystemZDesc.a
    -- Installing: /usr/local/lib/libLLVMX86CodeGen.a
    -- Installing: /usr/local/lib/libLLVMX86AsmParser.a
    -- Installing: /usr/local/lib/libLLVMX86Disassembler.a
    -- Installing: /usr/local/lib/libLLVMX86AsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMX86Desc.a
    -- Installing: /usr/local/lib/libLLVMX86Info.a
    -- Installing: /usr/local/lib/libLLVMX86Utils.a
    -- Installing: /usr/local/lib/libLLVMXCoreCodeGen.a
    -- Installing: /usr/local/lib/libLLVMXCoreDisassembler.a
    -- Installing: /usr/local/lib/libLLVMXCoreAsmPrinter.a
    -- Installing: /usr/local/lib/libLLVMXCoreInfo.a
    -- Installing: /usr/local/lib/libLLVMXCoreDesc.a
    -- Installing: /usr/local/lib/libLLVMAsmParser.a
    -- Installing: /usr/local/lib/libLLVMLineEditor.a
    -- Installing: /usr/local/lib/libLLVMProfileData.a
    -- Installing: /usr/local/lib/libLLVMPasses.a
    -- Installing: /usr/local/lib/libLLVMLibDriver.a
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/allocator_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/asan_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/common_interface_defs.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/coverage_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/dfsan_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/linux_syscall_hooks.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/lsan_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/msan_interface.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/sanitizer/tsan_interface_atomic.h
    -- Installing: /usr/local/lib/clang/3.8.0/cfi_blacklist.txt
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.lsan-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone_cxx-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone_cxx-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.ubsan_standalone_cxx-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan_cxx-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan_cxx-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-preinit-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-preinit-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-x86_64.so
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan_cxx-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.asan-i386.so
    -- Installing: /usr/local/lib/clang/3.8.0/asan_blacklist.txt
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.builtins-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.builtins-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.dfsan-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.dfsan-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/dfsan_abilist.txt
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.msan-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.msan_cxx-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.msan-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.msan_cxx-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/msan_blacklist.txt
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.profile-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.profile-i386.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.tsan-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.tsan_cxx-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.tsan-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.tsan_cxx-x86_64.a.syms
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.dd-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.dyndd-x86_64.so
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.safestack-x86_64.a
    -- Installing: /usr/local/lib/clang/3.8.0/lib/linux/libclang_rt.safestack-i386.a
    -- Installing: /usr/local/lib/libLTO.so.3.8.0svn
    -- Installing: /usr/local/lib/libLTO.so.3.8
    -- Installing: /usr/local/lib/libLTO.so
    -- Installing: /usr/local/include/llvm-c/lto.h
    -- Installing: /usr/local/include/clang
    -- Installing: /usr/local/include/clang/CodeGen
    -- Installing: /usr/local/include/clang/CodeGen/ObjectFilePCHContainerOperations.h
    -- Installing: /usr/local/include/clang/CodeGen/CodeGenABITypes.h
    -- Installing: /usr/local/include/clang/CodeGen/BackendUtil.h
    -- Installing: /usr/local/include/clang/CodeGen/CodeGenAction.h
    -- Installing: /usr/local/include/clang/CodeGen/CGFunctionInfo.h
    -- Installing: /usr/local/include/clang/CodeGen/ModuleBuilder.h
    -- Installing: /usr/local/include/clang/Analysis
    -- Installing: /usr/local/include/clang/Analysis/ProgramPoint.h
    -- Installing: /usr/local/include/clang/Analysis/CallGraph.h
    -- Installing: /usr/local/include/clang/Analysis/CodeInjector.h
    -- Installing: /usr/local/include/clang/Analysis/DomainSpecific
    -- Installing: /usr/local/include/clang/Analysis/DomainSpecific/ObjCNoReturn.h
    -- Installing: /usr/local/include/clang/Analysis/DomainSpecific/CocoaConventions.h
    -- Installing: /usr/local/include/clang/Analysis/CFG.h
    -- Installing: /usr/local/include/clang/Analysis/CFGStmtMap.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyTIL.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/LiveVariables.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/PostOrderCFGView.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyTraverse.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/UninitializedValues.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/CFGReachabilityAnalysis.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/FormatString.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafety.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyOps.def
    -- Installing: /usr/local/include/clang/Analysis/Analyses/Consumed.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyUtil.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ReachableCode.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/Dominators.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyLogical.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/ThreadSafetyCommon.h
    -- Installing: /usr/local/include/clang/Analysis/Analyses/PseudoConstantAnalysis.h
    -- Installing: /usr/local/include/clang/Analysis/Support
    -- Installing: /usr/local/include/clang/Analysis/Support/BumpVector.h
    -- Installing: /usr/local/include/clang/Analysis/FlowSensitive
    -- Installing: /usr/local/include/clang/Analysis/FlowSensitive/DataflowValues.h
    -- Installing: /usr/local/include/clang/Analysis/AnalysisDiagnostic.h
    -- Installing: /usr/local/include/clang/Analysis/AnalysisContext.h
    -- Installing: /usr/local/include/clang/Frontend
    -- Installing: /usr/local/include/clang/Frontend/ASTConsumers.h
    -- Installing: /usr/local/include/clang/Frontend/ChainedDiagnosticConsumer.h
    -- Installing: /usr/local/include/clang/Frontend/CompilerInstance.h
    -- Installing: /usr/local/include/clang/Frontend/PreprocessorOutputOptions.h
    -- Installing: /usr/local/include/clang/Frontend/LogDiagnosticPrinter.h
    -- Installing: /usr/local/include/clang/Frontend/CodeGenOptions.def
    -- Installing: /usr/local/include/clang/Frontend/Utils.h
    -- Installing: /usr/local/include/clang/Frontend/VerifyDiagnosticConsumer.h
    -- Installing: /usr/local/include/clang/Frontend/SerializedDiagnosticPrinter.h
    -- Installing: /usr/local/include/clang/Frontend/FrontendDiagnostic.h
    -- Installing: /usr/local/include/clang/Frontend/LangStandard.h
    -- Installing: /usr/local/include/clang/Frontend/CompilerInvocation.h
    -- Installing: /usr/local/include/clang/Frontend/MultiplexConsumer.h
    -- Installing: /usr/local/include/clang/Frontend/MigratorOptions.h
    -- Installing: /usr/local/include/clang/Frontend/FrontendActions.h
    -- Installing: /usr/local/include/clang/Frontend/FrontendAction.h
    -- Installing: /usr/local/include/clang/Frontend/ASTUnit.h
    -- Installing: /usr/local/include/clang/Frontend/DiagnosticRenderer.h
    -- Installing: /usr/local/include/clang/Frontend/TextDiagnosticPrinter.h
    -- Installing: /usr/local/include/clang/Frontend/CommandLineSourceLoc.h
    -- Installing: /usr/local/include/clang/Frontend/CodeGenOptions.h
    -- Installing: /usr/local/include/clang/Frontend/LangStandards.def
    -- Installing: /usr/local/include/clang/Frontend/PCHContainerOperations.h
    -- Installing: /usr/local/include/clang/Frontend/SerializedDiagnosticReader.h
    -- Installing: /usr/local/include/clang/Frontend/SerializedDiagnostics.h
    -- Installing: /usr/local/include/clang/Frontend/DependencyOutputOptions.h
    -- Installing: /usr/local/include/clang/Frontend/TextDiagnostic.h
    -- Installing: /usr/local/include/clang/Frontend/LayoutOverrideSource.h
    -- Installing: /usr/local/include/clang/Frontend/FrontendPluginRegistry.h
    -- Installing: /usr/local/include/clang/Frontend/FrontendOptions.h
    -- Installing: /usr/local/include/clang/Frontend/TextDiagnosticBuffer.h
    -- Installing: /usr/local/include/clang/AST
    -- Installing: /usr/local/include/clang/AST/RecordLayout.h
    -- Installing: /usr/local/include/clang/AST/StmtIterator.h
    -- Installing: /usr/local/include/clang/AST/CommentBriefParser.h
    -- Installing: /usr/local/include/clang/AST/TemplateBase.h
    -- Installing: /usr/local/include/clang/AST/Mangle.h
    -- Installing: /usr/local/include/clang/AST/LambdaCapture.h
    -- Installing: /usr/local/include/clang/AST/DeclGroup.h
    -- Installing: /usr/local/include/clang/AST/DeclFriend.h
    -- Installing: /usr/local/include/clang/AST/CommentSema.h
    -- Installing: /usr/local/include/clang/AST/DeclBase.h
    -- Installing: /usr/local/include/clang/AST/RecursiveASTVisitor.h
    -- Installing: /usr/local/include/clang/AST/EvaluatedExprVisitor.h
    -- Installing: /usr/local/include/clang/AST/TypeLoc.h
    -- Installing: /usr/local/include/clang/AST/DataRecursiveASTVisitor.h
    -- Installing: /usr/local/include/clang/AST/StmtVisitor.h
    -- Installing: /usr/local/include/clang/AST/DeclVisitor.h
    -- Installing: /usr/local/include/clang/AST/NSAPI.h
    -- Installing: /usr/local/include/clang/AST/GlobalDecl.h
    -- Installing: /usr/local/include/clang/AST/BaseSubobject.h
    -- Installing: /usr/local/include/clang/AST/ASTDiagnostic.h
    -- Installing: /usr/local/include/clang/AST/StmtOpenMP.h
    -- Installing: /usr/local/include/clang/AST/ASTLambda.h
    -- Installing: /usr/local/include/clang/AST/Expr.h
    -- Installing: /usr/local/include/clang/AST/DeclCXX.h
    -- Installing: /usr/local/include/clang/AST/CommentCommandTraits.h
    -- Installing: /usr/local/include/clang/AST/ParentMap.h
    -- Installing: /usr/local/include/clang/AST/DeclAccessPair.h
    -- Installing: /usr/local/include/clang/AST/OpenMPClause.h
    -- Installing: /usr/local/include/clang/AST/StmtCXX.h
    -- Installing: /usr/local/include/clang/AST/CanonicalType.h
    -- Installing: /usr/local/include/clang/AST/ASTConsumer.h
    -- Installing: /usr/local/include/clang/AST/UnresolvedSet.h
    -- Installing: /usr/local/include/clang/AST/Comment.h
    -- Installing: /usr/local/include/clang/AST/ASTTypeTraits.h
    -- Installing: /usr/local/include/clang/AST/ASTContext.h
    -- Installing: /usr/local/include/clang/AST/CommentVisitor.h
    -- Installing: /usr/local/include/clang/AST/ExprCXX.h
    -- Installing: /usr/local/include/clang/AST/CommentDiagnostic.h
    -- Installing: /usr/local/include/clang/AST/DependentDiagnostic.h
    -- Installing: /usr/local/include/clang/AST/ASTImporter.h
    -- Installing: /usr/local/include/clang/AST/DeclLookups.h
    -- Installing: /usr/local/include/clang/AST/TypeLocVisitor.h
    -- Installing: /usr/local/include/clang/AST/ExprOpenMP.h
    -- Installing: /usr/local/include/clang/AST/DeclContextInternals.h
    -- Installing: /usr/local/include/clang/AST/NestedNameSpecifier.h
    -- Installing: /usr/local/include/clang/AST/RawCommentList.h
    -- Installing: /usr/local/include/clang/AST/TypeVisitor.h
    -- Installing: /usr/local/include/clang/AST/DeclObjC.h
    -- Installing: /usr/local/include/clang/AST/DeclarationName.h
    -- Installing: /usr/local/include/clang/AST/OperationKinds.h
    -- Installing: /usr/local/include/clang/AST/ExprObjC.h
    -- Installing: /usr/local/include/clang/AST/PrettyPrinter.h
    -- Installing: /usr/local/include/clang/AST/ASTMutationListener.h
    -- Installing: /usr/local/include/clang/AST/CommentParser.h
    -- Installing: /usr/local/include/clang/AST/VTTBuilder.h
    -- Installing: /usr/local/include/clang/AST/Stmt.h
    -- Installing: /usr/local/include/clang/AST/Redeclarable.h
    -- Installing: /usr/local/include/clang/AST/AttrIterator.h
    -- Installing: /usr/local/include/clang/AST/TemplateName.h
    -- Installing: /usr/local/include/clang/AST/StmtObjC.h
    -- Installing: /usr/local/include/clang/AST/StmtGraphTraits.h
    -- Installing: /usr/local/include/clang/AST/ASTVector.h
    -- Installing: /usr/local/include/clang/AST/VTableBuilder.h
    -- Installing: /usr/local/include/clang/AST/BuiltinTypes.def
    -- Installing: /usr/local/include/clang/AST/Type.h
    -- Installing: /usr/local/include/clang/AST/CommentLexer.h
    -- Installing: /usr/local/include/clang/AST/DeclTemplate.h
    -- Installing: /usr/local/include/clang/AST/SelectorLocationsKind.h
    -- Installing: /usr/local/include/clang/AST/TypeNodes.def
    -- Installing: /usr/local/include/clang/AST/CXXInheritance.h
    -- Installing: /usr/local/include/clang/AST/APValue.h
    -- Installing: /usr/local/include/clang/AST/ASTUnresolvedSet.h
    -- Installing: /usr/local/include/clang/AST/DeclOpenMP.h
    -- Installing: /usr/local/include/clang/AST/Attr.h
    -- Installing: /usr/local/include/clang/AST/AST.h
    -- Installing: /usr/local/include/clang/AST/ASTFwd.h
    -- Installing: /usr/local/include/clang/AST/ExternalASTSource.h
    -- Installing: /usr/local/include/clang/AST/MangleNumberingContext.h
    -- Installing: /usr/local/include/clang/AST/TypeLocNodes.def
    -- Installing: /usr/local/include/clang/AST/TypeOrdering.h
    -- Installing: /usr/local/include/clang/AST/Decl.h
    -- Installing: /usr/local/include/clang/AST/CharUnits.h
    -- Installing: /usr/local/include/clang/Edit
    -- Installing: /usr/local/include/clang/Edit/FileOffset.h
    -- Installing: /usr/local/include/clang/Edit/EditedSource.h
    -- Installing: /usr/local/include/clang/Edit/EditsReceiver.h
    -- Installing: /usr/local/include/clang/Edit/Commit.h
    -- Installing: /usr/local/include/clang/Edit/Rewriters.h
    -- Installing: /usr/local/include/clang/Basic
    -- Installing: /usr/local/include/clang/Basic/VersionTuple.h
    -- Installing: /usr/local/include/clang/Basic/Linkage.h
    -- Installing: /usr/local/include/clang/Basic/ExceptionSpecificationType.h
    -- Installing: /usr/local/include/clang/Basic/TargetBuiltins.h
    -- Installing: /usr/local/include/clang/Basic/AllDiagnostics.h
    -- Installing: /usr/local/include/clang/Basic/ExpressionTraits.h
    -- Installing: /usr/local/include/clang/Basic/Diagnostic.h
    -- Installing: /usr/local/include/clang/Basic/PlistSupport.h
    -- Installing: /usr/local/include/clang/Basic/OpenMPKinds.h
    -- Installing: /usr/local/include/clang/Basic/TokenKinds.h
    -- Installing: /usr/local/include/clang/Basic/ABI.h
    -- Installing: /usr/local/include/clang/Basic/LangOptions.def
    -- Installing: /usr/local/include/clang/Basic/DiagnosticIDs.h
    -- Installing: /usr/local/include/clang/Basic/Sanitizers.h
    -- Installing: /usr/local/include/clang/Basic/TokenKinds.def
    -- Installing: /usr/local/include/clang/Basic/BuiltinsNVPTX.def
    -- Installing: /usr/local/include/clang/Basic/BuiltinsX86.def
    -- Installing: /usr/local/include/clang/Basic/BuiltinsSystemZ.def
    -- Installing: /usr/local/include/clang/Basic/VirtualFileSystem.h
    -- Installing: /usr/local/include/clang/Basic/SourceManagerInternals.h
    -- Installing: /usr/local/include/clang/Basic/TemplateKinds.h
    -- Installing: /usr/local/include/clang/Basic/DiagnosticOptions.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsHexagon.def
    -- Installing: /usr/local/include/clang/Basic/BuiltinsARM.def
    -- Installing: /usr/local/include/clang/Basic/Specifiers.h
    -- Installing: /usr/local/include/clang/Basic/PrettyStackTrace.h
    -- Installing: /usr/local/include/clang/Basic/Visibility.h
    -- Installing: /usr/local/include/clang/Basic/CharInfo.h
    -- Installing: /usr/local/include/clang/Basic/AddressSpaces.h
    -- Installing: /usr/local/include/clang/Basic/SanitizerBlacklist.h
    -- Installing: /usr/local/include/clang/Basic/Lambda.h
    -- Installing: /usr/local/include/clang/Basic/ObjCRuntime.h
    -- Installing: /usr/local/include/clang/Basic/Builtins.h
    -- Installing: /usr/local/include/clang/Basic/SourceManager.h
    -- Installing: /usr/local/include/clang/Basic/PartialDiagnostic.h
    -- Installing: /usr/local/include/clang/Basic/FileSystemStatCache.h
    -- Installing: /usr/local/include/clang/Basic/LangOptions.h
    -- Installing: /usr/local/include/clang/Basic/OpenMPKinds.def
    -- Installing: /usr/local/include/clang/Basic/OperatorKinds.h
    -- Installing: /usr/local/include/clang/Basic/LLVM.h
    -- Installing: /usr/local/include/clang/Basic/TargetCXXABI.h
    -- Installing: /usr/local/include/clang/Basic/SourceLocation.h
    -- Installing: /usr/local/include/clang/Basic/OperatorPrecedence.h
    -- Installing: /usr/local/include/clang/Basic/Attributes.h
    -- Installing: /usr/local/include/clang/Basic/TargetInfo.h
    -- Installing: /usr/local/include/clang/Basic/DiagnosticOptions.def
    -- Installing: /usr/local/include/clang/Basic/BuiltinsWebAssembly.def
    -- Installing: /usr/local/include/clang/Basic/Builtins.def
    -- Installing: /usr/local/include/clang/Basic/TargetOptions.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsPPC.def
    -- Installing: /usr/local/include/clang/Basic/CommentOptions.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsLe64.def
    -- Installing: /usr/local/include/clang/Basic/OpenCLExtensions.def
    -- Installing: /usr/local/include/clang/Basic/CapturedStmt.h
    -- Installing: /usr/local/include/clang/Basic/Version.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsNEON.def
    -- Installing: /usr/local/include/clang/Basic/DiagnosticCategories.h
    -- Installing: /usr/local/include/clang/Basic/MacroBuilder.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsAMDGPU.def
    -- Installing: /usr/local/include/clang/Basic/OperatorKinds.def
    -- Installing: /usr/local/include/clang/Basic/Sanitizers.def
    -- Installing: /usr/local/include/clang/Basic/FileSystemOptions.h
    -- Installing: /usr/local/include/clang/Basic/IdentifierTable.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsAArch64.def
    -- Installing: /usr/local/include/clang/Basic/Module.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsXCore.def
    -- Installing: /usr/local/include/clang/Basic/TypeTraits.h
    -- Installing: /usr/local/include/clang/Basic/BuiltinsMips.def
    -- Installing: /usr/local/include/clang/Basic/AttrKinds.h
    -- Installing: /usr/local/include/clang/Basic/FileManager.h
    -- Installing: /usr/local/include/clang/Config
    -- Installing: /usr/local/include/clang/Format
    -- Installing: /usr/local/include/clang/Format/Format.h
    -- Installing: /usr/local/include/clang/Index
    -- Installing: /usr/local/include/clang/Index/USRGeneration.h
    -- Installing: /usr/local/include/clang/Index/CommentToXML.h
    -- Installing: /usr/local/include/clang/Parse
    -- Installing: /usr/local/include/clang/Parse/ParseDiagnostic.h
    -- Installing: /usr/local/include/clang/Parse/ParseAST.h
    -- Installing: /usr/local/include/clang/Parse/Parser.h
    -- Installing: /usr/local/include/clang/Driver
    -- Installing: /usr/local/include/clang/Driver/Types.def
    -- Installing: /usr/local/include/clang/Driver/Phases.h
    -- Installing: /usr/local/include/clang/Driver/Tool.h
    -- Installing: /usr/local/include/clang/Driver/Multilib.h
    -- Installing: /usr/local/include/clang/Driver/SanitizerArgs.h
    -- Installing: /usr/local/include/clang/Driver/ToolChain.h
    -- Installing: /usr/local/include/clang/Driver/Types.h
    -- Installing: /usr/local/include/clang/Driver/Driver.h
    -- Installing: /usr/local/include/clang/Driver/Compilation.h
    -- Installing: /usr/local/include/clang/Driver/Util.h
    -- Installing: /usr/local/include/clang/Driver/DriverDiagnostic.h
    -- Installing: /usr/local/include/clang/Driver/Action.h
    -- Installing: /usr/local/include/clang/Driver/Job.h
    -- Installing: /usr/local/include/clang/Driver/Options.h
    -- Installing: /usr/local/include/clang/ASTMatchers
    -- Installing: /usr/local/include/clang/ASTMatchers/ASTMatchersMacros.h
    -- Installing: /usr/local/include/clang/ASTMatchers/ASTMatchFinder.h
    -- Installing: /usr/local/include/clang/ASTMatchers/ASTMatchers.h
    -- Installing: /usr/local/include/clang/ASTMatchers/ASTMatchersInternal.h
    -- Installing: /usr/local/include/clang/ASTMatchers/Dynamic
    -- Installing: /usr/local/include/clang/ASTMatchers/Dynamic/Registry.h
    -- Installing: /usr/local/include/clang/ASTMatchers/Dynamic/Diagnostics.h
    -- Installing: /usr/local/include/clang/ASTMatchers/Dynamic/VariantValue.h
    -- Installing: /usr/local/include/clang/ASTMatchers/Dynamic/Parser.h
    -- Installing: /usr/local/include/clang/FrontendTool
    -- Installing: /usr/local/include/clang/FrontendTool/Utils.h
    -- Installing: /usr/local/include/clang/Rewrite
    -- Installing: /usr/local/include/clang/Rewrite/Frontend
    -- Installing: /usr/local/include/clang/Rewrite/Frontend/ASTConsumers.h
    -- Installing: /usr/local/include/clang/Rewrite/Frontend/FixItRewriter.h
    -- Installing: /usr/local/include/clang/Rewrite/Frontend/FrontendActions.h
    -- Installing: /usr/local/include/clang/Rewrite/Frontend/Rewriters.h
    -- Installing: /usr/local/include/clang/Rewrite/Core
    -- Installing: /usr/local/include/clang/Rewrite/Core/RewriteBuffer.h
    -- Installing: /usr/local/include/clang/Rewrite/Core/RewriteRope.h
    -- Installing: /usr/local/include/clang/Rewrite/Core/TokenRewriter.h
    -- Installing: /usr/local/include/clang/Rewrite/Core/DeltaTree.h
    -- Installing: /usr/local/include/clang/Rewrite/Core/HTMLRewrite.h
    -- Installing: /usr/local/include/clang/Rewrite/Core/Rewriter.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Frontend
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Frontend/ModelConsumer.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Frontend/FrontendActions.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Frontend/CheckerRegistration.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Frontend/AnalysisConsumer.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Checkers
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Checkers/LocalCheckers.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Checkers/ClangCheckers.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Checkers/ObjCRetainCount.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter/PathDiagnostic.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter/BugReporter.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter/BugReporterVisitor.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter/BugType.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/BugReporter/CommonBugCategories.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/CheckerOptInfo.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/CheckerRegistry.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathDiagnosticConsumers.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/Analyses.def
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/CheckerManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/CheckerHelpers.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/Store.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ProgramState.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/SummaryManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/CheckerContext.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/APSIntType.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ConstraintManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/DynamicTypeInfo.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ProgramStateTrait.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/AnalysisManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/WorkList.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/TaintTag.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ProgramState_Fwd.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/SValBuilder.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/SubEngine.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/Environment.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/StoreRef.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/SVals.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/MemRegion.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/FunctionSummary.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ExplodedGraph.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/ExprEngine.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/DynamicTypeMap.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/BasicValueFactory.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/CallEvent.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/CoreEngine.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/TaintManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/BlockCounter.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/PathSensitive/SymbolManager.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/AnalyzerOptions.h
    -- Installing: /usr/local/include/clang/StaticAnalyzer/Core/Checker.h
    -- Installing: /usr/local/include/clang/Serialization
    -- Installing: /usr/local/include/clang/Serialization/ASTDeserializationListener.h
    -- Installing: /usr/local/include/clang/Serialization/ASTBitCodes.h
    -- Installing: /usr/local/include/clang/Serialization/ASTReader.h
    -- Installing: /usr/local/include/clang/Serialization/ContinuousRangeMap.h
    -- Installing: /usr/local/include/clang/Serialization/SerializationDiagnostic.h
    -- Installing: /usr/local/include/clang/Serialization/ASTWriter.h
    -- Installing: /usr/local/include/clang/Serialization/ModuleManager.h
    -- Installing: /usr/local/include/clang/Serialization/Module.h
    -- Installing: /usr/local/include/clang/Serialization/GlobalModuleIndex.h
    -- Installing: /usr/local/include/clang/Sema
    -- Installing: /usr/local/include/clang/Sema/SemaLambda.h
    -- Installing: /usr/local/include/clang/Sema/Designator.h
    -- Installing: /usr/local/include/clang/Sema/CXXFieldCollector.h
    -- Installing: /usr/local/include/clang/Sema/Ownership.h
    -- Installing: /usr/local/include/clang/Sema/TypoCorrection.h
    -- Installing: /usr/local/include/clang/Sema/ScopeInfo.h
    -- Installing: /usr/local/include/clang/Sema/SemaInternal.h
    -- Installing: /usr/local/include/clang/Sema/Scope.h
    -- Installing: /usr/local/include/clang/Sema/CodeCompleteOptions.h
    -- Installing: /usr/local/include/clang/Sema/SemaConsumer.h
    -- Installing: /usr/local/include/clang/Sema/CodeCompleteConsumer.h
    -- Installing: /usr/local/include/clang/Sema/Sema.h
    -- Installing: /usr/local/include/clang/Sema/ObjCMethodList.h
    -- Installing: /usr/local/include/clang/Sema/PrettyDeclStackTrace.h
    -- Installing: /usr/local/include/clang/Sema/DeclSpec.h
    -- Installing: /usr/local/include/clang/Sema/DelayedDiagnostic.h
    -- Installing: /usr/local/include/clang/Sema/Lookup.h
    -- Installing: /usr/local/include/clang/Sema/AnalysisBasedWarnings.h
    -- Installing: /usr/local/include/clang/Sema/Weak.h
    -- Installing: /usr/local/include/clang/Sema/ExternalSemaSource.h
    -- Installing: /usr/local/include/clang/Sema/TemplateDeduction.h
    -- Installing: /usr/local/include/clang/Sema/Template.h
    -- Installing: /usr/local/include/clang/Sema/ParsedTemplate.h
    -- Installing: /usr/local/include/clang/Sema/AttributeList.h
    -- Installing: /usr/local/include/clang/Sema/MultiplexExternalSemaSource.h
    -- Installing: /usr/local/include/clang/Sema/SemaDiagnostic.h
    -- Installing: /usr/local/include/clang/Sema/IdentifierResolver.h
    -- Installing: /usr/local/include/clang/Sema/Initialization.h
    -- Installing: /usr/local/include/clang/Sema/Overload.h
    -- Installing: /usr/local/include/clang/Sema/LoopHint.h
    -- Installing: /usr/local/include/clang/Sema/LocInfoType.h
    -- Installing: /usr/local/include/clang/Sema/SemaFixItUtils.h
    -- Installing: /usr/local/include/clang/ARCMigrate
    -- Installing: /usr/local/include/clang/ARCMigrate/ARCMT.h
    -- Installing: /usr/local/include/clang/ARCMigrate/FileRemapper.h
    -- Installing: /usr/local/include/clang/ARCMigrate/ARCMTActions.h
    -- Installing: /usr/local/include/clang/Lex
    -- Installing: /usr/local/include/clang/Lex/PPCallbacks.h
    -- Installing: /usr/local/include/clang/Lex/PTHManager.h
    -- Installing: /usr/local/include/clang/Lex/DirectoryLookup.h
    -- Installing: /usr/local/include/clang/Lex/ModuleLoader.h
    -- Installing: /usr/local/include/clang/Lex/MacroInfo.h
    -- Installing: /usr/local/include/clang/Lex/PreprocessingRecord.h
    -- Installing: /usr/local/include/clang/Lex/TokenLexer.h
    -- Installing: /usr/local/include/clang/Lex/ExternalPreprocessorSource.h
    -- Installing: /usr/local/include/clang/Lex/PreprocessorLexer.h
    -- Installing: /usr/local/include/clang/Lex/Lexer.h
    -- Installing: /usr/local/include/clang/Lex/Pragma.h
    -- Installing: /usr/local/include/clang/Lex/HeaderMap.h
    -- Installing: /usr/local/include/clang/Lex/MultipleIncludeOpt.h
    -- Installing: /usr/local/include/clang/Lex/TokenConcatenation.h
    -- Installing: /usr/local/include/clang/Lex/ScratchBuffer.h
    -- Installing: /usr/local/include/clang/Lex/LiteralSupport.h
    -- Installing: /usr/local/include/clang/Lex/Preprocessor.h
    -- Installing: /usr/local/include/clang/Lex/PTHLexer.h
    -- Installing: /usr/local/include/clang/Lex/HeaderSearch.h
    -- Installing: /usr/local/include/clang/Lex/LexDiagnostic.h
    -- Installing: /usr/local/include/clang/Lex/PreprocessorOptions.h
    -- Installing: /usr/local/include/clang/Lex/Token.h
    -- Installing: /usr/local/include/clang/Lex/ModuleMap.h
    -- Installing: /usr/local/include/clang/Lex/CodeCompletionHandler.h
    -- Installing: /usr/local/include/clang/Lex/HeaderSearchOptions.h
    -- Installing: /usr/local/include/clang/Lex/MacroArgs.h
    -- Installing: /usr/local/include/clang/Lex/PPConditionalDirectiveRecord.h
    -- Installing: /usr/local/include/clang/Tooling
    -- Installing: /usr/local/include/clang/Tooling/JSONCompilationDatabase.h
    -- Installing: /usr/local/include/clang/Tooling/CompilationDatabasePluginRegistry.h
    -- Installing: /usr/local/include/clang/Tooling/Refactoring.h
    -- Installing: /usr/local/include/clang/Tooling/Tooling.h
    -- Installing: /usr/local/include/clang/Tooling/FileMatchTrie.h
    -- Installing: /usr/local/include/clang/Tooling/ArgumentsAdjusters.h
    -- Installing: /usr/local/include/clang/Tooling/Core
    -- Installing: /usr/local/include/clang/Tooling/Core/Replacement.h
    -- Installing: /usr/local/include/clang/Tooling/CompilationDatabase.h
    -- Installing: /usr/local/include/clang/Tooling/CommonOptionsParser.h
    -- Installing: /usr/local/include/clang/Tooling/ReplacementsYaml.h
    -- Installing: /usr/local/include/clang/Tooling/RefactoringCallbacks.h
    -- Installing: /usr/local/include/clang-c
    -- Installing: /usr/local/include/clang-c/Platform.h
    -- Installing: /usr/local/include/clang-c/Index.h
    -- Installing: /usr/local/include/clang-c/CXErrorCode.h
    -- Installing: /usr/local/include/clang-c/BuildSystem.h
    -- Installing: /usr/local/include/clang-c/CXString.h
    -- Installing: /usr/local/include/clang-c/Documentation.h
    -- Installing: /usr/local/include/clang-c/CXCompilationDatabase.h
    -- Installing: /usr/local/include/clang
    -- Installing: /usr/local/include/clang/AST
    -- Installing: /usr/local/include/clang/AST/CommentCommandInfo.inc
    -- Installing: /usr/local/include/clang/AST/CommentNodes.inc
    -- Installing: /usr/local/include/clang/AST/Attrs.inc
    -- Installing: /usr/local/include/clang/AST/CommentHTMLNamedCharacterReferences.inc
    -- Installing: /usr/local/include/clang/AST/AttrDump.inc
    -- Installing: /usr/local/include/clang/AST/DeclNodes.inc
    -- Installing: /usr/local/include/clang/AST/CommentCommandList.inc
    -- Installing: /usr/local/include/clang/AST/CommentHTMLTags.inc
    -- Installing: /usr/local/include/clang/AST/AttrVisitor.inc
    -- Installing: /usr/local/include/clang/AST/StmtNodes.inc
    -- Installing: /usr/local/include/clang/AST/AttrImpl.inc
    -- Installing: /usr/local/include/clang/AST/CommentHTMLTagsProperties.inc
    -- Installing: /usr/local/include/clang/Basic
    -- Installing: /usr/local/include/clang/Basic/AttrList.inc
    -- Installing: /usr/local/include/clang/Basic/arm_neon.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticLexKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticASTKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticFrontendKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticCommonKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticSemaKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticIndexName.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticCommentKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticParseKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticAnalysisKinds.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticGroups.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticSerializationKinds.inc
    -- Installing: /usr/local/include/clang/Basic/Version.inc
    -- Installing: /usr/local/include/clang/Basic/AttrHasAttributeImpl.inc
    -- Installing: /usr/local/include/clang/Basic/DiagnosticDriverKinds.inc
    -- Installing: /usr/local/include/clang/Config
    -- Installing: /usr/local/include/clang/Config/config.h
    -- Installing: /usr/local/include/clang/Parse
    -- Installing: /usr/local/include/clang/Parse/AttrParserStringSwitches.inc
    -- Installing: /usr/local/include/clang/Driver
    -- Installing: /usr/local/include/clang/Driver/Options.inc
    -- Installing: /usr/local/include/clang/Serialization
    -- Installing: /usr/local/include/clang/Serialization/AttrPCHRead.inc
    -- Installing: /usr/local/include/clang/Serialization/AttrPCHWrite.inc
    -- Installing: /usr/local/include/clang/Sema
    -- Installing: /usr/local/include/clang/Sema/AttrSpellingListIndex.inc
    -- Installing: /usr/local/include/clang/Sema/AttrParsedAttrKinds.inc
    -- Installing: /usr/local/include/clang/Sema/AttrParsedAttrList.inc
    -- Installing: /usr/local/include/clang/Sema/AttrTemplateInstantiate.inc
    -- Installing: /usr/local/include/clang/Sema/AttrParsedAttrImpl.inc
    -- Installing: /usr/local/include/clang-c
    -- Installing: /usr/local/include/clang-c/Platform.h
    -- Installing: /usr/local/include/clang-c/Index.h
    -- Installing: /usr/local/include/clang-c/CXErrorCode.h
    -- Installing: /usr/local/include/clang-c/BuildSystem.h
    -- Installing: /usr/local/include/clang-c/CXString.h
    -- Installing: /usr/local/include/clang-c/Documentation.h
    -- Installing: /usr/local/include/clang-c/CXCompilationDatabase.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/adxintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/altivec.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/ammintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/arm_acle.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx2intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512bwintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512cdintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512erintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512fintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512vlbwintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512vlintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512dqintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avx512vldqintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/avxintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/bmi2intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/bmiintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/cpuid.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/cuda_builtin_vars.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/emmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/f16cintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/float.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/fma4intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/fmaintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/fxsrintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/htmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/htmxlintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/ia32intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/immintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/Intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/inttypes.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/iso646.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/limits.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/lzcntintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/mm3dnow.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/mmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/mm_malloc.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/module.modulemap
    -- Installing: /usr/local/lib/clang/3.8.0/include/nmmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/pmmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/popcntintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/prfchwintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/rdseedintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/rtmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/s390intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/shaintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/smmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdalign.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdarg.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdatomic.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdbool.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stddef.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/__stddef_max_align_t.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdint.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/stdnoreturn.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/tbmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/tgmath.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/tmmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/unwind.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/vadefs.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/varargs.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/vecintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/__wmmintrin_aes.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/wmmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/__wmmintrin_pclmul.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/x86intrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/xmmintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/xopintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/xtestintrin.h
    -- Installing: /usr/local/lib/clang/3.8.0/include/arm_neon.h
    -- Installing: /usr/local/lib/libclangBasic.a
    -- Installing: /usr/local/lib/libclangLex.a
    -- Installing: /usr/local/lib/libclangParse.a
    -- Installing: /usr/local/lib/libclangAST.a
    -- Installing: /usr/local/lib/libclangASTMatchers.a
    -- Installing: /usr/local/lib/libclangDynamicASTMatchers.a
    -- Installing: /usr/local/lib/libclangSema.a
    -- Installing: /usr/local/lib/libclangCodeGen.a
    -- Installing: /usr/local/lib/libclangAnalysis.a
    -- Installing: /usr/local/lib/libclangEdit.a
    -- Installing: /usr/local/lib/libclangRewrite.a
    -- Installing: /usr/local/lib/libclangARCMigrate.a
    -- Installing: /usr/local/lib/libclangDriver.a
    -- Installing: /usr/local/lib/libclangSerialization.a
    -- Installing: /usr/local/lib/libclangFrontend.a
    -- Installing: /usr/local/lib/libclangRewriteFrontend.a
    -- Installing: /usr/local/lib/libclangFrontendTool.a
    -- Installing: /usr/local/lib/libclangTooling.a
    -- Installing: /usr/local/lib/libclangToolingCore.a
    -- Installing: /usr/local/lib/libclangIndex.a
    -- Installing: /usr/local/lib/libclangStaticAnalyzerCore.a
    -- Installing: /usr/local/lib/libclangStaticAnalyzerCheckers.a
    -- Installing: /usr/local/lib/libclangStaticAnalyzerFrontend.a
    -- Installing: /usr/local/lib/libclangFormat.a
    -- Installing: /usr/local/bin/clang-3.8
    -- Installing: /usr/local/bin/clang
    -- Installing: /usr/local/bin/clang-format
    -- Installing: /usr/local/share/clang/clang-format-bbedit.applescript
    -- Installing: /usr/local/share/clang/clang-format-diff.py
    -- Installing: /usr/local/share/clang/clang-format-sublime.py
    -- Installing: /usr/local/share/clang/clang-format.el
    -- Installing: /usr/local/share/clang/clang-format.py
    -- Installing: /usr/local/bin/git-clang-format
    -- Installing: /usr/local/lib/libclang.so.3.8
    -- Installing: /usr/local/lib/libclang.so
    -- Installing: /usr/local/bin/clang-check
    -- Installing: /usr/local/bin/llvm-dis
    -- Installing: /usr/local/bin/opt
    -- Installing: /usr/local/bin/llvm-mcmarkup
    -- Installing: /usr/local/bin/macho-dump
    -- Installing: /usr/local/bin/llvm-cov
    -- Installing: /usr/local/bin/llvm-lto
    -- Installing: /usr/local/bin/llvm-stress
    -- Installing: /usr/local/bin/bugpoint
    -- Installing: /usr/local/bin/llvm-mc
    -- Installing: /usr/local/bin/lli
    -- Installing: /usr/local/bin/llvm-size
    -- Installing: /usr/local/bin/llvm-readobj
    -- Installing: /usr/local/bin/llvm-bcanalyzer
    -- Installing: /usr/local/bin/llvm-dwarfdump
    -- Installing: /usr/local/bin/llvm-config
    -- Installing: /usr/local/bin/llvm-pdbdump
    -- Installing: /usr/local/lib/BugpointPasses.so
    -- Installing: /usr/local/bin/llvm-diff
    -- Installing: /usr/local/bin/llc
    -- Installing: /usr/local/bin/llvm-cxxdump
    -- Installing: /usr/local/bin/llvm-profdata
    -- Installing: /usr/local/bin/verify-uselistorder
    -- Installing: /usr/local/bin/llvm-objdump
    -- Installing: /usr/local/bin/llvm-symbolizer
    -- Installing: /usr/local/bin/llvm-extract
    -- Installing: /usr/local/bin/llvm-nm
    -- Installing: /usr/local/bin/llvm-split
    -- Installing: /usr/local/bin/llvm-dsymutil
    -- Installing: /usr/local/bin/yaml2obj
    -- Installing: /usr/local/bin/llvm-c-test
    -- Installing: /usr/local/bin/llvm-as
    -- Installing: /usr/local/bin/llvm-link
    -- Installing: /usr/local/bin/obj2yaml
    -- Installing: /usr/local/bin/llvm-ar
    -- Installing: /usr/local/bin/llvm-rtdyld
    -- Installing: /usr/local/share/llvm/cmake/LLVMExports.cmake
    -- Installing: /usr/local/share/llvm/cmake/LLVMExports-noconfig.cmake
    -- Installing: /usr/local/share/llvm/cmake/LLVMConfig.cmake
    -- Installing: /usr/local/share/llvm/cmake/LLVMConfigVersion.cmake
    -- Installing: /usr/local/share/llvm/cmake/LLVM-Config.cmake
    -- Installing: /usr/local/share/llvm/cmake/.
    -- Installing: /usr/local/share/llvm/cmake/./GetSVN.cmake
    -- Installing: /usr/local/share/llvm/cmake/./AddSphinxTarget.cmake
    -- Installing: /usr/local/share/llvm/cmake/./AddOCaml.cmake
    -- Installing: /usr/local/share/llvm/cmake/./HandleLLVMStdlib.cmake
    -- Installing: /usr/local/share/llvm/cmake/./FindOCaml.cmake
    -- Installing: /usr/local/share/llvm/cmake/./AddLLVMDefinitions.cmake
    -- Installing: /usr/local/share/llvm/cmake/./FindSphinx.cmake
    -- Installing: /usr/local/share/llvm/cmake/./LLVMProcessSources.cmake
    -- Installing: /usr/local/share/llvm/cmake/./AddLLVM.cmake
    -- Installing: /usr/local/share/llvm/cmake/./ChooseMSVCCRT.cmake
    -- Installing: /usr/local/share/llvm/cmake/./CrossCompile.cmake
    -- Installing: /usr/local/share/llvm/cmake/./HandleLLVMOptions.cmake
    -- Installing: /usr/local/share/llvm/cmake/./TableGen.cmake
