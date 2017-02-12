:title: 初次使用 Pelican
:slug: pelican
:date: 2014-02-01 14:33
:category: Python
:tags: pelican, Python
:author: wdv4758h
:summary: 一些 Pelican 使用紀錄

首先，什麼是 `Pelican <http://docs.getpelican.com/en/>`_ 呢？
Pelican 是個 Python 寫的靜態網站 generator，
你可以使用 Markdown, reStructuredText, AsciiDoc 等 markup language 作為撰寫的格式，
然後經由 Pelican 去生成靜態的網頁，經由這種方式，可以方便地使用你喜歡的文字編輯器去撰寫你的文章，
還可以結合 Version Control 去管理，
而由於生成的網頁是靜態的，所以可以放到 Github Pages 或者其他可以放置靜態網頁的地方去 Host，無疑是個很方便的模式。

Pelican 初步設定
========================================

Theme
========================================

Disqus Support
========================================

Pelican 要支援 Disqus 非常簡單，首先只要在你的 Disqus 新增好你的網站，獲得你的 Disqul url 後，
只要在你的 pelicanconf.py 裡新增 DISQUS_SITENAME = 'your-disqus-url' 即可：

.. code-block:: python

    DISQUS_SITENAME = 'my-blog.disqus.com'
