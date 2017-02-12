源自程式人雜誌上, 有人詢問 C 的指標如何實現: https://www.facebook.com/groups/programmerMagazine/permalink/1067239946626054

回文先紀錄下來, 找一天改成完整介紹 variable 在組語中如何存取值, 能更了解全域/區域/動態分配的記憶體/變數的差別.
同時也介紹在研究上發揮很大作用的反組譯工具.

--

接續自己上面講的，machine code level 中對變數操作都是透過 memory access。

--

例如一行簡單的 c code: ``c = a+b``

在 assembly 的指令可能會像這樣
:: 

    mov (&a), %edx # edx = *(&a) 
    mov (&b), %eax # eax = *(&b)
    add %edx, %eax # eax = eax + edx
    mov %eax, (&c) # *(&c) = eax

其中 eax/edx 為 cpu 的 register，add 這類運算通常只支援對 register 操作 (因為 access memory 太慢，通常只有特定指令能 access)

&a, &b, &c 是示意，a, b, c 的 memory address 如何找到要用一些手法，這邊先不多談(上面的朋友已經有提到)

--

看到 mov 能把 memory address 對應到的記憶體值，取出來存到 register，要怎麼用 mov 實現指標應該有一些想法了。

以下就舉指標的一個範例: ``c = *aptr + b``
::

    mov (&aptr), %eax # eax = *(&aptr)
    mov (%eax), %edx # edx = *(eax), 其實就是 *(aptr)
    mov (&b), %eax # eax = *(&b)
    add %edx, %eax # eax = eax + edx
    mov %eax, (&c) # *(&c) = eax

其實就是把指標的變數值取出(也就是 address)，在做一次 mov 就能拿到/存入指標指向的記憶體。

可以發現 mov 指令能力就跟 c 語言 dereference 運算子(*)相同，在 machine code 取記憶體值，幾乎都是透過 dereference，所以指標的實現感覺很自然。

--

back to real world:

把 c code 編譯完的執行檔拿來反組譯觀察，是個理解 C 如何被 machine code 實現的好方式 

例如剛剛的兩個範例: http://imgur.com/aVkGaLm

補充:

1. ``mov -0x18(%rbp), %eax # eax = *(rbp - 0x18)``

2. 前面忽略的 &a 如何找出，要根據 a 是全域或區域變數有所不同，以上的範例 a, b, cptr, out 是區域變數，記憶體在 stack 上，rbp - 0x18 就是 stack 底端位移 0x18 byte。

   至於 a, b 各自是在 stack 的哪(位移幾 byte)，便是 compiler 的工作了，要負責分配並且在 c to assembly 時把變數換成 address。
   
   全域變數則像王端傑說的，換成 symbol，在 linking/dynamic linking/loading 的時間決定正確的 address。

3. 以上反組譯工具，gcc/clang compile 時加 -g flag，用 objdump -S <exe> 可以看 c source 跟 assembly 的對應
