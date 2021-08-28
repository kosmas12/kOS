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

#include "VGA.h"

#include <Kernel/TerminalIO.h>

#include <stdint.h>
#include <string.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

static size_t       terminal_row    = 0;
static size_t       terminal_column = 0;
static uint8_t      terminal_color  = 0;
static uint16_t*    terminal_buffer = { NULL };

void terminalSetCursorPosition(size_t x, size_t y)
{
    terminal_column  = x;
    terminal_row     = y;
}

size_t terminalGetCursorX()
{
    return terminal_column;
}

size_t terminalGetCursorY()
{
    return terminal_row;
}

void terminalClearScreen()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = VGA_TEXT(' ', terminal_color);
        }
    }
}

void terminalInit(void)
{
    terminal_row     = 0;
    terminal_column  = 0;
    terminal_color   = VGA_COLOR(VGA_Color_White, VGA_Color_Red);
    terminal_buffer  = (uint16_t*)0xB8000;

    terminalClearScreen();
}

void terminalScrollUp()
{
    for (size_t i = 0; i < (VGA_WIDTH*VGA_HEIGHT-VGA_WIDTH); i++) terminal_buffer[i] = terminal_buffer[i+VGA_WIDTH];

    for (size_t i = 0; i < VGA_WIDTH; i++) terminal_buffer[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = VGA_TEXT(' ', terminal_color);
}

void terminalSetColor(uint8_t color)
{
    terminal_color = color;
}

void terminalWriteVGA(char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = VGA_TEXT(c, color);
}

void terminalPutChar(char c)
{
    if (terminal_column == VGA_WIDTH || c == '\n')
    {
        terminal_column = 0;
        if (terminal_row == VGA_HEIGHT - 1) terminalScrollUp();
        else terminal_row++;
    }

    if (c == '\n') return;

    terminalWriteVGA(c, terminal_color, terminal_column++, terminal_row);
}

void terminalPrintData(const char* data, size_t size)
{
    for (size_t i = 0; i < size; i++) terminalPutChar(data[i]);
}

void terminalPrint(const char* data)
{
    terminalPrintData(data, strlen(data));
}
