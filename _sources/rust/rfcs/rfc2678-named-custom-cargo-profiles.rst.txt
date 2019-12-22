========================================
RFC 2678 - Custom Cargo Profiles
========================================


:URL: https://github.com/rust-lang/rfcs/blob/master/text/2678-named-custom-cargo-profiles.md


支援客製化 Cargo profiles，
不再只是 dev/release/test/bench。


範例：

.. code-block:: toml

    [profile.release-lto]
    inherits = "release"    # 繼承 release profile 來改
    lto = true


.. code-block:: sh

    cargo build --profile release-lto


額外屬性 dir-name：

.. code-block:: toml

    [profile.release-lto]
    inherits = "release"    # 繼承 release profile 來改
    dir-name = "lto"        # Emits to target/lto instead of target/release-lto
    lto = true
