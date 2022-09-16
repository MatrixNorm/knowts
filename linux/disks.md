# Detecting disks

>lsblk
```
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
sda      8:0    0 238,5G  0 disk 
├─sda1   8:1    0   487M  0 part /boot/efi
└─sda2   8:2    0   238G  0 part /
sdb      8:16   0 931,5G  0 disk 
├─sdb1   8:17   0 901,7G  0 part /mnt/hdd
└─sdb2   8:18   0  29,8G  0 part [SWAP]
sdc      8:32   0 119,2G  0 disk 
├─sdc1   8:33   0   512M  0 part 
├─sdc2   8:34   0 114,9G  0 part 
└─sdc3   8:35   0   3,9G  0 part
```

>lsblk -f
```
NAME   FSTYPE UUID             MOUNTPOINT
sda                         
├─sda1 vfat   1E86-1FD7        /boot/efi
└─sda2 ext4   b8ce0513-b0be... /
sdb                         
├─sdb1 ext4   5df085a3-5112... /mnt/hdd
└─sdb2 swap   2ec5d4b1-31cb... [SWAP]
sdc                         
├─sdc1 vfat   DFCC-033F     
├─sdc2 ext4   86ea6ab0-5640... 
└─sdc3 swap   4f1b9944-1a27...
```

>sudo lshw -class disk
```
*-disk                    
  description: ATA Disk
  product: ADATA SU800
  physical id: 0.0.0
  bus info: scsi@0:0.0.0
  logical name: /dev/sda
  version: 1A
  serial: 2H0720013312
  size: 238GiB (256GB)
  capabilities: gpt-1.00 partitioned partitioned:gpt
  configuration: ansiversion=5 
                 guid=7afd7b46-460d-428e-8bed-79094b3aaaba 
                 logicalsectorsize=512 
                 sectorsize=512
*-disk
  description: ATA Disk
  product: ST1000DM003-1SB1
  vendor: Seagate
  physical id: 0.0.0
  bus info: scsi@1:0.0.0
  logical name: /dev/sdb
  version: CC43
  serial: Z9A9JX4Z
  size: 931GiB (1TB)
  capabilities: gpt-1.00 partitioned partitioned:gpt
  configuration: ansiversion=5 
                 guid=ed890e8d-1227-4725-bde8-8e4b0af2480b 
                 logicalsectorsize=512 
                 sectorsize=4096
*-disk
  description: ATA Disk
  product: TS128GSSD360S
  physical id: 0.0.0
  bus info: scsi@4:0.0.0
  logical name: /dev/sdc
  version: 3A0
  serial: 82166282E445942E0026
  size: 119GiB (128GB)
  capabilities: gpt-1.00 partitioned partitioned:gpt
  configuration: ansiversion=5 
                 guid=22a624fe-1334-4a86-8991-51fe1c5f5dcd 
                 logicalsectorsize=512 
                 sectorsize=512
```

>sudo fdisk -l
```
Disk /dev/sda: 238,5 GiB, 256060514304 bytes, 500118192 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 7AFD7B46-460D-428E-8BED-79094B3AAABA

Device      Start       End   Sectors  Size Type
/dev/sda1    2048    999423    997376  487M EFI System
/dev/sda2  999424 500117503 499118080  238G Linux filesystem

Disk /dev/sdb: 931,5 GiB, 1000204886016 bytes, 1953525168 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 4096 bytes
I/O size (minimum/optimal): 4096 bytes / 4096 bytes
Disklabel type: gpt
Disk identifier: ED890E8D-1227-4725-BDE8-8E4B0AF2480B

Device          Start        End    Sectors   Size Type
/dev/sdb1        2048 1891022847 1891020800 901,7G Linux filesystem
/dev/sdb2  1891022848 1953523711   62500864  29,8G Linux swap

Disk /dev/sdc: 119,2 GiB, 128035676160 bytes, 250069680 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 22A624FE-1334-4A86-8991-51FE1C5F5DCD

Device         Start       End   Sectors   Size Type
/dev/sdc1       2048   1050623   1048576   512M EFI System
/dev/sdc2    1050624 241917951 240867328 114,9G Linux filesystem
/dev/sdc3  241917952 250068991   8151040   3,9G Linux swap
```

