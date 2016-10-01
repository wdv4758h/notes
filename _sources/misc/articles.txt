========================================
文章
========================================


.. contents:: 目錄


How we brought HTTPS Everywhere to the cloud
============================================

:來源: CloudFlare
:作者: Ingvar Stepanyan
:URL: https://blog.cloudflare.com/how-we-brought-https-everywhere-to-the-cloud-part-1/

目標是要自動把 ``http://`` 改成 ``https://`` ，
要達到這件事有兩個假設需要成立

1. 所有 HTTP 的子資源都可以經由 HTTPS 取得
2. 取得方式必須是同 Domain 且同路徑

HTTPS Everywhere 利用人力確認哪些網站適用這種自動轉換，
而 CloudFlare 則把這個清單拿來使用在 CDN 上。
