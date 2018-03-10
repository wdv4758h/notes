IPsec
===============================================================================

Encrypt at IP layer.

Transport mode

    ESP: encrypt + (optional) auth for IP payload only, not header

    AH: auth payload + part of header.

Tunnel mode

    Entire IP packet

    把 security 的 header 都加上去後，整個 東西視爲新的 payload，變成
    new outer payload，有 new outer IP。

    ESP: encrypt + (optional) auth for inner packet, include header。

    AH: auth entire inner packet, and part of outer packer header.

Padding
    可以讓別人不知道原本 payload 的長度。


Anti-Replay Attack
    用 Sequence number

    在 association 建立時，sender 先 init seq counter 爲 0。
    只要有 packet 在 SA 上面送的時候，這個 counter 就 +1 然後寫入到
    Sequence number field 。Anti-Replay enable 的時候這個 counter 不會變小或
    overflow，counter 用完的時候，SA 就要 terminate 然後建立新的 SA。

    Receiver 要實作 window with size W (default W = 64)，
    然後只接受 N-W+1 的 seq number ，N 爲目前收到最高的 seq number
