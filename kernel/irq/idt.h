//
// Created by kosmas on 22/4/21.
//

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

struct IDTEntry {
        unsigned short int offsetLowerBits;
        unsigned short int selector;
        unsigned char zero;
        unsigned char typeAttr;
        unsigned short int offsetHigherBits;
};

void IDTInit(void);

#endif //KOS_IDT_H
