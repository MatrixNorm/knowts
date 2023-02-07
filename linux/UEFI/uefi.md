# UEFI

PC motherboard has NVRAM (non-volatile random access memory) flash memory that stores UEFI's firmware code and durable state. Firmware code is supplied by motherboard vendor. Think about it as a very limited OS whose files live in NVRAM instead of SSD. Purpose of "UEFI OS" is to configure hardware and set up booting of real OS. Boomers are thinking about BIOS right now.

## UEFI applications

- executable *.efi files that can be run by UEFI firmware
- resides on the ESP (EFI System Partition)
- bootloader like GRUB or rEFInd is UEFI app
- UEFI shell is also an app

## ESP - EFI System Partition

 ESP is a partition with FAT32 filesystem that holds efi-executables like bootloader or shell and configuration files. Sane beaviour is to have no more than one ESP per disk.

## UEFI boot manager

This is built-in UEFI application that deals with initial stage of booting. Its task is to find bootloader like GRUB and pass control to it. Boot manager maintains an ordered list of boot options in NVRAM. Typically boot option holds ESP's PARTUUID and path to booloader executable within this partition.

## Bootloader

Bootloader if UEFI aplication that knows how to boot OS.