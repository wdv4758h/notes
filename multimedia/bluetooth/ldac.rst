========================================
LDAC codec
========================================


.. contents:: 目錄


介紹
========================================

LDAC 是 Sony 在 2015 年開始大量使用的 audio codec，
針對藍芽的使用環境做優化，
最高支援 990 kbit/s 24bit/96khz。

LDAC 是有損壓縮（Lossy），
採用基於 MDCT (Modified Discrete Cosine Transform) 的混合式編碼來提供更有效率的壓縮，
主要競爭者是 Qualcomm 的 aptX-HD。

自 Android 8.0 Oreo 開始，
來自 Sony 的 libldac 以 Apache 條款釋出，
LDAC 的支援被加入 AOSP 專案中。



BlueZ 支援
========================================

* `bluez-alsa - LDAC issue <https://github.com/Arkq/bluez-alsa/issues/104>`_
    - `bluez-alsa wiki - LDAC <https://github.com/Arkq/bluez-alsa/wiki/Installing-libldac-library>`_



參考
========================================

* `Sony - LDAC <https://www.sony.net/Products/LDAC/>`_
* `Wikipedia - LDAC (codec) <https://en.wikipedia.org/wiki/LDAC_(codec)>`_
* `Wikipedia - Bluetooth stack <https://en.wikipedia.org/wiki/Bluetooth_stack>`_
* `Wikipedia - List of Bluetooth protocols <https://en.wikipedia.org/wiki/List_of_Bluetooth_protocols>`_
* `Wikipedia - High-resolution audio <https://en.wikipedia.org/wiki/High-resolution_audio>`_
* `AOSP - libldac <https://android.googlesource.com/platform/external/libldac>`_
