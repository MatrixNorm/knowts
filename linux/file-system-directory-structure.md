
* /home - users' home directories (recommended separate partition)
* /root - root user's home directory

* /boot - boor loader, kernel files (usually separate partition)
* /etc - text config files
* /opt - 3rd party apps
* /media - removable media mount location
* /mnt
* /tmp (can be separate partition)

* /sbin - essential system binaries
* /bin - essential binaries that need to be available in single-user mode
* /lib - libraries for /bin and /sbin
  - self-contained libraries

* /usr - stuff not needed for single user mode
* /usr/bin - most command binaries
* /usr/lib - libraries for /usr/bin
* /usr/local - ???
* /usr/local/bin - ???

* /var - files that often change: logs, emails (recommended separate partition)
* /var/tmp - temp files not deleted on reboot

VIRTUAL FILESYSTEMS

* /dev - hardware represented as files
* /proc - generated on the fly, process & kernel information as files
* /sys - info about devices, drivers, kernel