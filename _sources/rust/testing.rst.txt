========================================
測試 (Testing)
========================================


.. contents:: 目錄


涵蓋率 (Coverage)
========================================

kcov
------------------------------

kcov 是針對編譯式語言的涵蓋率，工具，
會利用 DWARF 內的資訊來判斷涵蓋率，
但是也因此不能提供準確地結果，
會因許多狀況存在著誤差。


先編譯測試程式，但不執行：

.. code-block:: sh

    $ cargo test --no-run


利用 kcov 執行測試程式：

.. code-block:: sh

    # 注意 kcov 一次只會執行一個執行檔
    # 會把結果放在 target/cov/
    $ kcov --exclude-pattern=/.cargo,/usr/lib --verify target/cov target/debug/<testing executable name>

    # 執行 target/debug/ 內符合 test_* pattern 的執行檔
    $ find target/debug/ -maxdepth 1 -executable -name 'test_*' | xargs -n1 kcov --exclude-pattern=/.cargo,/usr/lib --verify target/cov


kcov 會直接生出各項測試的 HTML/XML Report 以及最終彙整的結果：

.. code-block:: sh

    $ ls -p target/cov/
    amber.png  index.html            test_annotations-cb88dc8524099677/  test_macros-5e2f11fbc7ad0de0/
    bcov.css   index.json            test_bytes-5ca1ae23487d7d1c/        test_ser-14a39c1458f10d62/
    data/      kcov-merged/          test_de-cc5ad65a70f2114a/           test_value-b60153e4a6c47960/
    glass.png  libkcov_sowrapper.so  test_gen-3e095da8cd3ccedb/


Cobertura XML 可以方便和現有其他工具結合，
例如 Jenkins。

.. code-block:: sh

    $ ls target/cov/kcov-merged/cobertura.xml
    target/cov/kcov-merged/cobertura.xml


kcov 也支援把結果直接上傳到 `Coveralls <http://coveralls.io/>`_ ，
跟 CI 結合後就會更方便：

.. code-block:: sh

    $ kcov --coveralls-id=$TRAVIS_JOB_ID ...



參考
========================================

* `Rust Code Coverage Guide: kcov + Travis CI + Codecov / Coveralls <http://sunjay.ca/2016/07/25/rust-code-coverage>`_
* `kcov - Code coverage tool for compiled programs <https://github.com/SimonKagstrom/kcov>`_
* `Codecov Rust Example <https://github.com/codecov/example-rust>`_
* `Disabling --gc-sections when --test is specified <https://internals.rust-lang.org/t/disabling-gc-sections-when-test-is-specified/2163>`_
