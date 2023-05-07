
```
$ sudo gdisk /dev/sdd
Command (? for help): p
...
Number  Start (sector)    End (sector)  Size       Code  Name
   1            2048          206847   100.0 MiB   EF00  EFI system partition
   2          206848        60538847   28.8 GiB    8300  Linux filesystem
```

```
$ lsblk
sdd      8:48   1  28,9G  0 disk 
├─sdd1   8:49   1   100M  0 part /tmp/efi
└─sdd2   8:50   1  28,8G  0 part
```

```
sudo qemu-system-x86_64 \
    -cpu host -enable-kvm -smp 2 -m 2G \
    -bios /usr/share/qemu/OVMF.fd \
    -hda /dev/sdd
```


Pres ESC in Qemu --> enter UEFI setup. Remove network boot options.

File `NvVars` is written to sdd1 that is visible from Qemu's EFI shell:

```
Shell>fs0:
FS0:\>ls
05/07/2023 08:34 11,741 NvVars
```

Meanwhile host does not see any files in `/tmp/efi` directory. umount has helped:

```
$ sudo umount /dev/sdd1
$ sudo mount /dev/sdd1 /tmp/efi/
$ ll /tmp/efi/
-rwxr-xr-x  1 root root  12K мая  7 11:34 NvVars
```

