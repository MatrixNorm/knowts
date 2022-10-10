## How can I check the available version of a package in the repositories?

```
>apt-cache policy fish

fish:
  Installed: (none)
  Candidate: 3.5.1-1~bionic
  Version table:
     3.5.1-1~bionic 500
        500 http://ppa.launchpad.net/fish-shell/release-3/ubuntu bionic/main amd64 Packages
     2.7.1-3 500
        500 http://archive.ubuntu.com/ubuntu bionic/universe amd64 Packages
```

## How do I check if a package is installed

```
>dpkg -s qemu-kvm

dpkg-query: package 'qemu' is not installed and no information is available
```

```
>dpkg -s redshift

Package: redshift
Status: install ok installed
Priority: extra
Section: x11
Installed-Size: 420
Maintainer: Ubuntu Developers <ubuntu-devel-discuss@lists.ubuntu.com>
Architecture: amd64
Version: 1.11-1ubuntu1
Depends: libc6 (>= 2.17), libdrm2 (>= 2.4.3), libglib2.0-0 (>= 2.26.0), libx11-6, libxcb-randr0 (>= 1.3), libxcb1, libxxf86vm1
```

## Get package info

```
>apt-cache show libvirt-clients

Package: libvirt-clients
Architecture: amd64
Version: 4.0.0-1ubuntu8.21
Priority: optional
Section: admin
Source: libvirt
Origin: Ubuntu
Maintainer: Ubuntu Developers <ubuntu-devel-discuss@lists.ubuntu.com>
Original-Maintainer: Debian Libvirt Maintainers <pkg-libvirt-maintainers@lists.alioth.debian.org>
Bugs: https://bugs.launchpad.net/ubuntu/+filebug
Installed-Size: 1988
Depends: libapparmor1 (>= 2.6~devel), libc6 (>= 2.17), libreadline7 (>= 6.0), libvirt0 (= 4.0.0-1ubuntu8.21), libxml2 (>= 2.7.4)
```

## Download package without installation

```
>apt-get download python3-venv
```