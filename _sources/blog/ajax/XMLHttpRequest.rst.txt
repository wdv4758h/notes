:title: XMLHttpRequest
:slug: XMLHttpRequest
:date: 2014-02-11 00:06
:category: Misc
:tags: XMLHttpRequest, ajax
:author: wdv4758h
:summary: XMLHttpRequest

有了 XMLHttpRequest 就讓我們可以利用 Javascript 去做 request

以下直接用一段 Javascript 去說明

.. code-block:: javascript

    var req = new XMLHttpRequest();
    req.onreadystatechange = function(){
        if(req.readyState === 4){
            alert(req.responseText);
        }
    }
    req.open('GET', "test.html", true);
    req.send(null);

首先是建立 XMLHttpRequest 物件，再來撰寫 readyState 改變時所要做的動作 ( **onreadystatechange** )，
open method 去指定要做的 request，再來呼叫 send method 送出

在收到回應後，XMLHttpRequest 物件會設定的一些屬性
=================================================

readyState
------------------------------

- 0 (UNSENT)

    The object has been constructed.

- 1 (OPENED)

    The open() method has been successfully invoked. During this state request headers can be set using setRequestHeader() and the request can be made using the send() method.

- 2 (HEADERS_RECEIVED)

    All redirects (if any) have been followed and all HTTP headers of the final response have been received. Several response members of the object are now available.

- 3 (LOADING)

    The response entity body is being received.

- 4 (DONE)

    The data transfer has been completed or something went wrong during the transfer (e.g. infinite redirects).

因此才在 onreadystatechange 裡做了 readyState 判斷，
on readyState change 顧名思義就是 readyState 有變動時會去 call 這個 method，
所以加上 readyState 的判斷後變成只有處理完後 "readyState 是 4 " 時才做動作

Status
------------------------------

就是 HTTP 的 Status Code

responseText
------------------------------

收到的內容

responseXML
------------------------------

收到的內容 (XML 格式)

Ref
========================================

- `XMLHttpRequest - MDN <https://developer.mozilla.org/en/docs/Web/API/XMLHttpRequest>`_
- `XMLHttpRequest - Wikipedia <https://en.wikipedia.org/wiki/XMLHttpRequest>`_
- `Ajax (programming) <https://en.wikipedia.org/wiki/Ajax_%28programming%29>`_
