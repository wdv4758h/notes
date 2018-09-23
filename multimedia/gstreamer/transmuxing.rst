========================================
Transmuxing
========================================


.. contents:: 目錄


範例
========================================

.. code-block:: sh

    # .mp4 -> .mkv (parsebin)
    gst-launch-1.0 filesrc location=test.mp4 ! \
        parsebin ! matroskamux ! \
        filesink location=test.mkv

    # .mp4 -> .mkv
    gst-launch-1.0 filesrc location=test.mp4 ! \
        qtdemux ! matroskamux ! \
        filesink location=test.mkv

    # .ts -> .mp4 (H264/AAC) (multiqueue)
    gst-launch-1.0 \
      multiqueue max-size-buffers=0 max-size-bytes=0 max-size-time=0 name=mq \
      filesrc location=test.ts ! \
      parsebin name=demux \
      demux. ! queue ! h264parse ! mq.sink_0 mq.src_0 ! muxer. \
      demux. ! queue ! aacparse ! mq.sink_1 mq.src_1 ! muxer. \
      qtmux name=muxer ! queue ! filesink location=test.mp4
