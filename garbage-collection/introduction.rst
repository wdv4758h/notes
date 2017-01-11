========================================
Garbage Collection 介紹
========================================


.. contents:: 目錄


歷史
========================================

Garbage Collection 的技術誕生於 1960 年代，
John McCarthy 在開發 Lisp 程式語言時，
發明了 Garbage Collection 來實做程式語言，
當時提出了使用 Mark & Sweep 演算法搭配 DFS （depth-first search）來辨別仍然可以被存取到的變數。
其中 John McCarthy 一開始堅持 Lisp 的 S-expression 結構必須是「不可變動的（immutable）」，
允許利用 reference sharing 作為 copying 的內部實做，
這樣的優化技巧以及後來放鬆限制允許「可變動」的結構，
是為發想出 Garbage Collection 的動機。

在開始開發 Lisp 的 1958 年的 40 年後，
1998 年的 10 月，
展開了第一場 「International Symposium on Memory Management （簡稱 ISMM）」。



常見 Garbage Collection 技術
========================================

GC 的實做都基於四種基本的演算法改造而成，
分別為：

* Mark-Sweep GC
* Mark-Compact GC
* Copying GC
* Reference Counting


而 GC 要做的事情可以分成三件：

* 分配新空間
* 分辨 Live Objects 與 Garbages
* 回收 Garbages


Mark-Sweep GC
------------------------------

為最早出現，
簡單且非常常見的 GC 演算法，
會先標記所有可以追蹤到的物件（也就是 Live Objects），
剩餘的則是 Garbages，
接著進行回收，
此過程會造成程式暫停執行其他工作，
此現象稱為「Stop The World」。


Tricolor
++++++++++++++++++++

Bitmap
++++++++++++++++++++

Lazy Sweeping
++++++++++++++++++++


Mark-Compact GC
------------------------------

在程式一開始，我們會有連續的可用記憶體可以分配，
但隨著執行時間變長，
在反覆地記憶體分配與重新分配中，
很容易出現記憶體破碎化的狀況（Memory Fragmentation），
這會造成至少兩個問題：

1. 雖然我們還有許多破碎的小空間，但是我們無法找到足夠大的連續空間分配給接下來的使用，造成要不到記憶體。在沒有使用 GC 的程式中，這通常會造成程式終止。在有 GC 的程式中，會過於頻繁地觸發 GC 運作，來嘗試清出空間。

2. 就算記憶體足夠，記憶體破碎化還是可能造成程式使用更多的 Address Space、Pages、Cache Lines，因此造成效能變差。

要完全避免記憶體破碎化是不太可能的，
一來是不能預測未來一連串的記憶體分配請求，
二來是就算知道接下來一連串的記憶體分配請求，
要最佳地分配好也是 NP-hard 的問題（[robs80]_）。

我們雖然不完全避免記憶體破碎化，
但是我們可以管理，
在「記憶體分配速度」和「記憶體破碎化」之間取一個平衡點。
而管理的方式就是利用「Compaction」或「Copying」技術，
說白了就是整理記憶體內使用的區塊，
把使用的部份集中起來。

在使用 Compaction 整理的時候會依照特定的整理原則，
常見的整理原則有三種：

* Arbitary：不管原本記憶體位址的順序，也不管是否有指到其他人
* Linearising：物件會被分配到和自己比較相關的物件的附近（例如資料結構內為 siblings）
* Sliding：物件會直接被擠到 Heap 的某一邊，保持原本的順序，並把 Garbage 擠去另外一邊

大部分的實做會選擇 Arbitary 或 Sliding。
Arbitary 實做容易且執行快速，
尤其是各節點都是同樣大小時，
但是不會保留原本的相對順序，
會對 mutator 造成 Spatial Locality 的問題（Pages、Cache Lines）
（已經有論文和實驗證實更改物件原本的順序會造成 Throughput 大幅下降 [abua04]_）。
現代的 Compaction 大多使用 Sliding，
不會改變相對的順序，
相比 Arbitary 所會遇到的 Spatial Locality 問題較小。

另外 Copying 則是可以更進一步地改善 Spatial Locality 的問題，
因為 siblings 都會放在比較靠近的位置。

參考：

* `Compacting Garbage Collection in SpiderMonkey <https://hacks.mozilla.org/2015/07/compacting-garbage-collection-in-spidermonkey/>`_


Two-Finger Compaction
+++++++++++++++++++++

Lisp 2 Algorithm
++++++++++++++++++++

Threaded Compaction
++++++++++++++++++++

One-pass Compaction
++++++++++++++++++++


Copying GC
---------------------------------

