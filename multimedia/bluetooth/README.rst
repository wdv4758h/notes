========================================
藍牙相關 (Bluetooth)
========================================

* `藍牙相關音訊編碼知識 (Bluetooth Codecs) <bluetooth-codecs-concept.rst>`_

* 編碼
    - Bluetooth Special Interest Group
        + `SBC <sbc.rst>`_
        + CVSD 8kHz
        + mSBC (modified SBC)
    - Qualcomm
        + `aptX <aptx.rst>`_
        + `aptX HD <aptx-hd.rst>`_
    - Sony
        + `LDAC <ldac.rst>`_

* 藍牙 Profile
    - A2DP (Advanced Audio Distribution Profile)
    - HSP (Headset Profile)
    - GATT (Generic Attribute Profile)

* 藍牙軟體層實做
    - 通用實做
        * Linux: Bluez
        * `Android: Fluoride Bluetooth Stack (BlueDroid 的後繼) <https://android.googlesource.com/platform/system/bt/>`_
        * FreeBSD: implemented using the Netgraph framework
        * Mac OS X:
    - 嵌入式實做

* 藍牙技術
    - 無線傳輸技術
    - 使用 2.4 GHz 頻段
    - 1999 - 藍牙 1.0
        + 最高傳輸速度： 0.7 Mbps
        + 最高傳輸距離： 10 公尺
        + 有安全性問題，會洩漏裝置 address
    - 2001 - 藍牙 1.1
        + 列入 IEEE 802.15.1
        + 定義 Physical Layer
        + 定義 Medium Access Control
        + 容易受到同頻率產品干擾
    - 2003 - 藍牙 1.2
        + 改善安全性問題，提供匿名性，避免受到追蹤或 Sniffing
        + 新增 AFH (Adaptive Frequency Hopping) 支援，利用偵測環境跳頻來減少與其他無線裝置間的干擾
        + 新增 eSCO (Extended Synchronous Connection-Oriented links)，提供 QoS 音訊傳出
        + 新增 Faster Connection，縮短再次連結的時間
        + 新增 Stereo 音訊支援，但是只能單工
    - 2004 - 藍牙 2.0 - EDR
        + 最高傳輸速度： 1 Mbps (core)、3 Mbps (EDR)
        + 最高傳輸距離： 30 公尺
        + 新增 EDR (Enhanced Data Rate)，提高多任務處理能力和多裝置同時運作的處理，並降低功耗
        + 新增雙工模式，可以一邊語音一邊傳輸文件
        + 增加連接設備的數量
    - 2007 - 藍牙 2.1 - SSP
        + 新增 Sniff Subrating 省電功能，設備間互相確認的訊號間隔從 0.1 降到 0.5 秒
        + 新增 SSP (Secure Simple Pairing) 簡易安全配對功能
        + 新增 EIR (Extended Inquiry Response)，加強裝置掃描時的過濾
        + 支援用 NFC 傳輸藍牙配對密碼
    - 2009 - 藍牙 3.0 - HS
        + 最高傳輸速度： 3 Mbps (EDR)、24 Mbps (over 802.11)
        + 最高傳輸距離： 30 公尺
        + 新增 High Speed 技術，會使用 802.11 WiFi 來提升傳輸速度
        + 新增 AMP (Generic Alternate MAC/PHY) 技術，允許對不同任務動態地選擇頻率
        + 新增 EPC 技術改善電源控制，搭配 802.11 技術，降低空閒時的功耗
        + 新增 UCD (unicast connectionless data) 技術，提高設備的回應能力
    - 2010 - 藍牙 4.0 - LE
        + 最高傳輸速度： 3 Mbps (EDR)、1 Mbps (BLE)
        + 最高傳輸距離： 60 公尺
        + 集結三種規格
        + 三種模式
            * 低功耗藍牙 (BLE) (Bluetooth Low Energy)：主打極低功率
            * 傳統藍牙：一般溝通和設備連接
            * 高速藍牙：主打資料傳輸效率
        + 晶片分為 Single Mode 和 Dual Mode
            * Single Mode： 只能與藍牙 4.0 溝通
            * Dual Mode： 向下相容藍牙 3.0/2.1/2.0
        + 新增 SM (Security Manager)，使用 AES-128 CCM 加密資料傳輸
        + 最短在 3 毫秒內完成設備連接
        + 新增 GATT (Generic Attribute Profile)
    - 2013 - 藍牙 4.1 - indirect internet connection
        + 支援和 LTE 共同運作，會自動協調兩者的傳輸，降低互相干擾
        + 允許開發者和製造商自己定義重新連接間隔
        + 只要連接到可連網的設備即可透過 IPv6 跟雲端同步資料
        + 支援終端設備（例如智慧手錶、計步器）互相溝通，不須透過中心設備（例如手機）
    - 2014 - 藍牙 4.2 - IPv6 direct internect connection
        + 改善傳輸速度和安全性，要連接設備或追蹤使用者必須先經過使用者同意
        + 支援 6LoWPAN (基於 IPv6 的低速無線個人網)，可以透過 IPv6 和 6LoWPAN 連結到外網，簡化網路結構
    - 2016 - 藍牙 5.0 - 4x range, 2x speed, 8x message capacity + IoT
        + 最高傳輸速度： 3 Mbps (EDR)、2 Mbps (BLE)
        + 最高傳輸距離： 240 公尺
        + BLE 模式下的傳輸速度是藍牙 4.2 的兩倍
        + 支援室內定位導航，結合 WiFI 可以達到精準度小於一公尺
    - 藍牙 Mesh 技術
        + 相容藍牙 4/5
        + 每個設備都能發送和接收資料，資料可以在設備間被中繼，只要有一個裝置可以對外連線，其他裝置就能互相溝通後也連到外網
        + 藉此可以擴大傳輸距離及便於為大空間建立智慧環境


