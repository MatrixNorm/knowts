
# ubuntu server 18.04 in virtualbox

### VM settings

Network: bridge adapter

### ssh server

Error while trying to ssh into VM:
>ssh monkey@192.168.0.185 
<<<Connection reset by 192.168.0.185 port 22

FIX:
>ssh-keygen -A
>systemctl restart sshd

### guest addition 

!!! Guest addition for VB 5.2.34 does not compile on Ubuntu 20.04 because of missing header files.

>sudo apt update
>sudo apt install build-essential dkms linux-headers-$(uname -r)

Insert virtual CD with Guest addition image

>sudo mkdir -p /media/cdrom
>sudo mount /dev/cdrom /media/cdrom
>cd /media/cdrom
>sudo sh ./VBoxLinuxAdditions.run --nox11
...
VirtualBox Guest Additions: Starting.
>sudo shutdown -r now
>lsmod | grep vboxguest
vboxguest 303104 2 vboxsf

### terminal resolution

>sudo vim /etc/default/grub
GRUB_GFXMODE=1600x1200
GRUB_CMDLINE_LINUX_DEFAULT="nomodeset"
GRUB_GFXPAYLOAD_LINUX=keep
>sudo update-grub
>sudo shutdown -r now

### copy file between host and guest

Error:
>sudo mount -t vboxsf shared ~/shared 
<<</sbin/mount.vboxsf: mounting failed with the error: Protocol error

