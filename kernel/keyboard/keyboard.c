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

#include "../irq/idt.h"
#include "keyboard.h"
#include "kbmap.h"
#include <stdio.h>
#include <stdint.h>
#include <kernel/terminalio.h>

uint8_t caps = 0;

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

        if (keycode == 0x3A) {
            caps = !caps;
            return;
        }

        if (keycode == 0x0E) {
            if (terminalGetCursorX() == 0 && terminalGetCursorY() > 0) {
                terminalSetCursorPosition(79, terminalGetCursorY() - 1);
            }
            else if (terminalGetCursorX() > 0){
                terminalSetCursorPosition(terminalGetCursorX() - 1, terminalGetCursorY());
            }

            putchar(' ');

            if (terminalGetCursorX() == 0 && terminalGetCursorY() > 0) {
                terminalSetCursorPosition(79, terminalGetCursorY() - 1);
            }
            else if (terminalGetCursorX() > 0){
                terminalSetCursorPosition(terminalGetCursorX() - 1, terminalGetCursorY());
            }

            return;
        }

        if (caps) {
            if (keyboardMap[(unsigned char) keycode] >= 'a' && keyboardMap[(unsigned char) keycode] <= 'z') {
                // Do some ASCII table magic
                putchar(keyboardMap[(unsigned char) keycode] - 32);
                return;
            }
        }

        putchar(keyboardMap[(unsigned char) keycode]);
    }
}
