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


參考：

* `String::parse <https://doc.rust-lang.org/std/string/struct.String.html#method.parse>`_
    - ``string.parse::<T>()``
    - turbofish: ``::<>``



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



cfg! Condition
========================================

原本內建的 macro 可以達到這樣的事：

.. code-block:: rust

    if cfg!(feature = "xxx") {
        ...
    } else if cfg!(target_os ="ooo") {
        ...
    } else {
        ...
    }

但是這不能用於 function 或 type 定義，
但是有第三方的 `cfg-if <https://github.com/alexcrichton/cfg-if>`_ 可以支援這樣的事：

.. code-block:: rust

    #[macro_use]
    extern crate cfg_if;

    cfg_if! {
        if #[cfg(unix)] {
            fn foo() { /* unix specific functionality */ }
        } else if #[cfg(target_pointer_width = "32")] {
            fn foo() { /* non-unix, 32-bit functionality */ }
        } else {
            fn foo() { /* fallback implementation */ }
        }
    }



I/O 處理
========================================

在進行有實做 Read trait 的型別時，
至少有三種以上的方式可以讀出資料：

1. Raw Reader，直接讀取檔案，沒有 Buffer，效能最差

.. code-block:: rust

    let f = File::open(path).unwrap();
    serde_json::from_reader(f).unwrap()


2. Buffered Reader，利用 ``BufReader`` 輔助檔案存取，效能比 Raw Reader 好

.. code-block:: rust

   let br = BufReader::new(File::open(path).unwrap());
   serde_json::from_reader(br).unwrap()


3. String，先把有資料讀到 String 中再處理，效能最好但最耗記憶體

.. code-block:: rust

    let mut bytes = Vec::new();
    File::open(path).unwrap().read_to_end(&mut bytes).unwrap();
    serde_json::from_slice(&contents).unwrap()


疑問：

* 有 ``BufReader`` struct、 ``BufRead`` trait、 ``BufWriter`` ，怎麼沒有 ``BufWrite`` trait ？


參考：

* `serde-rs/json - Parsing 20MB file using from_reader is slow <https://github.com/serde-rs/json/issues/160#issuecomment-253446892>`_
* `Trait std::io::BufRead <https://doc.rust-lang.org/std/io/trait.BufRead.html>`_




執行檔大小
========================================

如果想要盡量降低執行檔大小，
一來是盡量打開相關的優化：

* Link Time Optimization： ``Cargo.toml`` 內為 ``[profile.release]`` 加上 ``lto = ture``

二來是考慮使用 ``jemalloc`` 加 ``musl``


參考：

* `Optimizing Rust Binaries: Observation of Musl versus Glibc and Jemalloc versus System Alloc <https://users.rust-lang.org/t/optimizing-rust-binaries-observation-of-musl-versus-glibc-and-jemalloc-versus-system-alloc/8499>`_
* `jemalloc <http://jemalloc.net/>`_
* `musl libc <https://www.musl-libc.org/>`_
* `Cargo - src/cargo/core/manifest.rs <https://github.com/rust-lang/cargo/blob/master/src/cargo/core/manifest.rs>`_
    - struct ``Profile`` 定義了 profile 內可加入的參數



Iterator over contigunous windows of specific length
====================================================

``slice`` 內有 ``windows`` 函式可以固定長度的 Windows Iterator，
Iterator 看到的新資料的開頭會跟上一筆的結尾重複。
（若想要直接分成不重複片段，可以使用 ``chunks`` ）

程式碼：

.. code-block:: rust

    fn main() {
        let data = "測試123";

        let byte_window = data.as_bytes().windows(2).collect::<Vec<_>>();
        println!("{:?}", byte_window);

        let chars = data.chars().collect::<Vec<_>>();
        let char_window = chars.windows(2).collect::<Vec<_>>();
        println!("{:?}", char_window);

        let char_window3 = chars.windows(3).collect::<Vec<_>>();
        println!("{:?}", char_window3);
    }


輸出：

