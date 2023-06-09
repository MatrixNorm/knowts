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

These files are for real. It could be reasonable to place them on separate partition.

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
