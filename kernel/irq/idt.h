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

#ifndef KOS_IDT_H
#define KOS_IDT_H

#define PIC1_COMMAND_PORT 0x20
#define PIC1_DATA_PORT 0x21
#define PIC2_COMMAND_PORT 0xA0
#define PIC2_DATA_PORT 0xA1

#define IDT_SIZE 256
#define INTERRUPT_GATE 0x8E
#define KERNEL_CODE_SEGMENT_OFFSET 0x08

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

extern char readPort(unsigned short port);
extern void writePort(unsigned short port, unsigned char data);
extern void loadIDT(unsigned long *idt_ptr);


struct IDTEntry {
        unsigned short int offsetLowerBits;
        unsigned short int selector;
        unsigned char zero;
        unsigned char typeAttr;
        unsigned short int offsetHigherBits;
};

void IDTInit(void);

#endif //KOS_IDT_H