基本的 semispace copying 會把 Heap 分成兩塊，
稱為 semispace，
這兩塊又分別被稱為 fromspace 和 tospace，
一次只會有一邊在使用（所以這邊的缺點是可用 Heap 大小變一半），
GC 在運作時會把 Live Objects 從 fromspace 移到 tospace，
並在此時整理好 Heap，
此時角色就會互換，
原本的 fromspace 變成 tospace，
原本的 tospace 變成 fromspace，
以新的 fromspace 繼續作為可用的 Heap。


Generational Mark & Sweep GC
---------------------------------

Generational garbage collection 的核心觀念就是「大多數的物件的生命都很短」，
所以就修改原本的 GC 設計，依照不同的存在時間有不同的處理方式，
對於 Tracing 的 GC 會需要去掃過物件來檢查是否有物件已經成為 Garbage，
當程式會製造出大量的物件時，檢查的時間就會上升，這時如果用已經存在的時間來區分，
而做不同的處理方式時，多數的短期物件就可以更快的被回收，也不必頻繁檢查會長期存在的物件。

* SpiderMonkey 利用了這種方式來讓 temporary objects 的 penalty 下降
* [1984] `Garbage collection in a large Lisp system <http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.122.4295>`_


Nursery & Tenured
++++++++++++++++++++

多數的 objects 都會 allocate 到一個叫做 Nursery 的 memory region，
當 Nursery 滿的時候，只檢查 Nursery 裡的 objects，此時多數的 short-lived temporary objects 就會被清掉，
而這樣的檢查相對於原本 (檢查全部的 objects) 也來的快

此時，依然存活的 objects 就會被放到 Tenured region

Tenured heap 仍然會回收 grabage，但是頻率會比 Nursery 來的低

最終然會需要原整的 GC，但是頻率也會比 Nursery GC 來的低

所以就分成下面這種情況

.. table::
    :class: table table-bordered

    +--------------------+------------+-----------+-------+
    | Garbage Collection | Scan Place | frequency | speed |
    +====================+============+===========+=======+
    | minor GCs          | Nursery    | high      | fast  |
    +--------------------+------------+-----------+-------+
    | major GCs          | full heap  | low       | slow  |
    +--------------------+------------+-----------+-------+

.. table::
    :class: table table-bordered

    +---------------+-------+
    | memory region | age   |
    +===============+=======+
    | Nursery       | young |
    +---------------+-------+
    | Tenured       | old   |
    +---------------+-------+



Reference Counting
------------------------------

* 問題在 reference cycle，會需要一個 cycle detect algorithm 來爬過所有 objects，但這就會產生 undeterministic GC pause


Incremental
------------------------------

拆散整個 GC 過程，把每次暫停的時間縮短


Parallel GC
---------------------------------


Concurrent GC
---------------------------------


Real-time GC
---------------------------------



案例研究
========================================

OpenJDK
------------------------------

參考：

* `JEP 189: Shenandoah: An Ultra-Low-Pause-Time Garbage Collector <http://openjdk.java.net/jeps/189>`_
* `JEP 248: Make G1 the Default Garbage Collector <http://openjdk.java.net/jeps/248>`_
* `JEP 291: Deprecate the Concurrent Mark Sweep (CMS) Garbage Collector <http://openjdk.java.net/jeps/291>`_
* [2014][YouTube] `"Shenandoah: An open source pauseless GC for OpenJDK." by Christine Flood <https://www.youtube.com/watch?v=QcwyKLlmXeY>`_
* [2016] `Shenandoah GC: Java Without The Garbage Collection Hiccups (Christine Flood) <http://www.slideshare.net/RedHatDevelopers/shenandoah-gc-java-without-the-garbage-collection-hiccups-christine-flood>`_


SerialGC
++++++++++++++++++++

特色：

* Small Footprint
* Minimal Overhead


ParallelGC
++++++++++++++++++++

特色：

* High Throughput


CMS (ParNew/Concurrent Mark Sweep)
++++++++++++++++++++++++++++++++++

特色：

* Minimal Pause Time
* 有 Concurrent Marking
* 在 pause time 進行 young generation copying
* 不會對 old generation 進行 Compaction


G1 (Garbage First)
++++++++++++++++++++

特色：

* Managed Pause Times
* 有部份 Parallel 和 Concurrent
* 有 Compaction
* 沒有 Concurrent Evacuation


Shenandoah
++++++++++++++++++++

目標：<10 ms GC pause times for 100GB+ Heaps

此 GC 的目標是要提供極低（ultra-low）的 pause time，
先前的 CMS 和 G1 都已經可以 Concurrent 地進行 live objects marking，
Shenandoah 則是讓 Compaction 也可以 Concurrent 地進行。


Azul
------------------------------

C4 (Continuously Concurrent Compacting Collector)
+++++++++++++++++++++++++++++++++++++++++++++++++

