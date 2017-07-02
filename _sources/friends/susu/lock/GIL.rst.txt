Global Interpreter Lock
-----------------------

- Understanding the Python GIL (PyCon 2010): http://www.dabeaz.com/python/UnderstandingGIL.pdf

  - Part I: Threads and the GIL

    - CPython thread are real system threads (POSIX and Windows)
    - release GIL 
    
      a. on IO operation 
      b. executing every 100 ticks (doing periodic check every 100 ticks: release + reacquire GIL, sys.setcheckinterval())
  
         - tick is related to Python bytecode instead of timing.
  
  - Part II: The GIL and Thread Switching Deconstructed

    - CPython Locks: only one lock type ``pthread_lock`` implementation in C, used to build all other thread synchronization primitives
  
      - GIL is instance of this lock

    - ``pthread_lock``
      
      - https://github.com/python/cpython/blob/master/Python/thread_pthread.h#L132
      - binary semaphore from pthread mutex + conditional variable:
      - acquire/release lock implementation technique is like semaphore (slide p.18)
      
        - use conditional variable for acquire/release lock implementation.
        - use mutex to protect atomicity of acquire/release function.
  
      - Another implementation is POSIX Semaphore (``sem_t``)

  - Part III: What Can Go Wrong?

    - Single CPU: thread context after 100 ~ 1000 checks
    - Multiple CPU

      - Multicore Event Handling: response after 100 ~ 1000 checks

    - I/O Handling

      - GIL thrashing

  - Part IV: A Better GIL?

    - Python 3.2 new implementation
    - Consider GIL thrashing
    - Changes: ``static volatile int gil_drop_request`` && ``cv_wait(gotgil)``
    - Effect

      - Single Thread: not release GIL anymore. (``gil_drop_request = 0``)
      - Multi Thread: 
      
        - increase GIL release time. not release GIL every check, but using a TIMEOUT. (``gil_drop_request = 1 if TIMEOUT``)
        - The thread releasing lock doesn't acquire lock this time.

      - performance: On 4-core cpu, 2/4 thread program increase 3.5/7% time.

  - Part V: Die GIL Die!!!

    - increase response time
    - unfair wakeup/starvation
    - Convoy effect
    - A side-effect of an optimization in Python interpreter
    - ...

  - remove GIL?


reference
~~~~~~~~~
- Understanding the Python GIL (PyCon 2010): http://www.dabeaz.com/python/GIL.pdf

  - SWIG's author
  - A Zoomable Interactive Python Thread Visualization: http://www.dabeaz.com/GIL/gilvis/index.html
  - Inside the "Inside the Python GIL" Presentation: http://dabeaz.blogspot.tw/2009/08/inside-inside-python-gil-presentation.html
  - An Inside Look at the GIL Removal Patch of Lore: http://dabeaz.blogspot.tw/2011/08/inside-look-at-gil-removal-patch-of.html

- Python threads: Dive into GIL! (PyCon 2011): https://in.pycon.org/2011/static/files/talks/41/Python-threads_v1.0.pdf
- Larry Hastings - Removing Python's GIL: The Gilectomy - PyCon 2016: https://www.youtube.com/watch?v=P3AyI_u66Bw
- PyPy-stm

  - http://doc.pypy.org/en/latest/stm.html#implementation
  - pypy repo: ``pypy/doc/stm.rst``, https://github.com/tycho/pypy/blob/master/pypy/doc/stm.rst

- https://wiki.python.org/moin/GlobalInterpreterLock

Misc
----
- Signal Handler in Python

  - CPython Signal Handler (written in C) set flags which tell Python VM to execute Python Signal Handler
  - Synchronized Error(SIG_FPE, SIG_SEGV): ``faulthandler`` module in Python 3.3

    - faulthandler: https://github.com/python/cpython/blob/d26b850ba3f8665ca7d4cdc71e0d450932e42805/Modules/faulthandler.c#L307

  - https://docs.python.org/3/library/signal.html
  - Python VM run signal handler at periodic check, only main Python thread run signal handler 
  
    - (can't use signal for inter-thread communication)

  - http://thisismiller.github.io/blog/CPython-Signal-Handling/

- CPython resource

  - CPython internals: A ten-hour codewalk through the Python interpreter source code: http://pgbovine.net/cpython-internals.htm
  - Python Developer’s Guide: https://docs.python.org/devguide/index.html
