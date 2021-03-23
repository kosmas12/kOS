#!/bin/sh

# clean.sh - Delete built kOS image

set -e
. ./config.sh

for PROJECT in $PROJECTS; do
  (cd $PROJECT && $MAKE clean)
done

rm -rf sysroot
rm -rf isodir
rm -rf kOS.iso
