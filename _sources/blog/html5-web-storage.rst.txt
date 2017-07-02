:title: HTML5 - Web Storage
:slug: html5-web-storage
:date: 2015-03-05 16:59
:modified: 2015-03-05 16:59
:category: HTML5
:tags: Web Storage, HTML5, Javascript
:author: wdv4758h
:summary:

.. contents::

**以下是放置很久的紀錄，最近整理清出來 (ry**


Web Storage 是一種可讓網頁將資料儲存於 local 端的技術，純粹運作於 client side，其作用如同 cookie，但空間更大。
它原本是 HTML5 規格的一部份，後來單獨劃為一個規格。

Web Storage 主要分成兩種 :

* local storage (類似 persistent cookies)
* session storage (類似 session cookies)

Web Storage V.S. Cookies
========================================

不同處
------------------------------

Storage size
~~~~~~~~~~~~~~~~~~~~

Web storage 可存的 size 遠大於 cookies

Client-side interface
~~~~~~~~~~~~~~~~~~~~~

Cookies 在 server 和 client 端都可以 access，但 Web Storage 只在 client 端

Web Storage 的資料不會在每次 HTTP request 的時候都傳送過去，web server 也不能直接寫入 Web Storage (但這些都可以由 client-side scripts 達到)

Local and session storage
~~~~~~~~~~~~~~~~~~~~~~~~~

local storage 和 session storage 的差別在於 scope 和 lifetime

local storage 是用 `來源 (Same-origin policy) <https://en.wikipedia.org/wiki/Same-origin_policy>`_ 分的 (size 也是用這個方式分開來算的)，在 browser 關掉之後仍會持續存在

session storage 是 per-page-per-window，lifetime 限制在那個 window，關掉後就沒了

Session storage is intended to allow separate instances of the same web application to run in different windows without interfering with each other, a use case that's not well supported by cookies


.. table::
    :class: table table-bordered

    +----------+-------------------------+---------------------------+
    | 性質     | local storage           | session storage           |
    +==========+=========================+===========================+
    | lifetime | browser 關掉仍會存在    | windows/分頁 關掉後就沒了 |
    +----------+-------------------------+---------------------------+
    | scop     | 可跨分頁 (用 origin 分) | 不可跨分頁                |
    +----------+-------------------------+---------------------------+

Interface and data model
~~~~~~~~~~~~~~~~~~~~~~~~

Web storage 提供比 cookies 更好的 programmatic interface，使用了 associative array data model (keys 和 values 都是 strings)

Web Storage
========================================

Usage
------------------------------

支援 Web Storage 的 browsers 會有 `sessionStorage` 和 `localStorage` 這兩個 global variables，可以使用 Javascript 來操作

sessionStorage
~~~~~~~~~~~~~~~~~~~~

.. code-block:: javascript

    // Store value on browser for duration of the session
    sessionStorage.setItem('key', 'value');

    // Retrieve value (gets deleted when browser is closed and re-opened)
    alert(sessionStorage.getItem('key'));

localStorage
~~~~~~~~~~~~~~~~~~~~

.. code-block:: javascript

    // Store value on the browser beyond the duration of the session
    localStorage.setItem('key', 'value');

    // Retrieve value (persists even after closing and re-opening the browser)
    alert(localStorage.getItem('key'));

Accessing data for the currently browsed domain
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

以下是取得目前 domain 的所有在 local storage 裡的 data 的範例 code

.. code-block:: javascript

    var output = "LOCALSTORAGE DATA:\n------------------------------------\n";
    if (window.localStorage) {
        if (localStorage.length) {
           for (var i = 0; i < localStorage.length; i++) {
               output += localStorage.key(i) + ': ' + localStorage.getItem(localStorage.key(i)) + '\n';
           }
        } else {
           output += 'There is no data stored for this domain.';
        }
    } else {
        output += 'Your browser does not support local storage.'
    }
    console.log(output);

Data types
~~~~~~~~~~~~~~~~~~~~

只有 strings 可以透過 Storage API 儲存進去，在多數的 browser 裡，如果要嘗試存入非 string 的 data type，會自動轉為 string

.. code-block:: javascript

    // Store an object instead of a string
    localStorage.setItem('key', {name: 'value'});
    alert(typeof localStorage.getItem('key')); // string

    // Store an integer instead of a string
    localStorage.setItem('key', 1);
    alert(typeof localStorage.getItem('key')); // string

    // Store an object using JSON
    localStorage.setItem('key', JSON.stringify({name: 'value'}));
    alert(JSON.parse(localStorage.getItem('key')).name); // value

DOM Storage
------------------------------

Web Storage 也常被稱為 DOM storage (這裡指的不是 Document Object Model)

According to the W3C, "The term DOM is used to refer to the API set made available to scripts in Web applications, and does not necessarily imply the existence of an actual Document object..."

Web Storage Management
------------------------------

Local Storage
~~~~~~~~~~~~~~~~~~~~

Firefox 會把所有 web storage objects 存入一個叫作 webappsstore.sqlite 的 sqlite 檔案 (可以用 sqlite3 的 command 去看)，
例如 : ``~/.mozilla/firefox/XXX/webappsstore.sqlite`` ，
column 裡會有 reversed hostname 和 protocol

.. code-block:: sqlite3

    $ sqlite3 webappsstore.sqlite
    sqlite> .tables
    webappsstore2
    sqlite> .schema
    CREATE TABLE webappsstore2 (scope TEXT, key TEXT, value TEXT, secure INTEGER, owner TEXT);
    CREATE UNIQUE INDEX scope_key_index ON webappsstore2(scope, key);
    sqlite> select * from webappsstore2;
    moc.elpmaxe.www.:http:80|stringkey|value|0|
    moc.elpmaxe.www.:http:80|jsonkey|{"key","value"}|0|
    sqlite> .exit

Chrome 把這個 sqlite 的 file 依照 hostname 和 protocol 分開來

Chromium 的路徑 : ``~/.config/chromium/Default/Local Storage/``

Session Storage
~~~~~~~~~~~~~~~~~~~~

因為 session storage 在重開之後就會被清掉，所以不需要存進 database

Firefox 還是會把它寫入 disk 來提供目前 session 的 restore (主要用於 recover from crashes)，
這個檔案是一個 JSON file 在 ``~/.mozilla/firefox/XXX/sessionstore.js`` ，
裡面有個 key 叫 ``storage`` ，它的 value 是 URLs 和 sessionStorage data 的對應

Reference
========================================

* `Web Storage - Wikipedia <https://en.wikipedia.org/wiki/Web_storage>`_
* `HTML5 Web Storage <http://huan-lin.blogspot.com/2012/06/html5-web-storage.html>`_
* `Web Storage 使用經驗 <http://blog.roodo.com/rocksaying/archives/15967715.html>`_
* `The Past, Present & Future of Local Storage for web applications <http://diveintohtml5.info/storage.html>`_
* `HTML5 功能 - 儲存 - HTML5 Rocks <http://www.html5rocks.com/tw/features/storage>`_
* `DOM Storage guide <https://developer.mozilla.org/en/docs/Web/Guide/API/DOM/Storage>`_
* `How is HTML5 WebStorage data physically stored? <https://stackoverflow.com/questions/9669184/how-is-html5-webstorage-data-physically-stored>`_
* `Where does Firefox store javascript/HTML localStorage? <https://stackoverflow.com/questions/7079075/where-does-firefox-store-javascript-html-localstorage>`_
* `Web Storage - W3C <http://www.w3.org/TR/webstorage/>`_
