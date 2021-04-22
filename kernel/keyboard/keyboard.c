//
// Created by kosmas on 21/4/21.
//

#include "../irq/idt.h"
#include "keyboard.h"
#include "kbmap.h"
#include <stdio.h>

void kbInit(void) {
    // Enable IRQ1 *ONLY* (required for keyboard)
    writePort(PIC1_DATA_PORT, 0xFD);
}

void keyboardHandlerMain(void) {
    unsigned char status;
    char keycode;

    /* write EOI */
    writePort(PIC1_COMMAND_PORT, 0x20);

    status = readPort(KEYBOARD_COMMAND_PORT);
    /* Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = readPort(KEYBOARD_DATA_PORT);
        if(keycode < 0) {
            return;
        }
        putchar(keyboardMap[keycode]);
    }
}