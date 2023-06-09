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
$ dpkg -L gcc
/.
/usr
/usr/bin
/usr/bin/c89-gcc
/usr/bin/c99-gcc
...
```

https://serverfault.com/questions/96964/list-of-files-installed-from-apt-package

- Keep in mind that while this will get you most of what you need it will not give you everything. Several packages create configuration files as part of their setup scripts. These files will not be reported by dpkg.

- Conffiles of a package (if any) are listed by command dpkg --status $package. For the reverse operation use grep $filename /var/lib/dpkg/info/*.conffiles

## Given a file, which package provides it?

```
$ dpkg -S /usr/include/malloc.h 
libc6-dev:amd64: /usr/include/malloc.h
```

## How can I list all files which WILL be installed by an APT package?

1. simulate install to see what packages will be installed

```
$ apt-get install -s ocaml
...
The following additional packages will be installed:
  ledit libncurses-dev libncurses5-dev ocaml-base ocaml-compiler-libs ocaml-interp ocaml-man
Suggested packages:
  ncurses-doc ocaml-doc elpa-tuareg
The following NEW packages will be installed:
  ledit libncurses-dev libncurses5-dev ocaml ocaml-base ocaml-compiler-libs ocaml-interp ocaml-man
```

2. for each package use `apt-file list`

```
$ apt-file list ledit
ledit: /usr/bin/ledit                     
ledit: /usr/share/bash-completion/completions/ledit
ledit: /usr/share/doc/ledit/README
ledit: /usr/share/doc/ledit/README.Debian
ledit: /usr/share/doc/ledit/changelog.Debian.gz
ledit: /usr/share/doc/ledit/copyright
ledit: /usr/share/man/man1/ledit.1.gz
```

## XXX

W: An error occurred during the signature verification. The repository is not updated and the previous index files will be used. GPG error: https://repo.yandex.ru/yandex-browser/deb stable InRelease: The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 60B9CD3A083A7A9A
N: Skipping acquire of configured file 'main/binary-i386/Packages' as repository 'https://brave-browser-apt-release.s3.brave.com stable InRelease' doesn't support architecture 'i386'
W: Failed to fetch https://repo.yandex.ru/yandex-browser/deb/dists/stable/InRelease  The following signatures couldn't be verified because the public key is not available: NO_PUBKEY 60B9CD3A083A7A9A

