========================================
視覺化 (Visualization)
========================================

* Kibana
    - 專注於 log 和搜尋
    - 通常用來搜尋 log
    - 整合在 ELK stack，通常一起用
        + Elasticsearch: NoSQL database based on Lucene search engine
        + Logstash: log pipeline tool
        + Kibana: visualization layer for Elasticsearch
* Grafana (2013 年從 Kibana 專案 fork 出來，接著朝不同方向發展)
    - 專注為 time series data 建立 dashboard
    - 通常和 Time Series 資料庫一起使用
        + Graphite
        + InfluxDB
        + OpenTSDB
        + Elasticsearch
        + Prometheus
    - 支援多種資料來源，也可混合使用
