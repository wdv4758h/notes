- redirection: my google doc
- alias

  - ``function psa; ps -auxww; end``
  - ``function ll; ls -l $argv``

- environment variable

  - ``set -x LD_LIBRART_PATH (pwd)``

- inline environment variable::

  begin
      set -lx LD_LIBRART_PATH (pwd)
      <CMD>
  end

