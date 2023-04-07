```
$ lsblk  /dev/sda
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
sda      8:0    0 238,5G  0 disk 
├─sda1   8:1    0   487M  0 part 
└─sda2   8:2    0  67,1G  0 part /tmp/u18

$ mkdir /tmp/u18
$ sudo mount /dev/sda2 /tmp/u18
$ cd /tmp/u18
```

```
$ sudo du -hs * | sort -hr | head -n 9
28G	home
12G	var
11G	usr
1,7G	opt
1,3G	lib
205M	core
```

Что за файл core?

### /var

```
$ sudo du -hs var/* | sort -hr | head -n 9
6,8G	var/lib
4,1G	var/log
991M	var/cache
8,1M	var/backups
```

```
$ sudo du -hs var/log/* | sort -hr | head -n 9
4,1G	var/log/journal
2,8M	var/log/dist-upgrade
2,3M	var/log/installer
548K	var/log/kern.log.1
```

Журнал файловой системы ext4 занимает много места.

```
# контроль
$ find . -mtime +30 -printf "%TY-%Tm-%Td %p\n" | sort
# удаляем
$ sudo find . -mtime +30 -exec rm {} \;
```

### /usr

```
$ sudo du -hs usr/* | sort -hr | head -n 9
6,3G	usr/lib
3,1G	usr/share
602M	usr/bin
450M	usr/src
```

```
$ sudo du -hs usr/lib/* | sort -hr | head -n 9
1,9G	usr/lib/modules
1,7G	usr/lib/x86_64-linux-gnu
947M	usr/lib/firmware
390M	usr/lib/i386-linux-gnu
302M	usr/lib/libreoffice
92M	usr/lib/python3
```

После чистки:

```
$lsblk -o NAME,SIZE,FSUSED /dev/sda
NAME     SIZE FSUSED
sda    238,5G 
├─sda1   487M 
└─sda2  67,1G  38,2G
```

### Resize partion

```
$ efibootmgr -v
BootCurrent: 0000
Timeout: 1 seconds
BootOrder: 0000,0002,0001
Boot0000* ubuntu	HD(1,GPT,e25c...ab41,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
Boot0001  Hard Drive	BBS(HD,,0x0)...
Boot0002* ubuntu	HD(1,GPT,5307...9f94,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
```

```
$ lsblk -o NAME,PARTUUID | grep -v loop
NAME   PARTUUID
sda    
├─sda1 5307826d-84e7-4497-89df-234a9b109f94
└─sda2 ...
sdb    
├─sdb1 e25ce0d9-4902-4438-8f1e-617ed649ab41
├─sdb2 ...
└─sdb3 ...
...

$ lsblk /dev/sdb1
NAME MAJ:MIN RM  SIZE RO TYPE MOUNTPOINTS
sdb1   8:17   0  487M  0 part /boot/efi
```

```
$ cat /boot/efi/EFI/ubuntu/grub.cfg 
search.fs_uuid 6f6abe60-7961-4279-8b7a-8bdb93c66fe5 root hd1,gpt2 
set prefix=($root)'/boot/grub'
configfile $prefix/grub.cfg

$ lsblk -o NAME,UUID | grep -v loop
NAME   UUID
sda    
├─sda1 1E86-1FD7
└─sda2 b8ce0513-b0be-43cb-ba50-bbefb37072a2
sdb    
├─sdb1 C5AE-10A6
├─sdb2 6f6abe60-7961-4279-8b7a-8bdb93c66fe5
└─sdb3 499cb515-8a83-44c1-8b9f-a720a3ba42fd
```

/boot/grub/grub.cfg:

```
### BEGIN /etc/grub.d/40_custom ###
# This file provides an easy way to add custom menu entries.  Simply type the
# menu entries you want to add after this comment.  Be careful not to change
# the 'exec tail' line above.

menuentry 'Ubuntu 18.04 /dev/sda2' {
        ...
        set root='hd0,gpt2'
        if [ x$feature_platform_search_hint = xy ]; then
          search --no-floppy --fs-uuid --set=root --hint-bios=hd0,gpt2 --hint-efi=hd0,gpt2 --hint-baremetal=ahci0,gpt2  b8ce0513-b0be-43cb-ba50-bbefb37072a2
        else
          search --no-floppy --fs-uuid --set=root b8ce0513-b0be-43cb-ba50-bbefb37072a2
        fi
        linux /boot/vmlinuz-4.19.236-0419236-generic root=UUID=b8ce0513-b0be-43cb-ba50-bbefb37072a2 ro
        initrd /boot/initrd.img-4.19.236-0419236-generic
}

### END /etc/grub.d/40_custom ###
```

Вариант А, как уменьшить раздел sda2:

1. скопировать содержимое раздела в директорию на другом диске
2. удалить раздел
3. создать новый меньшего размера
4. скопировать содержимое назад

Проблема: изменятся UUID файловой системы и PARTUUD раздела.

Варианты решения:

1. исправить конфиг GRUB-а руками (некрасиво)
2. изменить UUID (via tune2fs) и PARTUUD (via gdisk), вернув им старые значения (это лучше)

Вариант Б, как уменьшить раздел sda2: