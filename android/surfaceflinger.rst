========================================
SurfaceFlinger
========================================


Andoird 上的 Graphic 可以分成 2D 和 3D，
2D 使用的是 android.graphics.Canvas API，
為最常用的 graphics API，
Canvas 還負責描繪出客制化的 android.view.View，
在 Android 中會利用 OpenGLRenderer (libhwui) 這個 library 來把 Canvas 操作轉換成 OpenGL 操作，
藉此可以利用 GPU 加速。

Android 4.0 以後預設會開啟 Canvas 的硬體加速，
所以在這之後強制限定 Android devices 至少要支援 OpenGL ES 2.0。

除了 Canvas 之外，
要描繪東西就是使用 OpenGL ES，
Android 的 ``android.opengl`` 有提供 OpenGL ES 的介面可以使用，
開發者可以透過 Android SDK/NDK 使用。

2D rendering path :

::

    +-----------------------------------+
    |            Activity               |
    +-----------------------------------+
                    |
                    v
    +-----------------------------------+
    |            Canvas                 |
    +-----------------------------------+
                    |
         hardware   |    software
         (default)  |
            +-------+-----------+
            |                   |
            v                   v
    +---------------+   +---------------+
    | HWUI          |   | Skia          |
    +---------------+   +---------------+
            |                   |
            v                   |
    +---------------+           |
    | OpenGL ES     |           |
    +---------------+           |
            |                   |
            v                   |
    +---------------+           |
    | Vender OpenGL |           |
    +---------------+           |
            |                   |
            v                   |
    +---------------+           |
    | GPU Driver    |           |
    +---------------+           |
            |                   |
            v                   v
    +-----------------------------------+
    |            Surface                |
    +-----------------------------------+

3D rendering path :

::

    +-----------------------------------+
    |            Activity               |
    +-----------------------------------+
                    |
                    v
    +-----------------------------------+
    |            OpenGL ES              |
    +-----------------------------------+
                    |
         hardware   |    software
         (default)  |
            +-------+-----------+
            |                   |
            v                   v
    +---------------+   +----------------+
    | Vender OpenGL |   | Android OpenGL |
    +---------------+   +----------------+
            |                   |
            v                   v
    +---------------+   +-----------------------------+
    | GPU Driver    |   | PixelFlinger (Software GPU) |
    +---------------+   +-----------------------------+
            |                   |
            v                   v
    +-----------------------------------+
    |            Surface                |
    +-----------------------------------+


無論是用哪種 rendering API，
最後都會 render 到 **surface** ，
surface 會作為 buffer queue 的 producer 存在，
而 SurfaceFlinger 則是 consumer，
以下是大致的運作流程 :

.. image:: https://source.android.com/devices/graphics/images/ape_fwk_graphics.png

----

Android 上所有 graphical 相關的核心是 BufferQueue，
它的工作是負責連接 producer 和 consumer，
producer 會產生 graphical data 的 buffer，
而 consumer 則會接收 data 來顯示或著做其他處理，
producer 和 consumer 可以是不同的 process，
Android 上幾乎所有在系統內傳送 graphical data 的都是靠 BufferQueue 完成。

BufferQueue :

.. image:: https://source.android.com/devices/graphics/images/bufferqueue.png

producer 會用 ``dequeueBuffer`` 來取得 free buffer，
producer 在放完資料後用 ``queueBuffer`` 來放回去 BufferQueue，
接著 consumer 用 ``acquireBuffer`` 來取得、使用 buffer 裡的 data，
最後用 ``releaseBuffer`` 釋出。

.. image:: https://source.android.com/devices/graphics/images/graphics_pipeline.png

BufferQueue 有三種運作模式：

* Synchronous-like mode
* Non-blocking mode
* Discard mode

----

* sync framework


Reference
========================================

* `Android - Graphics <https://source.android.com/devices/graphics/>`_
* `Android - Graphics architecture <https://source.android.com/devices/graphics/architecture.html>`_
