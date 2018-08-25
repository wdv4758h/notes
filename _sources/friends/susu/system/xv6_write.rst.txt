tracing xv6 write system call
-----------------------------
- xv6 source code(pdf): http://pdos.csail.mit.edu/6.828/2014/xv6/xv6-rev8.pdf
- xv6 source code(github): https://github.com/guilleiguaran/xv6

::
    
    # structure, global variable
    ## file.h
    struct file;
    struct inode;
    struct devsw;
    ## file.c
    struct devsw devsw[NDEV];
    
    ## define
    CONSOLE = 1 # file.h:38
    COM1 = 0x3f8 # uart.c:14 
    CRTPORT = 0x3d4 # console.c:126

    # call stack
    void syscall(void) in syscall.c:127
    int sys_write(void) in sysfile.c:79
    int filewrite(struct file *f, char *addr, int n) in file.c:117
    int writei(struct inode *ip, char *src, uint off, uint n) in fs.c:463
      - devsw[CONSOLE].write() => consolewrite()
    int consolewrite(struct inode *ip, char *buf, int n) in console.c:266
    void consputc(int c) in console.c:161
      - void uartputc(int c) in uart.c:52
      - static void cgaputc(int c) in console.c:130 
    
    uartputc => x86 asm: OUT COM1 data
    cgaputc => x86 asm: OUT CRTPORT data
    
    # about OUT instruction: http://x86.renejeschke.de/html/file_module_x86_id_222.html
