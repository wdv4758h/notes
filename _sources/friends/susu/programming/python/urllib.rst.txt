- urllib.request.urlopen()::

    #!/usr/bin/env python3
    """ get the google homepage. """
    from urllib.request import urlopen

    response = urlopen('http://www.google.com')

    print(response.code)        # 200
    print(response.msg)         # OK
    print(response.headers)     # (the HTTP headers)
    print(response.read())      # (the HTTP content)

- urllib.request.urlopen(url, data=None, [timeout, ]*, cafile=None, capath=None, cadefault=False, context=None)

  - url: string or Request object
  - Request object:

    - url
    - method: http method
    - header: http header
    - data: http request data, used in POST

- urllib.parse.urlencode()
- urllib.parse.quote()::

    #!/usr/bin/env python3
    """ 取得 wiki "銀河系" 頁面 """
    from urllib.request import urlopen
    from urllib.parse import quote

    url = 'http://zh.wikipedia.org/wiki/'
    keyword = '銀河系'

    # urlopen(url + keyword)
    # This will raise UnicodeEncodeError.
    # Because '銀河系' is not valid ascii codes.

    keyword_quote = quote(keyword)              # %E9%8A%80%E6%B2%B3%E7%B3%BB
    response = urlopen(url + keyword_quote)     # success

    open('result.html', 'w').write(response.read())

    
