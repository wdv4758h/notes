========
``sudo``
========
* ``sudo -E`` 保留使用者的環境變數

  - 在 ``visudo`` 中的 ``env_keep`` 有定義要被繼承的環境變數
  - ``secure_path`` 定義執行時的 path，若 ``sudo -E`` 找不到指令可能是因為這個