::

    [[230, 184], [184, 172], [172, 232], [232, 169], [169, 166], [166, 49], [49, 50], [50, 51]]
    [['測', '試'], ['試', '1'], ['1', '2'], ['2', '3']]
    [['測', '試', '1'], ['試', '1', '2'], ['1', '2', '3']]


參考：

* `std - primitive.slice#method.windows <https://doc.rust-lang.org/std/primitive.slice.html#method.windows>`_



ASCII 相關操作
========================================

Rust 內建就已經有好幾個 ASCII 相關的函式可以用，
只要實做了 ``AsciiExt`` trait 就可以支援，
目前包含以下函式：

* is_ascii
* to_ascii_uppercase
* to_ascii_lowercase
* eq_ignore_ascii_case
* make_ascii_uppercase
* make_ascii_lowercase

* `Rust - Trait std::ascii::AsciiExt <https://doc.rust-lang.org/std/ascii/trait.AsciiExt.html>`_



AsRef/AsMut/Into/From & Borrow
========================================

``AsRef`` 主要是用來建立統一一致的界面，
例如一個函式接受 ``AsRef<[u8]>`` 作為參數，
如此一來不管傳入的變數是要呼叫 ``.as_slice()`` 還是 ``.as_bytes()`` 才能轉成 ``&[u8]`` 都能拿來用，
範例程式碼：

.. code-block:: rust

    fn func<T: AsRef<[u8]>>(data: T) {
        println!("{:?}", data.as_ref());
    }

    fn main() {
        func([1, 2, 3]);
        func(vec![4, 5, 6]);    // need to call .as_slice() to make &[u8]
        func("test");           // need to call .as_bytes() to make &[u8]
    }

``AsRef`` 在 Standard Libray 內的很多地方都有使用，
例如 ``std::process::Command::args`` 就可以接受 ``&[AsRef<OsStr>]`` 作為指令參數來源。

和 ``AsRef`` 一起加入的 Trait 還有 ``AsMut`` 、 ``Into`` 、 ``From`` ，
``AsMut`` 是 ``AsRef`` 的 mutable reference 版本，
使用範例：

.. code-block:: rust

    fn func<T: AsMut<[u8]>>(data: &mut T) {
        let mut data = data.as_mut();
        data[0] += 42;
        println!("{:?}", data);
    }

    fn main() {
        func(&mut [4, 5, 6]);
        func(&mut vec![1, 2, 3]);
    }

``AsRef`` 和 ``AsMut`` 都是「一種 Reference 轉成另一種 Reference」，
另外的 ``Into`` 則會消耗掉原本的資料在「Arbitrary Types 之間轉換」，
但是 ``Into`` 通常不會直接被實做，
會被直接實做的是 ``From`` ，
而實做了 ``From`` 也就會跟著實做了 ``Into`` ，
因為 ``Into`` 在 Standard Library 內唯二的實做之一就是 ``impl<T, U> Into<U> for T where U: From<T>`` ，
另外一個實做則是保證了反身性（ ``impl<T> From<T> for T`` ），
使用範例：

.. code-block:: rust

    fn func<T: Into<Vec<u8>>>(data: T) {
        let mut data = data.into();
        // 也可以用 Into trait 來呼叫 into，但是要有足夠多的資訊讓編譯器知道要轉成的型別
        // let mut data = Into::into(data);
        data[0] += 42;
        println!("{:?}", data);
    }

    fn main() {
        let data = vec![1, 2, 3];
        func(data);     // value moved
        func(data);     // compile error !!!

        let data = "test".to_string();
        func(data);     // value moved
        func(data);     // compile error !!!
    }


使用 ``From`` 的範例：

.. code-block:: rust

    // 等同於前面使用 ``Into`` 的範例
    fn func<T>(data: T)
        where Vec<u8>: From<T> {
        // 用目標型別來呼叫 from
        let mut data = Vec::from(data);
        // 也可以直接用 From trait 來呼叫 from，但是編譯器要有足夠多的訊息來幫忙找到對應的型別
        let mut data: Vec<_> = From::from(data);
        data[0] += 42;
        println!("{:?}", data);
    }

    fn main() {
        let data = vec![1, 2, 3];
        func(data);     // value moved
        func(data);     // compile error !!!

        let data = "test".to_string();
        func(data);     // value moved
        func(data);     // compile error !!!
    }


