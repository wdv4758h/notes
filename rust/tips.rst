========================================
Rust Tips
========================================


.. contents:: 目錄


輸出中間產物
========================================

.. code-block:: sh

    # cargo arguments     -- rustc arguments
    cargo rustc           -- --emit=asm,llvm-bc,llvm-ir,obj,link,dep-info
    cargo rustc --release -- --emit=asm,llvm-bc,llvm-ir,obj,link,dep-info
    cargo rustc --release -- --emit=asm,llvm-bc,llvm-ir,obj,link,dep-info -C target-cpu=native

    # Use MIR
    cargo rustc --release -- --emit=asm,llvm-bc,llvm-ir,obj,link,dep-info -C target-cpu=native -Z orbit

    # Dump all MIR
    cargo rustc --release -- --emit=asm,llvm-bc,llvm-ir,obj,link,dep-info -Z dump-mir=all -Z dump-mir-dir=target/release/mir/

    # Only output MIR
    cargo rustc --release -- -Zunstable-options --unpretty=mir > unpretty.mir


Counter By HashMap
========================================

HashMap 內 key/value 的型別可以交給 Rust 編譯器來推斷，
利用 ``or_insert`` 可以在碰到沒有見過的 key 時插入預設值。

.. code-block:: rust

    let mut counter = HashMap::new();
    for key in data {
        *counter.entry(key).or_insert(0) += 1;
    }


Slices join/concat
========================================

只要實作了
`std::slice::SliceConcatExt <https://doc.rust-lang.org/std/slice/trait.SliceConcatExt.html>`_
trait，
就可以使用 ``join`` 和 ``concat`` ，
對於一連串的字串來說就很方便。

.. code-block:: rust

    let data = ["hello", "world"];
    assert_eq!(data.join(" "), "hello world");
    assert_eq!(data.concat(), "helloworld");
