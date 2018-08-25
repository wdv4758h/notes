MAC OS X 背後的故事: http://www.programmer.com.cn/category/%E7%A8%8B%E5%BA%8F%E6%98%A5%E7%A7%8B/page/2/
- (三)
  - Driverkit to IOkit: 當時外界對 Objective C 不看好, Apple 本身也不太自信, 最後導致 IOkit 回歸用 C++ 實作,
    並且移出 C++ 一些可能導致 multithread kernel unsafe 的功能, 如 exception, multiple inheritance.
  - IOkit 的一些進步
    - userspace driver
    - 考慮電腦發展趨勢, 在電源管理, 即插即用, 動態加載上做的更好.
  - for kernel support c++
    - libkern
    - libsa (algorithms)


Misc
----
- OO OS(object-oriented operating system): 
  在 kernel 的 code 中使用 oop 的技巧, 比如說 file, stream, device driver 可能都繼承同一個 abstract class.
  這些 class 的 method 就用來實作一些 system call.
  常見的 OO-OS: Windows NT, NeXTSTEP, Taligent.
  ref: OO OS wiki

- Fat binary: 
  把不同 arch 的 binary merge 成單一 binary
  http://en.wikipedia.org/wiki/Fat_binary#NeXT.27s.2FApple.27s_multi-architecture_binaries


- Tanenbaum-Torvalds_debate
  - microkernel v.s. monotholic kernel
- OpenSPARC, LEON

