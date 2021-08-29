# kOS
A test operating system made for fun

# ARCHIVAL NOTICE
This repository has been archived. It will stay here,
however development of kOS has moved over to this
organization: https://github.com/koperatingsystem

# Stage 1 Bootloader (Deprecated)
The bootloader is designed with floppy disks and x86 
BIOS systems in mind, and will attempt to read code 
from 2 sectors on a floppy disk starting from the 
second one. The loading message and pretty much 
anything else can be adjusted pretty easily as long 
as you read the comments in `bootloader.asm`. It is meant
to be built as a raw binary with `nasm` in 16-bit real mode.

It can then be burnt into media, or written to a disk
image. It must always be in the first sector of the
media/image.

This bootloader has been deprecated in favor of the below
GRUB + Stage 2 bootloader, and is kept only for research
purposes

# Stage 2 Bootloader
kOS has switched from using a stage 1 bootloader to using
GRUB + a stage 2 bootloader. This provides several
benefits, most notably easily booting off of multiple
types of media with no changes to kOS' bootloader, and
also multiboot support.

# Compiling the kernel
Compiling kOS is rather simple. All you need to do is run:
```shell
./build.sh # Build object files
./iso.sh # Generate bootable ISO 
```
You can also test this on `qemu-system-i386` by running
`./qemu.sh`
