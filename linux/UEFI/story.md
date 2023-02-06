# Part 1

At first there had been single disk sda with two partitions:
- /dev/sda1: ESP (EFI partition)
- /dev/sda2: Ubuntu 18.04

Afterward second disk sdb was connected and Ubuntu 22.04 installed on it. During installation from bootable USB stick following partitions were created:
- /dev/sdb1: FAT32 for ESP. 
- /dev/sdb2: ext4, mounted at /
- /dev/sdb3: ext4, mounted at /home

I intended to make separate EFI partitions for Ubuntu 22.04 on sdb1 and leave ESP on sda1 intact. Motivation was to not alter Ubuntu-18's bootloader. But I forgot to mount sdb1 at /boot/efi and installer dumped Ubuntu-22's GRUB on sda1. From the MAN page of efibootmgr:

> An OS installer would call efibootmgr -c. This assumes that /boot/efi is your EFI System Partition, and is mounted at /dev/sda1.

Anyway U-22 was installed and booted normally while U-18 failed to boot even though there was entry for it in the GRUB menu. I was able to fix this by tinkering with the GRUB config.

Ok, now I can log-in U-18. Observe EFI boot manager variables:

```
>efibootmgr -v

BootCurrent: 0000
Timeout: 1 seconds
BootOrder: 0000,0001
Boot0000* ubuntu	HD(1,GPT,5307826d-84e7-4497-89df-234a9b109f94,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
Boot0001  Hard Drive	BBS(HD,,0x0)/VenHw(5ce8128b-2cec-40f0-8372-80640e3dc858,0200)..GO...
```

This are the records within UEFI Boot Manager that are stored in the NVRAM on the motherboard. They were added by UEFI firmware itself. 

`5307...9f94` is PARTUUID of sda1 EFI partition (remember that UUID is an attribute of filesystem and PARTUUID - of partition):

```
>sudo blkid | grep -v loop 

/dev/sda1: UUID="1E86-1FD7" TYPE="vfat" PARTUUID="5307826d-84e7-4497-89df-234a9b109f94"
...
```

> What does `HD(1,` mean? Disk #1? Then why does numeration start from one and not from zero?

> What is `BBS(HD,,0x0)` and this id `5ce8128b-2cec-40f0-8372-80640e3dc858`? It is all over the Internet so it has nothing to do with UUID/GUID on my particular computer.

# State of UEFI firmware

This is how BBS priorities option in UEFI looks so far:

![BBS UEFI](./BBS1.jpg)

Although there are two EFI partitions (sda1 on SATA1, sdb1 on SATA2) BBS contains only one item because sdb1 partition contains no EFI executables and UEFI firmware sees that.

Now, what will happen if to copy data from sda1 to sdb1?

```
>md /tmp/sda1
>md /tmp/sdb1
>sudo mount /dev/sda1 /tmp/sda1
>sudo mount /dev/sdb1 /tmp/sdb1
>sudo cp -r /tmp/sda1/EFI /tmp/sdb1
>sync
>reboot
```

This is how BBS priorities option in UEFI looks now:

![BBS UEFI](./BBS2.jpg)

Second item in the list has appeared: UEFI firmware detected EFI executables in the sdb1 partion on SATA2 disk. Boot manager vars looks like this now:

```
>efibootmgr -v

BootCurrent: 0000
Timeout: 1 seconds
BootOrder: 0000,0001,0002
Boot0000* ubuntu	HD(1,GPT,5307826d-84e7-4497-89df-234a9b109f94,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
Boot0001  Hard Drive	BBS(HD,,0x0)...
Boot0002* ubuntu	HD(1,GPT,e25ce0d9-4902-4438-8f1e-617ed649ab41,0x800,0xf3800)/File(\EFI\Ubuntu\shimx64.efi)..BO
```

PARTUUIDs are matching up:

```
>sudo blkid | grep -v loop 

/dev/sda1: UUID="1E86-1FD7" TYPE="vfat" PARTUUID="5307826d-84e7-4497-89df-234a9b109f94"
...
/dev/sdb1: UUID="C5AE-10A6" TYPE="vfat" PARTUUID="e25ce0d9-4902-4438-8f1e-617ed649ab41"
...
```

Now I'm going to set SATA2 (sdb) to be a first item in BBS Priorities list thus instructing UEFI firware to seek SATA2 for ESP partition first (that is use bootloader at sdb1). I expect same boot process because data on sdb1 is the same as on sda1.

It is the same indeed. No problem booting both U-18 and U-22 fron sdb1. That is an expected behavour. EFI partition was filled by `grub-install` command that simply copies *.efi executables and config grub.cfg with content:

```
>cat EFI/ubuntu/grub.cfg 

search.fs_uuid 6f6abe60...6fe5 root hd1,gpt2 
set prefix=($root)'/boot/grub'
configfile $prefix/grub.cfg
```

`6f6abe60...6fe5` is UUID of file system on /dev/sdb2 where Ubuntu-22 was installed. This config instructs bootloder executable to 

1. go to disk sdb (sdb - hd1, sda - hd0)
2. find there file system with `UUID=6f6abe60...` located at /dev/sdb2
```
sudo blkid | grep -v loop
...
/dev/sdb2: UUID="6f6abe60...6fe5"
...
```
3. find file /boot/grub/grub.cfg and use to find boot options

> In `search.fs_uuid 6f6abe60...6fe5 root hd1,gpt2` why both `gpt2` and UUID are present? `gpt2` means second partition sdb2, right? Then why there is also UUID of file system on this partition. It seems redundant. 


Here is the state of UEFI Boot Manager after changing BBS priorities. Note change in boot order.

```
>efibootmgr -v

BootCurrent: 0004
Timeout: 1 seconds
BootOrder: 0002,0000,0001
Boot0000* ubuntu	HD(1,GPT,5307826d-84e7-4497-89df-234a9b109f94,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
Boot0001  Hard Drive	BBS(HD,,0x0)..
Boot0002* ubuntu	HD(1,GPT,e25ce0d9-4902-4438-8f1e-617ed649ab41,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)..BO
```

Say I want to install Windows as well but afraid that it will mess up EFI partition. By having backup ESP on another disk I can proceed without worries. If Windows installer overrides one ESP another will be intact.

Замечание про GUID раздела
==========================
```
>lsblk -p -o NAME,PARTTYPE | grep -v loop
NAME        PARTTYPE
/dev/sda    
├─/dev/sda1 c12a7328-f81f-11d2-ba4b-00a0c93ec93b
└─/dev/sda2 0fc63daf-8483-4772-8e79-3d69d8477de4
/dev/sdb    
├─/dev/sdb1 c12a7328-f81f-11d2-ba4b-00a0c93ec93b
├─/dev/sdb2 0fc63daf-8483-4772-8e79-3d69d8477de4
└─/dev/sdb3 0fc63daf-8483-4772-8e79-3d69d8477de4
/dev/sdc    
├─/dev/sdc1 0fc63daf-8483-4772-8e79-3d69d8477de4
└─/dev/sdc2 0657fd6d-a4ab-43c4-84e5-0933c84b4f4f
```