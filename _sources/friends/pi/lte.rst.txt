========
LTE 筆記
========

..  {{{

3G
----

::

    .----------------------------------------------------.
    |                                                    |
    |                         +-----+                    |
    |      (( o ))            | RNC |                    |
    |         |               +-----+                    |
    |        / \                  |                      |
    |       /   \             +-----+                    |
    |      /NodeB\------------| RNC |------ Core Network |
    |     /_______\           +-----+                    |
    |                             |                      |
    |   .                (( o ))  |                      |
    | .-'.                  |     |                      |
    | |UE|                 / \    |                      |
    | '--'                /   \   |                      |
    |                    /NodeB\--'                      |
    |                   /_______\                        |
    |                                                    |
    '----------------------------------------------------'

* UMTS

  - Universal Mobile Telecommunications System，通用行動通訊系統
  - 由許多東西組成

* NodeB

  - 就是基地台

* RNC

  - 連接各基地台的 Controller

* UTRAN

  - UMTS Terrestrial Radio Access Network
  - 包含 UE、NodeB、RNC

..  }}}

LTE
----

系統架構圖 ::

  {{{
  .--------------------------------------------------------------------------------------.
  |                       ||                                                             |
  |        E-UTRAN        ||                       Evolved Packet Core                   |
  |                  S1 Interface                                                        |
  |                       ||                                                             |
  |                       ||      S6a    .-----.                                         |
  |                       ||      .------| HSS |                                         |
  |                       ||      |      '-----'                                         |
  |                S1-MME ||   .------------.                                            |
  |             .--------------| Mobility   |                                            |
  |             |         ||   | Management |                  .------.                  |
  |         .--------.    ||   | Entity     |             .----| PCRF |------.           |
  |         | eNodeB |    ||   |   (MME)    |             |    '------'      |           |
  |         '--------'    ||   '------------'             |                  |           |
  |             |         ||            |                 |                  |           |
  |             |X2       ||            |S11              |                  |           |
  |   .         |         ||            |                 |               ,-*`'-._.-*-,  |
  | .-'.    .--------.    ||   .-----------------.S5/S8.-------------.   ( Operator's  ) |
  | |UE|----| eNodeB |---S1-U--| Serving Gateway |-----| PDN Gateway |---( IP services ) |
  | '--'    '--------'    ||   |     (S-GW)      |     |   (P-GW)    |    `*'-._.-*-.-'  |
  |                       ||   '-----------------'     '-------------'                   |
  |                       ||            |S4 (2G/3G)                                      |
  |                       ||            |                                                |
  '--------------------------------------------------------------------------------------'
  }}}

* E-UTRAN - Evolved Universal Terrestrial Radio Access

  - 是 LTE 的一部份，相當於 UTRAN，但只由 UE 和 eNodeB 組成，沒有 另外的 Controller

* Evolved-Node B

  - 就是 LTE 基地台，簡稱 eNB、eNodeB 等
  - eNodeB 的介面有標準化，使多個電信商之間可以合作
  - 使用 S1-AP Protocol 透過 S1-MME 介面和 MME 溝通
  - 使用 GTP-U Protocol 透過 S1-U 介面和 S-GW 溝通

* System Architecture Evolution (SAE)

  - 和 LTE 一起組成 Evolved Packet System (EPS)
  - 包含 Evolved Packet Core (EPC)

* Evolved Packet Core

  - LTE 核心網路，簡稱 EPC
  - 負責所有對 UE 的操作以及發起 bearer

  - 由以下節點組成

    + PDN Gateway (P-GW)
    + Serving Gateway (S-GW)
    + Mobility Management Entity (MME)
    + Home Subscriber Server (HSS)
    + Policy Control and Charging Rules Function (PCRF)

* PCRF - Policy Charging and Rules Function

  - 類似 P-GW 的 controller
  - Policy
  - Charging
  - Rules

* Home Subscribe Server (包含 Home Location Register (HLR))

  - 一個資料庫，處理每個 user 可否連接到各個 PDN，以及 roaming 時的連接限制

* P-GW - Packet Data Network Gateway，PDN Gateway

  - EPS 的入口，接上 Internet，通常只有一台
  - 為 UE 保留 IP (DHCP 功能)
  - 根據 PCRF 處理 flow-based charging (動態去問 PCRF 或是 UE 在 attach 時就下好 rule)
  - 處理 downlink QoS
  - LTE 和 non-3GPP 網路之間的錨點 (例如 CDMA2000 和 WiMAX)
  - 記錄 Uplink TFT (Traffic Flow Table)
  - 在特殊狀況下攔截、監聽封包

* S-GW - Serving Gateway

  - 可以多台，但一台很貴，品質好的一台 S-GW 可以支援數萬台 eNodeB
  - 所有 IP 封包都經過 S-GW
  - UE 在 eNodeB 之間換手時 S-GW 會處理
  - UE idle 時負責 buffer 住 downlink data
  - LTE 和其他 3GPP 網路之間的錨點 (如 GPRS 和 UMTS)

    + 若 UE 要換手到 2G/3G 網路
    + S-GW 會和舊網路建立一個 Shortcut，外來的流量仍然透過 S-GW 轉給舊網路，最後轉給 UE