``From`` 和 ``Into`` 在使用上非常類似，
但轉換的方向不同，
使用上為了讓意圖明顯和簡短方便，
分別的情境可能會是 ``TargetType::from(value)`` 和 ``value.into()`` 。

+---------+-----------------------------------------------------------------+-----------------+----------+
| Trait   | 功用                                                            | Moved/Reference | 可否失敗 |
+=========+=================================================================+=================+==========+
| From    | 在不同的資料型別間轉換                                          | Moved           | 否       |
+---------+-----------------------------------------------------------------+-----------------+----------+
| Into    | 在不同的資料型別間轉換，有 From 就自動會有 Into，但反向不成立   | Moved           | 否       |
+---------+-----------------------------------------------------------------+-----------------+----------+
| AsRef   | 在不同的 Reference 型別間轉換，不可更動                         | Reference       | 否       |
+---------+-----------------------------------------------------------------+-----------------+----------+
| AsMut   | 在不同的 Reference 型別間轉換，可更動                           | Reference       | 否       |
+---------+-----------------------------------------------------------------+-----------------+----------+
| TryFrom | 在不同的資料型別間轉換                                          | Moved           | 可       |
+---------+-----------------------------------------------------------------+-----------------+----------+
| TryInto | 在不同的資料型別間轉換，有 TryFrom 就自動有 TryInto，反向不成立 | Moved           | 可       |
+---------+-----------------------------------------------------------------+-----------------+----------+

另外還有也很類似的在 ``std::borrow::Borrow`` ，
``Borrow`` 的用途是來抽象化各種 borrow 的方式，
例如一般對於 ``T`` 會有 ``&T`` 和 ``&mut T`` ，
如果是 ``Vec<T>`` 還會有 borrowed slice ``&[T]`` 和 ``&mut [T]`` ，
為了讓這些不同的 borrow 都可以被接收，
所以用 ``Borrow`` Trait 來做一層簡單的包裝，
雖然在某些情況效果會跟 ``AsRef`` 雷同，
但兩者的語意不一樣。

``Borrow`` 在 Standard Libray 中被用來實做 ``HashMap`` 和 ``BTreeMap`` ，
這邊會假設同個值的 Owned 和 Borrowed 版本會有相同的 Hashing 和 Ordering，
但是 ``AsRef`` 不能保證這點，
也因為 ``Borrow`` 的條件限制比 AsRef 強，所以實做 Borrow 的型別會比較少



以下情況建議使用 ``Borrow`` ：

* 想要抽象化不同的 borrow 時
* 在建立資料結構，想要同等對待 owned 和 borrowed 值時，例如 Hashing 或數值比較


以下情況建議使用 ``AsRef`` ：

* 撰寫泛型程式時，想要把某個值直接轉成 Reference



相關連結：

* `Borrow and AsRef <https://doc.rust-lang.org/nightly/book/borrow-and-asref.html>`_
* `Rust - Trait std::convert::AsRef <https://doc.rust-lang.org/nightly/std/convert/trait.AsRef.html>`_
* `Rust - Trait std::borrow::Borrow <https://doc.rust-lang.org/nightly/std/borrow/trait.Borrow.html>`_
* `RFC #0235 - Collections Conventions <https://github.com/rust-lang/rfcs/blob/master/text/0235-collections-conventions.md>`_
* `RFC #0529 - Conversion Traits <https://github.com/rust-lang/rfcs/blob/master/text/0529-conversion-traits.md>`_
* `Convenient and idiomatic conversions in Rust <https://ricardomartins.cc/2016/08/03/convenient_and_idiomatic_conversions_in_rust>`_
* `Rust - src/libcore/convert.rs <https://github.com/rust-lang/rust/blob/master/src/libcore/convert.rs>`_



Cell & RefCell
========================================

