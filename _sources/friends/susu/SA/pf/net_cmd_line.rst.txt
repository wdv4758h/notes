- ifconfig

    - ifconfig $interface $ip netmask $netmask

    - ifconfig $interface 0 
        
        - 取消設定的 ip

- route

    - route add default $netmask

- /etc/resolv.conf
    
    - nameserver 8.8.8.8 # 設定 dns server 為 8.8.8.8

- dhclient

    - dhclient $interface # use dhcp
