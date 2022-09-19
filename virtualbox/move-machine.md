## How to move machine to different disk **VirtualBox 5.2**

**Use case**

Windows 10 virtual machine.
Snapshot Folder: ~/win10/Snapshots
Storage:
  - ~/win10/win10.vhd
  - ~/.config/VirtualBox/VBoxGuestAdditions_5.2.34.iso
VM location: /mnt/hdd/VMs/win10
>tree /mnt/hdd/VMs/win10
```
├── Logs
│   ├── VBox.log
│   ├── VBox.log.1
│   ├── VBox.log.2
│   └── VBox.log.3
├── win10.vbox
└── win10.vbox-prev
```

1. Copy `/mnt/hdd/VMs/win10` to `/mnt/ssd1/VirtualBoxVMs/win10`
2. Copy `~/win10/win10.vhd` to `/mnt/ssd1/VirtualBoxVMs/win10/win10.vhd`
3. Copy `~/win10/Snapshots` to `/mnt/ssd1/VirtualBoxVMs/win10/Snapshots`
4. Remove old machine from VB but keep all files
5. Machine -> Add :: add new machine to VB

Change new machine's settings:

1. General -> Snaphot folder :: set to `/mnt/ssd1/VirtualBoxVMs/win10/Snapshots`
2. Storage -> Cintroller:SATA -> win10.vhd -> right click -> Remove Attachment
3. File -> Virtual Media Manager -> win10.vhd :: remove but keep files on disk
4. Storage -> Cintroller:SATA -> add `/mnt/ssd1/VirtualBoxVMs/win10/win10.vhd`
5. Boot new VM and check everything is OK
6. Delete old VM's files from disk


