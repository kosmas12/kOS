/*
kOS - An operating system made for fun
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

#ifndef KOS_VGATERMINALIO_H
#define KOS_VGATERMINALIO_H

enum VGAColors {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14,
    VGA_COLOR_WHITE = 15,
};

/* Produce a VGA color */
static inline uint8_t VGAColor(enum VGAColors fg, enum VGAColors bg) {
    return fg | bg << 4;
}

/* Produce a letter with foreground and background colors */
static inline uint16_t VGAEntry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t *terminalBuffer;

/* Clear the terminal */
void terminalClearScreen() {
    /* Fill entire screen with spaces */
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminalBuffer[index] = VGAEntry(' ', terminalColor);
        }
    }
}

/* Initialize the terminal */
void terminalInit(void) {
    terminalRow = 0;
    terminalColumn = 0;
    terminalColor = VGAColor(VGA_COLOR_WHITE, VGA_COLOR_RED);
    terminalBuffer = (uint16_t *) 0xB8000;
    terminalClearScreen();
}

/* Scroll up the terminal */
void terminalScrollUp() {
    /* Each line has the characters of the next one */
    for(size_t i = 0; i < (VGA_WIDTH*VGA_HEIGHT-VGA_WIDTH); i++) {
        terminalBuffer[i] = terminalBuffer[i+VGA_WIDTH];
    }

    /* Fill last line with spaces */
    for(size_t i = 0; i < VGA_WIDTH; i++) {
        terminalBuffer[(VGA_HEIGHT - 1) * VGA_WIDTH + i] = VGAEntry(' ', terminalColor);
    }
}

/* Set the terminal color */
void terminalSetColor(uint8_t color) {
    terminalColor = color;
}

/* Write character with color and position */
void terminalWriteVGA(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminalBuffer[index] = VGAEntry(c, color);
}

/* Write a character at the current cursor position in the terminal */
void terminalPutChar(char c) {
    /* If we have reached the end of the current line or there's a newline,
       go to start of next line, scroll up if needed */

    if (terminalColumn == VGA_WIDTH || c == '\n') {
        terminalColumn = 0;
        if (terminalRow == VGA_HEIGHT - 1) {
            terminalScrollUp();
        }
        else {
            terminalRow++;
        }
    }
    if (c == '\n') return; // Nothing else has to be done if newline
    terminalWriteVGA(c, terminalColor, terminalColumn++, terminalRow);
}

/* Write as many bytes as we want from a char pointer, recommended to use terminalPrint instead */
void terminalPrintData(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminalPutChar(data[i]);
    }
}

/* Write a string to the terminal */
void terminalPrint(const char* data) {
    terminalPrintData(data, strlen(data));
}

#endif //KOS_VGATERMINALIO_H
