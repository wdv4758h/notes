- thread safety and reetrancy

- Problems: operation on thread-shared memory (e.g. global and static variable in C)

  - atomic operation on variables (e.g. atomic incr & decr on reference counting)
  - lock between operations on variables
  - using thread-local memory instead

    - changed to function parameters
    - changed to thread-local storage
