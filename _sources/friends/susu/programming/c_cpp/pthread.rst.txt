- thread termination

  - ``return *status``
  - ``pthread_exit(status)``
  - terminated by another thread: ``pthread_cancel(pthread_t pid)``

- thread_join

  - detached thread: threads not joined by main thread, which is released just after thread termination.
  - joined thread
  - assign by thread attributes