* MME - Mobility Management Entity

  - 可以多台
  - UE attach 時先向 MME 認證 (MME 再去向 HSS 查詢)
  - 處理 UE 和 Core Network 之間的信令
  - 只有 MME 可以存取 HSS

* UE - User Equipment

  - 通常指手機
  - UE 和 MME 之間的 Protocol 為 Non Access Stratum

    + "非接觸" 是指 UE 和 MME 之間沒有直接接觸（因為MME 不是基地台）

  - UE 和 eNodeB 之間的 Protocol 為 Access Stratum

LTE Protocol Stack
------------------

Control plane protocol stack (figure 2.7) ::

  {{{
  .------------------------------------------------------------.
  |             |                    |                         |
  |          LTE-Uu               S1-MME                       |
  |             |                    |                         |
  |   .------.  |    .----------.    |  .-------.              |
  |   | NAS  |  |  .'   Relay    '.  |  | NAS   |  Radio       |
  |   |------|  |  |-----. .------|  |  |-------|  Network     |
  |   | RRC  |  |  | RRC  | S1-AP |  |  | S1-AP |  Layer       |
  |   |------|  |  |------|-------|  |  |-------| ~ ~ ~ ~ ~ ~  |
  |   | PDCP |  |  | PDCP | SCTP  |  |  | SCTP  |  Transport   |
  |   |------|  |  |------|-------|  |  |-------|  Network     |
  |   | RLC  |  |  | RLC  | IP    |  |  | IP    |  Layer       |
  |   |------|  |  |------|-------|  |  |-------|              |
  |   | MAC  |  |  | MAC  | L2    |  |  | L2    |              |
  |   |------|  |  |------|-------|  |  |-------|              |
  |   | L1   |  |  | L1   | L1    |  |  | L1    |              |
  |   '------'  |  '--------------'  |  '-------'              |
  |      UE     |      eNodeB        |     MME                 |
  |             |                    |                         |
  '------------------------------------------------------------'
  }}}

User plane protocol stack (figure 2.6) ::

  {{{
  .----------------------------------------------------------------------------------.
  |                    |                     |                       |               |
  |                 LTE-Uu                 S1-U                    S5/S8             |
  |                    |                     |                       |               |
  |   .-------------.  |                     |                       |               |
  |   | Application |  |                     |                       |               |
  |   |-------------|  |    .-----------.    |    .-------------.    |  .--------.   |
  |   | IP          |  |  .'   Relay     '.  |  .'     Relay     '.  |  | IP     |   |
  |   |-------------|  |  |-----. .-------|  |  |-------. .-------|  |  |--------|   |
  |   | PDCP        |  |  | PDCP | GTP-U  |  |  | GTP-U  | GTP-U  |  |  | GTP-U  |   |
  |   |-------------|  |  |------|--------|  |  |--------|--------|  |  |--------|   |
  |   | RLC         |  |  | RLC  | UDP/IP |  |  | UDP/IP | UDP/IP |  |  | UDP/IP |   |
  |   |-------------|  |  |------|--------|  |  |--------|--------|  |  |--------|   |
  |   | MAC         |  |  | MAC  | L2     |  |  | L2     | L2     |  |  | L2     |   |
  |   |-------------|  |  |------|--------|  |  |--------|--------|  |  |--------|   |
  |   | L1          |  |  | L1   | L1     |  |  | L1     | L1     |  |  | L1     |   |
  |   '-------------'  |  '---------------'  |  '-----------------'  |  '--------'   |
  |         UE         |      eNodeB         |      Serving GW       |    PDN GW     |
  |                    |                     |                       |               |
  '----------------------------------------------------------------------------------'
  }}}

Radio Architecture ::

  {{{
  P.53 Figure 3.1
  .------------------------------------------------------------------------------------------------------------.
  |          Notification   Common                     Dedicated                                               |
  |                |           |                           |                                                   |
  |            +---'--+  +-----'-----+     +---------------'----------------+    SRB = Signalling Radio Bearer |
  |            |Paging|  |  System   |     |     Dedicated Control &        |    DRB = Dedicated Radio Bearer  |
  |            +---.--+  |information|     |      Information Transfer      |                                  |
  |       RRC      |     +-----.-----+     +--.------------.-------------.--+                                  |
  |                |           |              |            |             |                                     |
  | Radio   - - - -|- - - - - -|- - - - - - SRB0 - - - - SRB1 - - - -  SRB2 - - - -  DRB1 - - - -  DRB2        |
  |  Bearers       |           |              |            |             |             |             |         |
  |                |           |              |       +----'-----+  +----'-----+  +----'-----+  +----'-----+   |
  |                |           |              |       |integrity&|  |integrity&|  |Ciphering&|  |Ciphering&|   |
  |                |           |              |       |ciphering |  |ciphering |  |  ROHC    |  |  ROHC    |   |
  |                |           |              |       +----.-----+  +----.-----+  +----.-----+  +----.-----+   |
  | PDCP & RLC     |           |              |            |             |             |             |         |
  |                |           |              |          +-'-+         +-'-+         +-'-+         +-'-+       |
  |                |           |              |          |ARQ|         |ARQ|         |ARQ|         |ARQ|       |
  |                |           |              |          +-.-+         +-.-+         +-.-+         +-.-+       |
  |                |           |              |            |             |             |             |         |
  | Logical   - - PCCH - - - BCCH - - - - - CCCH - - - - DCCH1 - - - - DCCH2 - - - - DTCH1 - - - - DTCH2       |
  |  Channels      |           |              |            |             |             |             |         |
  |                |           +--------------+---------.  |             |             |             |         |
  |                |           |              |       +-'--'-------------'-------------'-------------'-----+   |
  |       MAC      |           |              |       |            Multiplexing & HARQ control             |   |
  |                |           |              |       +-------------.------------------.-------------------+   |
  |                |           |              |                     |                  |                       |
  | Transport - - PCH - - - - BCH - - - - - RACH - - - - - - - - DL-SCH - - - - - - UL-SCH                     |
  |  Channels      |           |              |                     |                  |                       |
  |              +-'-----------'--------------'---------------------'------------------'-------------------+   |
  |       PHY    |                            Physical Layer Functions                                     |   |
  |              +-------------.--------------.---------------------.------------------.-------------------+   |
  |                            |              |                     |                  |                       |
  | Physical - - - - - - - - PBCH - - - - - PRACH - - - - - - - - PDSCH - - - - - - - PUSCH                    |
  |  Channels                                                                                                  |
  '------------------------------------------------------------------------------------------------------------'
  }}}

