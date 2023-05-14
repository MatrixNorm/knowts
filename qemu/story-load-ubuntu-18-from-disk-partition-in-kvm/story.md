```
$ lsblk -f /dev/sda
NAME   FSTYPE FSVER LABEL    UUID                                 
sda                                                              
├─sda1 vfat   FAT32          1E86-1FD7                           
└─sda2 ext4   1.0   ubuntu18 b8ce0513-b0be-43cb-ba50-bbefb37072a2
```

```
$ sudo mount /dev/sda1 /tmp/sda1/
$ tree /tmp/sda1
/tmp/sda1
└── EFI
    ├── BOOT
    │   ├── BOOTX64.EFI
    │   └── fbx64.efi
    └── ubuntu
        ├── BOOTX64.CSV
        ├── grub.cfg
        ├── grubx64.efi
        ├── mmx64.efi
        └── shimx64.efi
```

```
$ sudo qemu-system-x86_64 -cpu host -enable-kvm \
    -smp 2 -m 2G \
    -bios /usr/share/qemu/OVMF.fd \
    -hda /dev/sda
```

![qemu](./pic1.png)

```
grub>ls
(hd0,gpt1)  (hd0,gpt2)

grub>ls (hd0,gpt1)/efi/ubuntu
BOOTX64.CSV grub.cfg grubx64.efi mmx64.efi shimx64.efi
```

```
$ cat /tmp/sda1/EFI/ubuntu/grub.cfg 
search.fs_uuid b8ce0513-b0be-43cb-ba50-bbefb37072a2 root hd0,gpt2 
set prefix=($root)'/boot/grub'
configfile $prefix/grub.cfg
```

```
$ sudo mount /dev/sda2 /tmp/sda2/
$ ll /tmp/sda2/boot/grub/grub.cfg
ls: cannot access '/tmp/sda2/boot/grub/grub.cfg': No such file or directory
```

Поместил туда файл, но qemu его не видит. Та же ситуация, то и с флешкой и с лже-диском в RAM. sync не помогает, umount+mount не помогает. 

Помогла только перезагрузка.

* The -hda option emulates a PATA disk. ???

# Слом

После всех этих манипуляций убунту-18 перестала грузиться на железе. Помогла команда `fsck`, применённая к sda1 и sda2.

# Решено

Вот это видео помогло: https://www.youtube.com/watch?v=YzA2ToW3Lk0

error: /boot/vmlinuz... has invalid signature --> choose another UEFI firmware without secure boot

