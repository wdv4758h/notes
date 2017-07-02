:title: ZIP unsupported compression method 99
:slug: zip-unsupported-99
:date: 2014-11-04 23:51
:category: Misc
:tags: zip
:author: wdv4758h
:summary: ZIP unsupported compression method 99

| 前陣子朋友碰到有設密碼的 zip 檔不能用 unzip 來解開，
| 會出現 "does not support compression method 99" 的錯誤，
| 原因是這些檔案用 AES 加密，
| 對 unzip 來說是新 method 所以不支援，
| 這時候只好用其他支援的工具解開啦，
| 例如 : 7z
