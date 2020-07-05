========================================
Python
========================================


以下採用 CPython 3.6.0


.. contents:: 目錄


語言環境
========================================

Virtual Machine
------------------------------

Python 是一個直譯式語言，
而事實上 Python 會先把程式碼編譯成 Byte Code，
Byte Code 會再被內部的程式執行，
一些 JIT 實做還會在執行中選擇較常使用的部份拿去再編譯，
以獲得更好的效能，
現有的 JIT 實做以 PyPy 最為成熟。

整體運作流程大致如下：

* 建立直譯器和 Main Thread
* 初始化 Built-in Types，不同型別可能會有不同 Cache Strategy 要處理
* 建立 ``__builtin__`` module，內含所有 Built-in Types 和 Built-in Functions
* 建立 ``sys`` ，內含 sys.path 和 sys.modules 等重要的執行期間的訊息
* 初始化 import 機制
* 初始化 Built-in Exception
* 建立 ``__main__`` module，準備執行時需要的 Namespace
* 透過 ``site.py`` 將 ``site-packages`` 中的第三方套件加到搜尋路徑列表中
* 執行程式的進入點，執行前會把 ``__main__.__dict__`` 當作 Namespace 傳進去
* 程式執行結束
* 清理，呼叫 exit 函式、GC 清理所有控管的記憶體、釋放所有 Modules 等
* 程式正式終結


Type & Object
------------------------------

對於 Python 來說，
任何東西都是物件，
包含型別本身也是個物件，
物件都有一個 Header 可以讓內部知道確切的型別。

以 CPython 來說，
Header 訊息由 Reference Counter 和型別指標組成，
Reference Counter 會在物件被 Reference 時增加，
超出 scope 或手動釋放時會減少，
等於 0 時就會被回收（某些特殊的物件永遠不會變成 0），
以 ``int`` 為例，
其 Header 為：

.. code-block:: c

    // Include/longobject.h
    typedef struct _longobject PyLongObject;

    // include/longintrepr.h
    struct _longobject {
        PyObject_VAR_HEAD
        digit ob_digit[1];
    };

    // include/object.h
    #define PyObject_VAR_HEAD      PyVarObject ob_base;

    typedef struct {
        PyObject ob_base;
        Py_ssize_t ob_size; /* Number of items in variable part */
    } PyVarObject;

    typedef struct _object {
        _PyObject_HEAD_EXTRA            // 這是用來建立 Double Linked List 的
                                        // 以追蹤 Heap 上所有 live objects
                                        // 開啟 Py_TRACE_REFS 時才會有，否則是空的
        Py_ssize_t ob_refcnt;           // 這裡是 Reference Counter
        struct _typeobject *ob_type;    // 這裡是型別指標
    } PyObject;


    #define _PyObject_HEAD_EXTRA            \
        struct _object *_ob_next;           \
        struct _object *_ob_prev;



利用 ``sys`` 做檢驗：

.. code-block:: python

    >>> import sys
    >>> x = 0x1234
    >>> sys.getsizeof(x)
    28
    >>> sys.getrefcount(x)
    2
    >>> y = x
    >>> sys.getrefcount(x)
    3
    >>> del y
    >>> sys.getrefcount(x)
    2


型別指標會指向型別物件，
其中包含繼承關係和靜態成員等資訊

.. code-block:: python

    >>> import types
    >>> x = 42
    >>> type(x) is int
    True
    >>> x.__class__     # 透過型別指標來取得型別物件
    <class 'int'>
    >>> x.__class__ is type(x) is int
    True
    >>> y = x
    >>> hex(id(x)), hex(id(y))      # id 會回傳物件的記憶體位置
    ('0x7fc382987ae0', '0x7fc382987ae0')


Namespace
------------------------------

.. code-block:: python

    >>> foo
    Traceback (most recent call last):
      File "<stdin>", line 1, in <module>
    NameError: name 'foo' is not defined

