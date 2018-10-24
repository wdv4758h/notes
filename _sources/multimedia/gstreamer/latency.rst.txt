========================================
GStreamer Latency 測量
========================================


.. contents:: 目錄


audiolatency
========================================

.. code-block:: sh

    gst-launch-1.0 -v autoaudiosrc ! audiolatency print-latency=true ! autoaudiosink



GST_TRACE
========================================

.. code-block:: sh

    $ env GST_DEBUG="GST_TRACER:7" GST_TRACERS=latency gst-launch-1.0 \
          audiotestsrc num-buffers=5 ! audioconvert ! volume volume=0.7 ! \
          autoaudiosink
    # 以下會看到 pipeline 從 src 到 sink 的 latency，單位是 ns
    0:00:00.017334932 12599 0x557610529160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x557610304cc0 (latency)
    0:00:00.017369502 12599 0x557610529160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x557610304c00 (log)
    0:00:00.017382938 12599 0x557610529160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x557610304b40 (rusage)
    0:00:00.017395524 12599 0x557610529160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x557610304a80 (stats)
    0:00:00.017441811 12599 0x557610529160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x5576103049c0 (leaks)
    0:00:00.017528371 12599 0x557610529160 TRACE             GST_TRACER gsttracerrecord.c:111:gst_tracer_record_build_format: latency.class, src=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", sink=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", time=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"time\\\ it\\\ took\\\ for\\\ the\\\ buffer\\\ to\\\ go\\\ from\\\ src\\\ to\\\ sink\\\ ns\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;", ts=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"ts\\\ when\\\ the\\\ latency\\\ has\\\ been\\\ logged\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;";
    0:00:00.017563256 12599 0x557610529160 DEBUG             GST_TRACER gsttracerrecord.c:125:gst_tracer_record_build_format: new format string: latency, src=(string)%s, sink=(string)%s, time=(guint64)%lu, ts=(guint64)%lu;
    Setting pipeline to PAUSED ...
    Pipeline is PREROLLING ...
    Redistribute latency...
    0:00:00.039506546 12599 0x557610547450 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)autoaudiosink0-actual-sink-pulse_sink, time=(guint64)270664, ts=(guint64)39495908;
    Pipeline is PREROLLED ...
    Setting pipeline to PLAYING ...
    New clock: GstPulseSinkClock
    # time = 81920，代表這次處理花了 81920 ns = 81.92 μs = 0.08192 ms = 0.00008192 sec
    0:00:00.040063361 12599 0x557610547450 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)autoaudiosink0-actual-sink-pulse_sink, time=(guint64)81920, ts=(guint64)40053273;
    0:00:00.040378620 12599 0x557610547450 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)autoaudiosink0-actual-sink-pulse_sink, time=(guint64)35296, ts=(guint64)40362637;
    0:00:00.040639325 12599 0x557610547450 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)autoaudiosink0-actual-sink-pulse_sink, time=(guint64)73055, ts=(guint64)40627866;
    0:00:00.040812470 12599 0x557610547450 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)autoaudiosink0-actual-sink-pulse_sink, time=(guint64)37600, ts=(guint64)40768440;
    Got EOS from element "pipeline0".
    Execution ended after 0:00:00.119590670
    Setting pipeline to PAUSED ...
    Setting pipeline to READY ...
    Setting pipeline to NULL ...
    Freeing pipeline ...


