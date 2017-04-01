========================================
Audio
========================================


.. contents:: 目錄


介紹
========================================

* Audio compression
    - ISO/IEC
        + MP3 (MPEG-1 Layer III)
        + AAC
        + ...
    - ITU-T
        + G.711
        + ...
    - IETF
        + Opus
        + iLBC
    - 3GPP
        + AMR
        + ...
    - 其他
        + ALAC
        + FLAC
        + ...

* Containers
    - ISO/IEC
        + MPEG-ES
        + MPEG-TS
        + MJPEG (Motion JPEG)
        + MP4 (MPEG-4 Part 14)
        + ...
    - ITU-T
        + H.222.0
        + ...
    - IETF
        + RTP
    - 其他
        + AVI
        + Ogg
        + WAV
        + ...



MP3
========================================



AAC (Advanced Audio Coding)
========================================

規範列表：

* MPEG-2 AAC
* MPEG-4 AAC
* HE-AAC
* HE-AAC V2


1997 年 4 月，
MPEG-2 AAC 壓縮演算法成為了規範，
其中應用了當時的一些新 spectrum processing 和壓縮工具
（例如 temporal noise shaping （TNS）），
和先前的音訊壓縮演算法相比有顯著的品質提昇和優異的壓縮率，
因此可以在 encoded bitstreams 內達到較低的 bit rate，
這規範也漸漸地成為 broadcasting、internet services、mobile applications 的常見選擇。

1999 年，
MPEG-4 AAC 基於 MPEG-2 AAC 發展更多的能力，
同時也維持良好的向下相容。
這個新規範改善了 scalability、error resilience 和新增一些 spectral processing 能力
（例如 Perceptual Noise Substitution （PNS）、Long-Term Predictor （LTP）），
因此如果使用這些新功能的話，
MPEG-2 AAC Decoder 會不能處理 MPEG-4 AAC，
但是 MPEG-4 AAC Decoder 仍然可以處理 MPEG-2 AAC bitstreams。

2003 年，
新增了 High Efficiency AAC （HE-AAC）規範，
這規範擴充了 AAC 演算法，
改進了在 low bit-rate 應用程式上的編碼效能。
HE-AAC 採用了新的工具叫 Spectral Band Replication （SBR），
可以藉由 low-frequency band data 和一些額外資訊來重新建立 high-frequency band data。

2004 年，
新增了 HE-AAC V2，
在 SBR 的基礎上利用了 Parametric Stereo （PS），
可以藉由 monaural downmixed signals 和 limited number of additional stereo parameters
來重新建立 stereo audio signals。


在 AAC 規範中，
保留了一些針對不同應用程式和環境客製化的空間，
因此可以適用到許多不一樣的使用情境，
這些客製化的選擇稱為 Profiles （在 MPEG-2 中）或 Audio Object Types （在 MPEG-4 中）。


.. image:: /images/streaming/mpeg4-audio-decoder.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/mpeg4-audio-object.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/mpeg4-transport.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/mpeg2-adts.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/he-aac-encoder.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/he-aac-decoder.png
    :alt: A closer look into MPEG-4 High Efficiency AAC

.. image:: /images/streaming/acc-sbr.png
    :alt: A closer look into MPEG-4 High Efficiency AAC


.. image:: /images/streaming/asc.png
    :alt: AAC Transport Formats

.. image:: /images/streaming/adts.png
    :alt: AAC Transport Formats

.. image:: /images/streaming/adif.png
    :alt: AAC Transport Formats

.. image:: /images/streaming/latm-loas.png
    :alt: AAC Transport Formats



ADTS (Audio Data Transport Stream)
----------------------------------

ADIF 和 ADTS 這兩個 ACC 格式定義在 MPEG-2 Part 7，
是原本的 Transport 和儲存的格式，
MPEG-4 引進了兩個新的格式 LATM 和 LOAS，
這兩個新格式不只可以儲存傳統的 AAC，
也支援較新的變種（例如 AAC-LD 和 AAC-ELD）。

ADTS 跟 ADIF 比起來是比較常被使用的格式。


ADIF (Audio Data Interchange Format)
------------------------------------

Overhead 最小的 AAC 格式，
不支援 Random Access，
較少使用。


LATM (Low-overhead MPEG-4 Audio Transport Multiplex)
----------------------------------------------------

會用於傳輸 HE-AAC V2（不包含 LOAS Sync Layer）。


LOAS (Low Overhead Audio Stream)
--------------------------------

為 LATM 加上 Sync 資訊，
支援 Random Access 或略過部份資訊，
用於 AAC-LD 的 Bitstream 格式，
和利用 MPEG-2 Transport Stream 傳輸 AAC 時。


MPEG-2 Transport Stream
------------------------------

內含 ADTS 或 LOAS 或 MPEG-4 Sync Layer Stream 的 PES 封包。


RFC 3016
------------------------------

藉由 RTP 封包來傳輸 MPEG-4 Audio LATM 或是 MPEG-4 Video。


RFC 3640
------------------------------

藉由 RTP 封包來傳輸 MPEG-4 Elementary Stream


MP4FF (MP4 File Format)
------------------------------

Audio 和 Video 的儲存格式。


3GP File Format
------------------------------

類似 MP4FF，
但是支援非 MPEG 的 codec，
例如 H.263 和 GSM-AMR。

.. image:: mp4-3gpp-file-format.png


License 和 Patents
------------------------------



Ogg
========================================



Opus
========================================

是一種開放格式，
使用上沒有任何專利限制。


.. image:: bitrate-latency-comparison.png



參考
========================================

* `AAC Transport Formats <https://www.iis.fraunhofer.de/content/dam/iis/de/doc/ame/wp/FraunhoferIIS_Application-Bulletin_AAC-Transport-Formats.pdf>`_
* `Opus Interactive Audio Codec <http://opus-codec.org/>`_
* [GitHub] `xiph/opus <https://github.com/xiph/opus>`_

* `Wikipedia - Data compression <https://en.wikipedia.org/wiki/Data_compression>`_
* `Wikipedia - Advanced Audio Coding <https://en.wikipedia.org/wiki/Advanced_Audio_Coding>`_
* `Wikipedia - Ogg <https://en.wikipedia.org/wiki/Ogg>`_
* `Wikipedia - Real-time Transport Protocol <https://en.wikipedia.org/wiki/Real-time_Transport_Protocol>`_
* `Wikipedia - RTP audio video profile <https://en.wikipedia.org/wiki/RTP_audio_video_profile>`_
* `Wikipedia - Opus (audio format) <https://en.wikipedia.org/wiki/Opus_(audio_format)>`_
