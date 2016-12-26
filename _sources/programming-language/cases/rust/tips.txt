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



Conditional Attribute
========================================

``#[cfg_attr(<p>, <attr>)]``

當 ``<p>`` 成立時，就加上後面的 ``<attr>`` ，
範例：

.. code-block:: rust

    #[cfg_attr(all(not(target_os = "linux"), target_endian = "big"), ignore)]
    fn test_broken_thing() { ... }

    #[cfg_attr(target_os = "linux", link(name="mylib"))]
    extern {}


* `RFC - 0194 - cfg syntax <https://github.com/rust-lang/rfcs/blob/master/text/0194-cfg-syntax.md>`_
* `Quick tip: the #[cfg_attr] attribute <https://chrismorgan.info/blog/rust-cfg_attr.html>`_



指定連結的 Libraries
========================================

要指定額外要連結 Libraries 可以使用 ``link`` attribute，
並且可以指定如何連結：

.. code-bloc:: rust

    #[link(name = "lzma")]
    #[link(name = "mylib", kind = "static")]
    extern {}

目前 ``link`` 可以指定兩項資訊，
一個是要連結的 Library 名稱。
另一個是如何連結，
沒指定的時候就是動態連結，
``static`` 就是靜態連結，
OSX 上還可以選擇 ``framework`` 。

* `官方文件 <https://doc.rust-lang.org/book/ffi.html>`_



建立 rustc 內部文件
========================================

.. code-block:: sh

    ./configure --enable-compiler-docs
    make docs -j4

    # 放到 GitHub pages
    ghp-import docs
    git push origin gh-pages:gh-pages



re-export
========================================

.. code-block:: rust

    pub use library::*;



FFI (Foreign Function Interface)
========================================

在 Rust 中， ``String`` 是由一連串的 ``u8`` 所組成，
並且保證會是有效的 UTF-8，
這意味著 String 當中也可以正常地儲存 ``NUL`` （ ``\0`` ）。
而在 C 中，字串是指向 ``char`` 的指標，並且以 ``NUL`` 作為結尾。
在處理 FFI 時，需要處理好 Rust 和 C 內兩種不同字串表示方法的轉換。

注意事項：

* Rust 的 ``str``/``String`` 不是以 ``NUL`` 結尾做辨別
* CStr 沒有 ``repr(C)`` 屬性，不要拿來作為 FFI function 的 signature

相關資源：

* `std::ffi <https://doc.rust-lang.org/std/ffi/>`_
* `The Rust FFI Omnibus <http://jakegoulding.com/rust-ffi-omnibus/>`_
* `Rust Book - Foreign Function Interface <https://doc.rust-lang.org/book/ffi.html>`_
* `The Rust Reference - Linkage <https://doc.rust-lang.org/reference.html#linkage>`_
* `The Guide to Rust Strings <http://www.steveklabnik.com/rust-issue-17340/>`_
* `Python - ctypes <https://docs.python.org/3/library/ctypes.html>`_
* `Python - CFFI <http://cffi.readthedocs.io/en/latest/>`_


範例一，傳入字串、回傳字串
------------------------------

Rust 程式碼：

.. code-block:: rust

    // func.rs

    use std::ffi::{CStr, CString};
    use std::os::raw::c_char;


    // 一般始用的 Rust function
    pub fn func(data: &str) -> &str {
        "this is a test function"
    }

    // 給外部使用的 Rust function （一般始用的 Rust function 的包裝）
    // *const c_char -> CStr -> &str
    // => func =>
    // &str -> Result<CString, NulError> -> CString -> *mut c_char -> *const c_char
    #[no_mangle]
    pub extern fn ffi_func_generate(data: *const c_char) -> *const c_char {
        // *const c_char -> CStr
        let data = unsafe {
            assert!(!data.is_null());
            CStr::from_ptr(data)
        };

        // CStr -> &str
        let data = data.to_str().unwrap();

        // &str => func => &str
        let result = func(data);

        // &str -> Result<CString, NulError> -> CString
        let result = CString::new(result).unwrap();

        // CString -> *mut c_char
        result.into_raw()

    }

    // 給外部回收記憶體用的 function
    #[no_mangle]
    pub extern fn ffi_func_free(ptr: *mut c_char) {
        unsafe {
            if ptr.is_null() { return }
            CString::from_raw(ptr)
        };
    }


編譯：

.. code-block:: sh

    $ rustc --crate-type dylib func.rs


Python 程式碼（ctypes）：

.. code-block:: python

    import ctypes
    from ctypes import c_char_p, c_void_p

    lib = ctypes.cdll.LoadLibrary("./libfunc.so")
    # 定義溝通界面
    lib.ffi_func_generate.argtypes = (c_char_p,)
    lib.ffi_func_generate.restypes = c_char_p
    lib.ffi_func_free.argtypes = (c_void_p,)
    lib.ffi_func_free.restypes = None

    def func(code):
        # 呼叫 function 取得字串指標
        ptr = lib.ffi_func_generate(code.encode())
        try:
            # 指標轉字串
            return ctypes.cast(ptr, c_char_p).value.decode('utf-8')
        finally:
            # 回收記憶體
            lib.ffi_func_free(ptr)


Python 程式碼（CFFI）：

