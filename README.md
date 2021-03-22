# kOS
A test operating system made for fun


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

# Stage 2 Bootloader
kOS has switched from using a stage 1 bootloader to using
GRUB + a stage 2 bootloader. This provides several
benefits, most notably easily booting off of multiple
types of media with no changes to kOS' bootloader, and
also multiboot support. To compile:

```
cd bootloader/stage2
make
```

# Compiling the kernel
Compiling kOS is pretty simple, all you need to do is
run  `make bootdisk` on the project root directory
and it will automatically build everything that's required
and create a bootable disk image that can be used on a
virtual machine or on an actual x86 computer. Just make
sure to have anything that `grub-mkrescue` needs to make
the image preinstalled (`xorriso` and `mtools`). You can
also directly test with `qemu-system-i386` by running
`make qemu`.