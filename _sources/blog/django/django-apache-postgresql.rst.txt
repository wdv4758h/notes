:title: Django, Apache, PostgreSQL
:slug: django-apache-postgresql
:date: 2014-11-22 01:00
:modified: 2014-11-22 01:00
:category: Django
:tags: Django
:author: wdv4758h
:summary: Django + Apache + PostgreSQL

Although I usually use Arch Linux,
this time I need to install every thing on Ubuntu Server (I get a task to install something on Ubuntu VM) ...

First, I give my public key to current VM administrator, so I can get permission to ssh to server by key.

Install Apache, mod-wsgi ...

Making a virtualenv, cloning current project, installing the requirement.txt

Modify Apache's configuration (Apache's configuration in Ubuntu is at ``/etc/apache2/apache2.conf``,
and default user that Apache use in Ubuntu is "www-data"), setting WSGIPythonPath to the virtualenv one

Install PostgreSQL (this is my first time to install PostgreSQL)

Setting PostgreSQL (create user, database, ...)
