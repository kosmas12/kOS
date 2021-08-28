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

// TODO: clean this up (and fix it too)

#include "../IRQ/IDT.h"
#include "Keyboard.h"
#include "KeyboardMap.h"
#include <stdio.h>
#include <stdint.h>
#include <Kernel/TerminalIO.h>

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
