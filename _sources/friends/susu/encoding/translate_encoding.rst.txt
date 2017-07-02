- iconv: translate encoding from input, to output
- convmv: translate encoding on filename

usage::

    iconv -f <from_encoding> -t <to_encoding>    
    convmv -f <from_encoding> -t <to_encoding> [-r] file/directory-path

ex::

    convmv -f cp936 -t utf8 -r XXX/
    convmv -f cp936 -t utf8 -notest -r XXX/


- reference

https://allencch.wordpress.com/2013/04/15/extracting-files-from-zip-which-contains-non-utf8-filename-in-linux/
http://www.robberphex.com/2013/05/141
