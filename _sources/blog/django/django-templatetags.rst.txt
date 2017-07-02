:title: 自製 template tags 和 filters
:slug: django-templatetags
:date: 2014-02-20 00:10
:category: Django
:tags: Django
:author: wdv4758h
:summary: 今天解問題的時候剛好查到利用 template tags 的解法，所以就寫一下紀錄

起手式
========================================

要建立自己的 template tags 之前，要先在一個 app 資料架底下建立 "templatetags" 資料夾，
如果這些 tags 是跟 app A 有關的話，那很理所當然可以放在 app A 資料夾下的 "templatetags"，
如果是比較不能區分的話，可以建立一個 app 專門放 template tags。

**注意要有 \_\_init\_\_.py 來讓 Python 把這個資料夾當作 package**

自製的 tags 和 filter 就放在 templatetags 資料夾底下的檔案，
檔案名字就是在 template 要 load 時的名字


結構可能長這樣:

| App/
|     __init__.py
|     models.py
|     templatetags/
|         __init__.py
|         abc.py
|     view.py

在 template 裡要用到 abc.py 這個檔案裡寫的 tags、filter 時，
就在 template 裡 "{% load abc %}"

有包含 custom tags 的 app 要加到 **INSTALLED_APPS** 裡 **{% load %}** 才會 work。

(security feature: 你可以在一台機器上裝多個 template libraries 而不讓它們可以 access 機器上的每個 Django 的程式)

鍛冶
========================================

要能製造出一個 valid 的 tag library 首先要有一個叫作 **register** 的 **template.Library** instance

所以開頭會長這樣 :

.. code-block:: python

    from django import template

    register = template.Library()

filters
------------------------------

tags
------------------------------

Ref
========================================

- `Custom template tags and filters <https://docs.djangoproject.com/en/dev/howto/custom-template-tags/>`_
- Django default tags & filters

    * django/template/defaultfilters.py
    * django/template/defaulttags.py
