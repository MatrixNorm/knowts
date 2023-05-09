
```
$ sudo mkdir /mnt/ramdisk

$ sudo mount -t tmpfs -o size=1G tmpfs /mnt/ramdisk/

$ sudo dd if=/dev/zero of=/mnt/ramdisk/fakedisk.img bs=1M seek=990 count=1

sudo gdisk /mnt/ramdisk/fakedisk.img
# ...

$ sudo losetup -P /dev/loop999 /mnt/ramdisk/fakedisk.img

$ sudo gdisk /dev/loop999

$ sudo mkfs.fat /dev/loop999p1
$ sudo mkfs.ext4 /dev/loop999p2

$ sudo mount /dev/loop999p1 /tmp/efi
```