LTE 的各個介面
--------------

* X2 介面

  - eNodeB 之間的介面
  - X2 介面是實體線路
  - UE 在 eNodeB 之間換手稱為 X2-handover

* S1-MME

  - eNodeB 和 MME 之間的介面
  - 使用 S1-AP Protocol

* S1-U

  - eNodeB 和 S-GW 溝通
  - 使用 GTP-U Protocol

LTE Frame Structure
-------------------

LTE 把時間分成許多部份，用來管理訊號在時間上的分佈

* 1 個 Frame 10 ms
* 1 個 Frame 有 10 個 Subframe (= 1 ms)
* 1 個 Subframe 有 2 個 Timeslot (= 0.5 ms)
* 1 個 Subframe 有 14 個 Symbol Period
* 1 個 Symbol Period 可以傳送一個 Symbol

* Special Subframe

  - 從 Downlink 轉為 Uplink 模式需要安插一個 Special Subframe
  - Special Subframe 的下一個保留給 Uplink 傳輸
  - 從 Uplink 轉為 Downlink 不需 Special Subframe

* Subframe 編號從 0 ~ 9

  - Subframe0 和 Subframe5 保留給 Downlink 傳輸

* Subframe0 在每個基地台之間是同步的

* Physical Resource Blocks (PRB)

  - 1 個 Timeslot x 12 個 Subcarrier (15kHz) = 1 個 PRB (180 kHz)
  - 每個時間點，1 個 PRB 只能有一個 User 傳資料

Physical Layer
--------------

* OFDMA (Orthogonal Frequency-Division Multiple Access)

  - LTE Downlink
  - OFDM 的演進
  - OFDMA 使用很多個互相 "垂直" 、窄的頻段載波來傳送資料

    + 每個 Subcarrier 寬度 15 kHz

  - 這些載波可以被當成資源在不同使用者之間 Scheduling
  - 傳輸方的能源消耗很重 (但這發生在基地台，相對手機端有很多能源可以用)
  - 不需要 Guard Band
  - 每個 Subcarrier 可以用 Time Division 方式分配
  - 兩方需要很精準的對時

  - 和 OFDM 的比較

    + OFDM 分配給每個 User 固定的 Subcarrier (不隨時間改變)
    + OFDMA 在每個 Timeslot 都可以調整每個 User 使用的 Subcarrier

      * 有些 User 在某些時段可能會沒有分到 Subcarrier

* SC-FDMA (Single-Carrier FDMA)

  - LTE Uplink
  - SC-FDMA 使用一整個頻段，用 Time Division 方式分配
  - 省電
  - 也使用多個載波，讓上下行都在一定程度上使用類似的技術

* Precoding

  - 把資料流映射到多根天線
  - 傳送端的多根天線都包含多個資料流
  - 接收端的每一根天線都接收所有資料

* SNR

  - Signal Noise Rate
  - 訊號和雜訊的比例，越高代表訊號品質越好

* QPSK - Quadrature Phase Shift Keying

  - 在一個 Symbol 內攜帶更多的訊息
  - 用 Signal Wave 的 Phase 編碼
  - 需要精準的同步（不然 Phase 會跑掉）

  - QAM - Quadrature Amplitude Modulation

    + Symbol 的豐富程度
    + 16 QAM 代表一個 Symbol 內可攜帶 4 個 bit
    + 64 QAM 代表一個 Symbol 內可攜帶 6 個 bit
    + 2 QAM 為 BPSK (Binary)，一個 Symbol 只能帶 1 個 bit，但抗噪能力是 PSK 系列中最強的

Physical Channels
~~~~~~~~~~~~~~~~~

* Downlink

  - PBCH - Physical Broadcast Channel

  - PMCH - PHysical Muticast Channel

  - PDCCH - Physical Downlink Control Channel

  - PDSCH - Physical Downlink Shared Channel

    + 傳資料

  - PCFICH - Physical Control Format Indicator Channel

    + 定義每個 Subframe 中 PDCCH OFDMA Symbol 的數量

  - PHICH - Physical Hybrid ARQ Indication Channel

    + 傳送 HARQ ACK/NACK