Cell 和 RefCell 在 ``std::cell`` 內，
該 module 提供的是「Shareable Mutable Containers」，
換句話說是提供「Interior Mutability」，
一般 Rust 的型別都是「Inherited Mutability」，
也就是說如果我的 struct 變數是「不可更動」的，
那裡面的每個變數都會是「不可更動」的，
但是有時候我們會需要 struct 為「不可更動」而裡面某個欄位為「可以更動」，
例如 ``std::rc::Rc`` 在實做 reference counting，
無論現在使用到的變數是不是可以更動，
裡面的計數器就是要可以改動。


利用 ``Cell`` 製造可以更動的欄位：

.. code-block:: rust

    use std::cell::Cell;

    struct FunctionWrapper<'a> {
        counter: Cell<usize>,
        func: &'a Fn(),
    }

    impl<'a> FunctionWrapper<'a> {
        pub fn new(func: &Fn()) -> FunctionWrapper {
            FunctionWrapper {
                counter: Cell::new(0),
                func: func,
            }
        }

        pub fn call(&self) {
            self.counter.set(self.counter.get()+1);
            (*(*self).func)();
        }

        pub fn count(&self) -> usize {
            self.counter.get()
        }
    }

    fn hello() {
        println!("Hello");
    }

    fn main() {
        let func = &hello;
        let func = FunctionWrapper::new(func);
        println!("Call times: {}", func.count());   // 0
        func.call();
        println!("Call times: {}", func.count());   // 1
        func.call();
    }


``Cell`` 雖然是 zero-cost，
但只能用於有實做 ``Copy`` 的型別，
對於沒有實做 ``Copy`` 的型別要使用 ``RefCell`` ，
而 ``RefCell`` 和其他編譯時期做靜態追蹤的 Native Reference 型別不同，
``RefCell`` 會利用 Rust 的 lifetime 實做「Dynamic Borrowing」，
追蹤會執行在 runtime，
也因此有機會 borrow 到已經 mutably borrowed 的值，
當這個狀況發生時會導致 Thread Panic。


以下狀況可能會使用到 Interior Mutability：

* 在不可更動的資料內加入可以內部更動的欄位
* 實做邏輯上不會更動的 method（例如為了 amortize running time 而在內部做了 cache）
* 更動 ``Clone`` 的實做
* 更動使用 Reference Counting 的值


``Cell`` 和 ``RefCell`` 相比下，雖然 ``Cell`` 沒有 Runtime Cost，但以下狀況可能會想要用 ``RefCell`` ：

* 要包的型別沒有實做 ``Copy``
* 想要在出錯時讓程式 crash 而不是讓資料有爛掉的可能性（RefCell 才有 Runtime Borrow Checking）
* expose 內部值得指標


總結：

* Interior Mutability：當你擁有 immutable reference 卻仍然可以更動更動內部某些值
* Cell 和 RefCell 可以用來達成 Interior Mutability，兩個都沒有 Compile-time Borrow Checking
* Cell 包裝有實做 Copy 的型別，沒有 Compile-time 和 Runtime Borrow Checking
* RefCell 包裝任意型別，有動態的 Borrow Checking，需要呼叫 borrow/borrow_mut 來取得 reference，此時會進行 Runtime 的 Borrow Checking
* Cell 具有 copy 的語意，會提供 values。RefCell 具有 move 的語意，會提供 references
* Cell 和 RefCell 都是 Non-thread-safe，在多執行緒下需要用 Mutex 或 RwLock


相關連結：

* `Module std::cell <https://doc.rust-lang.org/std/cell/>`_
* `Choosing your Guarantees <https://doc.rust-lang.org/beta/book/choosing-your-guarantees.html>`_
* `Interior mutability in Rust: what, why, how? <https://ricardomartins.cc/2016/06/08/interior-mutability>`_
* `Interior mutability in Rust, part 2: thread safety <https://ricardomartins.cc/2016/06/25/interior-mutability-thread-safety>`_
* `Interior mutability in Rust, part 3: behind the curtain <https://ricardomartins.cc/2016/07/11/interior-mutability-behind-the-curtain>`_