/usr/bin/qemu-system-x86_64 
    -name guest=ubuntu18,debug-threads=on 
    -S 
    -object {"qom-type":"secret","id":"masterKey0","format":"raw","file":"/var/lib/libvirt/qemu/domain-6-ubuntu18/master-key.aes"} 
    
    -blockdev {"driver":"file","filename":"/usr/share/OVMF/OVMF_CODE_4M.fd","node-name":"libvirt-pflash0-storage","auto-read-only":true,"discard":"unmap"} 
    
    -blockdev {"node-name":"libvirt-pflash0-format","read-only":true,"driver":"raw","file":"libvirt-pflash0-storage"} 
    
    -blockdev {"driver":"file","filename":"/var/lib/libvirt/qemu/nvram/ubuntu18_VARS.fd","node-name":"libvirt-pflash1-storage","auto-read-only":true,"discard":"unmap"} 
    
    -blockdev {"node-name":"libvirt-pflash1-format","read-only":false,"driver":"raw","file":"libvirt-pflash1-storage"} 
    
    -machine pc-q35-6.2,usb=off,vmport=off,dump-guest-core=off,pflash0=libvirt-pflash0-format,pflash1=libvirt-pflash1-format,memory-backend=pc.ram 
    -accel kvm 
    -cpu host,migratable=on 
    -m 6096 
    -object {"qom-type":"memory-backend-ram","id":"pc.ram","size":6392119296} 
    -overcommit mem-lock=off 
    -smp 2,sockets=2,cores=1,threads=1 
    -uuid d23d2091-75d6-4929-95e1-034025613206 
    -no-user-config 
    -nodefaults 
    -chardev socket,id=charmonitor,fd=33,server=on,wait=off 
    -mon chardev=charmonitor,id=monitor,mode=control 
    -rtc base=utc,driftfix=slew 
    -global kvm-pit.lost_tick_policy=delay 
    -no-hpet 
    -no-shutdown 
    -global ICH9-LPC.disable_s3=1 
    -global ICH9-LPC.disable_s4=1 
    -boot strict=on 
    -device pcie-root-port,port=16,chassis=1,id=pci.1,bus=pcie.0,multifunction=on,addr=0x2 
    -device pcie-root-port,port=17,chassis=2,id=pci.2,bus=pcie.0,addr=0x2.0x1 
    -device pcie-root-port,port=18,chassis=3,id=pci.3,bus=pcie.0,addr=0x2.0x2 
    -device pcie-root-port,port=19,chassis=4,id=pci.4,bus=pcie.0,addr=0x2.0x3 
    -device pcie-root-port,port=20,chassis=5,id=pci.5,bus=pcie.0,addr=0x2.0x4 
    -device pcie-root-port,port=21,chassis=6,id=pci.6,bus=pcie.0,addr=0x2.0x5 
    -device pcie-root-port,port=22,chassis=7,id=pci.7,bus=pcie.0,addr=0x2.0x6 
    -device pcie-root-port,port=23,chassis=8,id=pci.8,bus=pcie.0,addr=0x2.0x7 
    -device pcie-root-port,port=24,chassis=9,id=pci.9,bus=pcie.0,multifunction=on,addr=0x3 
    -device pcie-root-port,port=25,chassis=10,id=pci.10,bus=pcie.0,addr=0x3.0x1 
    -device pcie-root-port,port=26,chassis=11,id=pci.11,bus=pcie.0,addr=0x3.0x2 
    -device pcie-root-port,port=27,chassis=12,id=pci.12,bus=pcie.0,addr=0x3.0x3 
    -device pcie-root-port,port=28,chassis=13,id=pci.13,bus=pcie.0,addr=0x3.0x4 
    -device pcie-root-port,port=29,chassis=14,id=pci.14,bus=pcie.0,addr=0x3.0x5 
    -device qemu-xhci,p2=15,p3=15,id=usb,bus=pci.2,addr=0x0 
    -device virtio-serial-pci,id=virtio-serial0,bus=pci.3,addr=0x0 
    # ====================================================================
    -blockdev {"driver":"host_device","filename":"/dev/disk/by-id/ata-ADATA_SU800_2H0720013312","aio":"native","node-name":"libvirt-1-storage","cache":{"direct":true,"no-flush":false},"auto-read-only":true,"discard":"unmap"} 
    
    -blockdev {"node-name":"libvirt-1-format","read-only":false,"discard":"unmap","cache":{"direct":true,"no-flush":false},"driver":"raw","file":"libvirt-1-storage"} 
    
    -device ide-hd,bus=ide.0,drive=libvirt-1-format,id=sata0-0-0,bootindex=1,write-cache=on 
    # ====================================================================
    -netdev tap,fd=34,id=hostnet0,vhost=on,vhostfd=36 
    -device virtio-net-pci,netdev=hostnet0,id=net0,mac=52:54:00:ed:22:06,bus=pci.1,addr=0x0 
    -chardev pty,id=charserial0 -device isa-serial,chardev=charserial0,id=serial0 
    -chardev socket,id=charchannel0,fd=32,server=on,wait=off -device virtserialport,bus=virtio-serial0.0,nr=1,chardev=charchannel0,id=channel0,name=org.qemu.guest_agent.0 
    -chardev spicevmc,id=charchannel1,name=vdagent 
    -device virtserialport,bus=virtio-serial0.0,nr=2,chardev=charchannel1,id=channel1,name=com.redhat.spice.0 
    -device usb-tablet,id=input0,bus=usb.0,port=1 -audiodev {"id":"audio1","driver":"spice"} 
    -spice port=5900,addr=127.0.0.1,disable-ticketing=on,image-compression=off,seamless-migration=on 
    -device virtio-vga,id=video0,max_outputs=1,bus=pcie.0,addr=0x1 
    -device ich9-intel-hda,id=sound0,bus=pcie.0,addr=0x1b -device hda-duplex,id=sound0-codec0,bus=sound0.0,cad=0,audiodev=audio1 
    -chardev spicevmc,id=charredir0,name=usbredir -device usb-redir,chardev=charredir0,id=redir0,bus=usb.0,port=2 
    -chardev spicevmc,id=charredir1,name=usbredir -device usb-redir,chardev=charredir1,id=redir1,bus=usb.0,port=3 -device virtio-balloon-pci,id=balloon0,bus=pci.4,addr=0x0 
    -object {"qom-type":"rng-random","id":"objrng0","filename":"/dev/urandom"} 
    -device virtio-rng-pci,rng=objrng0,id=rng0,bus=pci.5,addr=0x0 -sandbox on,obsolete=deny,elevateprivileges=deny,spawn=deny,resourcecontrol=deny -msg timestamp=on