和 C 以記憶體位置做變數處理不同，
在 Python 中，
變數會以 Name 做查詢，
Namespace 內會維護一個字串對應到物件的字典。
在 Python 中有許多 Namespace，
例如 ``globals`` 、 ``locals`` 、 class 、 instance，
不同的 Namespace 決定了物件可使用和存活的範圍。


.. code-block:: python

    >>> x = 42
    >>> globals()
    {'__name__': '__main__', '__doc__': None, '__package__': None, '__loader__': <_frozen_importlib_external.SourceFileLoader object at 0x7fc0010759b0>, '__spec__': None, '__annotations__': {}, '__builtins__': <module 'builtins' (built-in)>, '__cached__': None, 'x': 42}
    >>> globals()['foo'] = "XD"     # 因為是一般的字典，所以可以直接加入新的值
    >>> foo
    'XD'


也因此變數名稱沒有型別，
物件才有，
「Names have no type, but objects do」。
變數名稱的用途是在使用時從 Namespace 中查詢，
找到真正的物件，
本身不包含物件的任何訊息，
正因為如此我們可以隨時將它對應到任何不同型別的物件。

.. code-block:: python

    >>> foo = 'Hello World'
    >>> type(foo)
    <class 'str'>
    >>> foo = __import__("string")    # 把變數對應到 module
    >>> type(foo)
    <class 'module'>
    >>> foo.digits      # module 物件的成員
    '0123456789'


可以使用 ``__dict__`` 來存取不同 module 的 Namespace

.. code-block:: python

    >>> import math
    >>> math.__dict__
    {'__name__': 'math', '__doc__': 'This module is always available.  It provides access to the\nmathematical functions defined by the C standard.', '__package__': '', '__loader__': <_frozen_importlib_external.ExtensionFileLoader object at 0x7f9f63b6f9e8>, '__spec__': ModuleSpec(name='math', loader=<_frozen_importlib_external.ExtensionFileLoader object at 0x7f9f63b6f9e8>, ... }
    >>> import sys
    >>> sys.modules[__name__].__dict__  # 目前 module 的 Namespace


與 Namespace 相關的內容很多，
包含 scope、LEGB 尋找規則、成員尋找規則等，
使用 Namespace 管理 context 物件可以提供很大的靈活性，
但相對的就犧牲了效能，
效能比 C 使用指標低了很多。

LEGB

* L: Local — Names assigned in any way within a function (def or lambda)), and not declared global in that function.
* E: Enclosing-function locals — Name in the local scope of any and all statically enclosing functions (def or lambda), from inner to outer.
* G: Global (module) — Names assigned at the top-level of a module file, or by executing a global statement in a def within the file.
* B: Built-in (Python) — Names preassigned in the built-in names module : open,range,SyntaxError,...


記憶體管理
------------------------------

CPython 在記憶體管理中做了很多事，
其中包含使用 Memory Pool 來減少跟作業要記憶體和回收的次數，
少於 512 bytes 的物件都會直接從 Memory Pool 中取得空間。

根據需求，
CPython 每次至少會向作業系統要 8192 bytes 的記憶體，
取名為 arena 的一大塊記憶體，
其執中會分割成多個 pool，
每個 pool 分割成 n 個大小相同的 block，
這是 memory pool 內最小的單位。
block 大小是 8 的倍數，
所以需要 13 bytes 的物件會佔用 16 bytes 的 pool，
這接都會用 Header 和 Linked List 管理，
以便查詢空的區域來使用。
大於 512 bytes 的物件會直接使用 malloc 來要記憶體，
由於程式中大部份的物件都小於這個值，
所以 memory pool 可以有效提昇效能。
當所有 arena 的總大小超過 64 MB 時，
就不會在要新的 arena 記憶體，
而是全部使用 malloc 來分配空間。
完全空閒的 arena 會被釋放，
交還給作業系統。

