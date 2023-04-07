
## file's mode,ownership,timestamps



# Permissions

### Preserve File Permissions While Copying Files in Linux

There are certain things starting users are often unaware of, such as how to retain file permissions in Linux while copying them. Since **copied files are essentially new files, their permission depends on the umask of the current user**. This can lead to situations where copied files or folders have entirely different permissions than the source.

The user file-creation mode mask (umask) is use to determine the file permission for newly created files. It can be used to control the default file permission for new files.

```bash
> umask
002
```

**Subtracting umask from base permission would give you actual file permissions.** All the files will be created with 664 (666-002) permissions and dir with 775 (777-002) permissions.

## list all directories sizes in a current directory

```bash
> du -h --max-depth=1 | sort -hr

#with files as well
> du -ah --max-depth=1 | sort -hr
```