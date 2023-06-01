### size of /var/log/journal

```
$ sudo du -hs /var/log/* | sort -hr | head -n 5
2,4G	/var/log/journal
1,8G	/var/log/syslog.1
1,2G	/var/log/syslog
20M	/var/log/syslog.4.gz
14M	/var/log/syslog.3.gz
```

```
$ sudo vim /etc/systemd/journald.conf

SystemMaxUse=500M

$ sudo systemctl restart systemd-journald.service

$ sudo du -sh /var/log/journal/
489M	/var/log/journal/
```

### Best filesystem for /var/logs? Optimized for writes?

* Ext4 with journaling turned off? Has TRIM support. FITRIM (fstrim)?

* Ext2? TRIM support?

* xfs? 

is a journaling file-system, and it’s not possible to disable this feature (really?)

* f2fs? f2fs kernel module???. does it has journal?

mkfs.f2fs - `sudo apt-get install f2fs-tools`