.. code-block:: c

    // Python/pyarena.c

    #define DEFAULT_BLOCK_SIZE 8192

    PyArena *
    PyArena_New()
    {
        PyArena* arena = (PyArena *)PyMem_Malloc(sizeof(PyArena));
        if (!arena)
            return (PyArena*)PyErr_NoMemory();

        arena->a_head = block_new(DEFAULT_BLOCK_SIZE);
        arena->a_cur = arena->a_head;
        ...
    }

    static void *
    block_alloc(block *b, size_t size)
    {
        void *p;
        size = _Py_SIZE_ROUND_UP(size, ALIGNMENT);
        if (b->ab_offset + size > b->ab_size) {
            /* If we need to allocate more memory than will fit in
               the default block, allocate a one-off block that is
               exactly the right size. */
            block *newbl = block_new(
                            size < DEFAULT_BLOCK_SIZE ?
                            DEFAULT_BLOCK_SIZE : size);
            if (!newbl)
                return NULL;
            assert(!b->ab_next);
            b->ab_next = newbl;
            b = newbl;
        }

        p = (void *)(((char *)b->ab_mem) + b->ab_offset);
        b->ab_offset += size;
        return p;
    }

    static block *
    block_new(size_t size)
    {
        /* Allocate header and block as one unit.
           ab_mem points just past header. */
        block *b = (block *)PyMem_Malloc(sizeof(block) + size);
        if (!b)
            return NULL;
        b->ab_size = size;
        b->ab_mem = (void *)(b + 1);
        b->ab_next = NULL;
        b->ab_offset = (char *)_Py_ALIGN_UP(b->ab_mem, ALIGNMENT) -
                (char *)(b->ab_mem);
        return b;
    }


.. code-block:: c

    // Objects/obmalloc.c

    /*
     * Allocation strategy abstract:
     *
     * For small requests, the allocator sub-allocates <Big> blocks of memory.
     * Requests greater than SMALL_REQUEST_THRESHOLD bytes are routed to the
     * system's allocator.
     *
     * ...
     *
     */

    #define SMALL_REQUEST_THRESHOLD 512


Pass by Reference
++++++++++++++++++++

Python 的物件都使用 Pass by Reference，
也就是會複製指標來指向同一個物件，
因為 arena 也是在 Heap 上的記憶體，
所以無論何種物件都存在 Heap 上。
Python 沒有 Value Type 和 Reference Type，
連基本的整數也是完整的物件

.. code-block:: python

    >>> a = object()
    >>> b = a
    >>> a is b
    True
    >>> hex(id(a)), hex(id(b))      # 記憶體位置相同
    ('0x7f9f63c6b110', '0x7f9f63c6b110')
    >>> def func(x): print(hex(id(x)))

    >>> func(a)     # Pass by Reference，所以記憶體位置相同
    0x7f9f63c6b110


如果不希望物件被更改，
則必須使用不可更動的型別，
內建的有：

* int
* str
* tuple
* frozenset

如此之外，
還可以使用 copy module 來做 deep copy，
或是使用 pickle、cPickle、marshal 將物件序列化

.. code-block:: python

    >>> import copy
    >>> x = object()
    >>> l = [x]

    >>> l2 = copy.copy(l)   # Shallow Copy，只複製物件本身，不會遞迴地複製其成員
    >>> l2 is l
    False
    >>> l2[0] is x
    True

    >>> l3 = copy.deepcopy(l)   # Deep Copy，遞迴地複製所有成員
    >>> l3 is l
    False
    >>> l3[0] is x              # Shallow Copy 和 Deep Copy 的差異
    False



Reference Counting
++++++++++++++++++++

CPython 使用 Reference Counting 來管理物件的記憶體，
當計數器變成 0 時，
就立即回收該物件的記憶體，
可能將 block 標成空閒或是還給作業系統。

要觀察回收可以使用 ``__del__``

.. code-block:: python

    >>> class MyObj(object):
    ...     def __del__(self):
    ...         print("Dying")

    >>> a = MyObj()
    >>> b = a
    >>> import sys
    >>> sys.getrefcount(a)
    3
    >>> del a
    >>> sys.getrefcount(a)
    2
    >>> del b
    Dying


某些內建的物件因為 Cache 的關係，
計數器永遠不會變成 0，
直到 VM 清理函式執行時釋放。

