
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

???

### copy file between host and guest

Error:
>sudo mount -t vboxsf shared ~/shared 
<<</sbin/mount.vboxsf: mounting failed with the error: No such device

Troubleshooting:
>sudo modprobe vboxsf
<<<modprobe: FATAL: Module vboxsf not found in directory /lib/modules/4.15.0-173-generic