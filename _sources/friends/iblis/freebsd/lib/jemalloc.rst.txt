jemalloc
===============================================================================

- ``malloc``: On FreeBSD, not guarantee to initialize the memory
  (it's implementation depends). Modern OS will initialize it due to
  security reason.

- ``calloc``: *will* initialize the memory to zero.

- ``MALLOC_CONF``: env var. Usually set to ``junk:true`` for debugging and
  discovering the initialization problem.