* Uplink

  - PRACH - Physical Random Access Channel

    + 想傳就傳的 Channel
    + Call Setup
    + UE 要傳上行資料前先用這個 Channel 取得資源

  - PUCCH - Physical Uplink Control Channel

    + Scheduling ACK/NACK
    + 用來排程上行的傳輸

  - PUSCH - Physical Uplink Shared Channel

    + 傳資料

* 其他 Signals

  - P-SS - Primary Synchronization Signal

    + 第一同步訊號，（FDD）出現在每個 Subframe 的第 7 個 Symbol
    + 出現在中間頻率的 Subcarrier

  - S-SS - Secondary Synchronization Signal

    + 第二同步訊號，（FDD）出現在每個 Subframe 的第 6 個 Symbol
    + 出現在中間頻率的 Subcarrier

  - Reference Signal

    + 參考訊號，出現在每個 Subframe 的第 1, 5, 8, 12 個 Symbol

    + Downlink

      * 基地台固定發送的特定 Sequence，給 UE 偵測

    + Uplink

      * 基地台偵測 Uplink Channel 狀況

Transport Channels
------------------

* PCH - Paging Channel

* DL-SCH - Downlink Shared Channel

Logical Channels
----------------

Logical Channel

* BCCH - Broadcast Control Channel

  - 頻率低，不需 Scheduling 的 Control Channel

* CCCH - Common Control Channel

  - 需要 Scheduling 的 Control Channel

其他
----

* Bearer - 載體

  - Bearer 是一個概念，一個 IP Packet Flow，介在 gateway 和 UE 之間

  - Default Bearer

    + 每個 UE 都有一個 Default Bearer，即使處理 Idle Mode
    + Non-GBR
    + UE 必須處於 EMM-REGISTERED State 才能使用 Default Bearer（確定為合法的使用者）

  - Dedicated Bearer

    + 為特定的需求而開的 Bearer
    + UE 不須處於 EMM-REGISTERED State

      * 因為 Default Bearer 一定會先建立，使用者的合法性可以確定

    + UE <---> P-GW

  - Traffic Flow Template - TFT

    + Flow 與 Bearer 的對應表

* SRB - Signalling Radio Bearer

  - 用來轉送 NAS 訊息 (UE - MME)

  - SRB0

    + Downlink 同步完成後建立
    + 使用 CCCH (因為 DCCH 還沒建立)
    + 建立 SRB1
    + 也用來廣播 MIB

  - SRB1

    + Uplink 同步完成後建立
    + DCCH
    + 為 UE 做認證，兩邊開始加密
    + 也用來傳送非 NAS 訊息

  - SRB2

    + UE 認證後建立
    + 用來傳送 NAS 訊息

* Handover

  - LTE 不支援 soft handover
  - 因為 LTE 的不同 cell 需要在不同的頻率下工作
  - UE 在 handover 時也需要切換到不同的頻率，無法同時監聽

* PLMN

  - Public Land Mobile Network
  - 指電信業者運行的網路

* Area

  - MME Pool Service Area

    + 由 Tracking Area 組成
    + 每個 MME Pool Service Area 中可以有多個 MME
    + UE 在同一個 MME Pool Service Area 中移動不需切換 MME
    + 每台 eNodeB 都對應一個 MME Pool Service Area

      * eNodeB 會對 MME Pool Service Area 中的每台 MME 都建立 S1-MME 介面

    + MME Pool Service Area 可以重疊，eg: 可以有 MME 同時屬於多個 MME Pool Service Area
    + 如果一個 MME Pool Service Area 的 Loading 越來越重，Operator 可以增加 MME 進入 MME Pool Service Area

  - S-GW Pool Service Area

    + 由 Tracking Area 組成
    + 每個 S-GW Pool Service Area 中可以有多個 S-GW
    + 和 MME Pool Service Area 的概念一樣
    + S-GW Pool Service Area 和 MME Pool Service Area 無關，可以部份重疊

  - Tracking Area

    + 由連續的 Cell 組成
    + 一次 Paging 的單位就是一個 Tracking Area
    + Tracking Area 組成 S-GW 和 MME Pool Service Area
    + 由 Cell 組成，一台基地台的每個 Cell 可以分屬不同的 Tracking Area
    + 一般而言 Tracking Area 之間不會重疊
    + 大小

      * 若一個地區的 UE 數量很多，Tracking Area 應縮小，避免 Paging Overhead 太高
      * 若一個地區的 UE 移動速度很快，Tracking Area 應放大，避免 Tracking Area Update 太頻繁

    + 一個 UE 可以同時註冊進多個 Tracking Area，做為上述兩個問題同時發生時的解決方式
    + Tracking Area Update

      * Normal TAU: UE 發現目前的 eNodeB 已經不在它的 Tracking Area List 內，發出 TAU
      * Periodic TAU: 定時（由 Time T3412 計時）發送 TAU，告訴 MME
      * 若 UE 實際上已經更換了 MME

        - 該 TAU 會被 Reject
        - UE 再發送第二次 TAU
        - 新的 MME 向舊的 MME 要資料 - Fast Authentication（不向 HSS 重新認證）

          + TAU 裡面有 MME ID，新的 MME 會知道該 UE 原本歸哪個 MME 管

        - 建立新的 Bearer Path
        - 更新 HSS
        - 刪掉舊的 Bearer Path
        - 回應 UE TA Update Accept

