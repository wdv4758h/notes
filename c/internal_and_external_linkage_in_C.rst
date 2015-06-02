(copy from https://github.com/u1240976/mess_note/blob/master/talk/internal_and_external_linkage_in_C.rst)

Internal and External Linkage in C
==================================

副標題: extern/static/inline variable/function

compiling, linking and forward declaration
------------------------------------------
C 在將 source code 轉化為 executable 時, 至少可分為 compile 跟 link 兩個階段.

1. 在 compile 階段把單獨的 C source code translate 成 cpu instructions 組成的 object code.
2. 在 link 階段把所有需要用到的 object code 連結組成一個執行檔 (除了 dynamic linking 以外)

由於 source code 轉換的最重要階段 compiling 時, compiler 無法看到這個 C source file 依賴的其他 C source file 跟外部 library (source code and object code).

所以 C 語言需要在每個 C source file 中, 標註該檔案中每個會用到的變數與函式的型別(type), 包含外部變數及函式. 這樣 compiler 才能在 compiling 階段進行 type checking.

換句話說, 對於每個 C source file 來看, 如果要使用任何變數跟函式, 都需要使用處的前面有完整的定義(definition), 或者有僅包含型別(type)的宣告(declaration).

也正是因為如此, C 語言甚至要使用 header file 跟額外的 preprocessor, 來幫助使用外部的 C source code 跟 library.

補充, 常見疑惑:

1. 所有的 library 本質上都跟 object code 一樣由 cpu instructions 組成, 包含 static library 跟 dynamic library.
   除了 dynamic library 的 cpu instructions 要強制符合 relocable(position independent code) 的條件.
   可參考: `Tsung's Blog - Linux 的 .a / .so / .la 函式庫的差異 <http://blog.longwin.com.tw/2013/03/linux-a-so-la-library-diff-2013/>`_
2. header file 不會被單獨 compile, header file 只會被 ``#include`` 貼入到其他 C source code 裡, 跟 C source code 一起被 compile 成 object code.

extern variable
---------------
(名詞解釋: 這邊的外部檔案指的是除了自己以外其他的 C source codes, libraries)

當需要使用外部檔案的變數時, 必須在使用前宣告該變數為 ``extern`` 並且寫上該變數的型別(type).

example

.. code:: c

    /* foo.c */
    int a = 10;

    /* main.c */
    extern int a;

    void print_a(void){
        printf("a = %d\n", &a);
    }

    int main(){
        print_a(); // a = 10
        a++;
        print_a(); // a = 11
        a = 100;
        print_a(); // a = 100
    }

比如說在上面的範例, ``main.c`` 中的 ``extern int a`` 便是引用 ``foo.c`` 中的全域變數 ``int a``.

- notice: ``extern`` 只能引用全域變數.

restriction
~~~~~~~~~~~
因為是引用已經定義好的變數, 對宣告方式有很嚴格的限制.

1. 型別需跟引用的變數相同, 不然為 undefined behavior. 以上面範例來說, ``extern double a`` 很顯然是錯的.
2. 不可給初始值(initialized value). 如 ``extern int a = 100`` 很顯然是錯的.

extern usage in header file
~~~~~~~~~~~~~~~~~~~~~~~~~~~
一般來說, 我們會用 ``extern`` 去引用別的 library 的全域變數.

通常 library 會把打算讓你引用的變數, 寫到 header file 裡, 讓所有要用的檔案 ``include`` 就能使用了.

以上面的 example 為例的話會直接建立一個 ``foo.h`` 給其他檔案如 ``main.c`` 來使用.

.. code:: c

    /* foo.h */
    extern int a;

    /* foo.c */
    int a = 10;

    /* main.c */
    #include "foo.h"

    void print_a(void){
        printf("a = %d\n", &a);
    }

    int main(){
        print_a(); // a = 10
        a++;
        print_a(); // a = 11
        a = 100;
        print_a(); // a = 100
    }

而事實上, 會出現在 header file 裡的全域變數基本上只會有 extern variable.

如果一般非 extern/static 的變數出現在 header file 裡, 並且在全域作 ``#include``, 便代表你在每個 ``#include`` 該 header file 的檔案都宣告同名的全域變數, 很顯然有重名問題. 這種作法對 header file 的設計不 make sense.

extern variable example in library
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- ``stdin, stdout, stderr``
- old implementation of ``errno`` (without considering multithreading)

.. code:: c

    // /usr/bin/stdio.h
    /* Standard streams.  */
    extern struct _IO_FILE *stdin;		/* Standard input stream.  */
    extern struct _IO_FILE *stdout;		/* Standard output stream.  */
    extern struct _IO_FILE *stderr;		/* Standard error output stream.  */
    /* C89/C99 say they're macros.  Make them happy.  */
    #define stdin stdin
    #define stdout stdout
    #define stderr stderr

    // /usr/bin/errno.h
    #ifndef errno
    extern int errno;
    #endif

extern variable in function
~~~~~~~~~~~~~~~~~~~~~~~~~~~
如果在函式中使用 extern 引用變數, scope 會跟區域變數一樣只在函式的範圍內.

.. code:: c

    // main.c
    int foo(){
        extern int a;
        ...
    }

    int main(){
        a = 30; // Error!!
    }


static variable
---------------
在 C 語言裡, static 主要有兩個效果

1. 對函式內的變數用 static 修飾: lifetime 擴展為整個程式的執行期間, 與全域變數的 lifetime 相同, 整個程式期間只存在一個本體, 不像區域變數每個函式有一個本體.
2. 對全域變數用 static 修飾: 變數不可被外部引用(連接: link), 也不汙染其他檔案的 namespace(symbol table in C). 也就是內部連結(internal linkage)的效果.

接下來一一解釋兩個效果.

static: internal linkage
~~~~~~~~~~~~~~~~~~~~~~~~
前面說過, 我們可以用宣告 extern variable 的手法, 使用外部 library 的變數.

那如果 library 想要造一個內部的全域變數, 不給外部檔案使用, 就可以宣告 ``static`` 讓變數無法被外部檔案看到, 無法被連接(link).

static variable in function
~~~~~~~~~~~~~~~~~~~~~~~~~~~
- static variable in function, 使用效果是可以做出有狀態 (stateful) 的 function.

  - example: strtok (http://www.cplusplus.com/reference/cstring/strtok)
  - 延伸思考: static variable in function 對 multithreading 的影響.

extern and static function
--------------------------
當需要使用外部檔案的函式時, 需宣告該函式的 type, 通常稱為 function prototype.

跟變數不同的是, function prototype 可加可不加 ``extern``.

而將 function prototype 也放在 header file 的原因跟 extern variable 一樣.

static function 的效果跟 static 的全域變數一樣, 讓函式不可被外部引用.

extern and static function example
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
- simple example

    - fabonacci library, 提供 fabonacci 函式使用.
    - fabonacci library 中需使用內部函式 add 的功能.

.. code:: c

    /* fabonacci.h */
    int fabonacci(int n);
    // extern int fabonacci(int n); // this is still ok.

    /* fabonacci.c */
    static int add(int a, int b);

    int fabonacci(int n){
        if(n == 0)
            return 0;
        return add(fabonacci(n-1) + fabonacci(n-2));
    }

    static int add(int a, int b){
        return a+b;
    }

    /* main.c */
    #include "fabonacci.h"

    int main(){
        printf("f(10) = %d\n", fabonacci(10));
        return 0;
    }

- more complex example

    - `3rd party library - argparse <https://github.com/Cofyc/argparse>`_
    - 提供設定 command line option 的函式跟結構(struct).
    - 內部函式 ``prefix_cmp``, ``prefix_skip``. 檢查是否為 prefix string.

.. code:: c

    // argparse.c
    static const char *
    prefix_skip(const char *str, const char *prefix)
    {
        size_t len = strlen(prefix);
        return strncmp(str, prefix, len) ? NULL : str + len;
    }

    static int
    prefix_cmp(const char *str, const char *prefix)
    {
        for (;; str++, prefix++)
            if (!*prefix)
                return 0;
            else if (*str != *prefix)
                return (unsigned char)*prefix - (unsigned char)*str;
    }

    // two functions are not in argparse.h

conflict of inline function and external linkage
------------------------------------------------
在講解前, 要先說明一下 function call 在執行檔的樣貌.

以下的 code 是一個簡單的函式 ``add``, 在 x86_64 組語下的實作.

(C code 是註解, 僅表示哪些 C code 被轉成該組語, 為了方便辨認, 在 C code 前加上 ``[C]`` 方便辨識.

.. code:: asm

    00000000004005d1 <add>:
 [C]int add(int a, int b){
      4005d1:       55                      push   %rbp
      4005d2:       48 89 e5                mov    %rsp,%rbp
      4005d5:       89 7d fc                mov    %edi,-0x4(%rbp)
      4005d8:       89 75 f8                mov    %esi,-0x8(%rbp)
 [C]    return a+b;
      4005db:       8b 55 fc                mov    -0x4(%rbp),%edx
      4005de:       8b 45 f8                mov    -0x8(%rbp),%eax
      4005e1:       01 d0                   add    %edx,%eax
 [C]}
      4005e3:       5d                      pop    %rbp
      4005e4:       c3                      retq

每個組語的 instruction 分成三部份.

1. 該 instruction 存在的 memory address. 如 ``4005d1:``
2. instruction 的 binary encoded form, machine code 真實存在執行檔的狀態. 如 ``55``
3. instruction 的 binary encoded form 被反組譯回來的組語. 如 ``push   %rbp``

函式的本體, 就是函式實作轉換成的 instructions, 結尾為 return 相關的 instruction.

而函式的名稱也只是這串 instructions 的 start address, 可以用 function call 相關的 instruction 跳到這個 start address.

如下 code 即為 ``x = add(a, b);`` 這行 C source code 轉換成組語的實作, 可以看到透過 ``callq`` instruction 跳到 add 函式(4005d1)

.. code:: asm

 [C]       x = add(a, b);
      40059f:       8b 55 f4                mov    -0xc(%rbp),%edx
      4005a2:       8b 45 f8                mov    -0x8(%rbp),%eax
      4005a5:       89 d6                   mov    %edx,%esi
      4005a7:       89 c7                   mov    %eax,%edi
      4005a9:       b8 00 00 00 00          mov    $0x0,%eax
      4005ae:       e8 1e 00 00 00          callq  4005d1 <add>
      4005b3:       89 45 fc                mov    %eax,-0x4(%rbp)

(p.s. ``call 400561 => e8 1e 00 00 00``, e8 為 call instruction 的 opcode, 0x1e = 0x4005d1 - 0x4005b3)

但 inline function 的效果, 是直接把函式的內容插入到 function call 的地方, 省略 call, return, 跟參數傳遞帶來效能增進.

也因此, 函式如果 inline 化之後, 就不需要存在本體了, 可以節省空間.(其實沒差多少, 可以 inline 的函式通常不大, 幾乎小於 10 行)

不過函式 inline 化這件事基本上是在 compilation 階段完成的, 只能在檔案內 call 這個函式的地方 inline 化.

如果外部檔案要 function call, 基本上只能正常 call and return, 需要函式的本體, 跟 inline 化的其中一個好處互相衝突.

因此在這個衝突底下, C 語言讓 programmer 使用 static 跟 extern 關鍵字去做設定要不要保留.

[C99] static inline v.s. extern inline
--------------------------------------
static inline 代表 internal linkage, 不給外部檔案使用, 很顯然的也就不需要保留本體.

反之, extern inline 代表 external linkage, 要給外部檔案使用, 必需要保留本體.

不過 ``inline`` 關鍵字是在 C99 在進入 C 標準的, 所以這是 C99 以後的規則, 純 ``inline`` 的效果也留到下一個 section 講.

inline and gnu89 inline
-----------------------
C89(ANSI C) 的年代, 因為還沒有 ``inline``, 所以第一個做出 ``inline`` 功能的就是 gcc.

想當然, ``inline/static inlink/extern inline`` 的效果就是 gnu 他們自訂的, 與現在 C99 規格化後的效果不同.

C99 以前的其他 compiler, 也有可能跟進 gcc 的設計.

整理之後 3 種 inline 在 compiler 相容度分 3 類

1. C89: 不支援 inline.
2. gnu89, 某些跟進 gnu89 的 C99 以前 compiler: 走 gnu89 的設計.
3. after C99, including gnu99: 走 C99 設計.

gnu89 v.s. C99

- gnu89 的 static inline 跟 C99 相同, 不需要保留本體.
- gnu89 的 inline 跟 C99 的 extern inline 相同, 會保留本體.
- gnu89 的 extern inline 跟 C99 的 inline 相同, 不過這個效果很詭異不建議使用.

實際測試
~~~~~~~~
- at C99 (gcc v4.9.2 -std=c99)

  - 開 O2, compiler 沒把 function inline 化
  - 開 O3, compiler 把 function inline 化了, static inline 跟 inline 的本體消失, extern inline 本體有被保留.

總結
----
1. 由於 C 的 compilation 流程限制, 每個檔案必須要在變數跟函式使用前加上前綴的型別宣告.
2. static 可以將變數跟函式的 scope 縮小為檔案內, extern variable 跟 function prototype 可以讓你引用別的檔案裡沒被 static 化的變數跟函式.
3. header file 的變數, 絕大部分情況只會有 extern variable.
4. extern inline 的 extern 被賦與第二種意義, 讓 inline function 可被外部引用. static inline 中的 static 仍為保護函式不可被外部引用.

+--------------------------------------+-----------------------+-------------------------+-------------------------+-------------------------+
| inline functions                     | C99 internal function | C99 external function   | gnu89 internal function | gnu89 external function |
+--------------------------------------+-----------------------+-------------------------+-------------------------+-------------------------+
| declaration in header file (``*.h``) |           X           | inline or extern inline |             X           |         inline          |
+--------------------------------------+-----------------------+-------------------------+-------------------------+-------------------------+
| forward declaration        (``*.c``) |     static inline     | inline or extern inline |       static inline     |         inline          |
+--------------------------------------+-----------------------+-------------------------+-------------------------+-------------------------+
| function definition        (``*.c``) |     static inline     |      extern inline      |       static inline     |         inline          |
+--------------------------------------+-----------------------+-------------------------+-------------------------+-------------------------+

- library 本身

    1. 變數跟函式希望被外部引用: 在 header file 加上 extern variable 或 function prototype
    2. 變數跟函式可被外部引用: 在 C source file 該變數宣告時, 不加上 static.
    3. 變數跟函式不可被外部引用: 在 C source file 該變數宣告時, 加上 static.

- 使用 library 的外部檔案

    1. 對應上面的 1., header file 有的話, include 後即可使用.
    2. 對應上面的 2., 需在本檔案中加上 extern variable 或 function prototype 才可使用. 如果沒有 library 的 source code 則無法使用. 因為無法知道變數跟函式的型態.
    3. 對應上面的 3., 在這種情況下無法使用該變數, 不過可以在這個檔案宣告同名變數使用.

.. code:: c

    /* just comments */
    /*
     * 1. external linkage, var1/func1
     * 2. can be external linked, var2/func2
     * 3. internal linkage, var3/func3
     */

    /* libfoo.h */
    extern int var1;

    void func1(void);

    /* libfoo.c */
    #include "libfoo.h"

    int var1 = 1;
    int var2 = 2;
    static int var3 = 2;

    // function forward declaration if needed.
    void func2(void);
    static void func3(void);

    // function definition
    void func1(void){
        printf("func1\n");
    }
    void func2(void){
        printf("func2\n");
    }
    static void func3(void){
        printf("func3\n");
    }

    /* main.c */
    #include "libfoo.h"

    extern int var2;  // if using 2.
    void func2(void); // if using 2.

    extern int var3;  // error
    extern void func3(void);  // error
    int var3 = 1000;  // but main.c can have independent var3
    void func3(void){ // but main.c can have independent func3
        printf("my func3\n");
    }

    int main(){
        var1 = 10; // 1. external linkage
        func1();   // 1. external linkage
    }

reference
---------
- http://stackoverflow.com/questions/216510/extern-inline/216546#21654
