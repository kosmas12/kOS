#!/bin/sh

# iso.sh - Generate ISO

set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/kOS.bin isodir/boot/kOS.bin
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "kOS" {
	multiboot /boot/kOS.bin
}
EOF
grub-mkrescue -o kOS.iso isodir
