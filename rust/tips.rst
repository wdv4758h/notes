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


字串轉特定型別
========================================

只要型別 T 有實做 ``std::str::FromStr`` ，
那就可以使用 ``.parse::<T>()`` 來轉換：

.. code-block:: rust

    let foo: T = "text".parse::<T>();


把相依套件抓下來
========================================

要裝專案的相依套件可以使用 ``cargo fetch`` ，
這指令會把需要的檔案抓到 ``$CARGO_HOME`` ，
在該資料夾下建立一個叫做 ``registry`` 的資料夾，
相關檔案都在裡面。

.. code-block:: sh

    $ env CARGO_HOME="." cargo fetch

.. code-block:: sh

    $ tree ./registry/
    ├── cache
    │   └── github.com-1ecc6299db9ec823
    │       └── log-0.3.6.crate
    ├── index
    │   └── github.com-1ecc6299db9ec823
    │       ├── 1
    │       │   ├── a
    │       │   ├── c
    │       │   ├── j
    │       │   ├── q
    │       │   ├── r
    ...
    │       ├── zs
    │       │   └── td
    │       │       └── zstd
    │       └── zw
    │           └── av
    │               └── zwave
    └── src
        └── github.com-1ecc6299db9ec823
            └── log-0.3.6
                ├── appveyor.yml
                ├── Cargo.toml
                ├── LICENSE-APACHE
                ├── LICENSE-MIT
                ├── README.md
                ├── src
                │   ├── lib.rs
                │   └── macros.rs
                └── tests
                    └── filters.rs

