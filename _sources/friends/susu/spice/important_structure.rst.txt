- SPICE protocol 相關

    - spice rendering command

        - RedDrawBase => SpiceMsgDisplayBase (https://github.com/SPICE/spice-common/blob/master/common/messages.h#L240)

            - bbox, clip

        - RED_DISPLAY_COPY_BITS: 從 source image copy 一個跟 bbox 一樣大的 rectangle(左上角 position 為參數) 到 bbox.
        - RED_DISPLAY_DRAW_FILL: Fill bounding_box using brush
        - RED_DISPLAY_DRAW_OPAQUE
        - RED_DISPLAY_DRAW_COPY: 從 source image copy 一個 rectangle 到 bbox
        - RED_DISPLAY_DRAW_BLEND: 從 source image, 拿一個 rectangle 跟 bbox 作 mix
        - RED_DISPLAY_DRAW_BLACKNESS, RED_DISPLAY_DRAW_WHITENESS, RED_DISPLAY_DRAW_INVERS: 把 bbox 的 pixel 轉成 black/white/反轉
        - RED_DISPLAY_DRAW_ROP3: mix source image 的 rectangle, bbox, 跟 brush
        - RED_DISPLAY_DRAW_TRANSPARENT
        - RED_DISPLAY_DRAW_ALPHA_BLEND
        - RED_DISPLAY_DRAW_STROKE: 看起來像 OpenGL 的 line strip, 有連接的線段的集合 (segment list)
        - RED_DISPLAY_DRAW_TEXT: render 文字, 跟 glyph(字型有關)

- QXL protocol 相關 (spice-protocol/spice/qxl_dev.h)

    - QXL CMD

        - QXL_CMD_NOP
        - QXL_CMD_DRAW
        - QXL_CMD_UPDATE
        - QXL_CMD_CURSOR
        - QXL_CMD_MESSAGE
        - QXL_CMD_SURFACE

    - QXL DRAW (QXLDrawable, QXLCompatDrawable)

        - 除了列出來的 2 個以外, 都跟 spice rendering command (ch5.11) 一樣.
        - QXL_DRAW_NOP 
        - QXL_DRAW_COMPOSITE

    - QXL OP

- RedWorker

    - 處理 Display 跟 Cursor channel 的 thread, 其餘 channel 都由 spice-server 主 thread 處理.
    - members

        - DisplayChannel, CursorChannel 
        - QXLInstance
        - RedDispatcher

        - RedSurface surfaces[NUM_SURFACES]
        - uint32_t n_surfaces
        - SpiceImageSurfaces image_surfaces

        - Ring current_list
            - uint32_t current_size;
            - uint32_t drawable_count;
            - uint32_t red_drawable_count;
            - uint32_t glz_drawable_count;
            - uint32_t transparent_count;

            - uint32_t shadows_count;
            - uint32_t containers_count;
            - uint32_t stream_count;
     
        - _Drawable drawables[NUM_DRAWABLES];
        - _Drawable *free_drawables;

        - int32_t streaming_video;
        - Stream streams_buf[NUM_STREAMS];
        - Stream *free_streams;
        - Ring streams;
        - ItemTrace items_trace[NUM_TRACE_ITEMS];
        - uint32_t next_item_trace;
        - uint64_t streams_size_total;
