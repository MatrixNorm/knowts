```
$ lsblk -o name,size,mountpoint,uuid -e7
NAME     SIZE MOUNTPOINT UUID
sda    238,5G            
├─sda1   487M            1E86-1FD7
├─sda2  44,7G            b8ce0513-b0be-43cb-ba50-bbefb37072a2
└─sda3    40G            1cec82ba-f4ae-4d04-80f8-e39367cef4b2 ### lxd's storage pool
sdb    119,2G            
├─sdb1   487M /boot/efi  C5AE-10A6
├─sdb2  23,3G /          6f6abe60-7961-4279-8b7a-8bdb93c66fe5
└─sdb3  95,5G /home      499cb515-8a83-44c1-8b9f-a720a3ba42fd
sdc    931,5G            
├─sdc1 901,7G /mnt/hdd   5df085a3-5112-4b56-beba-1cec9553c3da
└─sdc2  29,8G [SWAP]     2ec5d4b1-31cb-4a63-9dad-2970697e5137
```

Storage pools
-------------

```
$ lxc storage list
+---------+--------+--------------------------------------+-------------+---------+---------+
|  NAME   | DRIVER |                SOURCE                | DESCRIPTION | USED BY |  STATE  |
+---------+--------+--------------------------------------+-------------+---------+---------+
| default | btrfs  | 1cec82ba-f4ae-4d04-80f8-e39367cef4b2 |             | 2       | CREATED |
+---------+--------+--------------------------------------+-------------+---------+---------+
```

`1cec82ba-...-e39367cef4b2` - UUID of filesystem on /dev/sda3

LXD stores its data in storage pools, divided into storage volumes of different content types (like images or instances). You could think of a storage pool as the disk that is used to store data, while storage volumes are different partitions on this disk that are used for specific purposes.

Storage volumes
---------------

```
$ lxc storage volume list default
+-----------+--------+-------------+--------------+---------+
|   TYPE    |  NAME  | DESCRIPTION | CONTENT-TYPE | USED BY |
+-----------+--------+-------------+--------------+---------+
| container | nodejs |             | filesystem   | 1       |
+-----------+--------+-------------+--------------+---------+
```

```
$ sudo du -sh /var/snap/lxd
116M	/var/snap/lxd

## empty. oops..

$ ll /var/snap/lxd/common/lxd/storage-pools/default/
total 8
drwx--x--x 2 root root 4096 июн 15 22:28 ./
drwx--x--x 3 root root 4096 июн 15 22:28 ../
```
## XXX

```
$ ll /var/snap/lxd/common
..
lrwxrwxrwx  1 root root   15 сен 14 10:28 mntns -> /proc/1862/root

$ ls -l /proc/1862
ls: cannot read symbolic link '/proc/1862/root': Permission denied

$ sudo ls -l /proc/1862
...
lrwxrwxrwx  1 root root 0 сен 14 10:43 root -> /
```

`/proc/pid/root`: UNIX and Linux support the idea of a per-process root of the
filesystem, set by the chroot(2) system call. This file is
a symbolic link that points to the process's root directory.

```
# need root
$ sudo -i

(root)$ ll /var/snap/lxd/common/mntns/var/snap/lxd/common/lxd/storage-pools/default/
total 20
drwxr-xr-x 1 root root  214 июн 15 22:28 ./
drwx--x--x 3 root root 4096 июн 15 22:28 ../
drwx--x--x 1 root root    0 июн 15 22:28 buckets/
drwx--x--x 1 root root   12 июн 16 09:36 containers/
drwx--x--x 1 root root    0 июн 15 22:28 containers-snapshots/
drwx--x--x 1 root root    0 июн 15 22:28 custom/
drwx--x--x 1 root root    0 июн 15 22:28 custom-snapshots/
drwx--x--x 1 root root    0 июн 26 09:38 images/
drwx--x--x 1 root root    0 июн 15 22:28 virtual-machines/
drwx--x--x 1 root root    0 июн 15 22:28 virtual-machines-snapshots/
```

У процесса lxd свой вид на корневую файловую систему:

```
$ sudo ls -l /proc/1862/root/var/snap/lxd/common/lxd/storage-pools/default
drwx--x--x 1 root root   0 июн 15 22:28 buckets
drwx--x--x 1 root root  34 сен 12 14:26 containers
...

$ sudo ls -l /var/snap/lxd/common/lxd/storage-pools/default
(или то же самое)
$ sudo ls -l /proc/$$/root/var/snap/lxd/common/lxd/storage-pools/default
# => пусто
```

> LXD operates in a separate mount namespace
https://discuss.linuxcontainers.org/t/btrfs-empty-var-snap-lxd-common-lxd-storage-pools-default/10017

```
$ sudo ls -l /proc/1862/ns
lrwxrwxrwx 1 root root 0 сен 14 10:28 mnt -> 'mnt:[4026532562]'

$ sudo ls -l /proc/$$/ns
lrwxrwxrwx 1 me me 0 сен 14 14:32 mnt -> 'mnt:[4026531841]'
```

```
$ df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/sdb2        23G   17G  4,7G  79% /
/dev/sdb3        94G   11G   78G  13% /home
/dev/sdc1       888G  321G  522G  39% /mnt/hdd

$ sudo nsenter -m -t 1862 bash
[sudo] password for me: 
root@me-box:/# df -h
Filesystem      Size  Used Avail Use% Mounted on
/dev/sdb2        23G   17G  4.7G  79% /var/lib/snapd/hostfs
/dev/sdb3        94G   11G   78G  13% /home
/dev/sdc1       888G  321G  522G  39% /mnt/hdd
/dev/sda3        40G  5.9G   34G  16% /var/snap/lxd/common/lxd/storage-pools/defaul
```