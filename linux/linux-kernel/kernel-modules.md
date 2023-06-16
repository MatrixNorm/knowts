## why there are modules loaded not being used?

> I noticed that there are around 20 modules for either hardware that I don't have or they are not being used for anything, I checked /etc/modules-load.d/ and /etc/modprobe.d/ and both directory are empty, I wanted to see what was loading them

https://superuser.com/questions/1244202/why-there-are-modules-loaded-not-being-used

They are loaded because something used them at some time, possibly indirectly, for example during boot, but currently there are no applications using them.

It's safe to rmmod them (they'll just get reloaded when they will be needed), but it's not safe to blacklist them (because then whatever needed them won't work, nor will they work in the future if you decide you need to use that part of your hardware).

They take up very little of your memory, so there's no need to worry about them. Just leave everything as it is.

## What's the difference of `/etc/modules-load.d` and `/etc/modules`?

https://unix.stackexchange.com/questions/189670/whats-the-difference-of-etc-modules-load-d-and-etc-modules

## systemd: automate modprobe command at boot time

> Every time I reboot/restart my computer I need to run this command as root `modprobe rt2800usb`. How can I make it permanent?

https://unix.stackexchange.com/questions/71064/systemd-automate-modprobe-command-at-boot-time

On any distro using systemd you can automatically load the module via modules-load.d:

1. create the config file: `/etc/modules-load.d/rt2800usb.conf`

2. open it and edit like this (add the module name): `rt2800usb`

