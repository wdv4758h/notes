- Neovim: Porting OS layer to libuv

  - libuv filesystem operation

- libuv

  - I imagine, event loop library

    - non-blocking IO 
    - signal handling
    - child process
    - timer event

  - others

    - file system operation: blocking operation
    
      - but invoke function in thread pool
      - notify watchers registered with the event loop

      - example: uvcat (cat implemented by libuv)
      - http://nikhilm.github.io/uvbook/filesystem.html