+------------------------+--------------------------------------+--------------------------------------+
|                        | Low Energy                           | Classic Basic Rate & EDR             |
+========================+======================================+======================================+
| Channels               | 40 channels with 2 MHz spacing       | 79 channels with 1MHz spacing        |
+------------------------+--------------------------------------+--------------------------------------+
| Data Rate              | * BLE 5: 2 Mbps                      | * EDR (8DPK): 3 Mbps                 |
|                        | * BLE 4.2: 1 Mbps                    | * EDR (π/4 DQPSK): 2 Mbps            |
|                        | * BLE 5 Long Range (S=2): 500 Mbps   | * Bassic Data Rate: 1 Mbps           |
|                        | * BLE 5 Long Range (S=8): 125 Mbps   |                                      |
+------------------------+--------------------------------------+--------------------------------------+
| Power & Radio Profiles | * Class 1: 100 mW (+20 dBm)          | * Class 1: 100 mW (+20 dBm)          |
|                        | * Class 1.5: 10 mW (+10 dBm)         | * Class 2: 2.5 mW (+4 dBm)           |
|                        | * Class 2: 2.5 mW (+4 dBm)           | * Class 3: 1 mW (0 dBm)              |
|                        | * Class 3: 1 mW (0 dBm)              |                                      |
+------------------------+--------------------------------------+--------------------------------------+
| Power Consumption      | * ~ 0.01x to 0.5x of classic         | * Based on radio class               |
|                        | * 0.01 ~ 0.50 W (depend on use case) | * 1 W as reference                   |
+------------------------+--------------------------------------+--------------------------------------+
| Network Topologies     | * Point-to-Point (including piconet) | * Point-to-Point (including piconet) |
|                        | * Broadcast                          |                                      |
|                        | * Mesh                               |                                      |
+------------------------+--------------------------------------+--------------------------------------+


+--------------------------+---------------+-----+---------------+----------------+------------------------+
|                          | SBC           | AAC | aptX          | aptX HD        | LDAC                   |
+==========================+===============+=====+===============+================+========================+
| Compression Ratio        | 3             |     | 4             | 4              | ~ 4.655                |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| Audio Format (Stereo)    | 16bit, 48 kHz |     | 16bit, 44 kHz | 24bit, 48 kHz  | 24bit, 96 kHz          |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| Data Rates (kbps)        | 193 ~ 328     | 320 | 352           | 576            | * Connection mode: 330 |
|                          |               |     |               |                | * Normal mode:     660 |
|                          |               |     |               |                | * Priority mode:   990 |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| Frequency Response       |               |     |               | 20 Hz ~ 20 kHz | 20 Hz ~ 40 kHz         |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| SNR Ratio                |               |     |               | 129 dB SNR     |                        |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| THD+N                    |               |     |               | -80 dB         |                        |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| Bluetooth Latencies (ms) | 100 ~ 150     |     | ~ 40          | ~ 200          |                        |
+--------------------------+---------------+-----+---------------+----------------+------------------------+
| License Price            |               |     |               |                |                        |
+--------------------------+---------------+-----+---------------+----------------+------------------------+


參考：

* `Bluetooth Technology: What Has Changed Over The Years <https://medium.com/jaycon-systems/bluetooth-technology-what-has-changed-over-the-years-385da7ec7154>`_
