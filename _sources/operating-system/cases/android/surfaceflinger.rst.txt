========================================
SurfaceFlinger
========================================



一般來說 Graphic 相關事情會分成 2D 跟 3D，
Android 上也是如此。
Android 上 2D 使用的是一個叫作 ``android.graphics.Canvas`` 的 API，
為最常用的 graphics API。
在 Android 中 Canvas 會利用 OpenGLRenderer (libhwui) 這個 library 來把 Canvas 操作轉換成 OpenGL 操作，
藉此可以利用 GPU 加速。
(Canvas 負責的項目包含描繪出客制化的 ``android.view.View``)

註：Android 4.0 以後預設會開啟 Canvas 的硬體加速，
所以在這之後強制限定 Android devices 至少要支援 OpenGL ES 2.0。

除了 Canvas 之外，
要描繪出東西就是使用 OpenGL ES，
Android 的 ``android.opengl`` 就是負責提供 OpenGL ES 的介面來使用，
開發者可以透過 Android SDK/NDK 來呼叫。

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
    - 預設的模式
    - 保證每個從 producer 進來的資料都會交給 consumer
    - 不會有 buffer 被忽略
    - producer 產生太快造成 buffer 放不下的話會被 block 住
* Non-blocking mode
    - 不會有 buffer 被忽略
    - producer 產生太快造成 buffer 放不下的話會回傳 error，不會 block
    - 可用於避免應用程式不了解 graphics framework 的 dependencies 所造成的 deadlock
* Discard mode
    - buffer 可以被忽略

SurfaceFlinger 的行為是一個 OpenGL ES 的 client，
所以 SurfaceFlinger 在運作時會使用 OpenGL ES。
而 Hardware Composer HAL 則負責另一部份的工作，
作為 Android graphics rendering 的中心。

----

* sync framework

Code
========================================

SurfaceFlinger.cpp
------------------------------

* EGL
    - EGL 是 OpenGL 與 windowing system 銜接的 API
* ALOGI
    - log
    - ALOGI/ALOGE/ALOGW
    - Android Log
    - information / error / warning ?

Choreographer
========================================

* https://source.android.com/devices/graphics/architecture.html#choreographer

Reference
========================================

* `Android - Graphics <https://source.android.com/devices/graphics/>`_
* `Android - Graphics architecture <https://source.android.com/devices/graphics/architecture.html>`_
* `Wikipedia - EGL (API) <https://en.wikipedia.org/wiki/EGL_%28API%29>`_
* `The Android graphics path in depth <http://events.linuxfoundation.org/sites/events/files/slides/android-graphics-abs-2014_0.pdf>`_
