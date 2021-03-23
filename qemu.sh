#!/bin/sh

# qemu.sh - Generate ISO and run QEMU with it

set -e
. ./iso.sh

qemu-system-$(./targettoarch.sh $HOST) -cdrom kOS.iso
