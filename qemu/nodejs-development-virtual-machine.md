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