特色：

* Pauseless

參考：

* `Azul C4 Garbage Collector <https://www.azul.com/resources/azul-technology/azul-c4-garbage-collector/>`_
* `Understanding Java Garbage Collection <https://www.azul.com/files/Understanding_Java_Garbage_Collection_v41.pdf>`_
* [Paper] `C4: The Continuously Concurrent Compacting Collector <https://www.azul.com/files/c4_paper_acm1.pdf>`_
* `JVM performance optimization, Part 4: C4 garbage collection for low-latency Java applications <http://www.javaworld.com/article/2078661/java-concurrency/jvm-performance-optimization--part-4--c4-garbage-collection-for-low-latency-java-ap.html>`_


Android Dalvik VM
------------------------------

ART (Android Runtime)
------------------------------

Go
------------------------------

CPython - Reference Counting
------------------------------

PyPy
------------------------------

Boehm
------------------------------

LuaJIT
------------------------------



深入程式碼
========================================

Rust - Rc - Non-Thread-Safe Reference Counting
----------------------------------------------

Rust 有一個 single-threaded reference-counting 實做在 ``src/liballoc/rc.rs`` ，
以下對於實做的程式碼進行研究。

.. code-block:: rust

    use core::cell::Cell;
    use core::ptr::{self, Shared};

    struct RcBox<T: ?Sized> {
        strong: Cell<usize>,
        weak: Cell<usize>,
        value: T,
    }

    pub struct Rc<T: ?Sized> {
        ptr: Shared<RcBox<T>>,
    }


先從 ``Rc`` sturct 的內容來看，
`core::ptr::Shared <https://doc.rust-lang.org/core/ptr/struct.Shared.html>`_
是對於 ``*mut T`` 的包裝，
用來標示為 Shared Ownership，
所以實際上的資料在 ``RcBox`` 。

``RcBox`` 內含三種資料：

* strong：這個值的 Strong Reference 數量
* weak：這個值的 Weak Reference 數量
* value：實際上的值

``strong`` 和 ``weak`` 都是 ``usize`` ，
但是用了 ``Cell`` 包住，
藉此就算 ``RcBox`` 是 immutable 的，
還是可以更動 ``strong`` 和 ``weak`` 的值，
如此一來我們才能維護 Reference Counting。

我們可以看到下面不遠處有 ``Rc`` 的 method 實做，
從其中的 ``new`` 函式可以了解到我們的 ``Rc`` 是如何建立的：

.. code-block:: rust

    impl<T> Rc<T> {
        /// Constructs a new `Rc<T>`.
        ///
        /// # Examples
        ///
        /// ```
        /// use std::rc::Rc;
        ///
        /// let five = Rc::new(5);
        /// ```
        #[stable(feature = "rust1", since = "1.0.0")]
        pub fn new(value: T) -> Rc<T> {
            unsafe {
                Rc {
                    // there is an implicit weak pointer owned by all the strong
                    // pointers, which ensures that the weak destructor never frees
                    // the allocation while the strong destructor is running, even
                    // if the weak pointer is stored inside the strong one.
                    ptr: Shared::new(Box::into_raw(box RcBox {
                        strong: Cell::new(1),
                        weak: Cell::new(1),
                        value: value,
                    })),
                }
            }
        }

        ...
    }


在 ``Rc`` 剛建立時，
我們除了會有原本想要使用的值之外，
還會有 Strong Reference、Weak Reference，
兩個都被初始化為 1。

那我們會如何增加 Strong Reference 呢？
如果搜尋 ``inc_strong`` 函式，
可以找到一個關鍵 Trait「 ``RcBoxPtr`` 」，
這個 Trait 定義了各種我們想要的功能，
包含 Strong Reference 和 Weak Reference 的取得、增加、減少，
所以只要我們的 ``Rc`` struct 實做這個 Trait 就可以擁有我們 Reference Counting 需要的基本功能。

.. code-block:: rust

    trait RcBoxPtr<T: ?Sized> {
        fn inner(&self) -> &RcBox<T>;

        #[inline]
        fn strong(&self) -> usize {
            self.inner().strong.get()
        }

        #[inline]
        fn inc_strong(&self) {
            self.inner().strong.set(self.strong().checked_add(1).unwrap_or_else(|| unsafe { abort() }));
        }

        #[inline]
        fn dec_strong(&self) {
            self.inner().strong.set(self.strong() - 1);
        }

        #[inline]
        fn weak(&self) -> usize {
            self.inner().weak.get()
        }

        #[inline]
        fn inc_weak(&self) {
            self.inner().weak.set(self.weak().checked_add(1).unwrap_or_else(|| unsafe { abort() }));
        }

        #[inline]
        fn dec_weak(&self) {
            self.inner().weak.set(self.weak() - 1);
        }
    }


