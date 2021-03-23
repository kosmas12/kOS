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

#ifndef KOS_TERMINALIO_H
#define KOS_TERMINALIO_H

#include <stddef.h>
#include <stdint.h>

/* Clear the terminal */
void terminalClearScreen();

/* Initialize the terminal */
void terminalInit(void);

/* Scroll up the terminal */
void terminalScrollUp();

/* Set the terminal color */
void terminalSetColor(uint8_t color);

/* Write character with color and position */
void terminalWriteVGA(char c, uint8_t color, size_t x, size_t y);

/* Write a character at the current cursor position in the terminal */
void terminalPutChar(char c);

/* Write as many bytes as we want from a char pointer, recommended to use terminalPrint instead */
void terminalPrintData(const char* data, size_t size);

/* Write a string to the terminal */
void terminalPrint(const char* data);

#endif //KOS_TERMINALIO_H