.. code-block:: sh

    $ env GST_DEBUG="GST_TRACER:7" GST_TRACERS=latency gst-launch-1.0 \
          audiotestsrc num-buffers=5 ! opusenc ! fakesink
    0:00:00.014942634 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55aa5c8c8cc0 (latency)
    0:00:00.014973975 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55aa5c8c8c00 (log)
    0:00:00.014987720 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55aa5c8c8b40 (rusage)
    0:00:00.014999559 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55aa5c8c8a80 (stats)
    0:00:00.015015219 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55aa5c8c89c0 (leaks)
    0:00:00.015084284 16722 0x55aa5caed160 TRACE             GST_TRACER gsttracerrecord.c:111:gst_tracer_record_build_format: latency.class, src=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", sink=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", time=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"time\\\ it\\\ took\\\ for\\\ the\\\ buffer\\\ to\\\ go\\\ from\\\ src\\\ to\\\ sink\\\ ns\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;", ts=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"ts\\\ when\\\ the\\\ latency\\\ has\\\ been\\\ logged\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;";
    0:00:00.015099392 16722 0x55aa5caed160 DEBUG             GST_TRACER gsttracerrecord.c:125:gst_tracer_record_build_format: new format string: latency, src=(string)%s, sink=(string)%s, time=(guint64)%lu, ts=(guint64)%lu;
    Setting pipeline to PAUSED ...
    Pipeline is PREROLLING ...
    Redistribute latency...
    0:00:00.019206112 16722 0x55aa5cb10f20 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)371472, ts=(guint64)19194162;
    Pipeline is PREROLLED ...
    Setting pipeline to PLAYING ...
    New clock: GstSystemClock
    # time = 238824，代表這次處理花了 238824 ns = 238.824 μs = 0.238824 ms = 0.000238824 sec
    0:00:00.019709658 16722 0x55aa5cb10f20 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)238824, ts=(guint64)19701361;
    0:00:00.019938293 16722 0x55aa5cb10f20 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)167269, ts=(guint64)19932470;
    0:00:00.020158685 16722 0x55aa5cb10f20 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)144429, ts=(guint64)20153405;
    0:00:00.020403369 16722 0x55aa5cb10f20 TRACE             GST_TRACER :0:: latency, src=(string)audiotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)168749, ts=(guint64)20396403;
    Got EOS from element "pipeline0".
    Execution ended after 0:00:00.001237935
    Setting pipeline to PAUSED ...
    Setting pipeline to READY ...
    Setting pipeline to NULL ...
    Freeing pipeline ...


.. code-block:: sh

    $ env GST_DEBUG="GST_TRACER:7" GST_TRACERS=latency gst-launch-1.0 \
          videotestsrc num-buffers=25 ! x264enc ! fakesink
    0:00:00.029729829 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55ee00a5fcc0 (latency)
    0:00:00.029776539 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55ee00a5fc00 (log)
    0:00:00.029788692 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55ee00a5fb40 (rusage)
    0:00:00.029799904 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55ee00a5fa80 (stats)
    0:00:00.029815610 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracer.c:164:gst_tracer_register:<registry0> update existing feature 0x55ee00a5f9c0 (leaks)
    0:00:00.029903245 19772 0x55ee00c84160 TRACE             GST_TRACER gsttracerrecord.c:111:gst_tracer_record_build_format: latency.class, src=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", sink=(structure)"scope\,\ type\=\(type\)gchararray\,\ related-to\=\(GstTracerValueScope\)GST_TRACER_VALUE_SCOPE_PAD\;", time=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"time\\\ it\\\ took\\\ for\\\ the\\\ buffer\\\ to\\\ go\\\ from\\\ src\\\ to\\\ sink\\\ ns\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;", ts=(structure)"value\,\ type\=\(type\)guint64\,\ description\=\(string\)\"ts\\\ when\\\ the\\\ latency\\\ has\\\ been\\\ logged\"\,\ min\=\(guint64\)0\,\ max\=\(guint64\)18446744073709551615\;";
    0:00:00.029923268 19772 0x55ee00c84160 DEBUG             GST_TRACER gsttracerrecord.c:125:gst_tracer_record_build_format: new format string: latency, src=(string)%s, sink=(string)%s, time=(guint64)%lu, ts=(guint64)%lu;
    Setting pipeline to PAUSED ...
    Pipeline is PREROLLING ...
    Redistribute latency...
    0:00:00.073618607 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)28545183, ts=(guint64)73602510;
    0:00:00.075159065 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)27506991, ts=(guint64)75141270;
    Pipeline is PREROLLED ...
    Setting pipeline to PLAYING ...
    New clock: GstSystemClock
    # time = 30293861，代表這次處理花了 30293861 ns = 30293.861 μs = 30.293861 ms = 0.030293861 sec
    0:00:00.080092688 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)30293861, ts=(guint64)80073202;
    0:00:00.088350177 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)36479050, ts=(guint64)88326118;
    0:00:00.094017568 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)39613728, ts=(guint64)93994903;
    0:00:00.102433355 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)45504672, ts=(guint64)102411995;
    0:00:00.108762991 19772 0x55ee00ca8590 TRACE             GST_TRACER :0:: latency, src=(string)videotestsrc0_src, sink=(string)fakesink0_sink, time=(guint64)49325524, ts=(guint64)108745028;
    Got EOS from element "pipeline0".
    Execution ended after 0:00:00.034374020
    Setting pipeline to PAUSED ...
    Setting pipeline to READY ...
    Setting pipeline to NULL ...
    Freeing pipeline ...
