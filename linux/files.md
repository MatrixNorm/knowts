
## file's mode,ownership,timestamps

## Preserve File Permissions While Copying Files in Linux

File permissions are an integral part of the Unix specification. However, there are certain things starting users are often unaware of, such as how to retain file permissions in Linux while copying them.

Since **copied files are essentially new files, their permission depends on the umask of the current user**. This can lead to situations where copied files or folders have entirely different permissions than the source.

## user's umask

The user file-creation mode mask (umask) is use to determine the file permission for newly created files. It can be used to control the default file permission for new files.

$umask
>002

**Subtracting umask from base permission would give you actual file permissions.** All the files will be created with 664 (666-002) permissions and dir with 775 (777-002) permissions.