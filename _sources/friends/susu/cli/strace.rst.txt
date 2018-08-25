- child process

    trace one process and its all descendant processes
    
    - -f
    - -ff (log stored in <ofile>.<pid>, if using -o <ofile>)

- verbose output

    - -v
    - -e verbose=all
    - -s strsize

- filter

    - -e open (only system call open)
    - -e open, execve (open or execve)
    - -e process (process related)
    - more to see man strace & search -e

ref: http://linoxide.com/linux-command/linux-strace-command-examples/
