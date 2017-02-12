==============
安裝設定懶人包
==============

* Jails

  - 見 ``freebsd-jails.rst``

* Django ::

    $ pyvenv-3.4 .venv
    $ source .venv/bin/activate
    $ pip install Django
    # portmaster -Bdw database/py-sqlite3

    $ django-admin startproject { project-name }
    $ cd { project-name }
    $ mkdir templates
    $ mkdir static

    $ ./manage.py syncdb
    $ ./manage.py runserver

    $ ./manage.py startapp { app-name }
    $ mkdir templates/{ app-name }

  - 設定資源檔的路徑

    + 檢查 ``{ project-name }/{ project-name }/settings``

      * 基本路徑

        - ``BASE_DIR = os.path.dirname(os.path.dirname(__file__))``

      * CSS 相關

        - ``STATIC_URL = '/static/'``
        - ``STATICFILES_DIRS = ( os.path.join(BASE_DIR，"static"), )``

      * Template 相關

        - ``TEMPLATE_DIRS = ( os.path.join(BASE_DIR，'templates'), )``
