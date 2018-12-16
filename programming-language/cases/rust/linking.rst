========================================
Linking
========================================


.. contents:: 目錄


Cargo Linkage
========================================

Cargo Linkage 支援多種類型，
主要是 library 種類吧，有兩個向度，
第一個是靜態連結或動態連結，
第二個是 system library 或 Rust library，
system library 就是平常 C/C++ 會生出的那種，
Rust library 是會帶更多 Rust 資訊。
這樣就四種，加一種叫編譯器幫自己選 library 格式，
然後再加執行檔和擴充編譯器的 procedural macros，總共變成七種。


* bin:        我要做執行檔
* lib:        我要做 Rust library，格式編譯器幫我選
* staticlib:  靜態連結 system library (e.g. libfoo.a)
* cdylib:     動態連結 system library (e.g. libfoo.so)
* dylib:      動態連結 Rust library (e.g. libfoo.so)
* rlib:       靜態連結 Rust library
* proc-macro: 擴充編譯器的 procedural macros



LLVM Linkage
========================================

.. code-block:: rust

    // /src/librustc_typeck/collect.rs

    match name {
        "appending" => Appending,
        "available_externally" => AvailableExternally,
        "common" => Common,
        "extern_weak" => ExternalWeak,
        "external" => External,
        "internal" => Internal,
        "linkonce" => LinkOnceAny,
        "linkonce_odr" => LinkOnceODR,
        "private" => Private,
        "weak" => WeakAny,
        "weak_odr" => WeakODR,
        _ => {
            let span = tcx.hir().span_if_local(def_id);
            if let Some(span) = span {
                tcx.sess.span_fatal(span, "invalid linkage specified")
            } else {
                tcx.sess
                   .fatal(&format!("invalid linkage specified: {}", name))
            }
        }
    }


.. code-block:: rust

    // src/librustc/mir/mono.rs

    #[derive(Copy, Clone, PartialEq, Eq, Hash, Debug, RustcEncodable, RustcDecodable)]
    pub enum Linkage {
        External,
        AvailableExternally,
        LinkOnceAny,
        LinkOnceODR,
        WeakAny,
        WeakODR,
        Appending,
        Internal,
        Private,
        ExternalWeak,
        Common,
    }


.. code-block:: rust

    // src/librustc_codegen_llvm/llvm/ffi.rs

    /// LLVMRustLinkage
    #[derive(Copy, Clone, PartialEq, Eq, Hash, Debug)]
    #[repr(C)]
    pub enum Linkage {
        ExternalLinkage = 0,
        AvailableExternallyLinkage = 1,
        LinkOnceAnyLinkage = 2,
        LinkOnceODRLinkage = 3,
        WeakAnyLinkage = 4,
        WeakODRLinkage = 5,
        AppendingLinkage = 6,
        InternalLinkage = 7,
        PrivateLinkage = 8,
        ExternalWeakLinkage = 9,
        CommonLinkage = 10,
    }


.. code-block:: rust

    // src/librustc_codegen_llvm/base.rs

    pub fn linkage_to_llvm(linkage: Linkage) -> llvm::Linkage {
        match linkage {
            Linkage::External => llvm::Linkage::ExternalLinkage,
            Linkage::AvailableExternally => llvm::Linkage::AvailableExternallyLinkage,
            Linkage::LinkOnceAny => llvm::Linkage::LinkOnceAnyLinkage,
            Linkage::LinkOnceODR => llvm::Linkage::LinkOnceODRLinkage,
            Linkage::WeakAny => llvm::Linkage::WeakAnyLinkage,
            Linkage::WeakODR => llvm::Linkage::WeakODRLinkage,
            Linkage::Appending => llvm::Linkage::AppendingLinkage,
            Linkage::Internal => llvm::Linkage::InternalLinkage,
            Linkage::Private => llvm::Linkage::PrivateLinkage,
            Linkage::ExternalWeak => llvm::Linkage::ExternalWeakLinkage,
            Linkage::Common => llvm::Linkage::CommonLinkage,
        }
    }



參考
========================================

* `Tracking issue for the "linkage" feature <https://github.com/rust-lang/rust/issues/29603>`_
* `src/librustc_codegen_llvm/base.rs <https://github.com/rust-lang/rust/blob/21f26849506c141a6760532ca5bdfd8345247fdb/src/librustc_codegen_llvm/base.rs>`_
* `src/librustc_codegen_llvm/llvm/ffi.rs <https://github.com/rust-lang/rust/blob/9cd3bef4cfaaac2a608682d4b0834cda344249e0/src/librustc_codegen_llvm/llvm/ffi.rs>`_