除了直接 Reference 外（Strong Reference），
CPython 還支援 Weak Reference，
可以在不增加計數器和影響物件回收的情況下間接使用物件

.. code-block:: python

    >>> import sys, weakref
    >>> class MyObj(object): pass

    >>> def callback(r): print("Weak Reference", r)

    >>> x = MyObj()
    >>> r = weakref.ref(x, callback)
    >>> sys.getrefcount(x)  # 2 是因為 getrefcount 的參數造成的， Weak Reference 沒有造成計數器上升
    2
    >>> r() is x            # 間接使用原物件
    True
    >>> del x               # 物件被回收，callback 被呼叫
    Weak Reference <weakref at 0x7f9f61a950e8; dead>
    >>> r() is None         # 此時因為物件已死亡，所以回傳 None
    True


Reference Counting 是一個簡單的管理方式，
但是如果發生 Cycle Reference 就會無法被回收，
此時就要另外的 GC 去處理。


Garbage Collection
++++++++++++++++++++

CPython 的記憶體管理由兩部份組成，
其中一個是前面提到的 Reference Counting，
另一個是專門處理 Cycle Reference 的 GC。

.. code-block:: c

    // include/objimpl.h
    typedef union _gc_head {
        struct {
            union _gc_head *gc_next;
            union _gc_head *gc_prev;
            Py_ssize_t gc_refs;
        } gc;
        double dummy;  /* force worst-case alignment */
    } PyGC_Head;


如果確定不會發生 Cycle Reference 的話，
其實不執行這個 GC 也可以，
靠前面提到的單純 Reference Counting 就可以解決，
因此有提供可以關掉這個 Cycle GC 的方式：

.. code-block:: python

    >>> import gc
    >>> class MyObj(object):
    ...     def __del__(self):
    ...         print(hex(id(self)), "is dying")

    >>> gc.disable()    # 關掉 Cycle Reference 處理
    >>> x = MyObj()
    >>> del x           # 正常回收
    0x7f9f61f83e80 is dying


CPython 的 Cycle GC 把要回收的物件分成 3 個世代，
``GEN0`` 管理新加入的年輕物件，
``GEN1`` 則是上次回收後仍然存在的物件，
``GEN2`` 內的都是生命週期特別長的物件，
每個年齡層都有最大容量的門檻，
每次 ``GEN0`` 的物件數量超過門檻時就會觸發回收執行：

.. code-block:: c

    // Module/gcmodule.c

    /* If we change this, we need to change the default value in the signature of
       gc.collect. */
    #define NUM_GENERATIONS 3

    /* linked lists of container objects */
    static struct gc_generation generations[NUM_GENERATIONS] = {
        /* PyGC_Head,                               threshold,      count */
        {{{GEN_HEAD(0), GEN_HEAD(0), 0}},           700,            0},
        {{{GEN_HEAD(1), GEN_HEAD(1), 0}},           10,             0},
        {{{GEN_HEAD(2), GEN_HEAD(2), 0}},           10,             0},
    };


GC 先檢查 ``GEN2`` ，
如過超過門檻就合併 ``GEN2`` 、 ``GEN1`` 、 ``GEN0`` 的 Linked List，
如果沒有超過就檢查 ``GEN1`` ，
GC 執行完後將仍然存活的物件提昇各自的世代，
可回收的物件則破壞 Cycle Reference，
放到專門的列表中等回收。

.. code-block:: python

    >>> import gc
    >>> gc.get_threshold()  # 各世代的門檻
    (700, 10, 10)
    >>> gc.get_count()      # 各世代追蹤的物件數量
    (267, 4, 1)


我們可以用 ``weakref`` 來觀察：

