========================================
Nginx
========================================


.. contents:: 目錄


HTTPS
========================================

.. code-block:: nginx

    server {
        listen 443 ssl;
        server_name 0.0.0.0;

        ssl on;
        ssl_certificate /etc/nginx/ssl/nginx.crt;
        ssl_certificate_key /etc/nginx/ssl/nginx.key;

        location / {
            # ...
        }
    }



Redirect HTTP to HTTPS
========================================

.. code-block:: nginx

    server {
        listen 80 default_server;
        listen [::]:80 default_server;
        server_name _;
        return 301 https://$host$request_uri;
    }



Body Size
========================================

.. code-block:: nginx

    client_max_body_size 20M;



WebSocket support and Proxy to Unix Socket
==========================================

* `nginx - WebSocket proxying <https://nginx.org/en/docs/http/websocket.html>`_


.. code-block:: nginx

    upstream api {
        server unix:/path/to/api.sock;
    }

    upstream websocket {
        server unix:/path/to/websocket.sock;
    }


    server {
        # some settings ...

        location / {
            proxy_pass http://api;

            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            # enable this if and only if you use HTTPS
            proxy_set_header X-Forwarded-Proto https;
            proxy_set_header Host $http_host;
            # we don't want nginx trying to do something clever with
            # redirects, we set the Host: header above already.
            proxy_redirect off;

            # increase the allowed size of request body,
            client_max_body_size 10m;

            proxy_set_header X-Forwarded-Host $server_name;
            proxy_set_header X-Real-IP $remote_addr;
        }

        location /websocket {
            proxy_pass http://websocket;

            proxy_http_version 1.1;
            proxy_set_header Upgrade $http_upgrade;
            proxy_set_header Connection "upgrade";
            # this is important,
            # nginx by default will close the connection if there is no data transmitted within 60 seconds,
            # change to use bigger value for your need
            proxy_read_timeout 600;

            proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
            # enable this if and only if you use HTTPS
            proxy_set_header X-Forwarded-Proto https;
            proxy_set_header Host $http_host;
            # we don't want nginx trying to do something clever with
            # redirects, we set the Host: header above already.
            proxy_redirect off;

            proxy_set_header X-Forwarded-Host $server_name;
            proxy_set_header X-Real-IP $remote_addr;
        }
    }



參考
========================================

* `Gixy - Nginx configuration static analyzer <https://github.com/yandex/gixy>`_
* `Awesome Nginx <https://github.com/agile6v/awesome-nginx>`_
* `Nginx Resources <https://github.com/fcambus/nginx-resources>`_
