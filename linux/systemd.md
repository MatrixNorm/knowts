
### systemd unit

* item that is managed by systemd

* any resource sytemd knows how to operate on and manage

List available unit types

```
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

List units that systemd currently has in memory. This includes units that are either referenced directly or through a dependency, units that are pinned by applications programmatically, or units that were active in the past and have failed.

```
>systemctl list-units --type=service
# or
>systemctl --type=service
```

When listing units with list-units, also show inactive units and units which are following other units.

```
>systemctl list-units --type=service --all
# or
>systemctl --type=service --all
```

### get service status
```
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
   CGroup: ...
```

### a way to determine the systemd unit that caused the creation of a specific process

```
# find pid of process
> ps -ef | grep libvirtd
root      1242     1  0 06:57 ?        00:00:00 /usr/sbin/libvirtd

# and then
> systemctl status 1242
● libvirtd.service - Virtualization daemon
   Loaded: loaded (/lib/systemd/system/libvirtd.service; enabled; vendor preset: enabled)
   Active: active (running) since Mon 2022-10-10 06:57:53 MSK; 6h ago
   ...
```

### view service unit file

```
>systemctl cat libvirtd
```

### Unit search path

* Systemd searches for units working from most specific to most general configuration
  1. /etc/systemd/system : local configuration
  2. /run/systemd/system : runtime configuration
  3. /lib/systemd/system : distribution-wide configuration
<br/><br/>
* To override unit just place unit with the same name earlier in the sequence

* To disable unit replace it with empty file or link to /dev/null

### Service

* service is a unit that controls daemon
* name ends in .service
* has [Service] section

**Type of service**
___________________
* simple - (default) runs in background
* oneshot - run once
* forking

### Target

* Target is a Unit that lists dependencies on other Targets ???
* Name ends in .target

```
>systemctl cat multi-user.target

[Unit]
Description=Multi-User System
Documentation=man:systemd.special(7)
Requires=basic.target
Conflicts=rescue.service rescue.target
After=basic.target rescue.service rescue.target
AllowIsolate=yes
```

**The default target**
______________________

At boot systemd starts default.target. Usually a symbolic link to the target desired. 

```
>ls -l /lib/systemd/system/default.target

/lib/systemd/system/default.target -> graphical.target
```

### Sources

* https://www.youtube.com/watch?v=Ws6zR3rFXa4