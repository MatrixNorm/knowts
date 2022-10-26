
### Get all groups an user belongs to
```shell
>id user_name
```

To check which users are in the kvm group, use
>grep kvm /etc/group
kvm:x:135:

>whoami

me
>sudo adduser me kvm

>grep kvm /etc/group

kvm:x:135:me

### What is `/etc/group-` file?

It is a backup file. That is version of the file before the last change.