========================================
物聯網 (IoT) (Internet of Things)
========================================


物聯網不是什麼新技術或新概念，
是基於現有技術組合並延伸應用，
隨著不同的應用可能需要不同的技術組合，
是非常講求應用情境的概念。
近年相關技術的成熟與成本降低，
使得各式各樣的應用也更容易發展，
也成為被炒熱的名詞。


* 感測 (Sensor)      - 蒐集資料
    - 例如物體速度、圖像、溫度、濕度、位置遠近、光、壓力、電量等等
* 網路 (Network)     - 資料傳輸（傳輸距離、功耗、安全性）
    - 短距離無線傳輸
        + NFC
        + RFID
        + QR code
        + barcode
        + Wi-Fi
        + Bluetooth Mesh Network
        + ZigBee
        + Li-Fi
    - 中距離無線傳輸
        + LTE-Advanced
    - 長距離無線傳輸
        + 低功率廣域網路 (LPWAN) (Low-Power Wide-Area Networking)
        + VSAT (Very Small Aperture Terminal)
    - 有線傳輸
        + 乙太網路 (Ethernet)
        + 電力線網路 (PLC) (Power Line Communication)
* 應用 (Application) - 資料應用
    - 冰箱自動提醒快過期物品，並在缺少物品時訂購
    - 冷氣偵測環境去調節，並在使用者回家前先準備好舒適的溫度

----

* 定址
    - IPv6
* 相關通訊協定
    - MQTT
    - CoAP
    - AMQP
* 安全性
* 作業系統
    - `Zephyr Project <https://www.zephyrproject.org>`_
        + 由 Linux Foundation 及眾多廠商一同維護的 RTOS
        + 目標平台為 IoT 裝置，kernel 只需要的少量的記憶體即可運作
        + 支援 IoT 裝置常見的傳輸協定
* M2M (Machine to Machine)

* 參考
    - `Wikipedia - Internet of Things <https://en.wikipedia.org/wiki/Internet_of_things>`_
    - `Mozilla IoT <https://iot.mozilla.org/>`_
