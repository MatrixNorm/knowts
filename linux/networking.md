
## List open ports

```
$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
6: eth0@if7: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 00:16:3e:35:37:29 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 10.101.130.224/24 metric 100 brd 10.101.130.255 scope global dynamic eth0

$ sudo nmap -p- 127.0.0.1
Starting Nmap 7.80 ( https://nmap.org ) at 2023-07-07 12:16 UTC
Nmap scan report for localhost (127.0.0.1)
Host is up (0.0000030s latency).
Not shown: 65534 closed ports
PORT   STATE SERVICE
22/tcp open  ssh

$ sudo nmap -p- 10.101.130.224
Starting Nmap 7.80 ( https://nmap.org ) at 2023-07-07 12:17 UTC
Nmap scan report for nodejs.lxd (10.101.130.224)
Host is up (0.0000030s latency).
Not shown: 65534 closed ports
PORT   STATE SERVICE
22/tcp open  ssh
```
