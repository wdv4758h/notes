========================================
SVM (Suppoert Vector Machine)
========================================


.. contents:: 目錄


說明
========================================

* SVM (Support Vector Machine)
    - 可以對「可線性分割 (Linear Seperable)」的資料找到「最佳解」
    - 對於「不可線性分割」的資料，只要能夠使用 kernel function 轉換空間成為「可線性分割」即可解決
    - 使用於 classification、regression、outliers detection

* Support Vector 是資料中最接近最佳解超平面的資料點
    - 最難以區分的資料
    - 對於最佳解有直接的影響
    - 如果移除相關資料點會改變最佳解

* kernel function
    - 空間對空間的映射
    - 可以是低維度映射到高維度
    - 「不可線性分割」的資料在映射到新空間有可能變成「可線性分割」
    - 在此領域中，新的空間通常被稱為「Feature Space」

* 為「可線性分割」的資料找到最佳解超平面是「二次規劃 (Quadratic Programming)」問題
    - 已經有標準作法來找出最佳解
    - 因為是計算距離所以採用了 Euclidean norm 的平方，因此成為「二次規劃」
    - 找出函數在特定條件約束下的極值，以 SVM 的狀況其中約束條件是等式
    - 利用拉格朗日乘數法 (Lagrange Multiplier)，可以把 n 個變數與 k 個等式約束條件的最佳化問題轉成 n+k 個方程式解的問題
    - 拉格朗日乘數法會找到所有極值，不保證是最佳解，但是只要加上互相比較過濾後就可以找到最佳解

* 可線性分割 (Linear Seperable)
    - 資料的不同類別可以用超平面 (Hyperplane) 劃分
* 超平面 (Hyperplane)
    - 二維空間的超平面為直線
    - 三維空間的超平面為平面
    - N 維空間的超平面為 N-1 維
* Margin
    - 超平面間的距離
    - SVM 找最佳解超平面就是把 Margin 最大化

* Linear SVM
    - Hard Margin
        + 資料是可線性分割，直接找最佳解
    - Soft Margin
        + 資料是不可線性分割，加入 hinge loss function 來放寬條件
* Non-Linear SVM
    - 透過 kernel function 把資料映射到新的空間
    - 在新的空間找最佳化超平面，此超平面在原空間對應到的可能是非線性

* 處理 Overfitting
    - 如果可以，取得更多更全面的資料
    - SVM 在原理上是可以自動避免 Overfitting 的，但在實務上這依靠正規化和 kernel 的調整

* Generalization Error (out-of-samples error)
    - 衡量演算法對於先前沒有看過的資料的準確度
    - 演算法可以藉由降低 Overfitting 來減少 Generalization Error

* SVM 優點
    - 在小而乾淨的資料時運作良好，因為靠 Support Vector 處理，所以只須小部份的資料（子集）
* SVM 缺點
    - 計算量和記憶體需求對於資料量和種類量很敏感，計算量會跟著大量成長，訓練時間也會拉長
    - 對於雜訊多或者種類之間有重疊性的狀況處理較差，要靠適合的 kernel function 緩解

* SVM 擴充
    - SVC (Support Vector Clustering)
        + 利用更改 SVM 的 kernel function 來處理非監督式學習
    - Multiclass SVM
        + 支援區分多個種類
        + WTA SVM (one-versus-all method using winner-takes-all strategy)
            * 窮舉，一對其他 (one-vs-rest)，N 個種類的話就有 N 個 SVM 去分類
        + MWV SVM (one-versus-one method using max-wins voting strategy)
            * 窮舉，一對一 (one-vs-one)，N 個種類的話就有 N * (N-1) / 2 種組合，每個都建立 SVM 去分類，看哪個種類成績最好
        + Crammer and Singer
            * combines all class probabilities into a single SVM-like optimisation problem
        + MSVM
        + DAG (Directed Acyclic Graph) SVM
        + ECOC (Error-Correcting Output Codes) SVM
        + PWC KLR SVM
        + PWC PSVM
            * Pairwise Coupling + Posterior Probabilities
    - Transductive SVM
        + 支援半監督式學習 (Semi-Supervised Learning)
    - Structured SVM
    - Regression SVM
    - Bayesian SVM


大致發展過程：

* 提出 SVM 來針對兩個種類的線性可分割資料找出最佳解
* 加入 hinge loss function 來放寬條件，以套用在線性不可分割的資料
* 利用 kernel function 處理線性不可分割的資料
* 套用到多個種類


參考：

* `Why SVM is Quadratic Programming Problem instead of Linear Programming Problem? <https://stats.stackexchange.com/questions/293856/svm-why-quadratic-programming-problem>`_
* `SVM & Overfitting <https://stats.stackexchange.com/questions/35276/svm-overfitting-curse-of-dimensionality>`_
* `scikit-learn - Support Vector Machines <http://scikit-learn.org/stable/modules/svm.html>`_
    - 可以看其中的圖了解 kernel function 對分類的影響
* `Wikipedia - Constrained Optimization <https://en.wikipedia.org/wiki/Constrained_optimization>`_



實做
========================================

* `libsvm <https://github.com/cjlin1/libsvm>`_
    - by 林智仁 (Chih-Jen Lin) (cjlin) @ NTU
* `liblinear <https://github.com/cjlin1/liblinear>`_
    - by 林智仁 (Chih-Jen Lin) (cjlin) @ NTU
* `ThunderSVM: fast SVM Library on GPUs and CPUs <https://github.com/zeyiwen/thundersvm>`_



參考
========================================

* `Support Vector Machines for dummies: A Simple Explanation <http://blog.aylien.com/support-vector-machines-for-dummies-a-simple/>`_
* `An Idiot’s guide to Support vectormachines (SVMs) <https://web.mit.edu/6.034/wwwbob/svm-notes-long-08.pdf>`_
* `Interactive SVM Explorer, using Dash and scikit-learn <https://github.com/plotly/dash-svm>`_
    - `Support Vector Machine (SVM) Explorer <https://dash-svm.plot.ly/>`_
