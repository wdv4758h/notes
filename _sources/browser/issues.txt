========================================
Issues
========================================


.. contents:: 目錄


Bug 1308332 - [meta] The add-on SDK's module system is a performance disaster
=============================================================================

:URL: https://bugzilla.mozilla.org/show_bug.cgi?id=1308332

相關文章：

* `Faster Firefox startup & shutdown with add-ons present <https://blog.mozilla.org/nnethercote/2016/11/03/faster-firefox-startup-shutdown-with-add-ons-present/>`_

成果：

::

    Configuration: Two windows with 15 tabs each and 22 addons.

        Startup: 25 seconds -> 14 seconds (44% reduction)
        Shutdown: 30 seconds -> 5 seconds (83% reduction)
