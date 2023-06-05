# WARNING: can't stat() fuse.gvfsd-fuse file system

```
$ sudo lsof
lsof: WARNING: can't stat() fuse.gvfsd-fuse file system /run/user/1000/gvfs
      Output information may be incomplete.
lsof: WARNING: can't stat() fuse.portal file system /run/user/1000/doc
      Output information may be incomplete.
```

https://unix.stackexchange.com/questions/171519/lsof-warning-cant-stat-fuse-gvfsd-fuse-file-system

```
$ sudo lsof | wc -l
lsof: WARNING: can't stat() fuse.gvfsd-fuse file system /run/user/1000/gvfs
      Output information may be incomplete.
lsof: WARNING: can't stat() fuse.portal file system /run/user/1000/doc
      Output information may be incomplete.
176742
```

```
$ lsof | wc -l
170126

$ lsof -u root | wc -l
885
```


# number of open files per user


XXX как сделать wc -l в стиле group by?

```
$ cat /etc/passwd | cut -d: -f1 | xargs -I{} lsof -u {}
```

```
$ cat /etc/passwd | cut -d: -f1 | xargs -I{} ./lsof_per_user.sh {}
```

