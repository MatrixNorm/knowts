```
$ qemu-system-x86_64 -kernel vmlinuz \
     -initrd initrd \
     -cpu host -smp 2 -accel kvm -m 2G
```

Прямо в терминал:

```
$ qemu-system-x86_64 -kernel vmlinuz \
     -initrd initrd \
     -cpu host -smp 2 -accel kvm -m 2G \
     -nographic -append "console=ttyS0"
```