.. code-block:: python

    from cffi import FFI

    ffi = FFI()
    lib = ffi.dlopen("./libfunc.so")
    ffi.cdef('''
    char* const ffi_func_generate(char* const code);
    void ffi_func_free(char* ptr);
    ''')

    def func(code):
        ptr = lib.ffi_func_generate(code.encode())
        try:
            return ffi.string(ptr).decode('utf-8')
        finally:
            lib.ffi_func_free(ptr)



Pretty Print Debug
========================================

.. code-block:: sh

    println!("{:#?}", vec![1, 2, 3]);

    // [
    //     1,
    //     2,
    //     3
    // ]




Optional Arguments
========================================

Rust 1.12 開始 ``Option`` 實做了 ``From`` ，
``From`` 是一個很基本的型別轉換 ``trait`` ，
任何的 Rust 型別都可以實做 ``From`` 。

幾個使用範例：

.. code-block:: rust

    // str -> String
    // we have "impl<'a> From<&'a str> for String"
    let hello = String::from("Hello, world!");

    // i16 -> i32
    // we have "impl From<i16> for i32"
    let number = i32::from(42_i16);


我們從 Rust 1.12 開始也可以這樣做：

.. code-block:: rust

    // i32 -> Option<i32>
    let maybe_int = Option::from(42);


這看似沒有什麼重要的突破，
因為我們可以用 ``Some(42)`` 來達到同樣的事，
但是這其實在很多地方可以幫助我們少打 ``Some(x)`` 的次數。

假設我們原本有這樣的函式：

.. code-block:: rust

    fn maybe_plus_5(x: Option<i32>) -> i32 {
        x.unwrap_or(0) + 5
    }


在使用時得明確建立 ``Option`` 物件：

.. code-block:: rust

    let _ = maybe_plus_5(Some(42));  // OK
    let _ = maybe_plus_5(None);      // OK
    let _ = maybe_plus_5(42);        // error !!!


現在 ``Option<T>`` 有實做 ``From<T>`` 後，
狀況會改善很多：

.. code-block:: rust

    fn maybe_plus_5<T>(x: T) -> i32 where Option<i32>: From<T> {
        Option::from(x).unwrap_or(0) + 5
    }

.. code-block:: rust

    let _ = maybe_plus_5(Some(42));  // OK
    let _ = maybe_plus_5(None);      // OK
    let _ = maybe_plus_5(42);        // OK, 不用用 ``Some`` 包起來 !!!


更好的寫法：

.. code-block:: rust

    fn maybe_plus_5<T: Into<Option<i32>>>(x: T) -> i32 {
        x.into().unwrap_or(0) + 5
    }


* `Optional arguments in Rust 1.12 <http://xion.io/post/code/rust-optional-args.html>`_
* `core: impl From<T> for Option<T> <https://github.com/rust-lang/rust/pull/34828>`_



String 和 str
========================================

Rust 有兩種字串的型別，分別為 ``String`` 和 ``str`` ，

String 是 dynamic heap string type，
當我們需要更動或擁有所有權時，
會使用這個型別。

str 是不可更動（immutable）的一串未知長度的 UTF8，
儲存在記憶體的某處，
因為長度未知，通常會以 ``&str`` 來使用（reference 到某個 UTF8 資料），

``&str`` 可以指到以下地方：

* string literal，字串直接寫死在程式碼內並儲存在執行檔，當程式執行時直接存到記憶體，e.g. ``"foo"``
* heap allocated ``String`` ， ``String`` 可以 dereference 成 ``&str`` 做單純的讀取
* stack，stack-allocated byte array 可以以 ``&str`` 的形式做讀取


.. code-block:: rust

    use std::str;

    // static storage
    let static_str: &str = "this is test";

    // on stack
    let x: &[u8] = &['a' as u8, 'b' as u8];
    let stack_str: &str = str::from_utf8(x).unwrap();

    // on heap
    let y = String::from("test");
    let heap_str_1: &str = y.as_str();
    let heap_str_2: &str = &y;  // String -> &String -> &str
                                // &String can automatically coerce to a &str by "Deref coercions"
    let heap_str_3: &str = &*y; // String -> str -> &str


* `StackOverflow - Rust String versus str <http://stackoverflow.com/a/24159933/3880958>`_



``is_empty()`` 或 ``== ""``
========================================

實測產生出來的組語是一樣的

.. code-block:: rust

    fn function1(x: &str) -> bool {
        if x == "" {
            return true;
        }
        false
    }

    fn function2(x: &str) -> bool {
        if x.is_empty() {
            return true;
        }
        false
    }

    fn function3(x: &str) -> bool {
        x.is_empty()
    }

    fn main() {
        function1("asd");
        function2("asd");
        function3("asd");
    }


.. code-block:: sh

    $ rustc --emit=asm tmp.rs

.. code-block:: asm


    _ZN3tmp9function117h1b4755b813ebdd74E:
        .cfi_startproc
        subq	$56, %rsp

    _ZN3tmp9function217h08a5b6f3f7ebc34eE:
        .cfi_startproc
        subq	$40, %rsp

    _ZN3tmp9function317hac51923d2a830a73E:
        .cfi_startproc
        subq	$24, %rsp
