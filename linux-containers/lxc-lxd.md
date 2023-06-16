
## LXD vs LXC

LXD is a container manager, it runs Linux Containers - LXC.

LXC utilizes kernel's cgroups and namespaces.

## LXC vs Docker containder

LXCs are more similar to VM unlike docker containters.

## Installation and initialization

```bash
$ snap info lxd

$ sudo snap install lxd --channel=latest/stable
```
Before you can create a LXD instance, you must configure and initialize LXD.

ZFS storage driver
------------------
ZFS is major overkill.

BTRFS
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

