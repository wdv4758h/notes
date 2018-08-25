EncFS
-----

- https://wiki.archlinux.org/index.php/EncFS

- install

  - community/encfs

- usage::

  # encrypt directory at ~/.encrypt/.dir1/
  # unencrypt directory at ~/.encrypt/dir/

  # Prepare
  $ mkdir .encrypt/ && cd .encrypt/

  # Create encrypt directory
  # use absolute path
  # choose expert configuration, choose many config
  # choose the password
  $ encfs `pwd`/.dir1/ `pwd`/dir1/
  
  # Unmount directory
  $ fusemount -u `pwd`/dir1/

  # Mount directory
  # keyin your password
  $ encfs `pwd`/.dir1/ `pwd`/dir1/
