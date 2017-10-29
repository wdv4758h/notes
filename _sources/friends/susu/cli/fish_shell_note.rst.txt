Fish Shell Notes
================

- redirection: my google doc
- alias

  - ``function psa; ps -auxww; end``
  - ``function ll; ls -l $argv; end``

- environment variable

  - ``set -x LD_LIBRART_PATH (pwd)``

- inline environment variable

  - by ``env`` program::

      env LD_LIBRART_PATH=(pwd) <CMD>

  - fish::

      begin
          set -lx LD_LIBRART_PATH (pwd)
          <CMD>
      end
