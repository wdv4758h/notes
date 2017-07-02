Thread 是一個 class, Runnable 是一個 interface

extends Thread
implements Runnable

Thread 是一個 class，所以每個 Thread 物件是獨立的

Runnable 是一個 interface，所有的 instance 共用同一組 member variable

http://manikandanmv.wordpress.com/2010/12/10/thread-vs-runnable/ 建議用 Runnable

Runnable a = new X(); // X 只要 implements Runnable 就可以代換

