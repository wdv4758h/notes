========================================
功耗 (Power Consumption)
========================================


.. contents:: 目錄


介紹
========================================

基本單位： 1W = 1000 mW = 1000000 uW = 1000000000 nW


影響功耗的因素：

* 製程
* 設計
* 運轉時脈
* 供電電壓
* 運轉模式（例如睡眠、全速運轉）
* 喚醒時機
* 外接元件
* 漏電
* ...


在討論功耗時，
要知道睡眠狀態跟全速運轉狀態的功耗，
藉此可以了解功耗變化的範圍。



實際案例
========================================

* `STM32L5 <https://www.st.com/en/microcontrollers/stm32l5-series.html>`_
    - shutdown mode: 33 nA
    - stop mode: 3.6 µA
    - active mode: 60 µA/MHz
    - EEMBC ULPBench 分數 402 ULPMark-CP



效能比較 - EEMBC - Embedded Microprocessor Benchmark Consortium
===============================================================

:Site: https://www.eembc.org/products/
