#### Best filesystem for /var/logs? Optimized for writes?

* Ext4 with journaling turned off? Has TRIM support. FITRIM (fstrim)?

* Ext2? TRIM support?

* xfs? 

is a journaling file-system, and it’s not possible to disable this feature (really?)

* f2fs? f2fs kernel module???. does it has journal?

mkfs.f2fs - `sudo apt-get install f2fs-tools`