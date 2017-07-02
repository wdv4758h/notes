microkernel

- 1st generation: 1980's MIT Mach, poor performance.
- 2nd generation: 1990's L4 kernel, enhance IPC performance by reducing cache miss (poor spartial locality in Mach IPC).
- 3rd generation: seL4 kernel, high security and reliable system.

- L4 kernel 有多種變種: L4Ka, L4MIPS ... etc
- Qualcomm 的 REX OS + ASMM (based on L4) (RTOS) (http://www.xuebuyuan.com/909719.html)
- QNX kernel: microkernel + RTOS on phone.

- L4 kernel has only 7 system call, 12 kbytes size (http://blog.linux.org.tw/~jserv/archives/2012/01/l4_microkernel.html)
  
  - 3 part

    - address space
    - thread 
    - IPC

  - some detail: http://pdos.csail.mit.edu/6.097/lec/l14.html

http://www.slideshare.net/jserv/microkernel-evolution
https://www.facebook.com/groups/ncku.embedded2015/permalink/769734679839686/
