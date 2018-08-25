===============================================================================
github reStructuredText 支援
===============================================================================
github 大致上支援 reStructuredText，但有時我需要 reStructuredText 不提供的功能，例如刪除線。

這時候可以嵌入 HTML::

  ..  role:: raw-html(raw)
      :format: html

  :raw-html:`<s>刪除線</s>`

效果像這樣：

..  role:: raw-html(raw)
    :format: html

:raw-html:`<s>刪除線</s>`

--------

使用 raw HTML 的話，還可以用 ``<details>`` tag::

  :raw-html:`<details><summary>點擊查看水果列表</summary>`

  * Apple
  * Banana
  * Cookie (*喂這不是水果吧*)

  :raw-html:`</details>`

效果像這樣：

:raw-html:`<details><summary>點擊查看水果列表</summary>`

* Apple
* Banana
* Cookie (**喂這不是水果吧**)

:raw-html:`</details>`