* 各種 Cell

  - Macrocell: 大型基地台，覆蓋半徑可達 100 km
  - Smallcell: 小型基地台，範圍約 10 公尺到 2 公里
  - Picocell:  小型基地台，範圍約 200 公尺，用於室內，可以想成電信業者管理、透過專線連接的小型基地台
  - Femtocell: 小型基地台，範圍約 10 公尺，原用於室內，有 SON 功能，可以想成是 WiFi AP，被 Picocell 取代
  - Microcell: 就是 Smallcell
  - Metrocell: 就是 Microcell

* Femtocell {{{

  - 家庭基站，類似 WiFi AP，以室內為主，連接公眾網路，後來被 Picocell 取代
  - 出現的原因

    + 有超過 50% 的 Voice Call、70% 的流量其實是來自室內
    + 但室內常常收不到基地台的訊號
    + "那就放一個在室內吧，Backhaul 就接 ADSL 之類的" -> Home eNodeB
    + "還可以放在公眾區域！" -> Metrocell

      * 最後 Metrocell 沒有發展起來，因為其實用普通基地台就可以了，沒有必要特別去發展這個

  - 低功耗低成本 (相對大的基地台而言)
  - 和 eNodeB 之間沒有 X2 介面，故換手的成本較高
  - HeNB 會先連接 Home eNodeB Gateway，然後才接上 MME/S-GW

    + HeNB Gateway 負責加密

  - Inbound Handover - 從 Macrocell Handover 到 Femtocell
  - Outbound Handover - 從 Femtocell Handover 到 Macrocell
  - 每個 Femtocell 被切分成許多小地區，可以根據不同區域做不同的參數調整
  - 在另一個 Cell 的訊號強度比當前的 Cell 高出 HOM，持續 TTT (Time-To-Trigger) 時間以後，才啟動 Handover 機制

    + 避免 Ping-Pong 效應

  - Femtocell 發展遇到的困難

    + 扁平化的架構被稍微破壞
    + Dead Zone Problem

      * 室外的 UE 和室內的 Femtocell 可能會互相干擾
      * 用 SON 解決：Femtocell 自己根據狀況調整

    + Synchronization

      * 若兩座基地台之間沒有良好的同步，UE 可能會換手失敗，或是嚴重延遲

    + 因為 Backhaul 是外接，QoS 變得困難
    + 家用裝置必須是 Plug-and-Play 的裝置：要有 SON 功能

..  }}}

* Smallcell {{{

  - 定位

    + Macrocell 負責覆蓋率，使用低的頻率（700 / 800MHz）
    + Smallcell 負責分流，使用較高的頻率（2GHz）

      * 手機得克服「不能同時使用兩個 band」的限制

  - 取代 Femtocell，成為小型基地台發展的方向
  - 和 Femtocell 的差異

    + Femtocell 使用公眾網路，需要特別的加密機制

  - 遇到的困難

    + 大小基地台不易辨認，快速移動的 UE 應該要連上大基站，慢速移動 UE 應該要連小基站

      * 目前朝向「大基站指揮 UE 連向小基站」為主

    + Backhaul 怎麼接？
    + 架設點怎麼找？（租金問題）

      * 路燈桿
      * 房子上

..  }}}

* RRM - Radio Resource Management

  - 負責 Radio Resource 相關的所有功能

    + Radio Bearer 管理
    + Scheduling of Radio Resources
    + Dynamic Allocation of Resources
    + Transmission Power Management
    + Mobility Management

  - eNodeB 的核心功能
  - 有時會要求 UE 做 Buffer Status Report
  - 處理 Proportional Fair

    + 有些 UE 可能會待在 Channel Quality 比較差的地方
    + 若用 Round Robin 配給 UE 資源，對這些 UE 不公平
    + 若把資源分給 Channel Quality 最好的 UE，也不公平
    + 解：把資源分給「Channel Quality 相對最好」的 UE

      * 大家都能在 Channel Quality 比較好的時候傳資料

* RRC - Radio Resource Control

  - 廣播系統訊息、Paging
  - 管理 UE 和 E-UTRAN 之間的連線
    + 管理 UE 和 E-UTRAN 之間的 Temporary ID
  - Inter eNodeB / Inter-RAT 的 Handover
  - RRC 可以直接取得物理層的資料，不需要經過中間的轉送

  - RRC Connection 的用途

    + UE Registration/Deregistration
    + Traffic Data Transpotation
    + Location Registration

  - 一個 RRC Connection 包含

    + Radio Resource Configuration (Resource Blocks, MAC/PHY Configuration)
    + AS Security Context
    + Measurement Configuration
    + UE Radio Capability

* PDCP - Packet Data Convergence Protocol

  - 傳送 User Plane Data
  - 傳送 Control Plane Data
  - 上行/下行都可用
  - Header Compression
  - Ciphering
  - Integrity Protection: 防止封包被插入、置換
  - 換手的支援
    + 為 Handover 發生層以上的 PDU 封包重排序
    + 為 RLC Acknowledged Mode 的 User Plane Data 提供 Lossless Handover
  - PDCP SDU 最大可以傳 8188 byte

