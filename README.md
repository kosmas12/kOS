# kOS
A test operating system made for fun


# Bootloader
The bootloader is designed with floppy disks and x86 
BIOS systems in mind, and will attempt to read code 
from 2 sectors on a floppy disk starting from the 
second one. The loading message and pretty much 
anything else can be adjusted pretty easily as long 
as you read the comments in `bootloader.asm`.

To compile the bootloader:
```
cd bootloader
make
```
It can then be burnt into media, or written to a disk
image. It must always be in the first sector of the
media/image.