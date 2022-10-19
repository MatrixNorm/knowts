
### systemd unit

> item that is managed by sytemd

> any resource sytemd knows how to operate on and manage

List available unit types:
```zsh
> systemctl -t help

service: ssh, web-server (apache, nginx)
socket
target: group of units
device
mount
automount
swap
timer
path
slice
scope
```

### list all loaded services

```zsh
> systemctl list-units --type=service
```
or

```zsh
> systemctl --type=service
```

### get service status
```bash
> systemctl status libvirtd 
● libvirtd.service - Virtualization daemon
   Loaded: loaded (/lib/systemd/system/libvirtd.service; enabled; vendor preset: enabled)
   # an enabled unit will start at boot
   # vendor preset tells you if the unit was enabled on installation
   Active: active (running) since Mon 2022-10-10 06:57:53 MSK; 1h 48min ago
     Docs: man:libvirtd(8)
           https://libvirt.org
 Main PID: 1242 (libvirtd)
    Tasks: 19 (limit: 32768)
   CGroup: /system.slice/libvirtd.service
           ├─1242 /usr/sbin/libvirtd
           ├─2847 /usr/sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/lib/libvirt/libvirt_l
           └─2850 /usr/sbin/dnsmasq --conf-file=/var/lib/libvirt/dnsmasq/default.conf --leasefile-ro --dhcp-script=/usr/lib/libvirt/libvirt_l
```

### a way to determine the systemd unit that caused the creation of a specific process

```bash
> ps -ef | grep libvirtd
root      1242     1  0 06:57 ?        00:00:00 /usr/sbin/libvirtd

> systemctl status 1242
● libvirtd.service - Virtualization daemon
   Loaded: loaded (/lib/systemd/system/libvirtd.service; enabled; vendor preset: enabled)
   Active: active (running) since Mon 2022-10-10 06:57:53 MSK; 6h ago
   ...
```


### view service unit file

```zsh
>  systemctl cat libvirtd
```

```
```