Fish Shell Notes
================

fish shell is non-POSIX compatible shell, so it has some different syntaxs to other shells.

- command substitution: ``(<CMD>)``
- IO redirection:

  - to file: ``>, ^``
  - to pipe: ``|, 2>|``

- alias

  - ``function psa; ps -auxww; end``
  - ``function ll; ls -l $argv; end``

- environment variable

  - ``set -x LD_LIBRART_PATH (pwd)``
  - inline: ``env LD_LIBRART_PATH=(pwd) <CMD>`` (use ``env`` program)


