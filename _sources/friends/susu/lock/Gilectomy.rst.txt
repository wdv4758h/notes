Larry Hastings - Removing Python's GIL: The Gilectomy - PyCon 2016: https://www.youtube.com/watch?v=P3AyI_u66Bw

- needed

  - multithreading
  - cpython internal (e.g. ref counting)

- revisiting

  - 1992

- GIL ramifications

  - simple: easy & no deadlocks
  - low overhead: 很少碰到 lock
  - single-threaded code very fast.
  - i/o bound: ok
  - cpu bound: single-threaded

- world has changed
- free-threading patch (free-threading seems come from MS COM: http://stackoverflow.com/questions/3892259/difference-between-free-threaded-and-thread-safe)

  - python 1.4, 1999
  - 4x ~ 7x slow

- 4 technical considerations

  - ref count
  - globals & statics

    - per thread
    - shared singletons (e.g. module import)

- 3 political considerations

  - don't hurt single-threaded performance
  - don't break c extensions
  - don't make it too complicated

- tracing garbage collection
- software transactional memory
- author's proposal

  - ref count
  
    - atomic incr/decr (30% slow)

  - globals & statics
  - c ext and ...
  - atomicity
  
    - lock api
    - userspace locks: linux futex, windows critical_section, os x pthread_mutex

- two builds

- how to remove GIL

  - atomic incr & decr
  - pick lock
  - lock dictobject, listobject, 10 freelists
  - disable gc, track & untrack
  - murder GIL
  - use tls thread state
  - fix tests

- benchmark

  - 3.5x slower wall time
  - 25x slower cpu time

- why slow

  - synchronization and cache misses (python doesn't have private ...)
  - lock contention

- future

  - reference counting

    - buffered reference counting (把 ref count 的工作專門給一個 thread 來做, 這樣就不需要 synchronization)
    - immortal objects
    - coalesced reference counting (某些建完 reference 之後很快又斷掉 reference 的 ref count 直接忽略不做?)

  - thread private locking
  - garbage collection
    
    - stop-the-world
    - buffered track/untrack

  - auto-lock around c extensions
