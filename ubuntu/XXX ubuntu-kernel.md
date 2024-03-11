### GRUB

```console
sudo vim /etc/default/grub
```

GRUB_TIMEOUT_STYLE=menu
GRUB_TIMEOUT=10

```console
sudo update-grub
```

### install kernel of specific version

```console
mkdir foo
cd foo
```

download into this folder deb files from https://kernel.ubuntu.com/~kernel-ppa/mainline/VERSION-NUMBER/:

- amd64/linux-headers-VERSION-NUMBER_amd64.deb
- amd64/linux-headers-VERSION-NUMBER_all.deb
- amd64/linux-image-VERSION-NUMBER_amd64.deb
- amd64/linux-modules-VERSION-NUMBER_amd64.deb

Install them all:

```console
sudo dpkg -i *.deb
```

Update Grub and reboot:

```console
sudo update-grub
sudo reboot
```
