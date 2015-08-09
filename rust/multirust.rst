========================================
multirust
========================================

multirust 是要管理系統上要使用多個 Rust 版本的問題，
設定後可以根據所在的專案來選擇使用的 Rust compiler 版本。

安裝：

.. code-block:: sh

    $ yaourt -S multirust
    $ pacman -Ql multirust
    multirust /usr/
    multirust /usr/local/
    multirust /usr/local/bin/
    multirust /usr/local/bin/cargo
    multirust /usr/local/bin/multirust
    multirust /usr/local/bin/multirustproxy
    multirust /usr/local/bin/rust-gdb
    multirust /usr/local/bin/rustc
    multirust /usr/local/bin/rustdoc
    multirust /usr/local/bin/rustup.sh
    multirust /usr/local/lib/
    multirust /usr/local/lib/rustlib/
    multirust /usr/local/lib/rustlib/components
    multirust /usr/local/lib/rustlib/install.log
    multirust /usr/local/lib/rustlib/manifest-multirust
    multirust /usr/local/lib/rustlib/rust-installer-version
    multirust /usr/local/lib/rustlib/uninstall.sh


使用：

.. code-block:: sh

    $ mkdir i_need_nightly
    $ cd i_need_nightly
    $ multirust override nightly
    multirust: installing toolchain 'nightly'
    rustup: gpg available. signatures will be verified
    rustup: downloading manifest for 'nightly'
    rustup: downloading toolchain for 'nightly'
    ######################################################################## 100.0%
    gpg: assuming signed data in '/home/USERNAME/.multirust/rustup/dl/11c3c8d06c2df7315585/rust-nightly-x86_64-unknown-linux-gnu.tar.gz'
    gpg: Signature made Sun 09 Aug 2015 05:34:35 PM CST using RSA key ID 7B3B09DC
    gpg: Good signature from "Rust Language (Tag and Release Signing Key) <rust-key@rust-lang.org>" [unknown]
    gpg: WARNING: This key is not certified with a trusted signature!
    gpg:          There is no indication that the signature belongs to the owner.
    Primary key fingerprint: 108F 6620 5EAE B0AA A8DD  5E1C 85AB 96E6 FA1B E5FE
        Subkey fingerprint: C134 66B7 E169 A085 1886  3216 5CB4 A934 7B3B 09DC
    rustup: extracting installer
    rustup: installing toolchain for 'nightly'
    install: creating uninstall script at /home/USERNAME/.multirust/toolchains/nightly/lib/rustlib/uninstall.sh
    install: installing component 'rustc'
    install: installing component 'cargo'
    install: installing component 'rust-docs'

        Rust is ready to roll.

    multirust: override toolchain for '/home/USERNAME/i_need_nightly' set to 'nightly'
    $ rustc --version
    rustc 1.4.0-nightly (a5d33d891 2015-08-08)
    $ mkdir ../tmp
    $ cd ../tmp
    $ rustc --version
    multirust: no default toolchain configured
    /usr/local/bin/rustc: line 107: return: can only `return' from a function or sourced script
    multirustproxy: assert_nz toolchain is empty
    $ multirust override nightly
    multirust: using existing install for 'nightly'
    multirust: override toolchain for '/home/USERNAME/tmp' set to 'nightly'
    $ rustc --version
    rustc 1.4.0-nightly (a5d33d891 2015-08-08)
