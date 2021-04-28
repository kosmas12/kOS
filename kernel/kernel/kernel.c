/*
This file is part of kOS - An operating system made for fun
Copyright (C) 2021 Kosmas Raptis

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#ifdef __linux__
#error "Cross-compilation requried to produce kernel"
#endif

#ifndef __i386__
#error "Kernel only supports 32-bit"
#endif

#include <stdio.h>
#include "gdt/gdt.h"
#include "../irq/idt.h"
#include "../keyboard/keyboard.h"
#include <kernel/terminalio.h>

// Kernel entry point. Ignore any warnings saying this isn't used, it's called by the bootloader
void kernel_main(void) {
    terminalInit();

    GDTInstall();

    IDTInit();
    kbInit();

    // With our inits above, we can respond to user input despite the empty infinite loop
    while (1);

}