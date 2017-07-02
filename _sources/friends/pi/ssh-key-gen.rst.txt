===========
SSH key gen
===========

- 在自己的機器上產生 ssh-key pair ::

    ssh-keygen -t rsa

- 在需要不打密碼登入的主機上 ::

    cd
    scp username@host:~/.ssh/id_rsa.pub .
    cat id_rsa.pub >> .ssh/authorized_keys
