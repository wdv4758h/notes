========================================
GStreamer & 字幕
========================================


.. contents:: 目錄


單字幕
========================================

透過 textoverlay 我們可以在任意的串流中加入文字，
再搭配 subparse 就可以處理字幕，
以下是範例：


.. code-block:: sh

    # 測試影像 + 固定文字
    gst-launch-1.0 -v videotestsrc ! \
        textoverlay \
            text="Room A" valignment=top \
            halignment=left font-desc="Sans, 72" ! \
        autovideosink

    # MP4 影像 + SRT
    gst-launch-1.0 \
        textoverlay name=ov ! autovideosink \
        filesrc location=sample.mp4 ! decodebin ! ov.video_sink \
        filesrc location=sample.srt ! subparse ! ov.text_sink \

    # MP4 影像 + SRT (包含調整)
    gst-launch-1.0 \
        textoverlay name=ov \
            font-desc="Noto Sans" auto-resize=false scale-mode=user ! \
        autovideosink \
        filesrc location=sample.mp4 ! decodebin ! ov.video_sink \
        filesrc location=sample.srt ! subparse ! ov.text_sink \



雙字幕
========================================



動態切換字幕
========================================