接著我們可以在下方馬上找到 ``Rc`` 對於 ``RcBoxPtr`` 的實做：

.. code-block:: rust

    impl<T: ?Sized> RcBoxPtr<T> for Rc<T> {
        #[inline(always)]
        fn inner(&self) -> &RcBox<T> {
            unsafe {
                // Safe to assume this here, as if it weren't true, we'd be breaking
                // the contract anyway.
                // This allows the null check to be elided in the destructor if we
                // manipulated the reference count in the same function.
                assume(!(*(&self.ptr as *const _ as *const *const ())).is_null());
                &(**self.ptr)
            }
        }
    }

至此到一個段落，
接下來只要 ``Rc`` 在進行操作時呼叫對應的函式即可，
例如 clone 時要使用 ``inc_strong`` ：

.. code-block:: rust

    impl<T: ?Sized> Clone for Rc<T> {
        /// Makes a clone of the `Rc` pointer.
        ///
        /// This creates another pointer to the same inner value, increasing the
        /// strong reference count.
        ///
        /// # Examples
        ///
        /// ```
        /// use std::rc::Rc;
        ///
        /// let five = Rc::new(5);
        ///
        /// five.clone();
        /// ```
        #[inline]
        fn clone(&self) -> Rc<T> {
            self.inc_strong();
            Rc { ptr: self.ptr }
        }
    }

drop 時要呼叫 ``dec_strong`` 並判斷是否要回收記憶體：

.. code-block:: rust

    use core::mem::{self, align_of_val, size_of_val};
    use heap::deallocate;

    impl<T: ?Sized> Drop for Rc<T> {
        /// Drops the `Rc`.
        ///
        /// This will decrement the strong reference count. If the strong reference
        /// count reaches zero then the only other references (if any) are
        /// [`Weak`][weak], so we `drop` the inner value.
        ///
        /// [weak]: struct.Weak.html
        ///
        /// # Examples
        ///
        /// ```
        /// use std::rc::Rc;
        ///
        /// struct Foo;
        ///
        /// impl Drop for Foo {
        ///     fn drop(&mut self) {
        ///         println!("dropped!");
        ///     }
        /// }
        ///
        /// let foo  = Rc::new(Foo);
        /// let foo2 = foo.clone();
        ///
        /// drop(foo);    // Doesn't print anything
        /// drop(foo2);   // Prints "dropped!"
        /// ```
        #[unsafe_destructor_blind_to_params]
        fn drop(&mut self) {
            unsafe {
                let ptr = *self.ptr;

                self.dec_strong();
                if self.strong() == 0 {
                    // destroy the contained object
                    ptr::drop_in_place(&mut (*ptr).value);

                    // remove the implicit "strong weak" pointer now that we've
                    // destroyed the contents.
                    self.dec_weak();

                    if self.weak() == 0 {
                        deallocate(ptr as *mut u8, size_of_val(&*ptr), align_of_val(&*ptr))
                    }
                }
            }
        }
    }


要注意的是：

* 此 Reference Counting 不是 atomic 的（也因此 overhead 很小），所以 Rust 會在編譯時期確保沒有在 thread 間傳送
* 沒有 Cycle Detection，所以如果建立了 Cycle，該記憶體會永遠不被清除（直到程式結束），但是可以用 Weak Reference 來避免 Cycle 的產生
* 如果要使用可以在 Thread 間傳送的 Reference Counting 的話，另外有 ``Arc`` 負責


Rust - Arc - Thread-Safe Reference Counting
-------------------------------------------

前面已經介紹了 Rust 的 ``Rc`` ，
但是它不能在 Thread 間傳送，
如果我們真的有這樣的需求該怎麼辦呢？
Rust 中還有另外一個 Reference Counting 實做是可以在 Thread 間傳送的，
它叫做 ``Arc`` ，
顧名思義就是 atomic 版的 ``Rc`` ，
實做的檔案在 ``src/liballoc/arc.rs`` ，
以下接續研究。

一樣直接先來看 ``Arc`` struct：

.. code-block:: rust

    use core::sync::atomic;
    use core::ptr::{self, Shared};

    struct ArcInner<T: ?Sized> {
        strong: atomic::AtomicUsize,

        // the value usize::MAX acts as a sentinel for temporarily "locking" the
        // ability to upgrade weak pointers or downgrade strong ones; this is used
        // to avoid races in `make_mut` and `get_mut`.
        weak: atomic::AtomicUsize,

        data: T,
    }

    pub struct Arc<T: ?Sized> {
        ptr: Shared<ArcInner<T>>,
    }


