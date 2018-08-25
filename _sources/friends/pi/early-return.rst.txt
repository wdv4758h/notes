===============================================================================
Early return
===============================================================================
Early return 一直是個很有討論空間的議題。

究竟是提早 return 比較好，還是集中一個點 return 比較好，得從很多面向討論。

  It depends.
                    -- Anonymous


可讀性
-------------------------------------------------------------------------------
引用自 ``Code Complete``:

  17.1 return

  Minimize the number of returns in each routine. It's harder to understand a routine if, reading it at the bottom, you're unaware of the possibility that it returned somewhere above.

  Use a return when it enhances readability. In certain routines, once you know the answer, you want to return it to the calling routine immediately. If the routine is defined in such a way that it doesn't require any cleanup, not returning immediately means that you have to write more code.

這段文字提到了兩個大原則，一個是「儘可能減少 return 的數量」，
另一個是「如果立刻 return 可以增加可讀性，那就這麼做」。

它鼓勵集中 return，但同時要 programmer 自己注意：凡事都有例外。

以下是一個集中 return 和立即 return 的比較：

+-------------------------------------+-----------------------------+
| ::                                  | ::                          |
|                                     |                             |
|   int some_function () {            |   int some_function () {    |
|       int ret = OK;                 |       if (error A) {        |
|       if (not error A) {            |           handle error A    |
|           if (not error B) {        |           return ERROR_A;   |
|               if (not error C) {    |       }                     |
|                   // do something   |       if (error B) {        |
|                   ret = OK;         |           handle error B    |
|               } else {              |           return ERROR_B;   |
|                   handle error C    |       }                     |
|                   ret = ERROR_C;    |       if (error C) {        |
|               }                     |           handle error C    |
|           } else {                  |           return ERROR_C;   |
|               handle error B        |       }                     |
|               ret = ERROR_B;        |       // do something       |
|           }                         |       return OK;            |
|       } else {                      |   }                         |
|           handle error A            |                             |
|           ret = ERROR_A;            |                             |
|       }                             |                             |
|       return ret                    |                             |
|   }                                 |                             |
+-------------------------------------+-----------------------------+

上面的 early return 的例子有時被稱為「guard clause」。

* 贊成集中 return 的觀點（或是不贊成 early return 的觀點）

  - Return 前若需要做 clean up（例如釋放記憶體），集中起來是最不容易產生問題的
  - 為了讓 branch prediction 順利，if 判斷式的內容應該要放「比較常發生」的條件
  - Early return 的多個 ``return`` 可能會有不同深度的縮排，這點有時令人混淆 ::

      if (a) {
          return x;
      }
      return y;

    + 上面這段 code 的兩個 ``return`` 應該是同等意義，但卻有不同的縮排

  - 如果集中 return 讓你覺得函式變複雜，你的函式應該要切小一點

* 贊成 early return 的觀點

  - 不要讓 if 的 scope 超過一個螢幕的高度
  - 若把所有 return 都集中到最後，難保在中間不會誤改到 return 值
  - 如果多個 return 讓你覺得函式變複雜，你的函式應該要切小一點

--------

有一個觀點需要獨立出來討論：

  Single Entry, Single Exit
                            -- Structured Programming

有些觀點會以「Single Exit」來鼓勵「集中 return」，但這是 *錯誤的* 解釋。

那本書寫成的年代是個大部份程式都用組合語言、FORTRAN、COBOL 寫成的年代。
而這些語言都允許「在任意點進入函式」以及「return 到任意的地方」。

以 C 的語法表達這兩件事： ::

  double S (x, y, FAIL) {
      double R = sqrt((x * x) + (y * y));
      ENTER S2(R)
      if (R == 0) {
        return_to FAIL;
      }
      double ret = (R / 2) * (R / 2) * PI;
      return ret;
  }

這個函式可以用以下方式呼叫：

* ``S(3, 4)``
* ``S(5)`` ，如果 ``R`` 的值已知
* ``S(a, b, FAIL)`` ，如果 ``a`` 和 ``b`` 的值有問題，就跳到 ``FAIL`` 去

「Single Entry」指的是「不要讓你的函式有多個進入點」。

「Single Exit」指的是「讓你的函式只 return 到 caller 那裡去」。

現在的語言大多已經不支援這種寫法，所以「Single Entry, Single Exit」實質上已經是假議題。


可除錯性
-------------------------------------------------------------------------------
有時候我們需要追蹤一個函式（以 ``foo`` 為例）的回傳值，此時有兩個方向：

* 在 caller 端追蹤 ::

    int val = foo();
    log.message(val);

* 在 callee 端追蹤 ::

    int foo () {
        ...
        log.message(val);
        return val;
    }

在 caller 端追蹤的話，callee 內的結構不太影響這件事。
但在 ``foo()`` 被包在一串 expression 裡面的時候，這種方式就不太方便。

在 callee 端追蹤的話，如果這個 function 有很多個 return，
這件事就會變得很麻煩，只要有 return 前漏加了 log message，那個點就可能沒被追蹤到。


效能
-------------------------------------------------------------------------------
對高階語言來說這個問題沒什麼影響，對比較現代的 compiler 來說也都不是問題。

* 贊成集中 return 的觀點（或是不贊成 early return 的觀點）

  - 函式 return 時要把一些 register 設回原本的值；return 越多，這些指令也越多，編出來的 binary 越大

* 贊成 early return 的觀點

  - 巢狀的 if-else 會產生比較深的 scope，所以 *單就這點* 來說，early return 比較好。


Java - finally
-------------------------------------------------------------------------------
Java 的 ``finally`` 就算在 ``return`` 之後也一定會被執行。

這表示有些狀況下不需要為了 clean up 而把 return 集中。


資料來源
-------------------------------------------------------------------------------
* http://stackoverflow.com/questions/355670/is-returning-early-from-a-function-more-elegant-than-an-if-statement
* http://stackoverflow.com/questions/268132/invert-if-statement-to-reduce-nesting
* http://softwareengineering.stackexchange.com/questions/118703/where-did-the-notion-of-one-return-only-come-from
