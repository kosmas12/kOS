// Copyright (c) 2021 The kOS authors.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software.
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

// TODO: clean this up

#include "IDT.h"

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
