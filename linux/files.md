
### Preserve File Permissions While Copying Files in Linux

There are certain things starting users are often unaware of, such as how to retain file permissions in Linux while copying them. Since **copied files are essentially new files, their permission depends on the umask of the current user**. This can lead to situations where copied files or folders have entirely different permissions than the source.

The user file-creation mode mask (umask) is use to determine the file permission for newly created files. It can be used to control the default file permission for new files.

```
> umask
002
```

**Subtracting umask from base permission would give you actual file permissions.** All the files will be created with 664 (666-002) permissions and dir with 775 (777-002) permissions.

### list all directories sizes in a current directory

```bash
# current dir
du -h --max-depth=1 | sort -hr
# with dir path
du -h --max-depth=1 /usr | sort -hr

######################
# with files as well #
######################

# current dir
du -ah --max-depth=1 | sort -hr
du -hs * | sort -hr | head -n 9
# with dir path
du -hs /var/* | sort -hr | head -n 9
```

`-x, --one-file-system` - skip directories on different file systems

```bash
# without -x flag du counts dirs on different file systems

$ sudo du -hs -t100M /* | sort -hr
303G	/mnt
11G	/home
7,9G	/usr
7,5G	/var
7,1G	/snap
892M	/opt
212M	/boot

$ findmnt 
TARGET                               SOURCE           FSTYPE
/                                    /dev/sdb2        ext4          
├─/snap/firefox/2710                 /dev/loop6       squashfs      
├─/snap/firefox/2667                 /dev/loop5       squashfs      
├─/home                              /dev/sdb3        ext4          
├─/boot/efi                          /dev/sdb1        vfat
└─/mnt/hdd
```

```bash
# still includes /home for some reason

$ sudo du -hsx -t100M /* | sort -hr
11G	/home
7,9G	/usr
7,5G	/var
892M	/opt
206M	/boot
```

