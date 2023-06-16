### what are snaps exactly?

apt-get + docker ~ snap: https://www.youtube.com/watch?v=0z3yusiCOCk

Snaps are self-contained applications, isolated from the underlying operating systems by several layers of confinement.

### do snaps take huge amount of disk space?

```
$ sudo du -sh /snap/
7,1G    /snap/

$ sudo du -hs /snap/firefox/*
634M	/snap/firefox/2667
636M	/snap/firefox/2710
0	/snap/firefox/current
```

don't worry this is virtual file systems. /snap dir takes no real space on disk

```
$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
loop5    7:5    0   242M  1 loop /snap/firefox/2667
loop6    7:6    0 242,9M  1 loop /snap/firefox/2710
```

these are mounted .snap files

```
$ mount | grep snap
/var/lib/snapd/snaps/firefox_2710.snap on /snap/firefox/2710 type squashfs ...
/var/lib/snapd/snaps/firefox_2667.snap on /snap/firefox/2667 type squashfs ...

```

These files are for real. It could be reasonable to place /var/lib/snapd/ on separate partition.

```
$ ll /var/lib/snapd/snaps/
243M мая 13 10:30 firefox_2667.snap
243M мая 24 14:17 firefox_2710.snap

$ sudo du -sh /var/lib/snapd/* -t10M
535M	/var/lib/snapd/cache
811M	/var/lib/snapd/seed
2,6G	/var/lib/snapd/snaps
```

### old versions of snaps

```
$ snap list --all | awk '/disabled/{print $1, $3}' |
> while read snapname revision; do
> echo "$snapname,$revision"
> done

core20,1879
core22,634
firefox,2667
gnome-3-38-2004,137
gnome-42-2204,102
snap-store,638
snapd,19122
snapd-desktop-integration,57
```

### where can an app inside a snap write its config, data and other files?

https://askubuntu.com/questions/762354/where-can-ubuntu-snaps-write-data

* SNAP COMMON, `/var/snap/firefox/common` – Reflected in the SNAP_COMMON environment variable, this directory is owned and writable by root, and it used to store data that is common across multiple revisions of the snap

* SNAP DATA, `/var/snap/firefox/2710` – Reflected in the SNAP_DATA environment variable, it is also used to store data, mostly information utilized by background application and services, for logging, and other tasks that require persistence between snap launches. This directory is backed up and then restored when performing a snap update (refresh) or revert operation. In contrast, SNAP_COMMON is not.

* SNAP_USER_COMMON, `/home/me/snap/firefox/common` – This directory maps to user data that is common across revisions of a snap. A typical path would be something like: /home/”username”/snap/”snap name”/common. It is not backed up or restored on snap operations.

* SNAP_USER_DATA, `/home/me/snap/firefox/2710` – This directory will contain any user data that the snap writes to its own home. A typical path would be: /home/”username”/snap/”snap name”/”revision”.


### what does it mean by this?

```
$ which firefox
/snap/bin/firefox

$ ll /snap/bin/
lrwxrwxrwx  1 root root   13 мая 24 14:17 firefox -> /usr/bin/snap
lrwxrwxrwx  1 root root   13 мая 24 14:17 firefox.geckodriver -> /usr/bin/snap
lrwxrwxrwx  1 root root   13 апр 29 09:41 snap-store -> /usr/bin/snap
```

### configure snaps autoupdate