``Arc`` 長的跟 ``Rc`` 非常像，
但是裡面的 ``RcBox`` 換成了 ``ArcInner`` ，
因此關鍵就在於這 ``ArcInner`` 。
找到 ``ArcInner`` 後會發現，
欄位其實跟 ``RcBox`` 一模一樣，
但是 Strong Reference 和 Weak Reference 的部份從原本的 ``usize`` 換成了 ``atomic::AtomicUsize`` ，
``AtomicUsize`` 是可以安全地在 Thread 間傳送的整數型別。

我們先開個分之出去看 ``AtomicUsize`` 的實做是如何確保 Thread 間操作的正確性的，
``AtomicUsize`` 的實做在 ``src/libcore/sync/atomic.rs`` ，
直接搜尋 ``AtomicUsize`` 會找到一個叫 ``atomic_int!`` 的 macro：

.. code-block:: rust

    #[cfg(target_has_atomic = "ptr")]
    atomic_int!{
        stable(feature = "rust1", since = "1.0.0"),
        stable(feature = "extended_compare_and_swap", since = "1.10.0"),
        stable(feature = "atomic_debug", since = "1.3.0"),
        stable(feature = "atomic_access", since = "1.15.0"),
        usize AtomicUsize ATOMIC_USIZE_INIT
    }

很明顯地所有數值的 Atomic 實做都被包成一個叫 ``atomic_int!`` 的 macro，
如此一來只要呼叫 macro 就可以實做好幾個數值的 Atomic 版本，
我們立馬來看這 macro 做了什麼（為了減少篇幅這邊刪去了不少註解）：

.. code-block:: rust

    macro_rules! atomic_int {
        ($stable:meta,
         $stable_cxchg:meta,
         $stable_debug:meta,
         $stable_access:meta,
         $int_type:ident $atomic_type:ident $atomic_init:ident) => {
            /// An integer type which can be safely shared between threads.
            ///
            /// This type has the same in-memory representation as the underlying integer type.
            #[$stable]
            pub struct $atomic_type {
                v: UnsafeCell<$int_type>,
            }

            /// An atomic integer initialized to `0`.
            #[$stable]
            pub const $atomic_init: $atomic_type = $atomic_type::new(0);

            #[$stable]
            impl Default for $atomic_type {
                fn default() -> Self {
                    Self::new(Default::default())
                }
            }

            #[$stable_debug]
            impl fmt::Debug for $atomic_type {
                fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
                    f.debug_tuple(stringify!($atomic_type))
                     .field(&self.load(Ordering::SeqCst))
                     .finish()
                }
            }

            // Send is implicitly implemented.
            #[$stable]
            unsafe impl Sync for $atomic_type {}

            impl $atomic_type {
                #[inline]
                #[$stable]
                pub const fn new(v: $int_type) -> Self {
                    $atomic_type {v: UnsafeCell::new(v)}
                }

                /// Returns a mutable reference to the underlying integer.
                ///
                /// This is safe because the mutable reference guarantees that no other threads are
                /// concurrently accessing the atomic data.
                #[inline]
                #[$stable_access]
                pub fn get_mut(&mut self) -> &mut $int_type {
                    unsafe { &mut *self.v.get() }
                }

                /// Consumes the atomic and returns the contained value.
                ///
                /// This is safe because passing `self` by value guarantees that no other threads are
                /// concurrently accessing the atomic data.
                #[inline]
                #[$stable_access]
                pub fn into_inner(self) -> $int_type {
                    unsafe { self.v.into_inner() }
                }

                /// Loads a value from the atomic integer.
                #[inline]
                #[$stable]
                pub fn load(&self, order: Ordering) -> $int_type {
                    unsafe { atomic_load(self.v.get(), order) }
                }

                /// Stores a value into the atomic integer.
                #[inline]
                #[$stable]
                pub fn store(&self, val: $int_type, order: Ordering) {
                    unsafe { atomic_store(self.v.get(), val, order); }
                }

                /// Stores a value into the atomic integer, returning the old value.
                #[inline]
                #[$stable]
                pub fn swap(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_swap(self.v.get(), val, order) }
                }

                /// Stores a value into the atomic integer if the current value is the same as the
                /// `current` value.
                ///
                /// The return value is always the previous value. If it is equal to `current`, then the
                /// value was updated.
                #[inline]
                #[$stable]
                pub fn compare_and_swap(&self,
                                        current: $int_type,
                                        new: $int_type,
                                        order: Ordering) -> $int_type {
                    match self.compare_exchange(current,
                                                new,
                                                order,
                                                strongest_failure_ordering(order)) {
                        Ok(x) => x,
                        Err(x) => x,
                    }
                }

                /// Stores a value into the atomic integer if the current value is the same as the
                /// `current` value.
                ///
                /// The return value is a result indicating whether the new value was written and
                /// containing the previous value. On success this value is guaranteed to be equal to
                /// `current`.
                ///
                /// `compare_exchange` takes two [`Ordering`] arguments to describe the memory
                /// ordering of this operation. The first describes the required ordering if
                /// the operation succeeds while the second describes the required ordering when
                /// the operation fails. The failure ordering can't be [`Release`] or [`AcqRel`] and
                /// must be equivalent or weaker than the success ordering.
                #[inline]
                #[$stable_cxchg]
                pub fn compare_exchange(&self,
                                        current: $int_type,
                                        new: $int_type,
                                        success: Ordering,
                                        failure: Ordering) -> Result<$int_type, $int_type> {
                    unsafe { atomic_compare_exchange(self.v.get(), current, new, success, failure) }
                }

                /// Stores a value into the atomic integer if the current value is the same as the
                /// `current` value.
                ///
                /// Unlike [`compare_exchange`], this function is allowed to spuriously fail even
                /// when the comparison succeeds, which can result in more efficient code on some
                /// platforms. The return value is a result indicating whether the new value was
                /// written and containing the previous value.
                ///
                /// `compare_exchange_weak` takes two [`Ordering`] arguments to describe the memory
                /// ordering of this operation. The first describes the required ordering if the
                /// operation succeeds while the second describes the required ordering when the
                /// operation fails. The failure ordering can't be [`Release`] or [`AcqRel`] and
                /// must be equivalent or weaker than the success ordering.
                #[inline]
                #[$stable_cxchg]
                pub fn compare_exchange_weak(&self,
                                             current: $int_type,
                                             new: $int_type,
                                             success: Ordering,
                                             failure: Ordering) -> Result<$int_type, $int_type> {
                    unsafe {
                        atomic_compare_exchange_weak(self.v.get(), current, new, success, failure)
                    }
                }

                /// Add to the current value, returning the previous value.
                #[inline]
                #[$stable]
                pub fn fetch_add(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_add(self.v.get(), val, order) }
                }

                /// Subtract from the current value, returning the previous value.
                #[inline]
                #[$stable]
                pub fn fetch_sub(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_sub(self.v.get(), val, order) }
                }

                /// Bitwise and with the current value, returning the previous value.
                #[inline]
                #[$stable]
                pub fn fetch_and(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_and(self.v.get(), val, order) }
                }

                /// Bitwise or with the current value, returning the previous value.
                #[inline]
                #[$stable]
                pub fn fetch_or(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_or(self.v.get(), val, order) }
                }

                /// Bitwise xor with the current value, returning the previous value.
                #[inline]
                #[$stable]
                pub fn fetch_xor(&self, val: $int_type, order: Ordering) -> $int_type {
                    unsafe { atomic_xor(self.v.get(), val, order) }
                }
            }
        }
    }


