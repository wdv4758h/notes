========================================
GNU Extension
========================================

想要使用 GNU Extension 的話有兩種簡單的方式，
一個是編譯時使用 ``-std=gnu11`` ，
另一種是在 C 的 source code 的開頭加上 ``#define _GNU_SOURCE`` ，
接著就算使用 ``-std=c11`` ，
加上 "_GNU_SOURCE" 的檔案還是可以使用 GNU Extension (gcc 當然支援，clang 的話則是也有在做支援)

一些專案使用 GNU Extension 的原因：

* 許多非標準的 GNU/Linux extension functions
* 使用被 POSIX 去除的 function (最好不要)
* 一些不能跨平台的 low-level functions (例如 mount、ifconfig)
* 跟 POSIX 行為不一樣的 function (當 GNU 的人不同意 POSIX 定的行為 ...) (儘量不要)

一些 GNU Extension 裡的 function
========================================

* `strfry - randomize a string <http://linux.die.net/man/3/strfry>`_
* `memfrob - frobnicate (encrypt) a memory area <http://linux.die.net/man/3/memfrob>`_
    - only suitable for hiding strings

一些用到 GNU Extension 的 library
========================================

* [Linux] ucontext
