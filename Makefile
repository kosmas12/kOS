BUILD_DIR = build
BOOTLOADER = $(BUILD_DIR)/bootloader/bootloader.o
OS = $(BUILD_DIR)/os/kernel.o
DISK_DIR = build/diskimage/boot
DISK_IMG = $(DISK_DIR)/kOS.bin
DISK_ISO = $(DISK_DIR)/kOS.iso
CFLAGS += -T linker.ld -ffreestanding -O2 -nostdlib -lgcc

all: bootdisk

.PHONY: bootdisk bootloader os

bootloader:
	make -C bootloader/stage2

os:
	make -C os

bootdisk: bootloader os
	mkdir -p $(DISK_DIR)/grub
	cp grub.cfg $(DISK_DIR)/grub
	i686-elf-gcc -o $(DISK_IMG) $(CFLAGS) $(BOOTLOADER) $(OS)
	grub-mkrescue -o $(DISK_ISO) $(DISK_DIR)/..

qemu:
	qemu-system-i386 -cdrom $(DISK_ISO)

clean:
	rm -r $(DISK_DIR)/*
	make -C bootloader/stage2 clean
	make -C os clean
