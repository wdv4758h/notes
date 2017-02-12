InterProcess Communication
--------------------------
- communication

  - File
  - pipe
  - FIFO
  - shared memory
  - socket

- locking

  - mutex
  - semaphore
  - conditional variable

file IO
-------
- int open(const char* pathname, int flags, mode_t mode);

  - flags

    - O_RDONLY
    - O_WRONLY | O_CREAT | O_TRUNC

file status and existence
~~~~~~~~~~~~~~~~~~~~~~~~~
- access: check if you can access file

  - access(const char* path, int mode)

    - mode

      - F_OK
      - R_OK, W_OK, X_OK

- stat

pipe
----
* pipe(int pipefd[2]) 

  + create pipe connect with 2 fd
  + return 

    - pipefd[0]: read fd
    - pipefd[1]: write fd

* dup(int oldfd), dup2(int oldfd, int newfd)

  + duplicate file descriptor, make oldfd and newfd interchangable.
  + copy oldfd to newfd.
