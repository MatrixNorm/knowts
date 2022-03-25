
### GRUB

>sudo vim /etc/default/grub
GRUB_TIMEOUT_STYLE=menu
GRUB_TIMEOUT=10

>sudo update-grub

### install kernel of specific version

>md kernels/4.19.236
>cd kernels/4.19.236
download into . deb files from https://kernel.ubuntu.com/~kernel-ppa/mainline/v4.19.236/ :

amd64/linux-headers-4.19.236-0419236-generic_4.19.236-0419236.202203231010_amd64.deb
amd64/linux-headers-4.19.236-0419236_4.19.236-0419236.202203231010_all.deb
amd64/linux-image-unsigned-4.19.236-0419236-generic_4.19.236-0419236.202203231010_amd64.deb
amd64/linux-modules-4.19.236-0419236-generic_4.19.236-0419236.202203231010_amd64.deb

>sudo dpkg -i *.deb
>sudo update-grub
>sudo reboot