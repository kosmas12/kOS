#include <stdint.h>
#include "vga.h"
#include <string.h>
#include <kernel/terminalio.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t *terminalBuffer;

void terminalSetCursorPosition(size_t x, size_t y) {
    if (x > 0) {
        terminalColumn = x;
    }
    else {
        terminalColumn = 0;
    }
    if (y > 0) {
        terminalRow = y;
    }
    else {
        terminalRow = 0;
    }
}

size_t terminalGetCursorX() {
    return terminalColumn;
}

size_t terminalGetCursorY() {
    return terminalRow;
}

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