實做的函式大致上有這些：

* new
* get_mut
* into_inner
* load
* store
* swap
* compare_and_swap
* compare_exchange
* compare_exchange_weak
* fetch_add
* fetch_sub
* fetch_and
* fetch_or
* fetch_xor

仔細看的話就會發現，
其實都是呼叫對應的 ``atomic_XXX`` 函式來完成，
所以對於 Atomic 的處理必定在那之中，
我們以 ``fetch_add`` 為例，
它呼叫了 ``atomic_add`` ，
搜尋後可以找到這段程式碼：

.. code-block:: rust

    /// Returns the old value (like __sync_fetch_and_add).
    #[inline]
    unsafe fn atomic_add<T>(dst: *mut T, val: T, order: Ordering) -> T {
        match order {
            Acquire => intrinsics::atomic_xadd_acq(dst, val),
            Release => intrinsics::atomic_xadd_rel(dst, val),
            AcqRel => intrinsics::atomic_xadd_acqrel(dst, val),
            Relaxed => intrinsics::atomic_xadd_relaxed(dst, val),
            SeqCst => intrinsics::atomic_xadd(dst, val),
            __Nonexhaustive => panic!("invalid memory ordering"),
        }
    }


根據不同的 Ordering 規則，
會對應到同的 Intrinsics 函式，
部份相關的文件在
`std::intrinsics#Atomics <https://doc.rust-lang.org/std/intrinsics/index.html#atomics>`_ ，
從文件中可以知道 Rust 的 Ordering 規則和 C++11 相同，
這些函式說穿了在 libcore 中其實定義好界面拿來用，
實做也不在其中，
而實際上的定義在 ``src/libcore/intrinsics.rs`` ：