.. code-block:: python

    >>> import gc, weakref
    >>> class MyObj(object): pass

    >>> def callback(r): print("Weak Reference", r)

    >>> gc.disable()
    >>> a = MyObj(); wa = weakref.ref(a, callback)
    >>> b = MyObj(); wb = weakref.ref(b, callback)
    >>> a.b, b.a = b, a     # 建立 Cycle Reference
    >>> del a; del b        # 刪除名稱的引用
    >>> wa(), wb()          # 物件仍然存在
    (<__main__.MyObj object at 0x7f9f5e2d0b38>, <__main__.MyObj object at 0x7f9f5e2d08d0>)
    >>> gc.enable()
    >>> gc.isenabled()
    True
    >>> gc.collect()        # 手動觸發
    Weak Reference <weakref at 0x7f9f5c44e2c8; dead>    # 這是 Weak Reference 物件的記憶體位置
    Weak Reference <weakref at 0x7f9f5c44e318; dead>
    4


我們也可以用 ``__del__`` 觀察，
還可以開 gc module 的除錯訊息來看：

.. code-block:: python

    >>> import gc, weakref
    >>> class MyObj(object):
    ...     def __del__(self):
    ...         print(hex(id(self)), "is dying")

    >>> gc.disable()
    >>> a = MyObj()
    >>> b = MyObj()
    >>> a.b, b.a = b, a     # 建立 Cycle Reference
    >>> del a; del b        # 刪除名稱的引用
    >>> gc.enable()
    >>> gc.set_debug(gc.DEBUG_STATS | gc.DEBUG_LEAK)    # 看更多訊息
    >>> gc.isenabled()
    True
    >>> gc.collect()        # 手動觸發
    gc: collecting generation 2...
    gc: objects in each generation: 817 289 4981
    gc: collectable <tuple 0x7fbd4dd31da0>
    gc: collectable <function 0x7fbd4dac9158>
    gc: collectable <tuple 0x7fbd4dd39168>
    gc: collectable <function 0x7fbd4dac91e0>
    gc: collectable <tuple 0x7fbd4dd31d68>
    gc: collectable <function 0x7fbd4dac9268>
    gc: collectable <function 0x7fbd4dac92f0>
    gc: collectable <function 0x7fbd4dac9378>
    gc: collectable <function 0x7fbd4dac9400>
    gc: collectable <function 0x7fbd4dac9488>
    gc: collectable <function 0x7fbd4dac9510>
    gc: collectable <function 0x7fbd4dac9598>
    gc: collectable <function 0x7fbd4dac9620>
    gc: collectable <function 0x7fbd4dac96a8>
    gc: collectable <function 0x7fbd4dac9730>
    gc: collectable <tuple 0x7fbd4dd31fd0>
    gc: collectable <function 0x7fbd4dac97b8>
    gc: collectable <function 0x7fbd4dac9840>
    gc: collectable <cell 0x7fbd4dd2f078>
    gc: collectable <function 0x7fbd4dac9950>
    gc: collectable <cell 0x7fbd4dd2f0a8>
    gc: collectable <cell 0x7fbd4dd2f0d8>
    gc: collectable <set 0x7fbd4f8f19e8>
    gc: collectable <tuple 0x7fbd4dd40f30>
    gc: collectable <function 0x7fbd4dac99d8>
    gc: collectable <function 0x7fbd4dac98c8>
    gc: collectable <function 0x7fbd4dac9a60>
    gc: collectable <function 0x7fbd4dac9ae8>
    gc: collectable <classmethod 0x7fbd4dac4320>
    gc: collectable <function 0x7fbd4dac9b70>
    gc: collectable <dict 0x7fbd4dac66c0>
    gc: collectable <type 0x1002fa8>
    gc: collectable <getset_descriptor 0x7fbd4dac6750>
    gc: collectable <getset_descriptor 0x7fbd4dac6798>
    gc: collectable <tuple 0x7fbd4dac67e0>
    gc: collectable <MyObj 0x7fbd4dd0ac50>
    gc: collectable <MyObj 0x7fbd4f914b38>
    gc: collectable <dict 0x7fbd4f990480>
    gc: collectable <dict 0x7fbd4f915e58>
    0x7fbd4dd0ac50 is dying     # 我們物件的 __del__
    0x7fbd4f914b38 is dying
    gc: done, 39 unreachable, 0 uncollectable, 0.0018s elapsed
    39
