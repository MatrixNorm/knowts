
## ubuntu server 18.04 in virtualbox

### VM settings

Network: bridge adapter

### ssh

Firstly install ssh server on guest machine.

Error while trying to ssh into VM from the host:
```console
ssh monkey@192.168.0.185
```
Connection reset by 192.168.0.185 port 22

FIX:
```console
ssh-keygen -A
systemctl restart sshd
```
How to ssh without password:

1. on guest create file ~/.ssh/authorized_keys
2. on host cd into ~/.ssh and then

```console
ssh-copy-id kyky@192.168.0.177
```

### guest addition 

!!! Guest addition for VB 5.2.34 does not compile on Ubuntu 20.04 because of missing header files.

1. In the guest install prerequisites:
```console
sudo apt update
sudo apt install build-essential dkms linux-headers-$(uname -r)
```

2. Insert virtual CD with Guest addition image

3. Mount CD
```console
sudo mkdir -p /media/cdrom
sudo mount /dev/cdrom /media/cdrom
```
4. Install guest addition
```console
cd /media/cdrom
sudo sh ./VBoxLinuxAdditions.run --nox11
#...
#VirtualBox Guest Additions: Starting.
```


5. Reboot guest
```console
sudo shutdown -r now
```

6. Check whether kernel module is loaded
```console
lsmod | grep vboxguest
#vboxguest 303104 2 vboxsf
```


### terminal resolution

```console
sudo vim /etc/default/grub
```

GRUB_GFXMODE=1600x1200
GRUB_CMDLINE_LINUX_DEFAULT="nomodeset"
GRUB_GFXPAYLOAD_LINUX=keep

```console
sudo update-grub
sudo shutdown -r now
```

### share folder between host and guest

```console
sudo mount -t vboxsf shared ~/node-projects/
```
по какой-то странной причине названия директорий должны быть разные

ПРОБЛЕМА: эта команда меняет хозяина папки ~/node-projects на рута.

```console
sudo mount -t vboxsf -o uid=1000,gid=1000 shared ~/node-projects/
```

Make it persistent between reboots by editing /etc/fstab:

```
<file system>  <mount point>             <type>  <options>          <dump>  <pass>
shared         /home/kyky/node-projects  vboxsf  uid=1000,gid=1000  0       0
```