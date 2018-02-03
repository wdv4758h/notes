========================================
效能調整 (Performance)
========================================


.. contents:: 目錄


介紹
========================================

Deep Learning 的 model 雖然強大，
但是要在真正應用中使用還是要對效能和資源用量最調整，
並在使用情狀做適當的效能與準確度的取捨。



知識萃取 (Knowledge Distillation)
========================================

從現有較強大的 model 中萃取出重要的處理，
藉此製造出較小的 model，
並且維持相當水準的準確度。



刪減技巧 (Pruning Technique)
========================================

對 model 的 feature maps 各自計算浮點數的運算量和效能，
以及估算移除該 feature map 會造成的準確度影響，
從中找出運算量大但成效不彰的目標來移除。



參考
========================================

* `Awesome Knowledge Distillation <https://github.com/dkozlov/awesome-knowledge-distillation>`_
* [2015] `Distilling the Knowledge in a Neural Network <https://arxiv.org/abs/1503.02531>`_
* `Speedy Neural Networks for Smart Auto-Cropping of Images <https://blog.twitter.com/engineering/en_us/topics/infrastructure/2018/Smart-Auto-Cropping-of-Images.html>`_
		- [2018] `Faster gaze prediction with dense networks and Fisher pruning <https://arxiv.org/abs/1801.05787>`_
