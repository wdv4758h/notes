ECMAScript 6
===============================================================================

.. highlight:: javascript


Destructuring
----------------------------------------------------------------------

Looks like var unpacking in python, but more powerful.
It can handle object.

Ref
    - https://github.com/lukehoban/es6features#destructuring


Fetch API
----------------------------------------------------------------------

::

    fetch('https://path/toapi/url')
        .then(function(res){console.log('aaaaa'); return res})
        .then(function(res){console.log(res)})

Ref
    - https://developer.mozilla.org/en-US/docs/Web/API/Fetch_API
    - https://developer.mozilla.org/en-US/docs/Web/API/GlobalFetch/fetch
