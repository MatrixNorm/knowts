### How do I check cgroup v2 is installed on my machine?

```
$ grep cgroup /proc/filesystems 
nodev	cgroup
nodev	cgroup2
```

### How to get the complete and exact list of mounted filesystems in Linux?

The definitive list of mounted filesystems is in `/proc/mounts`. If you have any form of containers on your system, `/proc/mounts` only lists the filesystems that are in your present container. For example, in a chroot, `/proc/mounts` lists only the filesystems whose mount point is within the chroot. 

```
$ findmnt
TARGET          SOURCE   FSTYPE
/sys/fs/cgroup  cgroup2  cgroup2
```