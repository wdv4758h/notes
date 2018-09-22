========================================
GStreamer & 串流混合 (Mixing)
========================================


.. contents:: 目錄


影像混合
========================================

.. code-block:: sh

    # 4 路 videotestsrc
    gst-launch-1.0 -ve videomixer name=mix \
        sink_0::alpha=1 sink_0::xpos=0   sink_0::ypos=0 \
        sink_1::alpha=1 sink_1::xpos=646 sink_1::ypos=0 \
        sink_2::alpha=1 sink_2::xpos=0   sink_2::ypos=486 \
        sink_3::alpha=1 sink_3::xpos=646 sink_3::ypos=486 ! \
        autovideosink \
        videotestsrc pattern=snow !  mix. \
        videotestsrc pattern=gamut ! mix. \
        videotestsrc pattern=spokes ! mix. \
        videotestsrc pattern=colors ! mix.

    # 4 路 videotestsrc (調大小)
    gst-launch-1.0 -ve videomixer name=mix \
        sink_0::alpha=1 sink_0::xpos=0   sink_0::ypos=0 \
        sink_1::alpha=1 sink_1::xpos=646 sink_1::ypos=0 \
        sink_2::alpha=1 sink_2::xpos=0   sink_2::ypos=486 \
        sink_3::alpha=1 sink_3::xpos=646 sink_3::ypos=486 ! \
        autovideosink \
        videotestsrc pattern=snow ! video/x-raw,width=640,height=480 !  mix. \
        videotestsrc pattern=gamut ! video/x-raw,width=640,height=480 ! mix. \
        videotestsrc pattern=spokes ! video/x-raw,width=640,height=480 ! mix. \
        videotestsrc pattern=colors ! video/x-raw,width=640,height=480 ! mix.
