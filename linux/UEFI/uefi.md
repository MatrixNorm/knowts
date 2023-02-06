# UEFI

PC motherboard has NVRAM (non-volatile random access memory) flash memory that stores UEFI's firmware code and durable state. Think about very limited OS living in NVRAM instead of SSD whos purpose is to configure hardware and set up booting of real OS. Boomers are thinking about BIOS right now.

## UEFI boot manager

This is UEFI application that deals with initial stage of booting. Its task is to find bootloader like GRUB and pass control to it.

## Bootloader

Bootloader if UEFI aplication that knows how to boot OS.