:title: Notification things
:slug: notification-things
:date: 2014-12-26 18:56
:modified: 2014-12-27 01:33
:category: Misc
:tags: linux, notification
:author: wdv4758h
:summary:

Linux
========================================

* `Arch Wiki - Desktop Notifications <https://wiki.archlinux.org/index.php/Desktop_notifications>`_

Libnotify
------------------------------

* `Arch Package - libnotify <https://www.archlinux.org/packages/extra/x86_64/libnotify/>`_

* desktop independent
* **need a notification server**

Dependencies
~~~~~~~~~~~~~~~~~~~~

gdk-pixbuf2
+++++++++++

* `Wikipedia - GDK <http://en.wikipedia.org/wiki/GDK>`_
    - GIMP Drawing Kit
    - GDK was originally developed on the X Window System for the GIMP

GdkPixbuf is a toolkit for image loading and pixel buffer manipulation.

In GTK+ version 2.22 from 2010-09-23 GdkPixbuf was split off from GDK into a separate package in preparation for the transition to GTK+ 3.

Notification servers
------------------------------

Bult-in
~~~~~~~~~~~~~~~~~~~~

The following desktop environments use their own implementations to display notifications, and you cannot replace them.
Their notification servers are started automatically on login to receive notifications from applications via ``DBus``.

* Cinnamon
* Enlightenment
* GNOME
* KDE

Standalone
~~~~~~~~~~~~~~~~~~~~

Mac OS X
========================================

Growl
------------------------------

- `Wikipedia - Growl <http://en.wikipedia.org/wiki/Growl_%28software%29>`_
- `Growl - Website <http://growl.info/>`_

Browser
========================================

Firefox
------------------------------

* `MDN - Notification - Web API Interfaces <https://developer.mozilla.org/en/docs/Web/API/notification>`_

Chromium
------------------------------

* `Chromium - Linux Technical FAQ <http://www.chromium.org/developers/linux-technical-faq>`_
    - Why don't Chromium notifications use the D-BUS-based notifications system (aka libnotify / notification-daemon)?
        + HTML5 notifications can contain arbitrary HTML, which is not supported by the notification protocol. (This is the same reason we don't use Growl on OS X.)
        + Chromium's notifications include a button that brings up an options menu, which is also not supported by the notification protocol.
        + The glitzy Ubuntu notifications daemon, by design, does not allow the user to interact with notifications at all, which doesn't work when the notification HTML includes clickable links.
        + It would be nice to extend the protocol to allow Chromium to integrate.
