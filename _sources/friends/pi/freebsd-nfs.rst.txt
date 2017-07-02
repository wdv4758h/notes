===
NFS
===
簡記 NFS server 以及 NFS client with autofs 設定方式

假設：

* NFS server 的 domain name 為 ``nfs_server``
* NFS client 的 domain name 為 ``nfs_client``
* NFS server export 出 ``/vol/data`` 、 ``/vol/data2``
* NFS client 將 ``nfs_server:/vol/data`` 掛載至 ``/net/data``

  - 保留 root 權限、檔案系統可讀寫

* NFS client 將 ``nds:server:/vol/data2`` 掛載至 ``/net/data2``

  - 將 root 對應為 nobody、檔案系統唯讀


Server
-------
在 ``/etc/rc.conf`` 設定 enable NFS 相關服務 ::

  rpcbind_enable="YES"
  nfs_server_enable="YES"
  mountd_enable="YES"
  mountd_flags="-r"

執行 ``service nfsd start`` 將 NFS Server 啟動

在 ``/etc/exports`` 設定要 export 給 ``nfs_client`` 的目錄們 ::

  /vol/data -maproot=root nfs_client
  /vol/data2 -ro -maproot=nobody nfs_client

注意 ``/vol/data`` 和 ``/vol/data2`` 必須是不同 file system，否則會失敗

執行 ``# service mountd reload`` 重新載入 ``/etc/exports``


Client
-------
在 ``/etc/rc.conf`` 設定 enable autofs ::

  autofs_enable="YES"

執行 ``service automount start`` 將 autofs 啟動

在 ``/etc/auto_master`` 設定「 ``/net`` NFS 目錄的設定請見 ``/etc/auto_local`` 」 ::

  /net auto_local

在 ``/etc/auto_local`` 設定 ``/net`` 的掛載設定 ::

  data nfs_server:/vol/data
  data2 nfs_server:/vol/data2

〔可能有誤〕今天我設定完 Client 以後，目錄還是掛不起來，但重開機就好了
