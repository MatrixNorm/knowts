
## LXD vs LXC

LXD is a container manager, it runs Linux Containers - LXC. LXC utilizes kernel's cgroups and namespaces.

## Installation and initialization

```bash
$ snap info lxd

$ sudo snap install lxd --channel=latest/stable
```
Before you can create a LXD instance, you must configure and initialize LXD.

ZFS storage driver
------------------
ZFS is major overkill. Not gonna use it.

BTRFS storage driver
-----
```
$ apt-cache show btrfs-progs
This package contains utilities (mkfs, fsck) used to work with btrfs
 and an utility (btrfs-convert) to make a btrfs filesystem from an ext3
```

`lxd init` - select btrfs and `/dev/sda3` partition (created beforehand)

```
$ lxc storage list
+---------+--------+--------------------------------------+
|  NAME   | DRIVER |                SOURCE                |
+---------+--------+--------------------------------------+
| default | btrfs  | 1cec82ba-f4ae-4d04-80f8-e39367cef4b2 |
+---------+--------+--------------------------------------+

$ sudo blkid /dev/sda3
/dev/sda3: LABEL="default" UUID="1cec82ba-f4ae-4d04-80f8-e39367cef4b2" TYPE="btrfs"
```

cgroups conflict
----------------

```
$ lxc list
+------+-------+------+------+------+-----------+
| NAME | STATE | IPV4 | IPV6 | TYPE | SNAPSHOTS |
+------+-------+------+------+------+-----------+

$ lxc launch ubuntu:22.04 nodejs
Creating nodejs
Starting nodejs                               
Error: Failed to run: /snap/lxd/current/bin/lxd forkstart nodejs /var/snap/lxd/common/lxd/containers /var/snap/lxd/common/lxd/logs/nodejs/lxc.conf: exit status 1
Try `lxc info --show-log local:nodejs` for more info
```

https://discuss.linuxcontainers.org/t/ubuntu-22-04-lxd-fails-to-launch-container-with-mullvad-vpn/14887/5

```
$ cat /proc/self/mountinfo | grep cgroup
33 24 0:28 / /sys/fs/cgroup rw,nosuid,nodev,noexec,relatime shared:9 - cgroup2 cgroup2 rw
2233 33 0:72 / /sys/fs/cgroup/net_cls rw,relatime shared:888 - cgroup none rw,net_cls
```

```
2233 33 0:72 / /sys/fs/cgroup/net_cls rw,relatime shared:888 - cgroup none rw,net_cls
```

That’s the issue. We’ve seen it occasionally but haven’t yet found the root cause for this.
It’s a cgroup1 controller mounted on top of a cgroup2 tree, that’s a very bad idea and causes a bunch of issues. A temporary fix is to run `umount -l /sys/fs/cgroup/net_cls` but that will not survive a reboot.

https://discuss.linuxcontainers.org/t/help-help-help-cgroup2-related-issue-on-ubuntu-jammy-with-mullvad-and-privateinternetaccess-vpn/14705

https://github.com/pia-foss/desktop/issues/50

```
$ grep cgroup /proc/mounts 
cgroup2 /sys/fs/cgroup cgroup2 rw,nosuid,nodev,noexec,relatime 0 0
none /sys/fs/cgroup/net_cls cgroup rw,relatime,net_cls 0 0
```

I had the same issue, and in my case the net_cls V1 cgroup is being mounted by pia-daemon, which is part of the PrivateInternetAccess VPN:

```
[linux_cgroup][daemon/src/linux/linux_cgroup.cpp:23][warning] The directory "/sys/fs/cgroup/net_cls" is not found, but is required by the split tunnel feature. Attempting to create.
[linux_cgroup][daemon/src/linux/linux_cgroup.cpp:30][info] Successfully created "/sys/fs/cgroup/net_cls"
```

I’ll disable the "Split tunnel" feature, that I wasn’t actively using anyway, and hopefully this will go away for good.

How to disable "Split tunnel" feature of PIA
--------------------------------------------

### login into container as a non-root user

По-умолчанию логинится в рута

```
$ lxc exec mycontainer bash
root@nodejs:~#
```

В контейнере есть юзер ubuntu

```
root@nodejs:~# cat /etc/passwd
ubuntu:x:1000:1000:Ubuntu:/home/ubuntu:/bin/bash
```

https://discuss.linuxcontainers.org/t/logging-in-a-container-as-a-normal-user/190

```
$ lxc exec mycontainer -- su ubuntu
ubuntu@nodejs:$

# or
$ lxc exec mycontainer -- sudo --user ubuntu --login
```

### ssh into container

```
$ lxc exec nodejs bash
root@nodejs:~# su ubuntu
root@nodejs:~# nano ~/.ssh/authorized_keys
# paster host public key to .ssh/authorized_keys
# of ubuntu user inside container
```

### How do I copy a file/directory from host into a LXD container?

to copy file.txt from host to /home/ubuntu/ directory of the container `cntr`

`lxc file push file.txt cntr/home/ubuntu/file.txt`

to copy a directory from host to container, use -r

`lxc file push -r directory/ cntr/home/ubuntu/`

to copy file from container to host, use pull

`lxc file pull cntr/home/ubuntu/file.txt .`

### rename container

`>lxc move nodejs nodejs-flow`

### container autostart

to disable autostart for existing container: 
* `lxc config set nodejs boot.autostart=false`

how to change the default setting in LXD so that any newly created container does not autostart:
* `lxc profile set default boot.autostart=false`

### Visual Studio Code Remote - SSH


### Get list of exposed ports

