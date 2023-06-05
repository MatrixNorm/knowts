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
$ apt-cache policy gcc
gcc:
  Installed: 4:11.2.0-1ubuntu1
  Candidate: 4:11.2.0-1ubuntu1

# or

$ dpkg -s gcc
Package: gcc
Status: install ok installed
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

## How can I list all files which HAVE BEEN installed by an APT package?

```
 dpkg -L gcc
/.
/usr
/usr/bin
/usr/bin/c89-gcc
/usr/bin/c99-gcc
...
```

## How can I list all files which WILL be installed by an APT package?

1. simulate install to see what packages will be installed

```
$ apt-get install -s build-essential 
The following additional packages will be installed:
  g++ g++-11 libstdc++-11-dev
Suggested packages:
  g++-multilib g++-11-multilib gcc-11-doc libstdc++-11-doc
The following NEW packages will be installed:
  build-essential g++ g++-11 libstdc++-11-dev
0 upgraded, 4 newly installed, 0 to remove and 270 not upgraded.
Inst libstdc++-11-dev (11.3.0-1ubuntu1~22.04.1 Ubuntu:22.04/jammy-updates, Ubuntu:22.04/jammy-security [amd64])
Inst g++-11 (11.3.0-1ubuntu1~22.04.1 Ubuntu:22.04/jammy-updates, Ubuntu:22.04/jammy-security [amd64])
Inst g++ (4:11.2.0-1ubuntu1 Ubuntu:22.04/jammy [amd64])
Inst build-essential (12.9ubuntu3 Ubuntu:22.04/jammy [amd64])
Conf libstdc++-11-dev (11.3.0-1ubuntu1~22.04.1 Ubuntu:22.04/jammy-updates, Ubuntu:22.04/jammy-security [amd64])
Conf g++-11 (11.3.0-1ubuntu1~22.04.1 Ubuntu:22.04/jammy-updates, Ubuntu:22.04/jammy-security [amd64])
Conf g++ (4:11.2.0-1ubuntu1 Ubuntu:22.04/jammy [amd64])
Conf build-essential (12.9ubuntu3 Ubuntu:22.04/jammy [amd64])
```

2. ??? apt-file