select
------
::

    int select(int nfds, fd_set *readfds, fd_set *writefds,
               fd_set *exceptfds, struct timeval *timeout);

    void FD_ZERO(fd_set *set);
    void FD_SET(int fd, fd_set *set);
    void FD_CLR(int fd, fd_set *set);
    int  FD_ISSET(int fd, fd_set *set);
