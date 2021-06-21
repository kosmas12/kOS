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

#include "idt.h"

extern void keyboardHandler(void);

struct IDTEntry IDT[IDT_SIZE];

void IDTInit(void) {
    unsigned long keyboard_address;
    unsigned long idt_address;
    unsigned long idt_ptr[2];

    /* populate IDT entry of keyboard's interrupt */
    keyboard_address = (unsigned long)keyboardHandler;
    IDT[0x21].offsetLowerBits = keyboard_address & 0xffff;
    IDT[0x21].selector = KERNEL_CODE_SEGMENT_OFFSET;
    IDT[0x21].zero = 0;
    IDT[0x21].typeAttr = INTERRUPT_GATE;
    IDT[0x21].offsetHigherBits = (keyboard_address & 0xffff0000) >> 16;

    /* ICW1 - begin initialization */
    writePort(PIC1_COMMAND_PORT, 0x11);
    writePort(PIC2_COMMAND_PORT, 0x11);

    /* ICW2 - remap offset address of IDT */
    /*
    * In x86 protected mode, we have to remap the PICs beyond 0x20 because
    * Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    */
    writePort(PIC1_DATA_PORT , 0x20);
    writePort(PIC2_DATA_PORT , 0x28);

    /* ICW3 - setup cascading */
    writePort(PIC1_DATA_PORT , 0x00);
    writePort(PIC2_DATA_PORT , 0x00);

    /* ICW4 - environment info */
    writePort(PIC1_DATA_PORT , 0x01);
    writePort(PIC2_DATA_PORT , 0x01);
    /* Initialization finished */

    /* mask interrupts */
    writePort(PIC1_DATA_PORT , 0xff);
    writePort(PIC2_DATA_PORT , 0xff);

    /* fill the IDT descriptor */
    idt_address = (unsigned long)IDT ;
    idt_ptr[0] = (sizeof (struct IDTEntry) * IDT_SIZE) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16 ;

    loadIDT(idt_ptr);
}