* RLC - Radio Layer Control

  - 負責偵錯、重傳
  - 根據 MAC 層的指示切割/連接 SDU
  - 重排、偵測重複、重組
  - Acknowledged Mode (AM)
  - Unacknowledged Mode (UM)
  - Transparent Mode (TM)

* MAC - Medium Access Control Layer

  - 在 Logical Channel 和 Transport Channel 之間做對應、Scheduling

    + Scheduling 發生在多個 User 分配到同一個 PRB 的時候
    + Scheduling 的單位是 UE，而不是 UE 內的 RLC Buffer
    + 只有 Shared Channel 需要被排程
    + eNodeB 用 C-RNTI 通知 UE 可以傳資料

  - Uplink 被 Buffer 住的資料量會回報給 eNodeB (Buffer Status Report)
  - 根據 UE 回報的 Channel Condition 決定 Coding Scheme，並指揮 RLC 層

* Inter-Symbol Interference (ISI)

  - 前一個傳出去的 Symbol，撞到障礙物，在下一個 Symbol 傳送時才彈回來，造成干擾

* TDD LTE 就算有 Guard Band，在 150 MHz 之內還是會干擾

* Handover 和 Mobility 是不同的

  - Handover 需維持連線
  - Mobility 只需要回報位置 (手機可以進 Idle Mode)

* Category

  - LTE 把 UE 分類，目前有 Category 1 ~ 8，代表 UE 的等級

      ======== ======== ======== ========
      Category downlink  天線數   uplink
      ======== ======== ======== ========
       1        1        10.3     5.2
       2        2        51.0     25.5
       3        3        102.0    51.0
       4        3        150.8    51.0
       5        4        299.6    75.4
       6        2/4      301.5    51.0
       7        2/4      301.5    102.0
       8        8        2998.6   1497.8
      ======== ======== ======== ========

* PDU / SDU

  - 上層傳下來/傳給下層的資料稱為 SDU
  - 傳給下層/上層傳上來的資料稱為 PDU

* 台灣現存的電信網路

  - 2.5G: GPRS (頻段已被 LTE 取代)
  - 3G:   WCDMA
  - 3.5G: HSPA / HSPA+
  - 4G:   LTE / LTE-A

* NAS - Non Access Stratum

  - MME 和 UE 之間使用 NAS 溝通，透過 eNodeB 轉送資料
  - Incoming Call 的訊息是由 MME 發起，透過 NAS 送給 UE 的
  - 控制 UE 的 Mobility

* RRU - Remote Radio Unit

  - 就是 Cell

* HARQ - Hybrid Automatic Repeat reQuest

  - LTE 物理層自動重送封包的機制
  - 只在 DL-SCH 和 UL-SCH 使用
  - 在 MAC 層有 8 個 Process 平行處理，以免來不及 Decode

  - HARQ Incremental Redundancy Algorithm

    + 送出資料後，若收到 NAK，表示接收端 Decode 失敗
    + 再送出 Codec 的 Redundancy 部份，給接收端更多資訊做 Decode

  - Asynchronous Adaptive HARQ

    + 傳輸時的屬性（Codec 等）會改變，改變時需要溝通

  - Synchronous Non-adaptive HARQ

    + 傳輸時的屬性是預先設計好的，不能更改

  - LTE 的 Downlink 使用 Asynchronous Adaptive
  - LTE 的 Uplink 使用 Synchronous

    + 原因：控制權在 eNodeB 手上，能夠在參數改變時及時溝通，但 UE 端的改變是來不及溝通的，只能先設好參數

* 重送

  - HARQ

    + 重送速率快
    + 錯誤率較高
    + 通道品質要求高

  - RLC AM

    + 比較慢
    + Error-Free

      * 不夠低的 Error Rate 會使 TCP 服務變得非常慢（一掉包就 Exponential 降速）

  - HARQ 和 RLC 的重傳可以同時啟動
  - 可以動態啟動（在 3G 的 HSPA 網路辦不到，因為功能分在不同的 Node）

* QCI - QoS Class Identifier

  - QCI 5 的 Priority 最高，但卻是 Non-GBR，是因為 IMS signalling 不是連續傳送

* State

  - UE 在 LTE 網路中帶有多種 State

  - EPS Mobility Management (EMM) State

    + EMM-DEREGISTERED
    + EMM-REGISTERED
    + 辨認 UE 是否為合法的使用者

      * Attach Request，Attach Accept

    + 辨認 UE 的 Tracking Area

      * Tracking Area Update (TAU) Request，TAU Accept

  - EPS Connection Management (ECM) State (也可稱為 ESM - EPS Session Management)

    + ECM-IDLE

      * UE 和 MME 之間沒有 NAS Signalling Connection
      * Mobility 用 Cell Selection/Reselection 方式處理

    + ECM-CONNECTED

      * UE 已建立 RRC Connection
      * UE 已建立 S1 Connection
      * UE 可以和 MME 溝通
      * Mobility 用 Handover 方式處理
      * UE 只在 eNodeB 通知時才會發出 Tracking Area Update

        - 可能是換 MME 時會觸發，舊的 MME 叫 新的 MME 去要求 UE 做 Tracking Area Update

    + 使用情境

      * eNodeB 發起：UE 長時間沒有活動、RRC Signaling Integrity Check Failure
      * MME 發起：Authenticaiton Failure、Detach Procedure

  - RRC State

    + RRC-IDLE
    + RRC-CONNECTED

