At first there had been disk sda with two partitions:
- /dev/sda1: ESP
- /dev/sda2: Ubuntu 18.04

Then I connected second disk sdb and installed Ubuntu 22.04 on it. During installation following partitions were created:
- /dev/sdb1: FAT32 for ESP. 
- /dev/sdb2: ext4 for /
- /dev/sdb3: ext4 for /home

I intended to make separate EFI partitions for Ubuntu 22.04 on /dev/sdb1 and leave ESP on /dev/sda1 intact. Motivation was to not alter Ubuntu-18's GRUB but I messed up and Ubuntu-22's GRUB was dumped on /dev/sda1 and /dev/sdb1 was leaved empty.

So U-22 was installed and booted normally while U-18 failed to boot eve though there was entry of it in GRUB menu. I was able to fix this (XXX descrive how).

Anyway now I'm logged-in U-18 and:
```
>efibootmgr -v

BootCurrent: 0000
Timeout: 1 seconds
BootOrder: 0000,0001
Boot0000* ubuntu	HD(1,GPT,5307826d-84e7-4497-89df-234a9b109f94,0x800,0xf3800)/File(\EFI\UBUNTU\SHIMX64.EFI)
Boot0001  Hard Drive	BBS(HD,,0x0)/VenHw(5ce8128b-2cec-40f0-8372-80640e3dc858,0200)
```

This is records in UEFI Boot Manager that are stored in NVRAM on the motherboard. They were added by UEFI firmware.