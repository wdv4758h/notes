========================================
GLib
========================================


.. contents:: 目錄


Memory Allocation
========================================

GLib 的 `Memory Allocation <https://developer.gnome.org/glib/unstable/glib-Memory-Allocation.html>`_
相關處理都在 ``glib/gmem.h`` 和 ``glib/gmem.c`` ，
大部分都是基於 C stdlib 的包裝，
多加些檢查和提供更方便的介面。

GLib 以前支援使用非系統的 allocator，
但是現在已經移除，
只會使用系統提供的 allocator。


以 malloc 為範例；

* malloc
    - 直接分配特定大小的記憶體
* `g_malloc <https://github.com/GNOME/glib/blob/8a96fca3908609407f59c8f5be8de982a76114c1/glib/gmem.c#L93>`_
    - 基於 malloc 多加了 log 和失敗檢查
* `g_malloc_n <https://github.com/GNOME/glib/blob/8a96fca3908609407f59c8f5be8de982a76114c1/glib/gmem.c#L331>`_
    - 基於 g_malloc，參數包裝成「幾塊」和「每塊大小」
    - 檢查 overflow
* `_G_NEW <https://github.com/GNOME/glib/blob/8a96fca3908609407f59c8f5be8de982a76114c1/glib/gmem.h#L257>`_
    - 基於 g_malloc_n，參數包裝成「型別」、「數量」、「使用的 allocator 名稱」
    - ``_G_NEW`` 有另外優化的版本，如果可以在編譯時確定不會 overflow 的話就省去 ``_n`` 系列的函式呼叫
* `g_new <https://github.com/GNOME/glib/blob/8a96fca3908609407f59c8f5be8de982a76114c1/glib/gmem.h#L280>`_
    - 基於 _G_NEW，參數包裝成「型別」、「數量」


.. code-block:: c

    // 使用
    DATA_TYPE *mem                = g_new(DATA_TYPE, COUNT);
    gint *newkey                  = g_new(gint, 1);
    guint **mema                  = g_new(guint*, n);
    char **foo                    = g_new(char*, 1);
    GSourceCallback* new_callback = g_new(GSourceCallback, 1);

    // g_new
    #define g_new(struct_type, n_structs) _G_NEW (struct_type, n_structs, malloc)

    // _G_NEW
    #define _G_NEW(struct_type, n_structs, func) ((struct_type *) g_##func##_n ((n_structs), sizeof (struct_type)))

    // g_malloc_n
    gpointer
    g_malloc_n (gsize n_blocks,
                gsize n_block_bytes)
    {
      if (SIZE_OVERFLOWS (n_blocks, n_block_bytes))
        {
          g_error ("%s: overflow allocating %"G_GSIZE_FORMAT"*%"G_GSIZE_FORMAT" bytes",
                   G_STRLOC, n_blocks, n_block_bytes);
        }

      return g_malloc (n_blocks * n_block_bytes);
    }

    // g_malloc
    gpointer
    g_malloc (gsize n_bytes)
    {
      if (G_LIKELY (n_bytes))
        {
          gpointer mem;

          mem = malloc (n_bytes);
          TRACE (GLIB_MEM_ALLOC((void*) mem, (unsigned int) n_bytes, 0, 0));
          if (mem)
            return mem;

          g_error ("%s: failed to allocate %"G_GSIZE_FORMAT" bytes",
                   G_STRLOC, n_bytes);
        }

      TRACE(GLIB_MEM_ALLOC((void*) NULL, (int) n_bytes, 0, 0));

      return NULL;
    }

    // malloc
    // 系統 libc 實做



I/O
========================================



參考
========================================

* `GLib Reference Manual <https://developer.gnome.org/glib/unstable/>`_
* `Hackfests in the GNOME-related world <https://wiki.gnome.org/Hackfests>`_
* `Events - GNOME Wiki! <https://wiki.gnome.org/Events>`_
* `Planet GNOME <http://planet.gnome.org/>`_
