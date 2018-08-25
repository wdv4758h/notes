- C

  - socket api in IPC.rst
  - [C99] fixed-width integer
  - perror, errno, strerror
  - string.h processing api
  - valist-based format printing

    - Reason: passing variables to printf
    - vprintf
    - snprintf, asprintf

- c string api

  - strchr (first char)
  - strrchr (last char)
  - strpbrk (first char set)
  - strspn (first non-char set, return length)
  - strcspn (first char set, return length)
  - strstr (first substring)

C++ fileIO
----------
binary IO
+++++++++

- member function

    - ``void open(const char* filename[, int mode][, int prot]);``
    - ``ostream& write(void* buffer, streamsize n);``
    - ``istream& read(void* buffer, streamsize n);``

::

    ifstream inFile;
    inFile.open("hello.dat", ios::in | ios::binary );
    ofstream outFile;
    outFile.open ("data2.bin", ios::out | ios::binary);

