## Choose Linux distribution

Ubuntu или Debian, чтобы было всё знакомо. Графика не нужна. Ubuntu Server подойдёт.

## SSH

Нужен ssh сервер для входа в гости через терминал и для vscode's Remote - SSH extension.

```
$ virsh list --all
 Id   Name                             State
-------------------------------------------------
 1    Ubuntu_Server_23_NodeJs_DevEnv   running
 -    archlinux                        shut off
 -    ubuntu18                         shut off
```

How to ssh into guest?
----------------------

Узнать адрес гостя: посмотреть в virt-manager в параметрах гостя или зайти в гости и выполнить команду `ip addr`. В моём случае ip гостя 192.168.122.233.

На госте есть ssh сервер:
```
(host)$ nc 192.168.122.233 22
SSH-2.0-OpenSSH_9.0p1 Ubuntu-1ubuntu8
```

```
(host)$ ssh bublik@192.168.122.233
#input password
```

And without password: add host's public key to guest.

## Shared folder

Make host's folder `/mnt/hdd/programming/nodejs` shared with guest.