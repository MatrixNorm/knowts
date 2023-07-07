

```
$ node --inspect --inspect-brk demo.js 
Debugger listening on ws://127.0.0.1:9229/a5d732ad-2914-4ef3-b0a0-4796d207ae0d
```

```
$ ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
6: eth0@if7: <BROADCAST,MULTICAST,UP,LOWER_UP> mtu 1500 qdisc noqueue state UP group default qlen 1000
    link/ether 00:16:3e:35:37:29 brd ff:ff:ff:ff:ff:ff link-netnsid 0
    inet 10.101.130.224/24 metric 100 brd 10.101.130.255 scope global dynamic eth0

$ sudo nmap -p- 127.0.0.1
Starting Nmap 7.80 ( https://nmap.org ) at 2023-07-07 12:18 UTC
Nmap scan report for localhost (127.0.0.1)
Host is up (0.0000030s latency).
Not shown: 65533 closed ports
PORT     STATE SERVICE
22/tcp   open  ssh
9229/tcp open  unknown
```

Port 9229 is not exposed on 10.101.130.224/24:

```
$ sudo nmap -p- 10.101.130.224
Starting Nmap 7.80 ( https://nmap.org ) at 2023-07-07 12:52 UTC
Nmap scan report for nodejs.lxd (10.101.130.224)
Host is up (0.0000030s latency).
Not shown: 65534 closed ports
PORT   STATE SERVICE
22/tcp open  ssh
```

Now exposed:

```
$ node --inspect=10.101.130.224 --inspect-brk demo.js 
Debugger listening on ws://10.101.130.224:9229/80aa24cd-c1b3-491a-8464-816809b6785a
```

Open `brave://inspect/` and configure address and port `10.101.130.224:9229`.