>hwinfo --disk
```
IDE 100.0: 10600 Disk                                       
[Created at block.245]
Unique ID: WZeP.dCMeGm1lvW1
Parent ID: kEn8.Oy0HQKbM2z6
SysFS ID: /class/block/sdb
SysFS BusID: 1:0:0:0
SysFS Device Link: /devices/pci0000:00/0000:00:01.3/0000:03:00.1/ata2/host1/target1:0:0/1:0:0:0
Hardware Class: disk
Model: "ST1000DM003-1SB1"
Device: "ST1000DM003-1SB1"
Revision: "CC43"
Driver: "ahci", "sd"
Driver Modules: "ahci"
Device File: /dev/sdb
Device Files: /dev/sdb, /dev/disk/by-id/ata-ST1000DM003-1SB102_Z9A9JX4Z, /dev/disk/by-id/wwn-0x5000c500939fa9f2, /dev/disk/by-path/pci-0000:03:00.1-ata-2
Device Number: block 8:16-8:31
BIOS id: 0x80
Drive status: no medium
Config Status: cfg=new, avail=yes, need=no, active=unknown
Attached to: #17 (SATA controller)

IDE 400.0: 10600 Disk
[Created at block.245]
Unique ID: _kuT.EN7CA7XBlX0
Parent ID: kEn8.Oy0HQKbM2z6
SysFS ID: /class/block/sdc
SysFS BusID: 4:0:0:0
SysFS Device Link: /devices/pci0000:00/0000:00:01.3/0000:03:00.1/ata5/host4/target4:0:0/4:0:0:0
Hardware Class: disk
Model: "TS128GSSD360S"
Device: "TS128GSSD360S"
Revision: "3A0"
Driver: "ahci", "sd"
Driver Modules: "ahci"
Device File: /dev/sdc
Device Files: /dev/sdc, /dev/disk/by-id/ata-TS128GSSD360S_82166282E445942E0026, /dev/disk/by-path/pci-0000:03:00.1-ata-5
Device Number: block 8:32-8:47
BIOS id: 0x81
Drive status: no medium
Config Status: cfg=new, avail=yes, need=no, active=unknown
Attached to: #17 (SATA controller)

IDE 00.0: 10600 Disk
[Created at block.245]
Unique ID: 3OOL.ISXXhxQVH51
Parent ID: kEn8.Oy0HQKbM2z6
SysFS ID: /class/block/sda
SysFS BusID: 0:0:0:0
SysFS Device Link: /devices/pci0000:00/0000:00:01.3/0000:03:00.1/ata1/host0/target0:0:0/0:0:0:0
Hardware Class: disk
Model: "A SU800"
Vendor: "ADATA"
Device: "SU800"
Revision: "1A"
Driver: "ahci", "sd"
Driver Modules: "ahci"
Device File: /dev/sda
Device Files: /dev/sda, /dev/disk/by-id/ata-ADATA_SU800_2H0720013312, /dev/disk/by-id/wwn-0x5707c1810044ee46, /dev/disk/by-path/pci-0000:03:00.1-ata-1
Device Number: block 8:0-8:15
BIOS id: 0x82
Drive status: no medium
Config Status: cfg=new, avail=yes, need=no, active=unknown
Attached to: #17 (SATA controller)
```

