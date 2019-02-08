========================================
Google Cast
========================================


.. contents:: 目錄


使用
========================================

.. code-block:: sh

    # 找到想要使用的 Chromecast 裝置的 IP
    sudo systemctl start avahi-daemon
    avahi-discover

    # 取得裝置資訊
    rust-caster -a $IP -i
    # 播放指定的 video URL
    rust-caster -a $IP -m https://URL/TO/VIDEO
    # 播放指定的 YouTube 影片
    rust-caster -a $IP -m $YOUTUBE_VIDEO_ID --media-app youtube


* `Google Cast <https://developers.google.com/cast/>`_
* `Google Cast Repos <https://github.com/googlecast>`_
* `Wikipedia - Google Cast <https://en.wikipedia.org/wiki/Google_Cast>`_
* `Wikipedia - Chromecast <https://en.wikipedia.org/wiki/Chromecast>`_
* `Wikipedia - List of apps with Google Cast support <https://en.wikipedia.org/wiki/List_of_apps_with_Google_Cast_support>`_
* `rust-cast - lib to communicate with the Google Cast devices <https://github.com/azasypkin/rust-cast>`_
* `rust-caster - Test tool that demonstrates Rust Cast crate <https://github.com/azasypkin/rust-caster>`_
