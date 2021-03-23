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

#ifndef KOS_TIMING_H
#define KOS_TIMING_H

/* TODO: This is highly dependent on CPU speed and compiler optimizations, add better implementation */
void delay(int t) {
    volatile int i;
    volatile int j;

    for(i=0; i<t; i++) {
        for (j = 0; j < 300000; j++) {
            __asm__("NOP");
        }
    }
}

#endif //KOS_TIMING_H
