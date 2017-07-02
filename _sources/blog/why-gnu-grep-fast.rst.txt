:title: [留存] Why GNU grep is fast
:slug: why-gnu-grep-is-fast
:date: 2015-03-11 00:41
:modified: 2015-03-11 00:41
:category: Misc
:tags: grep
:author: wdv4758h
:summary:

* `Why GNU grep is fast (2010) <https://lists.freebsd.org/pipermail/freebsd-current/2010-August/019310.html>`_
    - 用 Boyer-Moore (而且做點 loop unroll)
    - 避免在搜尋前複製 input bytes
    - 在 match 之前不找 newlines
    - 看 "Fast String Searching" (by Andrew Hume and Daniel Sunday, in the November 1991 issue of Software Practice & Experience) 裡的 Boyer-Moore implementation tricks
    - Try to set things up (page-aligned buffers, page-sized read chunks, optionally use mmap) so the kernel can ALSO avoid copying the byte

* `Wikipedia - Boyer–Moore string search algorithm <http://en.wikipedia.org/wiki/Boyer%E2%80%93Moore_string_search_algorithm>`_
