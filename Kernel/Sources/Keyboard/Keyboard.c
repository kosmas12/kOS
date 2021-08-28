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

#include "Keyboard.h"
#include "Map.h"

#include <Kernel/TerminalIO.h>

#include "../IRQ/IDT.h"

#include <stdio.h>
#include <stdint.h>

static uint8_t caps = 0;

void Keyboard_Init(void)
{
    IDT_Write(PIC1_DATA_PORT, 0xFD); // Enable IRQ1 *ONLY* (required for keyboard)
}

void Keyboard_Handler(void)
{
    IDT_Write(PIC1_COMMAND_PORT, 0x20);

    uint8_t status = IDT_Read(KEYBOARD_COMMAND_PORT);
    if (status & 0x01) // Lowest bit of status will be set if buffer is not empty
    {
        int8_t keycode = IDT_Read(KEYBOARD_DATA_PORT);
        if (keycode < 0) return;

        if (keycode == 0x3A)
        {
            caps = !caps;
            return;
        }

        if (keycode == 0x0E)
        {
            if (Terminal_Get_Cursor_X() == 0 && Terminal_Get_Cursor_Y() > 0) Terminal_Set_Cursor_Position(79, Terminal_Get_Cursor_Y() - 1);
            else if (Terminal_Get_Cursor_X() > 0) Terminal_Set_Cursor_Position(Terminal_Get_Cursor_X() - 1, Terminal_Get_Cursor_Y());

            putchar(' ');

            if (Terminal_Get_Cursor_X() == 0 && Terminal_Get_Cursor_Y() > 0) Terminal_Set_Cursor_Position(79, Terminal_Get_Cursor_Y() - 1);
            else if (Terminal_Get_Cursor_X() > 0) Terminal_Set_Cursor_Position(Terminal_Get_Cursor_X() - 1, Terminal_Get_Cursor_Y());

            return;
        }

        if (caps && Keyboard_Map[(uint8_t)keycode] >= 'a' && Keyboard_Map[(uint8_t)keycode] <= 'z')
        {
            putchar(Keyboard_Map[(uint8_t)keycode] - 32);
            return;
        }

        putchar(Keyboard_Map[(uint8_t)keycode]);
    }

    __asm__("iret");
}
