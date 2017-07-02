http://linoxide.com/linux-command/linux-strace-command-examples/

- child process
    
    - -f
    - -ff (log stored in <ofile>.<pid>, if using -o <ofile>)

- verbose

    - -v
    - -e verbose=all
    - -s strsize

- filter

    - -e open (only system call open)
    - -e open, execve (open or execve)
    - -e process (process related)
    - more to see man strace & search -e