.. code-block:: rust

    extern "rust-intrinsic" {
        ...
        pub fn atomic_xadd<T>(dst: *mut T, src: T) -> T;
        pub fn atomic_xadd_acq<T>(dst: *mut T, src: T) -> T;
        pub fn atomic_xadd_rel<T>(dst: *mut T, src: T) -> T;
        pub fn atomic_xadd_acqrel<T>(dst: *mut T, src: T) -> T;
        pub fn atomic_xadd_relaxed<T>(dst: *mut T, src: T) -> T;
        ...
    }

至此我們可以知道這些 ``atomic_XXX`` 系列的函式都會對應到一個編譯器支援的特別函式。
（如果想要看編譯器如何處理這些 Intrinsics 函式來接到 LLVM 的，
可以看 ``src/librustc_trans/intrinsic.rs`` 程式碼內有 ``name.starts_with("atomic_")`` 的部份）

接下來我們做個大跳躍，
跳回來看 ``Arc`` 是如何被建立的，
這部份其實跟 ``Rc::new`` 大同小異，
做的事情差不了多少：

.. code-block:: rust

    impl<T> Arc<T> {
        /// Constructs a new `Arc<T>`.
        ///
        /// # Examples
        ///
        /// ```
        /// use std::sync::Arc;
        ///
        /// let five = Arc::new(5);
        /// ```
        #[inline]
        #[stable(feature = "rust1", since = "1.0.0")]
        pub fn new(data: T) -> Arc<T> {
            // Start the weak pointer count as 1 which is the weak pointer that's
            // held by all the strong pointers (kinda), see std/rc.rs for more info
            let x: Box<_> = box ArcInner {
                strong: atomic::AtomicUsize::new(1),
                weak: atomic::AtomicUsize::new(1),
                data: data,
            };
            Arc { ptr: unsafe { Shared::new(Box::into_raw(x)) } }
        }

        ...
    }


接著可以在下方不遠處發現先前我們在替 ``Rc`` 實做 ``RcBoxPtr`` Trait 時，
所要提供的函式 ``inner`` ，
但是 ``Arc`` 這邊沒有對應的 Trait 要實做，
不過 ``inner`` 函式要做的事還是相似的：

.. code-block:: rust

    impl<T: ?Sized> Arc<T> {
        ...

        #[inline]
        fn inner(&self) -> &ArcInner<T> {
            // This unsafety is ok because while this arc is alive we're guaranteed
            // that the inner pointer is valid. Furthermore, we know that the
            // `ArcInner` structure itself is `Sync` because the inner data is
            // `Sync` as well, so we're ok loaning out an immutable pointer to these
            // contents.
            unsafe { &**self.ptr }
        }

        ...
    }


有了 ``inner`` 函式我們就可以存取到 ``ArcInner`` 裡面的 Reference Counting 數值，
藉此就能更動裡面的計數器。

接著來看 clone 的實做，
其中直接呼叫了 ``inner`` 函式來存取 Strong Reference，
要注意的是這邊使用了 ``fetch_add`` 來增加 Reference 數量，
做的是對原本的數值加一，
並回傳「原本的數值」，
原本的數值會在後面拿來檢查，
確保沒有 Overflow，
以避免 use after free。
另外要注意的是呼叫 ``fetch_add`` 時，
還傳入了一個參數 ``Relaxed`` ，
這個參數指定的是編譯器和 CPU 可以對指令重新排列的程度，
``Relaxed`` 對應到的是 LLVM 內的 ``Monotonic`` Ordering，
對於指令排列的順序不太有限制，
只要保證是 Atomic 即可
（這邊有引用到 C++ Boost Library 的說明，
在 Reference Counting 的 Context 下，
這邊的操作是可以選擇 ``Relaxed`` 的）：

.. code-block:: rust

    impl<T: ?Sized> Clone for Arc<T> {
        /// Makes a clone of the `Arc` pointer.
        ///
        /// This creates another pointer to the same inner value, increasing the
        /// strong reference count.
        ///
        /// # Examples
        ///
        /// ```
        /// use std::sync::Arc;
        ///
        /// let five = Arc::new(5);
        ///
        /// five.clone();
        /// ```
        #[inline]
        fn clone(&self) -> Arc<T> {
            // Using a relaxed ordering is alright here, as knowledge of the
            // original reference prevents other threads from erroneously deleting
            // the object.
            //
            // As explained in the [Boost documentation][1], Increasing the
            // reference counter can always be done with memory_order_relaxed: New
            // references to an object can only be formed from an existing
            // reference, and passing an existing reference from one thread to
            // another must already provide any required synchronization.
            //
            // [1]: (www.boost.org/doc/libs/1_55_0/doc/html/atomic/usage_examples.html)
            let old_size = self.inner().strong.fetch_add(1, Relaxed);

            // However we need to guard against massive refcounts in case someone
            // is `mem::forget`ing Arcs. If we don't do this the count can overflow
            // and users will use-after free. We racily saturate to `isize::MAX` on
            // the assumption that there aren't ~2 billion threads incrementing
            // the reference count at once. This branch will never be taken in
            // any realistic program.
            //
            // We abort because such a program is incredibly degenerate, and we
            // don't care to support it.
            if old_size > MAX_REFCOUNT {
                unsafe {
                    abort();
                }
            }

            Arc { ptr: self.ptr }
        }
    }


