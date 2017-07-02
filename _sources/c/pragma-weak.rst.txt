========================================
pragma weak
========================================

``#pragma weak`` 是 C 和 C++ 語言裡宣告 weak symbol 的方式，
在 C 和 C++ 的規範中並未定義 weak symbol 的使用，
所以只好使用 ``#pragma`` 來支援，
而這就會有不 portable 的問題 (各平台狀況不一樣)。


.. code-block:: c

    #pragma weak symbol_name

    int symbol_name(int x);


weak symbol 為 ELF 在 linking 時的一種標示，
一般的狀況下 symbol 都是 strong 的，
但是可以特別指定某些 symbol 為 weak，
如此一來在 linking 的時候，同樣名字的 strong symbol 可以蓋掉 weak symbol，
不然兩個同名的 strong symbol 一起出現會造成 link-time error。
在 linking 執行檔時，weak symbol 可以沒有 definition，但是 strong symbol 一定要有 definition，
不然會有 undefined symbol 的錯誤。

藉由 weak symbol 的方式，
程式可以提供預設的實作，
並且可以在 link-time 時提供被換掉的可能性 (換成該平台上效能更好的實作)，
或者可以做客制化。

程式的 symbols 可以使用 ``nm`` 這個指令來觀看，
有 definition 的 weak function symbol 會標 "W"，
沒有 definition 的 weak function symbol 會標 "w"，
weak variable symbol 會標 "V" 或 "v"，
範例：

.. code-block:: c

    // hello.c

    #include <stdio.h>

    #pragma weak hello
    #pragma weak hello_var

    int hello_var;

    void hello () {
        printf("Hello World!\n");
    }

    int main () {
        hello();
        return 0;
    }


.. code-block:: sh

    $ gcc hello.c -o hello
    $ nm hello | grep hello
    0000000000400596 W hello
    00000000004019dc V hello_var


Reference
========================================

* `Wikipedia - Weak symbol <https://en.wikipedia.org/wiki/Weak_symbol>`_
* `GCC - Weak Pragmas <https://gcc.gnu.org/onlinedocs/gcc/Weak-Pragmas.html>`_