* SIB - System Information Block

  - UE 中記錄的系統資訊最長有效時間為 3 個小時
  - 系統訊息更新的週期：ModificationPeriod，是 Paging Cycle 的整數倍

    + 每達到這個週期，UE 就會醒來，連上 eNodeB，取得 MIB 和 SIB1，再取得其他 SIB 的訊息

  - The Master Information Block (MIB)

    + 包含最常被傳輸的訊息，對於 UE 加入網路是必需的
    + 包含物理層的資訊
    + 每個 Subframe #0 都有
    + 每 40ms 更新一次
    + BCH / PBCH

  - System Information Block Type 1 (SIB1)

    + 用來判斷一個 Cell 是否適合某個 UE
    + 在每個偶數 Frame 之中的 Subframe #5 出現
    + 每 80ms 更新一次
    + DL-SCH / PDCCH
    + 由 SI-RNTI 值提示 SIB1 的位置
    + SIB1 裡面有一個 Value Tag，表明系統資訊有沒有更新

    + SIB1 中的 schedulingInformation 記錄其他 SIB 的位置

      * si-WindowLength
      * 這些 SIB 被分成 SI 1 ~ 3 三組，每一組裡面都帶有各自的週期 (8, 16, 32, 64)
      * 範例

        - SI 1: { 8,  SIB2, SIB3, SIB4 }
        - SI 2: { 16, SIB5 }
        - SI 3: { 32, SIB6, SIB7, SIB8 }
        - si-WindowLength = 20ms

        - SIB5 的 n = 2，si-Periodicty = 16
        - 先計算 x = (n - 1) * si-WindowLength = (2 - 1) * 20 = 20
        - SIB5 會出現的 Frame 為 SFN mod si-Periodicty = Floor(x / 10) 的 Frame

          + SFN mod 16 = 2
          + 從 Frame #2 開始，週期為 16 個 Frame

        - SIB5 會出現的 Subframe 為 x mod 10 = 20 mod 10 = 0

..  SIB1 需要 SI-RNTI 值提示它的位置，但是 MIB 卻不用
    是因為 MIB 是透過 BCH 傳，位置固定
    而 SIB1 是透過 PDCCH 傳，雖然 PDCCH 的位置也是固定的，但 UE 連上時不知道會用到哪個 Subcarrier

  - SIB2

    + Channel 相關的訊息
    + RACH 訊息 (重要：讓 UE 有機會爭取 Uplink 資源)
    + UE 的時間 (從 2G 開始，手機會和系統對時)

  - SIB3 ~ SIB8

    + 都跟換手有關係，重選 Cell 時所需要參數

  - SIB9

    + Home eNodeB ID (Femtocell 清單)

  - SIB10、SIB11

    + ETWS 主要、次要通知
    + ETWS = Earthquake and Tsunami Warning System，地震海嘯警報系統

* DRX - Discontinued Reception

  - 讓手機可以在沒有封包的時候進入睡眠模式
  - 分成: Connected DRX / Paging DRX / Extended DRX
  - Connected DRX

    + 在不同狀態有不同計時器

      * Power Active Mode

        - t_{I}: Inactivity Period
        - UE 閒置超過 t_{I} 時，進入 Power Saving Mode

      * Power Saving Mode

        - t_{D}: DRX Cycle
        - t_{S}: Sleep Period
        - UE 每 t_{D} 醒來一次聽訊息（醒來的時間長度為 τ）

    + eNodeB 會記錄每個 UE 的 DRX Cycle，並在 DRX Cycle 結束時發一個 Paging 給 UE

      * 相同 Cycle 的 UE 會一起被 Paging

  - Paging DRX
  - Extended DRX

* 3GPP

  - 3^{rd} Generation Partnership Project

* C-RAN - Cloud Radio Access Network

  - 把天線拉出基地台，天線可以放在不同的位置，不一定要在基站上
  - 未來天線可能會植入窗戶裡面、牆壁裡面

* UPCON

  - 讓核心網路可以判斷應用服務的種類

* Offload & Traffic Breakout

  - Offload - User Plane 資料完全不經過基地台
  - Traffic Breakout - User Plane 資料會經過基地台，但是在進入核心網路前就經由其他 link 進入 Internet
  - Control Plane 的訊息還是會進入核心網路
  - LIPA - Local IP Access

    + 若發送端和接收端都在同一個區域網路內，流量可以在透過 HeNB 轉送

      * UE -> HeNB（內建一個 LIPA Gateway） -> UE
      * 這樣當然就沒辦法按流量計費了，就改成 買斷 / 月租 / 企業方案 之類的
      * LIPA Gateway 有點像是 P-GW，也會 Assign 一個 IP Address 給 UE

  - SIPTO - Selected IP Traffic Offload

    + Femtocell / HeNB 出去的流量預設有 Tunnel 包裝，通往核心網路
    + 不丟進 Tunnel 的流量就會跑到 Internet 上，不進入核心網路

