User management commands (LinuxMint 16)
---------------------------------------
- useradd [options] $USERNAME
  -D: default
  -m: add home directory
  -g $GROUP: add group to thuis user
  -s $SHELL: default shell
  # -p $PASSWORD: 建議使用 passwd command 

- passwd $USERNAME
  對非本人修改 password 需要 root 權限
    
- userdel $USERNAME


- user
  - username, passwd
  - groups, quota (權限)
  - home directory, base directory (login directory for no home directory user)
  - shell
  - nologin

