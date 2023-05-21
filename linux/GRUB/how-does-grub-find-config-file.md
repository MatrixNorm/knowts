
## How does the GRUB know where to look for the configuration file

* Load an embedded configuration file.
* Load a configuration file in the same directory as the GRUB binary.
* ??? Load a configuration file from a path decided at grub-mkimage (called by grub-install) execution time.

If I run strings /boot/efi/EFI/debian/grubx64.efi | tail -1 on my current workstation, it prints out the stored value: (,gpt2)/boot/grub, telling grubx64.efi to look for its configuration file in /boot/grub on GPT partition 2. The bit before the comma (the GRUB disk device name) gets filled in at runtime based on which disk the grubx64.efi image itself was loaded from.

https://stackoverflow.com/questions/35269943/how-does-the-grub-2-uefi-loader-know-where-to-look-for-the-configuration-file-o


```
$ grub-mkimage --config=FILE
```

grub-mkimage is the key central for grub to build all other stuffs when needed. For example, grub-[install,mkstandalone,mkrescue] all refer to the use of grub-mkimage, so once grub-mkimage is understood, everything looks easy to do.

https://unix.stackexchange.com/questions/253657/actual-usage-of-grub-mkimage-config