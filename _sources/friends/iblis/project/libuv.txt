libuv
===============================================================================

Ref: https://nikhilm.github.io/uvbook/index.html

- Async, event-driven style of programming.

- event loop: ``uv_run()``

- 解 I/O blocking 慢的問題之解法: event-loop approach
    - ``read``, ``write`` 等，遇到 I/O 就開個 thread (or thread pool)

    - ``libuv`` 用 async, non-blocking ，用現代 OS 提供的 event subsystem:

        - Async: 「我對 X file 有興趣」 與 「拿到 X 的資料要做的處理」 是
          兩件事。

        - Non-blocking: 沒人規定我對 X file 的處理現在就要做。 free to do other
          task.