* LTE 的 MTC - Machine Type Communications

  - 從 LTE Release10 開始制定
  - 只有 Mobile Originated 資料
  - MTC 資料的特徵對 LTE 而言很麻煩

    + 問題

      * Infrequent Transmission（不適合一直維持著連線）
      * Small data Transmission（建立連線所需要的訊號遠大於真正的資料）
      * Priority Alarm Message（某些重要 Device 的資料不能等，一定要馬上傳）
      * Huge Volume Device（Device 數量超多）

    + 相關議題

      * Signalling Reduction
      * Addressing
      * Identifiers
      * Subscription Control
      * Security
      * Grouping

        - 把 Device 包成一群一群，只選一些做為代表和 eNodeB 連線
        - 沒有連線的 Device 和代表用其他協定連線

  - Device 可以接收傳統簡訊和 IMS 的簡訊

    + 跟著 Paging 訊息一起傳

* RAN Sharing

  - 讓一個小型基站給多個營運商使用

* Moving Network

  - 高鐵上的 UE → 高鐵上的 Smallcell → 鐵軌旁的基地台 → Wireless 回程網路

* Initial Access

  1.  UE 搜尋 Cell
  2.  UE 取得系統資訊

      * 透過 Primary Synchronization Signal 找到 Cell ID
      * 透過 Secondary Synchronization Signal 找到 Frame、Subframe 的位置

        - 取得 eNodeB 是使用 TDD / FDD

      * 透過 PBCH 取得 MIB

        - 取得物理層資訊

      * 透過 PDCCH 取得 SIB1

        - 取得其他 SIB 的週期

      * 透過 PDSCH 取得其他 SIB

        - 取得 PLMN ID，檢查這個 Cell 可不可以連，記錄下來做為以後 Reselection 的快取
        - 再回到 A. ，繼續尋找下一個 Cell，記錄約 6 個以後停止

  3.  UE 用 Random Access 取得上行 Radio 資源，發出 Attach Request
  4.  UE RX/TX

* Cell Selection/Reselection

  - Suitable Cell

    + 一個 Suitable Cell 是 UE 最佳的選擇
    + PLMN 合適
    + 不在 Forbidden Tracking Area 內
    + 滿足 Selection 的條件（訊號很好）
    + 該 UE 在白名單內

  - Acceptable Cell

    + UE 可以連，但是只能撥緊急電話
    + 滿足 Selection 的條件（訊號夠好）

      * 條件比 Suitable Cell 鬆很多，只供緊急使用

  - ``~/Documents/3gpp-lte/3GPP-Long-Term-Evolution技術概述-Class-5-r103.pdf`` P.48 有 State Diagram

* Random Access Procedure

  - 在 Random Access 過程中，資源是用搶的
  - 「資源」被稱為 Preamble
  - 過程

    1.  [UE] 透過 PRACH 送出 Random Access Preamble

        - 包含一個 5 bit Preamble ID

    2.  [UE] 等待該 Preamble ID 的回應

        - 如果沒收到大概就是撞爛了，做 Random Backoff，和 WiFi 一樣

    3.  [eNodeB] eNodeB 回應 Random Access Response

        - UE 的 Random ID
        - C-RNTI
        - Initial Uplink Resource Grant（告訴 UE 什麼時候可以透過 UL-SCH 傳資料）

    4.  [UE] 確定取得 Uplink 資源，等到資源可用時，開始傳資料

* UE Registration/Deregistration

  - Registration 有四個目的

    + 讓 UE/網路 互相確認對方是合法的
    + UE 取得 TMSI (Temporary Mobile Subscriber Identity)
    + UE Location Registration（為了以後做 Paging）
    + 建立 Default Bearer

      * 分配 IP 給 UE

  - Deregistration

    + UE 離開網路，不再能接觸 EPS
    + Explicitly Detach
    + Implicitly Detach

      * UE 太久（三小時）沒有 Update，MME 直接踢掉不通知 UE

* UE 的 ID

  - IMSI - International Mobile Subscriber Identity

    + MCC - Mobile Country Code
    + MNC - Mobile Network Code
    + MSIN - Mobile Subscriber Identification Number

  - GUTI - Globally Unique Temporary UE Identifier

    + 在合法註冊後 UE 拿到的 ID，在註冊期間不會改變
    + GUTI = GUMMEI + M-TMSI

  - GUMMEI - Globally Unique MME Identifier

    + GUMMEI = MCC + MNC + MME ID
    + MME ID = MME Group ID + MME Code

* 5G

  - 萬物都連網，滿滿的資料

    + Big data

  - 速度將會是 4G 網路的 1000 倍
  - 每一代的特色

    + 2G: Voice
    + 2.5G: Low-speed data
    + 3G: High-speed Data
    + 4G: Video
    + B4G Intelligent networks，Service centric data，Heterogeneous Networks (HetNet)

  - 邊緣計算: 能在 Local 算完就算完，能在 Local 傳完就傳完，不要跟大家擠

    + Localized Shortcut IP Access

  - Small Cell as a Service

* SaMOG

  - 讓 UE 可以透過非 3GPP 網路、穿過 P-GW 連往 Internet
  - 對 P-GW 來說，UE 只是換了一個 S-GW
  - SaMOG GW 模擬了 S-GW 的行為（？）

* SON - Self Optimize/Organize Network
