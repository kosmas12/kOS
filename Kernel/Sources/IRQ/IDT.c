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

#include "IDT.h"

#include <stdint.h>

extern void Keyboard_Handler(void);

IDT_Entry idt[IDT_SIZE];

void IDT_Init(void)
{
    uint32_t keyboard_address = (uint32_t)Keyboard_Handler;

    idt[0x21].offset_low    = keyboard_address & 0xffff;
    idt[0x21].selector      = KERNEL_CODE_SEGMENT_OFFSET;
    idt[0x21].zero          = 0;
    idt[0x21].attributes    = INTERRUPT_GATE;
    idt[0x21].offset_high   = (keyboard_address & 0xffff0000) >> 16;

    // Begin initialization
    IDT_Write(PIC1_COMMAND_PORT, 0x11);
    IDT_Write(PIC2_COMMAND_PORT, 0x11);

    // Remap addresses
    // In x86 protected mode, we have to remap the PICs beyond 0x20 because
    // Intel have designated the first 32 interrupts as "reserved" for cpu exceptions
    IDT_Write(PIC1_DATA_PORT, 0x20);
    IDT_Write(PIC2_DATA_PORT, 0x28);

    // Setup cascading
    IDT_Write(PIC1_DATA_PORT, 0x00);
    IDT_Write(PIC2_DATA_PORT, 0x00);

    // TODO: be more specific about this
    // (Fetch?) Environment information
    IDT_Write(PIC1_DATA_PORT, 0x01);
    IDT_Write(PIC2_DATA_PORT, 0x01);

    // Mask the interrupts
    IDT_Write(PIC1_DATA_PORT, 0xff);
    IDT_Write(PIC2_DATA_PORT, 0xff);

    uint32_t idt_address    = (uint32_t)idt;
    uint32_t idt_pointer[2] =
    {
        (sizeof(IDT_Entry) * IDT_SIZE) + ((idt_address & 0xffff) << 16),
        idt_address >> 16
    };

    IDT_Load(idt_pointer);
}