>tree /dev/disk/
```
/dev/disk/
├── by-id
│   ├── ata-ADATA_SU800_2H0720013312 -> ../../sda
│   ├── ata-ADATA_SU800_2H0720013312-part1 -> ../../sda1
│   ├── ata-ADATA_SU800_2H0720013312-part2 -> ../../sda2
│   ├── ata-ST1000DM003-1SB102_Z9A9JX4Z -> ../../sdb
│   ├── ata-ST1000DM003-1SB102_Z9A9JX4Z-part1 -> ../../sdb1
│   ├── ata-ST1000DM003-1SB102_Z9A9JX4Z-part2 -> ../../sdb2
│   ├── ata-TS128GSSD360S_82166282E445942E0026 -> ../../sdc
│   ├── ata-TS128GSSD360S_82166282E445942E0026-part1 -> ../../sdc1
│   ├── ata-TS128GSSD360S_82166282E445942E0026-part2 -> ../../sdc2
│   ├── ata-TS128GSSD360S_82166282E445942E0026-part3 -> ../../sdc3
│   ├── wwn-0x5000c500939fa9f2 -> ../../sdb
│   ├── wwn-0x5000c500939fa9f2-part1 -> ../../sdb1
│   ├── wwn-0x5000c500939fa9f2-part2 -> ../../sdb2
│   ├── wwn-0x5707c1810044ee46 -> ../../sda
│   ├── wwn-0x5707c1810044ee46-part1 -> ../../sda1
│   └── wwn-0x5707c1810044ee46-part2 -> ../../sda2
├── by-partlabel
│   └── EFI\x20System\x20Partition -> ../../sdc1
├── by-partuuid
│   ├── 5307826d-84e7-4497-89df-234a9b109f94 -> ../../sda1
│   ├── 5e462820-a555-43db-8d0c-77d3f8627280 -> ../../sdc3
│   ├── 814edc7c-9bda-4f02-85bf-7772a2128054 -> ../../sdb2
│   ├── 96579937-1639-4e98-9323-1e0fd98f9a80 -> ../../sda2
│   ├── 9c460977-078e-45d7-9c5d-9c5103aec012 -> ../../sdc2
│   ├── a5515dc2-73e2-451b-8ea7-37d9d4421d81 -> ../../sdc1
│   └── fc4d9008-98db-4f7f-b4be-7e87ea528510 -> ../../sdb1
├── by-path
│   ├── pci-0000:03:00.1-ata-1 -> ../../sda
│   ├── pci-0000:03:00.1-ata-1-part1 -> ../../sda1
│   ├── pci-0000:03:00.1-ata-1-part2 -> ../../sda2
│   ├── pci-0000:03:00.1-ata-2 -> ../../sdb
│   ├── pci-0000:03:00.1-ata-2-part1 -> ../../sdb1
│   ├── pci-0000:03:00.1-ata-2-part2 -> ../../sdb2
│   ├── pci-0000:03:00.1-ata-5 -> ../../sdc
│   ├── pci-0000:03:00.1-ata-5-part1 -> ../../sdc1
│   ├── pci-0000:03:00.1-ata-5-part2 -> ../../sdc2
│   └── pci-0000:03:00.1-ata-5-part3 -> ../../sdc3
└── by-uuid
    ├── 1E86-1FD7 -> ../../sda1
    ├── 2ec5d4b1-31cb-4a63-9dad-2970697e5137 -> ../../sdb2
    ├── 4f1b9944-1a27-4e49-bcc4-feb30c394233 -> ../../sdc3
    ├── 5df085a3-5112-4b56-beba-1cec9553c3da -> ../../sdb1
    ├── 86ea6ab0-5640-4e1a-8bc5-3542f1303504 -> ../../sdc2
    ├── b8ce0513-b0be-43cb-ba50-bbefb37072a2 -> ../../sda2
    └── DFCC-033F -> ../../sdc1
```

>cat /etc/fstab
```
# <file system> <mount point>   <type>  <options>       <dump>  <pass>

# / was on /dev/sda2 during installation
UUID=b8ce0513-b0be-43cb-ba50-bbefb37072a2 /               ext4    noatime,errors=remount-ro 0       1

# /boot/efi was on /dev/sda1 during installation
UUID=1E86-1FD7  /boot/efi       vfat    umask=0077      0       1

# /mnt/hdd was on /dev/sdb1 during installation
UUID=5df085a3-5112-4b56-beba-1cec9553c3da /mnt/hdd        ext4    defaults        0       2

# swap was on /dev/sdb2 during installation
UUID=2ec5d4b1-31cb-4a63-9dad-2970697e5137 none            swap    sw              0       0
```

