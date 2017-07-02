[備份]

clear all environment variable

glibc 2.0 以上有 clearenv() 支援, 根據下面的資料 bionic 應該也有實作.
不過其他平台應該如何實作這個功能?

查了一些現有的實作來參考, 考慮 code 不算長就直接貼在這了.

- glibc(__gnat_clearenv): 

  - https://github.com/gcc-mirror/gcc/blob/master/gcc/ada/env.c

  Sun::

      #elif defined (sun) \
        || (defined (__vxworks) && ! defined (__RTP__)) || defined (__Lynx__) \
        || defined (__PikeOS__)
        /* On Solaris, VxWorks (not RTPs), and Lynx there is no system
           call to unset a variable or to clear the environment so set all
           the entries in the environ table to NULL (see comment in
           __gnat_unsetenv for more explanation). */
        char **env = __gnat_environ ();
        int index = 0;

        while (env[index] != NULL) {
          env[index]=NULL;
          index++;
        }

  FreeBSD::
      
      #elif defined (__MINGW32__) || defined (__FreeBSD__) || defined (__APPLE__) \
         || (defined (__vxworks) && defined (__RTP__)) || defined (__CYGWIN__) \
         || defined (__NetBSD__) || defined (__OpenBSD__) || defined (__rtems__)
        /* On Windows, FreeBSD and MacOS there is no function to clean all the
           environment but there is a "clean" way to unset a variable. So go
           through the environ table and call __gnat_unsetenv on all entries */
        char **env = __gnat_environ ();
        size_t size;

        while (env[0] != NULL) {
          size = 0;
          while (env[0][size] != '=')
            size++;
          /* create a string that contains "name" */
          size++;
          {
            char *expression;
            expression = (char *) xmalloc (size * sizeof (char));
            strncpy (expression, env[0], size);
            expression[size - 1] = 0;
            __gnat_unsetenv (expression);
            free (expression);
          }
        }

- bionic:

  - https://code.google.com/p/android-source-browsing/source/browse/libc/bionic/clearenv.c?repo=platform--bionic&r=fc10b24accd082fb33c8f92ff8b92481c22fe3dc

  ``clearenv()``::

    extern char** environ;

    int clearenv(void)
    {
            char **P = environ;
            int offset;

            for (P = &environ[offset]; *P; ++P)
                    *P = 0;
            return 0;
    }

- cpython (*Error* 實際上是某人用 ctypes access 作為範例)

  - 實作 keys, dumps 出來在各自 unsetenv:
  - http://blog.labix.org/2007/10/17/pythons-osenviron

  ::
    
      def keys(self):
          result = []
          environ = c_char_pp.in_dll(self._process, "environ")
          i = 0
          while environ[i]:
              result.append(environ[i].split("=", 1)[0])
              i += 1
          return result

  - Lib/os.py 反而找不太到 environ.keys() 的實作 (或許有只是我沒看懂)
    
    - https://github.com/python/cpython/blob/0fd3f3616fb2f0068b289552db47e0756a7b578a/Lib/os.py
  
