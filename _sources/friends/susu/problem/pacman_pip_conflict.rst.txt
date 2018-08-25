今天用 yaourt 裝 aur/nemo-dropbox 時, 發現 nemo-dropbox 依賴 python2-docutil

可是 python2-docutil 已經在我裝 rst2pdf 時, 用 pip 安裝好了, 所以 yaourt 無法安裝.

解法有兩個, 參考 http://www.douban.com/group/topic/34442515/

1. 自己下載 aur/nemo-dropbox, 把 PKGBUILD 裡的 dependency 去掉 python2-docutil, 再 build nemo-dropbox.

   - 使用步驟(請注意, 未測試過是否正確)
   - ``yaourt -G aur/nemo-dropbox``
   - 修改 nemo-dropbox/PKGBUILD
   - ``makepkg -si``

2. 把 pip 安裝的 python2-docutil 移除, 全部用系統的 yaourt 來安裝 nemo-dropbox
   
   - rst2pdf 則轉移到一個 virtualenv 中再用 pip 安裝, 系統的 python 套件全用 pacman/yaourt 來裝.
