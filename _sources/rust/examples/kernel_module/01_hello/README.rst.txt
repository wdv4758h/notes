========================================
Linux Kernel Module in Rust
========================================

Build
========================================

.. code-block:: sh

    $ make
    /usr/local/bin/cargo rustc --release --verbose  --target="x86_64-unknown-none-gnu" -- --emit obj -o hello_rust.o
       Compiling core v0.1.0 (https://github.com/phil-opp/nightly-libcore.git#bdc956fc)
         Running `rustc /home/dv/.multirust/toolchains/nightly/cargo/git/checkouts/nightly-libcore-7f94967e143b5c9a/master/src/lib.rs --crate-name core --crate-type lib -C opt-level=3 --cfg feature=\"disable_float\" -C metadata=1bcee92286ce2cdd -C extra-filename=-1bcee92286ce2cdd --out-dir /tmp/hello/target/x86_64-unknown-none-gnu/release/deps --emit=dep-info,link --target x86_64-unknown-none-gnu -L dependency=/tmp/hello/target/x86_64-unknown-none-gnu/release/deps -L dependency=/tmp/hello/target/x86_64-unknown-none-gnu/release/deps --cap-lints allow`
       Compiling hello v0.1.0 (file:///tmp/hello)
         Running `rustc src/lib.rs --crate-name hello --crate-type lib -C opt-level=3 --emit obj -o hello_rust.o --out-dir /tmp/hello/target/x86_64-unknown-none-gnu/release --emit=dep-info,link --target x86_64-unknown-none-gnu -L dependency=/tmp/hello/target/x86_64-unknown-none-gnu/release -L dependency=/tmp/hello/target/x86_64-unknown-none-gnu/release/deps --extern core=/tmp/hello/target/x86_64-unknown-none-gnu/release/deps/libcore-1bcee92286ce2cdd.rlib`
    warning: ignoring specified output filename because multiple outputs were requested
    warning: ignoring --out-dir flag due to -o flag.
    make -C /lib/modules/4.4.1-2-ARCH/build M=/tmp/hello modules
    make[1]: Entering directory '/usr/lib/modules/4.4.1-2-ARCH/build'
      CC [M]  /tmp/hello/src/module.o
      LD [M]  /tmp/hello/hello.o
      Building modules, stage 2.
      MODPOST 1 modules
      CC      /tmp/hello/hello.mod.o
      LD [M]  /tmp/hello/hello.ko
    make[1]: Leaving directory '/usr/lib/modules/4.4.1-2-ARCH/build'
    cp "hello.ko" "hello.stripped.ko" && strip "hello.stripped.ko"
    $ ls -l hello*.ko
    -rw-r--r-- 1 dv users 4880 Mar  7 02:08 hello.ko
    -rw-r--r-- 1 dv users 2912 Mar  7 02:08 hello.stripped.ko


Build Flow
========================================

::

    　                  +-------+
                        | make  |
                        +-------+
                           | |
        +------------------+ +--------------+
        |                                   |
        | envoke                            | envoke
        |                                   |
        v                                   v
    +--------+                            +-------+
    | kbuild | <----- src/module.c        | cargo | <----- src/lib.rs & libcore
    +--------+                            +-------+
        |                                   |
        |                                   |
        | src/module.o                      | hello_rust.o
        |                                   |
        +------------------+ +--------------+
                           | |
                           v v
                        +--------+
                        | Linker |
                        +--------+
                            |
                            |
                            v

                         hello.ko


Reference
========================================

* `Building External Modules <https://www.kernel.org/doc/Documentation/kbuild/modules.txt>`_
* `Linux Kernel Makefiles <https://www.kernel.org/doc/Documentation/kbuild/makefiles.txt>`_
* `kbuild <https://www.kernel.org/doc/Documentation/kbuild/kbuild.txt>`_
* `Arch Wiki - Compile Kernel Module <https://wiki.archlinux.org/index.php/Compile_kernel_module>`_
* `rust.ko - A minimal Linux kernel module written in rust <https://github.com/tsgates/rust.ko>`_