# Mount

>mount | grep ^/dev

* /dev/sda2 on / type ext4 (rw,noatime,errors=remount-ro)
* /dev/sda1 on /boot/efi type vfat (rw,relatime,fmask=0077,dmask=0077,codepage=437,iocharset=iso8859-1,shortname=mixed,errors=remount-ro)
* /dev/sdb1 on /mnt/hdd type ext4 (rw,relatime)

>sudo fdisk /dev/sdc
```
Welcome to fdisk (util-linux 2.31.1).
Changes will remain in memory only, until you decide to write them.
Be careful before using the write command.

The old ext4 signature will be removed by a write command.

Device does not contain a recognized partition table.
Created a new DOS disklabel with disk identifier 0x15b77160.

Command (m for help): m

Help:

  DOS (MBR)
   a   toggle a bootable flag
   b   edit nested BSD disklabel
   c   toggle the dos compatibility flag

  Generic
   d   delete a partition
   F   list free unpartitioned space
   l   list known partition types
   n   add a new partition
   p   print the partition table
   t   change a partition type
   v   verify the partition table
   i   print information about a partition

  Misc
   m   print this menu
   u   change display/entry units
   x   extra functionality (experts only)

  Script
   I   load disk layout from sfdisk script file
   O   dump disk layout to sfdisk script file

  Save & Exit
   w   write table to disk and exit
   q   quit without saving changes

  Create a new label
   g   create a new empty GPT partition table
   G   create a new empty SGI (IRIX) partition table
   o   create a new empty DOS partition table
   s   create a new empty Sun partition table


Command (m for help): p
Disk /dev/sdc: 119,2 GiB, 128035676160 bytes, 250069680 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0x15b77160

Command (m for help): g
Created a new GPT disklabel (GUID: 6361C2FD-2291-9747-83C0-AF23CAF8758A).
The old ext4 signature will be removed by a write command.

Command (m for help): p

Disk /dev/sdc: 119,2 GiB, 128035676160 bytes, 250069680 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 6361C2FD-2291-9747-83C0-AF23CAF8758A

Command (m for help): n
Partition number (1-128, default 1): 1
First sector (2048-250069646, default 2048): 
Last sector, +sectors or +size{K,M,G,T,P} (2048-250069646, default 250069646): 

Created a new partition 1 of type 'Linux filesystem' and of size 119,2 GiB.

Command (m for help): p
Disk /dev/sdc: 119,2 GiB, 128035676160 bytes, 250069680 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: gpt
Disk identifier: 6361C2FD-2291-9747-83C0-AF23CAF8758A

Device     Start       End   Sectors   Size Type
/dev/sdc1   2048 250069646 250067599 119,2G Linux filesystem

Command (m for help): w
The partition table has been altered.
Calling ioctl() to re-read partition table.
Syncing disks.
>
```
>lsblk -f | grep -v loop
```
NAME   FSTYPE  UUID MOUNTPOINT
sda                                                        
├─sda1 vfat 1E86-1FD7    /boot/efi
└─sda2 ext4 b8ce0513-... /
sdb                                                      
├─sdb1 ext4 5df085a3-... /mnt/hdd
└─sdb2 swap 2ec5d4b1-... [SWAP]
sdc                                                        
└─sdc1
```

>sudo mkfs.ext4 /dev/sdc1
>lsblk -f | grep sdc
```
sdc                                                        
└─sdc1 ext4  53ced694-...
```

>sudo mkdir /mnt/ssd1
>ls -l /mnt
>sudo chown -R me:me /mnt/ssd1
```
drwxr-xr-x 20 me me 4096 сен 10 23:38 hdd
drwxr-xr-x  2 me me 4096 сен 16 21:15 ssd1
```

>sudo mount /dev/sdc1 /mnt/ssd1
>lsblk -f | grep sdc       
```
sdc                                                        
└─sdc1 ext4 53ced694-... /mnt/ssd1
```

>df -h | grep sdc
```
/dev/sdc1       117G   61M  111G   1% /mnt/ssd1
```