實做 drop，並檢查是否需要清除記憶體：

.. code-block:: rust

    impl<T: ?Sized> Drop for Arc<T> {
        /// Drops the `Arc`.
        ///
        /// This will decrement the strong reference count. If the strong reference
        /// count reaches zero then the only other references (if any) are
        /// [`Weak`][weak], so we `drop` the inner value.
        ///
        /// [weak]: struct.Weak.html
        ///
        /// # Examples
        ///
        /// ```
        /// use std::sync::Arc;
        ///
        /// struct Foo;
        ///
        /// impl Drop for Foo {
        ///     fn drop(&mut self) {
        ///         println!("dropped!");
        ///     }
        /// }
        ///
        /// let foo  = Arc::new(Foo);
        /// let foo2 = foo.clone();
        ///
        /// drop(foo);    // Doesn't print anything
        /// drop(foo2);   // Prints "dropped!"
        /// ```
        #[unsafe_destructor_blind_to_params]
        #[inline]
        fn drop(&mut self) {
            // Because `fetch_sub` is already atomic, we do not need to synchronize
            // with other threads unless we are going to delete the object. This
            // same logic applies to the below `fetch_sub` to the `weak` count.
            if self.inner().strong.fetch_sub(1, Release) != 1 {
                return;
            }

            // This fence is needed to prevent reordering of use of the data and
            // deletion of the data.  Because it is marked `Release`, the decreasing
            // of the reference count synchronizes with this `Acquire` fence. This
            // means that use of the data happens before decreasing the reference
            // count, which happens before this fence, which happens before the
            // deletion of the data.
            //
            // As explained in the [Boost documentation][1],
            //
            // > It is important to enforce any possible access to the object in one
            // > thread (through an existing reference) to *happen before* deleting
            // > the object in a different thread. This is achieved by a "release"
            // > operation after dropping a reference (any access to the object
            // > through this reference must obviously happened before), and an
            // > "acquire" operation before deleting the object.
            //
            // [1]: (www.boost.org/doc/libs/1_55_0/doc/html/atomic/usage_examples.html)
            atomic::fence(Acquire);

            unsafe {
                self.drop_slow();
            }
        }
    }


而實際上回收記憶體的程式碼在這裡：

.. code-block:: rust

    impl<T: ?Sized> Arc<T> {
        ...

        #[inline(never)]
        unsafe fn drop_slow(&mut self) {
            let ptr = *self.ptr;

            // Destroy the data at this time, even though we may not free the box
            // allocation itself (there may still be weak pointers lying around).
            ptr::drop_in_place(&mut (*ptr).data);

            if self.inner().weak.fetch_sub(1, Release) == 1 {
                atomic::fence(Acquire);
                deallocate(ptr as *mut u8, size_of_val(&*ptr), align_of_val(&*ptr))
            }
        }

        ...
    }


要注意的是：

* 沒有 Cycle Detection，所以如果建立了 Cycle，該記憶體會永遠不被清除（直到程式結束），但是可以用 Weak Reference 來避免 Cycle 的產生



參考
========================================

* `Wikipedia - Mark-compact algorithm <https://en.wikipedia.org/wiki/Mark-compact_algorithm>`_
* `the Garbage Collection Bibliography <https://www.cs.kent.ac.uk/people/staff/rej/gcbib/>`_
* `Garbage collection thoughts <http://sebastiansylvan.com/post/garbage-collection-thoughts/>`_
* `Origins of Garbage Collection <https://www.seas.harvard.edu/courses/cs252/2016fa/16.pdf>`_
* `International Symposium on Memory Management (ISMM) <http://www.sigplan.org/Conferences/ISMM/>`_

.. [robs80] [1980] J. M. Robson. `Storage allocation is NP-hard <http://dx.doi.org/10.1016/0020-0190(80)90124-6>`_
.. [abua04] [2004] Diab Abuaiadh, Yoav Ossia, Erez Petrank, and Uri Silbershtein. `An efficient parallel heap compaction algorithm <https://www.research.ibm.com/haifa/projects/systems/rs/papers/ParCompac_OOPSLA04.pdf>`_
